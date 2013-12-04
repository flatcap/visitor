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

#include "dump_visitor.h"

#include "container.h"
#include "disk.h"
#include "partition.h"
#include "filesystem.h"

/**
 * DumpVisitor
 */
DumpVisitor::DumpVisitor (void)
{
}

/**
 * ~DumpVisitor
 */
DumpVisitor::~DumpVisitor()
{
}


/**
 * indent
 */
static void
indent (int depth)
{
	for (int i = 0; i < depth; i++)
		std::cout << '\t';
}


/**
 * visit_enter
 */
bool
DumpVisitor::visit_enter (const Container& c)
{
	depth++;
	return true;
}

/**
 * visit_leave
 */
bool
DumpVisitor::visit_leave (void)
{
	depth--;
	return true;
}


/**
 * visit (Container)
 */
bool
DumpVisitor::visit (const Container& c)
{
	indent (depth);
	std::cout << "[Container]: " << &c << " : " << c.get_size() << std::endl;
	return true;
}

/**
 * visit (Disk)
 */
bool
DumpVisitor::visit (const Disk& d)
{
	indent (depth);
	std::cout << "[Disk] : " << &d << " : " << d.get_device() << std::endl;
	return true;
}

/**
 * visit (Partition)
 */
bool
DumpVisitor::visit (const Partition& p)
{
	indent (depth);
	std::cout << "[Partition] : " << &p << " : " << p.get_id() << std::endl;
	return true;
}

/**
 * visit (Filesystem)
 */
bool
DumpVisitor::visit (const Filesystem& f)
{
	indent (depth);
	std::cout << "[Filesystem] : " << &f << " : " << f.get_label() << std::endl;
	return true;
}


