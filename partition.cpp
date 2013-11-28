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
#include "main.h"

/**
 * Partition (default)
 */
Partition::Partition (void) :
	id(0)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	name = "partition";
}

/**
 * Partition (copy)
 */
Partition::Partition (const Partition &p) :
	Container (p),
	id (p.id)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}

/**
 * ~Partition
 */
Partition::~Partition()
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}


/**
 * create (static)
 */
PPtr
Partition::create (void)
{
	PPtr p (new Partition);

	pool.push_back(p);

	cp++;
	return p;
}


/**
 * backup
 */
CPtr
Partition::backup (void)
{
	//Container::backup();
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	CPtr old (new Partition (*this));
	cp++;
	return old;
}

/**
 * restore
 */
void
Partition::restore (void)
{
	Container::restore();
	std::cout << __PRETTY_FUNCTION__ << std::endl;
}


/**
 * get_id
 */
int
Partition::get_id (void)
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


