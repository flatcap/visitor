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
#include "visitor.h"

/**
 * create (static)
 */
DPtr
Disk::create (void)
{
	Disk* d = new Disk();

	d->name = "disk";

	DPtr dp (d);

	d->me = dp;	// keep a weak pointer to myself

	return dp;
}


/**
 * Disk (copy)
 */
Disk::Disk (const Disk& d) :
	Container (d),
	device (d.device)
{
	std::cout << "Disk ctor (copy): " << d.device << std::endl;
}

/**
 * Disk (move)
 */
Disk::Disk (Disk&& d)
{
	std::cout << "Disk ctor (move): " << d.device << std::endl;
	swap (d);
}


/**
 * operator= (copy)
 */
Disk&
Disk::operator= (const Disk& d)
{
	std::cout << "Disk assign (copy): "<< device << ", " << d.device << std::endl;
	Container::operator= (d);

	device = d.device;

	return *this;
}

/**
 * operator= (move)
 */
Disk&
Disk::operator= (Disk&& d)
{
	std::cout << "Disk assign (move): "<< device << ", " << d.device << std::endl;
	swap (d);
	return *this;
}


/**
 * swap (member)
 */
void
Disk::swap (Disk& d)
{
	std::cout << "Disk swap (member): " << device << ", " << d.device << std::endl;
	Container::swap (d);
	std::swap (device, d.device);
}

/**
 * swap (global)
 */
void swap (Disk& lhs, Disk& rhs)
{
	std::cout << "Disk swap (global): " << lhs.device << ", " << rhs.device << std::endl;
	lhs.swap (rhs);
}


/**
 * accept
 */
bool
Disk::accept (Visitor& v)
{
	DPtr d = std::dynamic_pointer_cast<Disk> (me.lock());
	if (!v.visit (d))
		return false;
	return visit_children (v);
}

/**
 * clone
 */
Disk*
Disk::clone (void)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new Disk (*this);
}


/**
 * get_device
 */
std::string
Disk::get_device (void) const
{
	return device;
}

/**
 * set_device
 */
std::string
Disk::set_device (std::string value)
{
	std::string old = device;
	device = value;
	changed();
	return old;
}


