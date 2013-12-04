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

#include "dot_visitor.h"

/**
 * DotVisitor
 */
DotVisitor::DotVisitor (void)
{
}

/**
 * ~DotVisitor
 */
DotVisitor::~DotVisitor()
{
}


/**
 * visit (Container)
 */
void
DotVisitor::visit (const Container& parent, const Container& c)
{
	std::cout << "DotVisited Container: " << &c << std::endl;
}

/**
 * visit (Disk)
 */
void
DotVisitor::visit (const Container& parent, const Disk& d)
{
	std::cout << "DotVisited Disk: " << &d << std::endl;
}

/**
 * visit (Partition)
 */
void
DotVisitor::visit (const Container& parent, const Partition& p)
{
	std::cout << "DotVisited Partition: " << &p << std::endl;
}

/**
 * visit (Filesystem)
 */
void
DotVisitor::visit (const Container& parent, const Filesystem& f)
{
	std::cout << "DotVisited Filesystem: " << &f << std::endl;
}


/**
 * get_output
 */
const std::string&
DotVisitor::get_output (void)
{
	return output;
}


