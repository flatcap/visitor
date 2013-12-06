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

#include "dump_visitor.h"
#include "dot_visitor.h"
#include "lambda_visitor.h"

/**
 * select
 */
bool
choose (CPtr& c)
{
	return (c->name == "partition");
}

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

	c->add_child (d);
	d->add_child (p1);
	p1->add_child (f1);
	d->add_child (p2);
	p2->add_child (f2);

	CPtr d_work = d->copy();

#if 0 // Timeline
	Timeline tl;

	tl.backup (d, "initial");
	//tl.dump();
	//tl.display();

	//display_dot (c, 2, "initial");
	//d->remove_child(1);
	f1->set_label ("XXX");
	//display_dot (c, 1, "deleted");
	//tl.restore();
	//display_dot (c, 0, "restored");
#endif

#if 0 // DumpVisitor (c)
	DumpVisitor v1;
	c->accept(v1);
	std::cout << std::endl;
#endif

#if 1 // DumpVisitor (d_work)
	DumpVisitor v2;
	d_work->accept(v2);
#endif

#if 0 // DotVisitor
	DotVisitor dv;
	d_work->accept (dv);
	dv.run_dotty();
#endif

#if 0 // LambdaVisitor (functor)
	struct {
		bool operator() (CPtr& c)
		{
			return c->name == "disk";
		}
	} functor;

	LambdaVisitor lv1 (functor);
	c->accept (lv1);
	for (auto c : lv1.get_results()) {
		std::cout << "[" << c->name << "]: " << c << " : " << c->get_size() << std::endl;
	}
	std::cout << std::endl;
#endif

#if 0 // LambdaVisitor (function)
	LambdaVisitor lv2 (choose);
	c->accept (lv2);
	for (auto c : lv2.get_results()) {
		std::cout << "[" << c->name << "]: " << c << " : " << c->get_size() << std::endl;
	}
	std::cout << std::endl;
#endif

#if 0 // LambdaVisitor (lamda)
	std::string search = "filesystem";
	LambdaVisitor lv3 ([search] (CPtr& c) { return (c->name == search); });
	c->accept (lv3);
	for (auto c : lv3.get_results()) {
		std::cout << "[" << c->name << "]: " << c << " : " << c->get_size() << std::endl;
	}
	std::cout << std::endl;
#endif

#if 0 // Shared/Weak pointer
	std::weak_ptr<Disk> wp;
	std::shared_ptr<Disk> sp;

	wp = d;

	std::cout << d.use_count()  << std::endl;
	std::cout << wp.use_count() << std::endl;
	std::cout << sp.use_count() << std::endl << std::endl;

	sp = wp.lock();
	wp.reset();

	std::cout << d.use_count()  << std::endl;
	std::cout << wp.use_count() << std::endl;
	std::cout << sp.use_count() << std::endl << std::endl;

	sp = nullptr;

	std::cout << d.use_count()  << std::endl;
	std::cout << wp.use_count() << std::endl;
	std::cout << sp.use_count() << std::endl << std::endl;

	sp = wp.lock();

	std::cout << d.use_count()  << std::endl;
	std::cout << wp.use_count() << std::endl;
	std::cout << sp.use_count() << std::endl << std::endl;
#endif


	return 0;
}


