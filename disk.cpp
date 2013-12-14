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

#include "disk.h"
#include "variant.h"

static int counter = 1;

/**
 * create (static)
 */
DPtr
Disk::create (void)
{
	Disk* d = new Disk();

	d->set_type ("disk");

	d->_a = counter;
	d->_b = counter + 1;
	d->_c = counter + 2;
	counter++;

	d->set_prop ("integer", 42 * counter);
	d->set_prop ("double",  3.14159 * counter);
	d->set_prop ("str",     std::to_string (counter));

	DPtr dp (d);

	d->weak = dp;	// keep a weak pointer to myself

	std::cout << "Disk create: " << dp << std::endl;
	return dp;
}


/**
 * Disk (copy)
 */
Disk::Disk (const Disk& d) :
	Container (d)
{
	std::cout << "Disk ctor (copy)" << std::endl;
	_a = d._a;
	_b = d._b;
	_c = d._c;
}

/**
 * Disk (move)
 */
Disk::Disk (Disk&& d)
{
	std::cout << "Disk ctor (move)" << std::endl;
	swap (d);
}


/**
 * operator= (copy)
 */
Disk&
Disk::operator= (const Disk& d)
{
	std::cout << "Disk assign (copy)" << std::endl;
	Container::operator= (d);

	_a = d._a;
	_b = d._b;
	_c = d._c;

	return *this;
}

/**
 * operator= (move)
 */
Disk&
Disk::operator= (Disk&& d)
{
	std::cout << "Disk assign (move)" << std::endl;
	swap (d);
	return *this;
}


/**
 * swap (member)
 */
void
Disk::swap (Disk& d)
{
	std::cout << "Disk swap (member)" << std::endl;
	Container::swap (d);
}

/**
 * swap (global)
 */
void swap (Disk& lhs, Disk& rhs)
{
	std::cout << "Disk swap (global)" << std::endl;
	lhs.swap (rhs);
}


/**
 * clone
 */
Disk*
Disk::clone (void) const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new Disk (*this);
}


/**
 * operator<<
 */
std::ostream&
operator<< (std::ostream &stream, const DPtr &d)
{
	CPtr c(d);
	stream << c;

	stream << " D[" << d->_a << d->_b << d->_c << "]";

	return stream;
}
