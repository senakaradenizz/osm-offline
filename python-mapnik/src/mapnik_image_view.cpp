/*****************************************************************************
 *
 * This file is part of Mapnik (c++ mapping toolkit)
 *
 * Copyright (C) 2015 Artem Pavlenko, Jean-Francois Doyon
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

#include <mapnik/config.hpp>
#include "boost_std_shared_shim.hpp"

#pragma GCC diagnostic push
#include <mapnik/warning_ignore.hpp>
#include <boost/python.hpp>
#include <boost/python/module.hpp>
#include <boost/python/def.hpp>
#pragma GCC diagnostic pop

// mapnik
#include <mapnik/image.hpp>
#include <mapnik/image_view.hpp>
#include <mapnik/image_view_any.hpp>
#include <mapnik/image_util.hpp>
#include <mapnik/palette.hpp>
#include <sstream>

using mapnik::image_view_any;
using mapnik::save_to_file;

// output 'raw' pixels
PyObject* view_tostring1(image_view_any const& view)
{
    std::ostringstream ss(std::ios::out|std::ios::binary);
    mapnik::view_to_stream(view, ss);
    return
#if PY_VERSION_HEX >= 0x03000000
        ::PyBytes_FromStringAndSize
#else
        ::PyString_FromStringAndSize
#endif
        ((const char*)ss.str().c_str(),ss.str().size());
}

// encode (png,jpeg)
PyObject* view_tostring2(image_view_any const & view, std::string const& format)
{
    std::string s = save_to_string(view, format);
    return
#if PY_VERSION_HEX >= 0x03000000
        ::PyBytes_FromStringAndSize
#else
        ::PyString_FromStringAndSize
#endif
        (s.data(),s.size());
}

PyObject* view_tostring3(image_view_any const & view, std::string const& format, mapnik::rgba_palette const& pal)
{
    std::string s = save_to_string(view, format, pal);
    return
#if PY_VERSION_HEX >= 0x03000000
        ::PyBytes_FromStringAndSize
#else
        ::PyString_FromStringAndSize
#endif
        (s.data(),s.size());
}

bool is_solid(image_view_any const& view)
{
    return mapnik::is_solid(view);
}

void save_view1(image_view_any const& view,
                std::string const& filename)
{
    save_to_file(view,filename);
}

void save_view2(image_view_any const& view,
                std::string const& filename,
                std::string const& type)
{
    save_to_file(view,filename,type);
}

void save_view3(image_view_any const& view,
                std::string const& filename,
                std::string const& type,
                mapnik::rgba_palette const& pal)
{
    save_to_file(view,filename,type,pal);
}


void export_image_view()
{
    using namespace boost::python;
    class_<image_view_any>("ImageView","A view into an image.",no_init)
        .def("width",&image_view_any::width)
        .def("height",&image_view_any::height)
        .def("is_solid",&is_solid)
        .def("tostring",&view_tostring1)
        .def("tostring",&view_tostring2)
        .def("tostring",&view_tostring3)
        .def("save",&save_view1)
        .def("save",&save_view2)
        .def("save",&save_view3)
        ;
}
