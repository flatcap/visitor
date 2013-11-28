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

#include "filesystem.h"

/**
 * Filesystem (default)
 */
Filesystem::Filesystem (void)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	name = "filesystem";
}

/**
 * Filesystem (copy)
 */
Filesystem::Filesystem (const Filesystem &f) :
	Container (f),
	label (f.label)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}

/**
 * ~Filesystem
 */
Filesystem::~Filesystem()
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}


/**
 * operator=
 */
Filesystem &
Filesystem::operator= (const Filesystem &f)
{
	Container::operator= (f);

	label = f.label;

	return *this;
}


/**
 * create (static)
 */
FPtr
Filesystem::create (void)
{
	FPtr f (new Filesystem);

	return f;
}


/**
 * backup
 */
CPtr
Filesystem::backup (void)
{
	//Container::backup();
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	CPtr old (new Filesystem (*this));
	return old;
}

/**
 * restore
 */
void
Filesystem::restore (void)
{
	Container::restore();
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
}


/**
 * get_label
 */
std::string
Filesystem::get_label (void)
{
	return label;
}

/**
 * set_label
 */
std::string
Filesystem::set_label (const std::string &value)
{
	std::string old = label;
	label = value;
	changed();
	return old;
}


