#ifndef OSMIUM_HANDLER_CHECK_ORDER_HPP
#define OSMIUM_HANDLER_CHECK_ORDER_HPP

/*

This file is part of Osmium (https://osmcode.org/libosmium).

Copyright 2013-2020 Jochen Topf <jochen@topf.org> and others (see README).

Boost Software License - Version 1.0 - August 17th, 2003

Permission is hereby granted, free of charge, to any person or organization
obtaining a copy of the software and accompanying documentation covered by
this license (the "Software") to use, reproduce, display, distribute,
execute, and transmit the Software, and to prepare derivative works of the
Software, and to permit third-parties to whom the Software is furnished to
do so, all subject to the following:

The copyright notices in the Software and this entire statement, including
the above license grant, this restriction and the following disclaimer,
must be included in all copies of the Software, in whole or in part, and
all derivative works of the Software, unless such copies or derivative
works are solely in the form of machine-executable object code generated by
a source language processor.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
DEALINGS IN THE SOFTWARE.

*/

#include <osmium/handler.hpp>
#include <osmium/osm/node.hpp>
#include <osmium/osm/object_comparisons.hpp>
#include <osmium/osm/relation.hpp>
#include <osmium/osm/types.hpp>
#include <osmium/osm/way.hpp>

#include <limits>
#include <stdexcept>
#include <string>

namespace osmium {

    /**
     * Exception thrown when a method in the CheckOrder class detects
     * that the input is out of order.
     */
    struct out_of_order_error : public std::runtime_error {

        osmium::object_id_type object_id;

        explicit out_of_order_error(const std::string& what, osmium::object_id_type id) :
            std::runtime_error(what),
            object_id(id) {
        }

        explicit out_of_order_error(const char* what, osmium::object_id_type id) :
            std::runtime_error(what),
            object_id(id) {
        }

    }; // struct out_of_order_error

    namespace handler {

        /**
         * Handler that can be used to check that an OSM file is ordered
         * correctly. Ordered in this case refers to the usual order in OSM
         * files: First nodes in the order of their IDs, then ways in the order
         * of their IDs, then relations in the order or their IDs. Negative
         * IDs are ordered first then positive IDs, both ordered by absolute
         * value.
         *
         * IDs have to be unique for each type. This check will fail for
         * history files.
         *
         * To use this, add a CheckOrder member variable to your handler and
         * call the node(), way(), and relation() methods from your node(),
         * way(), and relations() handlers, respectively. An out_of_order_error
         * exception will be thrown when the input is not in order.
         */
        class CheckOrder : public osmium::handler::Handler {

            osmium::object_id_type m_max_node_id     = std::numeric_limits<osmium::object_id_type>::min();
            osmium::object_id_type m_max_way_id      = std::numeric_limits<osmium::object_id_type>::min();
            osmium::object_id_type m_max_relation_id = std::numeric_limits<osmium::object_id_type>::min();

        public:

            void node(const osmium::Node& node) {
                if (m_max_way_id > std::numeric_limits<osmium::object_id_type>::min()) {
                    throw out_of_order_error{"Found a node after a way.", node.id()};
                }
                if (m_max_relation_id > std::numeric_limits<osmium::object_id_type>::min()) {
                    throw out_of_order_error{"Found a node after a relation.", node.id()};
                }

                if (m_max_node_id == node.id()) {
                    throw out_of_order_error{"Node ID twice in input. Maybe you are using a history or change file?", node.id()};
                }
                if (id_order{}(node.id(), m_max_node_id)) {
                    throw out_of_order_error{"Node IDs out of order.", node.id()};
                }
                m_max_node_id = node.id();
            }

            void way(const osmium::Way& way) {
                if (m_max_relation_id > std::numeric_limits<osmium::object_id_type>::min()) {
                    throw out_of_order_error{"Found a way after a relation.", way.id()};
                }

                if (m_max_way_id == way.id()) {
                    throw out_of_order_error{"Way ID twice in input. Maybe you are using a history or change file?", way.id()};
                }
                if (id_order{}(way.id(), m_max_way_id)) {
                    throw out_of_order_error{"Way IDs out of order.", way.id()};
                }
                m_max_way_id = way.id();
            }

            void relation(const osmium::Relation& relation) {
                if (m_max_relation_id == relation.id()) {
                    throw out_of_order_error{"Relation ID twice in input. Maybe you are using a history or change file?", relation.id()};
                }
                if (id_order{}(relation.id(), m_max_relation_id)) {
                    throw out_of_order_error{"Relation IDs out of order.", relation.id()};
                }
                m_max_relation_id = relation.id();
            }

            osmium::object_id_type max_node_id() const noexcept {
                return m_max_node_id;
            }

            osmium::object_id_type max_way_id() const noexcept {
                return m_max_way_id;
            }

            osmium::object_id_type max_relation_id() const noexcept {
                return m_max_relation_id;
            }

        }; // class CheckOrder

    } // namespace handler

} // namespace osmium

#endif // OSMIUM_HANDLER_CHECK_ORDER_HPP
