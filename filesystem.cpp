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
#include "visitor.h"

/**
 * create (static)
 */
FPtr
Filesystem::create (void)
{
	Filesystem* f = new Filesystem();

	f->name = "filesystem";

	FPtr fp (f);

	f->me = fp;	// keep a weak pointer to myself

	return fp;
}


/**
 * Filesystem (copy)
 */
Filesystem::Filesystem (const Filesystem& f) :
	Container (f),
	label (f.label)
{
	std::cout << "Filesystem ctor (copy): " << f.label << std::endl;
}

/**
 * Filesystem (move)
 */
Filesystem::Filesystem (Filesystem&& f)
{
	std::cout << "Filesystem ctor (move): " << f.label << std::endl;
	swap (f);
}


/**
 * operator= (copy)
 */
Filesystem&
Filesystem::operator= (const Filesystem& f)
{
	std::cout << "Filesystem assign (copy): " << label << ", " << f.label << std::endl;
	Container::operator= (f);

	label = f.label;
	return *this;
}

/**
 * operator= (move)
 */
Filesystem&
Filesystem::operator= (Filesystem&& f)
{
	std::cout << "Filesystem assign (move): " << label << ", " << f.label << std::endl;
	swap (f);
	return *this;
}


/**
 * swap (member)
 */
void
Filesystem::swap (Filesystem& f)
{
	std::cout << "Filesystem swap (member): " << label << ", " << f.label << std::endl;
	Container::swap (f);
	std::swap (label, f.label);
}

/**
 * swap (global)
 */
void swap (Filesystem& lhs, Filesystem& rhs)
{
	std::cout << "Filesystem swap (global): " << lhs.label << ", " << rhs.label << std::endl;
	lhs.swap (rhs);
}


/**
 * accept
 */
bool
Filesystem::accept (Visitor& v)
{
	FPtr f = std::dynamic_pointer_cast<Filesystem> (me.lock());
	if (!v.visit (f))
		return false;
	return visit_children (v);
}

/**
 * clone
 */
Filesystem*
Filesystem::clone (void)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new Filesystem (*this);
}


/**
 * get_label
 */
std::string
Filesystem::get_label (void) const
{
	return label;
}

/**
 * set_label
 */
std::string
Filesystem::set_label (const std::string& value)
{
	std::string old = label;
	label = value;
	changed();
	return old;
}


