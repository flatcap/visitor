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
 * copy (helper)
 */
template<typename T>
std::shared_ptr<T>
copy (const std::shared_ptr<T> &orig)
{
	return std::dynamic_pointer_cast<T> (orig->copy());
}

/**
 * swap (helper)
 */
template<typename T>
void
swap_objects (std::shared_ptr<T> lhs, std::shared_ptr<T> rhs)
{
	std::cout << "my shared_ptr swap\n";
	swap (*lhs.get(), *rhs.get());
}

/**
 * move_c
 */
void
move_c (void)
{
	CPtr c1  = Container::create();
	CPtr c2  = Container::create();

	CPtr c3 (c1);
	CPtr c4 (c2);

	std::cout << c1 << std::endl;
	swap_objects (c3, c4);
	std::cout << c1 << std::endl;
	swap_objects (c3, c4);
	std::cout << c1 << std::endl;
	std::cout << std::endl;
}

/**
 * move_d
 */
void
move_d (void)
{
	DPtr d1 = Disk::create();
	DPtr d2 = Disk::create();

#if 0
	d2 = copy(d1);

	std::cout << d1 << std::endl;
	swap_objects (d1, d2);
	std::cout << d1 << std::endl;
#endif

#if 1
	DPtr d3 (d1);
	DPtr d4 (d2);

	std::cout << d1 << std::endl;
	swap_objects (d3, d4);
	std::cout << d1 << std::endl;
	swap_objects (d3, d4);
	std::cout << d1 << std::endl;
	std::cout << std::endl;
#endif

#if 0
	const Disk *d5 = d1.get();
	const Variant &v = d5->get_prop ("double");
	std::cout << "d = " << (double)v << "(" << (int) v.type << ")" << std::endl;
#endif
	Variant &v = d1->get_prop ("double");
	std::cout << "d = " << (double)v << std::endl;
#if 1
	v = 123.456;
	std::cout << "d = " << (double)v << std::endl;
#endif
}


/**
 * main
 */
int main (int, char *[])
{
#if 0
	move_c();
#endif
	move_d();

#if 0
	DPtr d1 = Disk::create();
	DPtr d2 = Disk::create();

	std::cout << d1 << std::endl;
	std::cout << d2 << std::endl;
	std::cout << std::endl;

	swap (*d1.get(), *d2.get());

	std::cout << d1 << std::endl;
	std::cout << d2 << std::endl;
	std::cout << std::endl;
#endif

	return 0;
}

