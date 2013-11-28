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
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <typeinfo>
#include <deque>
#include <tuple>
#include <new>

#include "pointers.h"

#include "timeline.h"
#include "container.h"
#include "disk.h"
#include "partition.h"
#include "filesystem.h"
#include "dot.h"

int cc = 0;
int cd = 0;
int cp = 0;
int cf = 0;

/**
 * main
 */
int main (int, char *[])
{
	CPtr c  = Container::create();

	DPtr d  = Disk::create();
	PPtr p1 = Partition::create();
	PPtr p2 = Partition::create();
	FPtr f1 = Filesystem::create();
	FPtr f2 = Filesystem::create();

	d->set_size   (1234);
	d->set_device ("/dev/loop0");

	p1->set_size   (632);
	p1->set_id     (2);

	p2->set_size   (243);
	p2->set_id     (4);

	f1->set_size   (630);
	f1->set_label  ("wibble");

	f2->set_size   (240);
	f2->set_label  ("hatstand");

	Timeline tl;
	CPtr old;

	c->add_child (d);
	d->add_child (p1);
	p1->add_child (f1);
	d->add_child (p2);
	p2->add_child (f2);

	tl.backup (d, "initial");

	old = d->backup();
	tl.push (Action(c, old, "initial"));

#if 0
	std::cout << "count:\n"
		<< "\t" << cc << "\tcontainers\n"
		<< "\t" << cd << "\tdisks\n"
		<< "\t" << cp << "\tpartitions\n"
		<< "\t" << cf << "\tfilesystems\n";
#endif

	display_dot (c, 1, "objects");
	d->remove_child(1);
	display_dot (c, 0, "objects");

	//tl.restore();

	//tl.dump();
	tl.display();

	return 0;
}


