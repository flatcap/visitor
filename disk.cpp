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
 * Disk (copy)
 */
Disk::Disk (const Disk& d) :
	Container (d),
	device (d.device)
{
	std::cout << __PRETTY_FUNCTION__ << " : " << d.device << std::endl;
}

/**
 * operator=
 */
Disk&
Disk::operator= (const Disk& d)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Container::operator= (d);

	device = d.device;

	return *this;
}


/**
 * create (static)
 */
DPtr
Disk::create (void)
{
	Disk* d = new Disk();

	d->name = "disk";

	DPtr dp (d);

	d->me = dp;

	return dp;
}


#if 0
/**
 * backup
 */
CPtr
Disk::backup (void)
{
	//Container::backup();
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	CPtr old (new Disk (*this));
	return old;
}

/**
 * restore
 */
void
Disk::restore (void)
{
	Container::restore();
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}

#endif

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


