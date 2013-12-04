/* Copyright (c) 2013 Richard Russon (FlatCap)
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later
 * version.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License for
 * more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#include <iostream>

#include "filesystem.h"
#include "visitor.h"

/**
 * Filesystem (default)
 */
Filesystem::Filesystem (void)
{
	name = "filesystem";
}


/**
 * accept_visitor
 */
bool
Filesystem::accept_visitor (Visitor& v)
{
	if (!v.visit (*this))
		return false;
	return visit_children (v);
}


/**
 * get_label
 */
std::string
Filesystem::get_label (void) const
{
	return label;
}

/**
 * set_label
 */
std::string
Filesystem::set_label (const std::string& value)
{
	std::string old = label;
	label = value;
	changed();
	return old;
}


