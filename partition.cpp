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
 * Partition (copy)
 */
Partition::Partition (const Partition& p) :
	Container (p),
	id (p.id)
{
	//std::cout << __PRETTY_FUNCTION__ << " : " << p.id << std::endl;
}

/**
 * operator=
 */
Partition&
Partition::operator= (const Partition& p)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Container::operator= (p);

	id = p.id;

	return *this;
}


/**
 * create (static)
 */
PPtr
Partition::create (void)
{
	Partition* p = new Partition();

	p->name = "partition";

	PPtr pp (p);

	p->me = pp;

	return pp;
}


#if 0
/**
 * backup
 */
CPtr
Partition::backup (void)
{
	//Container::backup();
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	CPtr old (new Partition (*this));
	return old;
}

/**
 * restore
 */
void
Partition::restore (void)
{
	Container::restore();
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}

#endif

/**
 * clone
 */
Partition*
Partition::clone (void)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new Partition (*this);
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


