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

#include "partition.h"
#include "visitor.h"

/**
 * Partition (default)
 */
Partition::Partition (void)
{
	name = "partition";
}


/**
 * create
 */
PPtr
Partition::create (void)
{
	Partition *p = new Partition();

	PPtr pp (p);

	p->me = pp;

	return pp;
}

/**
 * accept
 */
bool
Partition::accept (Visitor& v)
{
	PPtr p = std::dynamic_pointer_cast<Partition> (me.lock());
	if (!v.visit (p))
		return false;
	return visit_children (v);
}


/**
 * get_id
 */
int
Partition::get_id (void) const
{
	return id;
}

/**
 * set_id
 */
int
Partition::set_id (int value)
{
	int old = id;
	id = value;
	changed();
	return old;
}


