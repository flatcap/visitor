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

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <new>
#include <sstream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

#include "pointers.h"

#include "container.h"
#include "disk.h"

/**
 * move_c
 */
void
move_c (void)
{
	CPtr c1  = Container::create();
	CPtr c2  = Container::create();

	c1->set_size (42);
	c2->set_size (99);

	CPtr c3 (c1);
	CPtr c4 (c2);

	std::cout << c1->get_size() << ", " << c2->get_size() << std::endl;
	swap (*c3.get(), *c4.get());
	std::cout << c1->get_size() << ", " << c2->get_size() << std::endl;
	swap (*c3.get(), *c4.get());
	std::cout << c1->get_size() << ", " << c2->get_size() << std::endl;
	std::cout << std::endl;
}

/**
 * move_d
 */
void
move_d (void)
{
	DPtr d1  = Disk::create();
	DPtr d2  = Disk::create();

	d1->set_size (42);
	d1->set_device ("apple");
	d2->set_size (99);
	d2->set_device ("banana");

	DPtr d3 (d1);
	DPtr d4 (d2);

	std::cout << d1->get_size() << "/" << d1->get_device() << ", " << d2->get_size() << "/" << d2->get_device() << std::endl;
	swap (*d3.get(), *d4.get());
	std::cout << d1->get_size() << "/" << d1->get_device() << ", " << d2->get_size() << "/" << d2->get_device() << std::endl;
	swap (*d3.get(), *d4.get());
	std::cout << d1->get_size() << "/" << d1->get_device() << ", " << d2->get_size() << "/" << d2->get_device() << std::endl;
	std::cout << std::endl;
}


/**
 * main
 */
int main (int, char *[])
{
	move_c();
	move_d();
	return 0;
}

