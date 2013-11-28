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

/**
 * Disk (default)
 */
Disk::Disk (void)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	name = "disk";
}

/**
 * Disk (copy)
 */
Disk::Disk (const Disk &d) :
	Container (d),
	device (d.device)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}

/**
 * ~Disk
 */
Disk::~Disk()
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}


/**
 * operator=
 */
Disk &
Disk::operator= (const Disk &d)
{
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
	DPtr d (new Disk);

	return d;
}


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


/**
 * get_device
 */
std::string
Disk::get_device (void)
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


