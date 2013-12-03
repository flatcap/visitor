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
#include <string>

#include "visitor.h"

#include "container.h"
#include "disk.h"
#include "partition.h"
#include "filesystem.h"

/**
 * Visitor
 */
Visitor::Visitor (void)
{
}

/**
 * ~Visitor
 */
Visitor::~Visitor()
{
}


/**
 * visit (Container)
 */
void
Visitor::visit (const Container& c)
{
	std::cout << "Visited Container: " << &c << std::endl;
}

/**
 * visit (Disk)
 */
void
Visitor::visit (const Disk& d)
{
	std::cout << "Visited Disk: " << &d << std::endl;
}

/**
 * visit (Partition)
 */
void
Visitor::visit (const Partition& p)
{
	std::cout << "Visited Partition: " << &p << std::endl;
}

/**
 * visit (Filesystem)
 */
void
Visitor::visit (const Filesystem& f)
{
	std::cout << "Visited Filesystem: " << &f << std::endl;
}


