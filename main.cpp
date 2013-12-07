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

#include <algorithm>
#include <deque>
#include <iostream>
#include <memory>
#include <new>
#include <sstream>
#include <string>
#include <tuple>
#include <typeinfo>
#include <vector>

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
 * dot
 */
void
dot (CPtr &c)
{
	DotVisitor dv;
	c->accept (dv);
	dv.run_dotty();
}

#if 0
/**
 * dump
 */
void
dump (CPtr& c)
{
	DumpVisitor v;
	c->accept(v);
}

/**
 * weak
 */
void
weak (CPtr& c, DPtr& d)
{
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
}

/**
 * select
 */
bool
choose (CPtr& c)
{
	return (c->name == "partition");
}

/**
 * lamda_function
 */
void
lamda_function (CPtr& c)
{
	LambdaVisitor lv2 (choose);
	c->accept (lv2);
	for (auto c : lv2.get_results()) {
		std::cout << "[" << c->name << "]: " << c << " : " << c->get_size() << std::endl;
	}
}

/**
 * lamda_functor
 */
void
lamda_functor (CPtr& c)
{
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
}

/**
 * lambda_lambda
 */
void
lambda_lambda (CPtr& c)
{
	std::string search = "filesystem";
	LambdaVisitor lv3 ([search] (CPtr& c) { return (c->name == search); });
	c->accept (lv3);
	for (auto c : lv3.get_results()) {
		std::cout << "[" << c->name << "]: " << c << " : " << c->get_size() << std::endl;
	}
	std::cout << std::endl;
}

/**
 * swap
 */
template<class L,class R>
void
swap (L& l, R& r)
{
	{
		std::string ltype = typeid(l).name();
		std::string rtype = typeid(r).name();

		CPtr lc = std::dynamic_pointer_cast<Container>(l);
		CPtr rc = std::dynamic_pointer_cast<Container>(r);

		std::cout << "swapping: " << lc << "(" << ltype << "), " << rc << "(" << rtype + ")" << std::endl;

		std::swap (lc, rc);
	}
	{
		std::string ltype = typeid(l).name();
		std::string rtype = typeid(r).name();

		CPtr lc = std::dynamic_pointer_cast<Container>(l);
		CPtr rc = std::dynamic_pointer_cast<Container>(r);

		std::cout << "swapping: " << lc << "(" << ltype << "), " << rc << "(" << rtype + ")" << std::endl;
		std::cout << std::endl;
	}
}

/**
 * swap_test1
 */
void
swap_test1 (void)
{
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (c, d); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (c, p); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (c, f); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (d, c); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (d, p); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (d, f); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (p, c); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (p, d); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (p, f); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (f, c); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (f, d); }
	{ CPtr c = Container::create(); DPtr d = Disk::create(); PPtr p = Partition::create(); FPtr f = Filesystem::create(); swap (f, p); }
}

/**
 * swap_test2
 */
void
swap_test2 (void)
{
	CPtr c = Container::create();
	DPtr d = Disk::create();
	PPtr p = Partition::create();
	FPtr f = Filesystem::create();

	std::cout << sizeof(c) << std::endl;
	std::cout << sizeof(d) << std::endl;
	std::cout << sizeof(p) << std::endl;
	std::cout << sizeof(f) << std::endl;
	std::cout << std::endl;

	swap (c, d);
	swap (c, p);
	swap (c, f);
	swap (d, c);
	swap (d, p);
	swap (d, f);
	swap (p, c);
	swap (p, d);
	swap (p, f);
	swap (f, c);
	swap (f, d);
	swap (f, p);
}

/**
 * swap_test3
 */
void
swap_test3 (void)
{
	{
		DPtr d1 = Disk::create(); d1->set_device ("apple");
		DPtr d2 = Disk::create(); d2->set_device ("banana");

		std::cout << d1->get_device() << ", " << d2->get_device() << std::endl;
		swap (d1, d2);
		std::cout << d1->get_device() << ", " << d2->get_device() << std::endl << std::endl;
	}
	{
		DPtr d1 = Disk::create(); d1->set_device ("apple");
		DPtr d2 = Disk::create(); d2->set_device ("banana");

		CPtr c1 = std::dynamic_pointer_cast<Container> (d1);
		CPtr c2 = std::dynamic_pointer_cast<Container> (d2);

		std::cout << d1->get_device() << ", " << d2->get_device() << std::endl;
		swap (c1, c2);
		std::cout << d1->get_device() << ", " << d2->get_device() << std::endl << std::endl;

		std::cout << d1.get() << ", " << d2.get() << std::endl;
		std::cout << c1.get() << ", " << c2.get() << std::endl << std::endl;
	}
}

#endif

/**
 * main
 */
int main (int, char *[])
{
#if 0
	CPtr c  = Container::create();
	DPtr d  = Disk::create();
	FPtr f1 = Filesystem::create();
	d->set_device("orig");
	f1->set_label("apple");
	c->add_child (d);
	d->add_child (f1);


	CPtr d_copy = d->copy();
	DPtr dd_copy = std::dynamic_pointer_cast<Disk> (d_copy);
	dd_copy->set_device("copy");
	FPtr f_copy = std::dynamic_pointer_cast<Filesystem> (d_copy->get_children()[0]);

	f_copy->set_label ("banana");

	dot (c);
	dot (d_copy);

	Disk* swap_left  = dynamic_cast<Disk*> (d.get());
	Disk* swap_right = dynamic_cast<Disk*> (d_copy.get());
	std::swap (*swap_left, *swap_right);

	dot (c);
	dot (d_copy);
#endif

#if 0
	Timeline tl;
	tl.backup (left, right, std::string ("label"));
	tl.display();

	tl.dump();
	d->remove_child(1);
	f1->set_label ("XXX");
	tl.restore();
#endif

	return 0;
}


