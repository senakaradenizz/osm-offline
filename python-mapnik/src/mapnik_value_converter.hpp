/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2015 Artem Pavlenko
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 *
 *****************************************************************************/
#ifndef MAPNIK_PYTHON_BINDING_VALUE_CONVERTER_INCLUDED
#define MAPNIK_PYTHON_BINDING_VALUE_CONVERTER_INCLUDED

// mapnik
#include <mapnik/value.hpp>
#include <mapnik/util/variant.hpp>

#pragma GCC diagnostic push
#include <mapnik/warning_ignore.hpp>
#include <boost/python.hpp>
#include <boost/implicit_cast.hpp>
#pragma GCC diagnostic pop

namespace boost { namespace python {

    struct value_converter
    {
        PyObject * operator() (mapnik::value_integer val) const
        {
            return ::PyLong_FromLongLong(val);
        }

        PyObject * operator() (mapnik::value_double val) const
        {
            return ::PyFloat_FromDouble(val);
        }

        PyObject * operator() (mapnik::value_bool val) const
        {
            return ::PyBool_FromLong(val);
        }

        PyObject * operator() (std::string const& s) const
        {
            return ::PyUnicode_DecodeUTF8(s.c_str(),implicit_cast<ssize_t>(s.length()),0);
        }

        PyObject * operator() (mapnik::value_unicode_string const& s) const
        {
            const char* data = reinterpret_cast<const char*>(s.getBuffer());
            Py_ssize_t size = implicit_cast<Py_ssize_t>(s.length() * sizeof(s[0]));
            return ::PyUnicode_DecodeUTF16(data, size, nullptr, nullptr);
        }

        PyObject * operator() (mapnik::value_null const& /*s*/) const
        {
            Py_RETURN_NONE;
        }
    };


    struct mapnik_value_to_python
    {
        static PyObject* convert(mapnik::value const& v)
        {
            return mapnik::util::apply_visitor(value_converter(),v);
        }

    };

    struct mapnik_param_to_python
    {
        static PyObject* convert(mapnik::value_holder const& v)
        {
            return mapnik::util::apply_visitor(value_converter(),v);
        }
    };


}}

#endif // MAPNIK_PYTHON_BINDING_VALUE_CONVERTER_INCLUDED
