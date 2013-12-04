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

#include "container.h"
#include "visitor.h"

static int base_seqnum = 1000;

/**
 * Container (default)
 */
Container::Container (void)
{
	seqnum = base_seqnum;
	base_seqnum += 1000;

	name = "container";
}


/**
 * visit_children
 */
bool
Container::visit_children (Visitor& v)
{
	if (!v.visit_enter (*this))
		return false;

	for (auto c : children) {
		if (!c->accept_visitor (v))
			return false;
	}

	if (!v.visit_leave())
		return false;

	return true;
}

/**
 * accept_visitor
 */
bool
Container::accept_visitor (Visitor& v)
{
	if (!v.visit (*this))
		return false;
	return visit_children (v);
}


/**
 * get_size
 */
int
Container::get_size (void) const
{
	return size;
}

/**
 * set_size
 */
int
Container::set_size (int value)
{
	int old = size;
	size = value;
	changed();
	return old;
}


/**
 * add_child
 */
int
Container::add_child (CPtr child)
{
	children.push_back (child);
	changed();
	return children.size();
}

/**
 * remove_child
 */
void
Container::remove_child (size_t index)
{
	if (index >= children.size())
		return;

	children.erase (children.begin()+index);
	changed();
}


/**
 * get_children
 */
const std::vector<CPtr>&
Container::get_children (void)
{
	return children;
}


/**
 * get_seqnum
 */
int
Container::get_seqnum (void)
{
	return seqnum;
}


/**
 * changed
 */
void
Container::changed (void)
{
	if (seqnum < 1)
		return;

	seqnum++;
}

