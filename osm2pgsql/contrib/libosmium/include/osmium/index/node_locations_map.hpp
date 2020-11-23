#ifndef OSMIUM_INDEX_NODE_LOCATIONS_MAP_HPP
#define OSMIUM_INDEX_NODE_LOCATIONS_MAP_HPP

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

#include <osmium/index/map.hpp> // IWYU pragma: keep
#include <osmium/osm/location.hpp>
#include <osmium/osm/types.hpp>

#define OSMIUM_WANT_NODE_LOCATION_MAPS

#ifdef OSMIUM_HAS_INDEX_MAP_DENSE_FILE_ARRAY
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::DenseFileArray, dense_file_array)
#endif

#ifdef OSMIUM_HAS_INDEX_MAP_DENSE_MEM_ARRAY
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::DenseMemArray, dense_mem_array)
#endif

#ifdef OSMIUM_HAS_INDEX_MAP_DENSE_MMAP_ARRAY
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::DenseMmapArray, dense_mmap_array)
#endif

#ifdef OSMIUM_HAS_INDEX_MAP_SPARSE_FILE_ARRAY
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::SparseFileArray, sparse_file_array)
#endif

#ifdef OSMIUM_HAS_INDEX_MAP_SPARSE_MEM_ARRAY
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::SparseMemArray, sparse_mem_array)
#endif

#ifdef OSMIUM_HAS_INDEX_MAP_SPARSE_MEM_MAP
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::SparseMemMap, sparse_mem_map)
#endif

#ifdef OSMIUM_HAS_INDEX_MAP_SPARSE_MEM_TABLE
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::SparseMemTable, sparse_mem_table)
#endif

#ifdef OSMIUM_HAS_INDEX_MAP_SPARSE_MMAP_ARRAY
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::SparseMmapArray, sparse_mmap_array)
#endif

#ifdef OSMIUM_HAS_INDEX_MAP_FLEX_MEM
    REGISTER_MAP(osmium::unsigned_object_id_type, osmium::Location, osmium::index::map::FlexMem, flex_mem)
#endif

#endif // OSMIUM_INDEX_NODE_LOCATIONS_MAP_HPP
