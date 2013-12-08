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

#if 0
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
 * swap2
 */
template<class L,class R>
void
swap2 (L& l, R& r)
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

/**
 * swap
 */
template<class L,class R>
void
swap (L& l, R& r)
{
	if (typeid(l).name() != typeid(r).name()) {
		std::cout << "Tried to swap different types: " << typeid(l).name() << " and " << typeid(r).name() << std::endl;
		//return;
	}

	if (typeid(l.get()).name() != typeid(r.get()).name()) {
		std::cout << "Tried to swap different types: " << typeid(l.get()).name() << " and " << typeid(r.get()).name() << std::endl;
		//return;
	}

	Container* lc = dynamic_cast<Container*>(l.get());
	Container* rc = dynamic_cast<Container*>(r.get());
	std::cout << "Types: " << typeid(lc).name() << " and " << typeid(rc).name() << std::endl;

	std::swap (lc, rc);
}

/**
 * test
 */
template<class T,class U>
void
test (const std::shared_ptr<T>& first, const std::shared_ptr<U>& second)
{
	std::cout << typeid(*first).name() << " : " << typeid(*second).name() << std::endl;

#if 0
	T* t1 = dynamic_cast<T*> (second.get());
	U* u1 = dynamic_cast<U*> (first.get());
#endif

	std::shared_ptr<T> t2 = std::dynamic_pointer_cast<T> (second);
	std::shared_ptr<U> u2 = std::dynamic_pointer_cast<U> (first);

	//std::cout << "t1 = " << t1 << ", u1 = " << u1 << std::endl;
	//std::cout << typeid(*t1).name() << " : " << typeid(*u1).name() << std::endl;

	if (t2) {
		if (u2) {
			std::cout << "\tsame types\n";
		} else {
			std::cout << '\t' << typeid(*second).name() << " is more derived\n";
		}
	} else {
		if (u2) {
			std::cout << '\t' << typeid(*first).name() << " is more derived\n";
		} else {
			std::cout << "\tnot related\n";
		}
	}

	if (typeid(*first) == typeid(*second)) {
		std::cout << "\tSAME typeid\n";
	}

	//raw->swap (*first);
	std::cout << std::endl;
}

/**
 * template_test
 */
void
template_test (void)
{
	CPtr c  = Container::create();
	DPtr d  = Disk::create();
	FPtr f1 = Filesystem::create();

#if 1
	test(c, f1);
	test(d, c);
	test(f1, d);
	test(d, d);
#endif

#if 1
	CPtr x1 = std::dynamic_pointer_cast<Container> (c);
	CPtr x2 = std::dynamic_pointer_cast<Container> (d);
	CPtr x3 = std::dynamic_pointer_cast<Container> (f1);

	test(x1, x3);
	test(x2, x1);
	test(x3, x2);
	test(x2, x2);
#endif

}

/**
 * swap3
 */
template<class T,class U>
void
swap3 (const std::shared_ptr<T>& first, const std::shared_ptr<U>& second)
{
	if (typeid(*first) != typeid(*second)) {
		std::cout << "different typeid\n";
		return;
	}

	T* t1 = dynamic_cast<T*> (first.get());
	T* t2 = dynamic_cast<T*> (second.get());

	swap (*t1, *t2);
	std::cout << "swapped\n";
}

/**
 * dummy
 */
void dummy (void)
{
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

#if 0
	dot (c);
	dot (d_copy);

	swap3 (d, d_copy);

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
}

#endif

/**
 * move_c
 */
void
move_c (void)
{
	CPtr c1  = Container::create();
	CPtr c2  = Container::create();

	c1->set_size (42);
	c2->set_size (99);

	CPtr c3 (c1);
	CPtr c4 (c2);

	std::cout << c1->get_size() << ", " << c2->get_size() << std::endl;
	swap (*c3.get(), *c4.get());
	std::cout << c1->get_size() << ", " << c2->get_size() << std::endl;
	swap (*c3.get(), *c4.get());
	std::cout << c1->get_size() << ", " << c2->get_size() << std::endl;
	std::cout << std::endl;
}

/**
 * move_d
 */
void
move_d (void)
{
	DPtr d1  = Disk::create();
	DPtr d2  = Disk::create();

	d1->set_size (42);
	d1->set_device ("apple");
	d2->set_size (99);
	d2->set_device ("banana");

	DPtr d3 (d1);
	DPtr d4 (d2);

	std::cout << d1->get_size() << "/" << d1->get_device() << ", " << d2->get_size() << "/" << d2->get_device() << std::endl;
	swap (*d3.get(), *d4.get());
	std::cout << d1->get_size() << "/" << d1->get_device() << ", " << d2->get_size() << "/" << d2->get_device() << std::endl;
	swap (*d3.get(), *d4.get());
	std::cout << d1->get_size() << "/" << d1->get_device() << ", " << d2->get_size() << "/" << d2->get_device() << std::endl;
	std::cout << std::endl;
}

/**
 * move_p
 */
void
move_p (void)
{
	PPtr p1  = Partition::create();
	PPtr p2  = Partition::create();

	p1->set_size (42);
	p1->set_id (1701);
	p2->set_size (99);
	p2->set_id (2001);

	PPtr p3 (p1);
	PPtr p4 (p2);

	std::cout << p1->get_size() << "/" << p1->get_id() << ", " << p2->get_size() << "/" << p2->get_id() << std::endl;
	swap (*p3.get(), *p4.get());
	std::cout << p1->get_size() << "/" << p1->get_id() << ", " << p2->get_size() << "/" << p2->get_id() << std::endl;
	swap (*p3.get(), *p4.get());
	std::cout << p1->get_size() << "/" << p1->get_id() << ", " << p2->get_size() << "/" << p2->get_id() << std::endl;
	std::cout << std::endl;
}

/**
 * move_f
 */
void
move_f (void)
{
	FPtr f1  = Filesystem::create();
	FPtr f2  = Filesystem::create();

	f1->set_size (42);
	f1->set_label ("peter");
	f2->set_size (99);
	f2->set_label ("quincy");

	FPtr f3 (f1);
	FPtr f4 (f2);

	std::cout << f1->get_size() << "/" << f1->get_label() << ", " << f2->get_size() << "/" << f2->get_label() << std::endl;
	swap (*f3.get(), *f4.get());
	std::cout << f1->get_size() << "/" << f1->get_label() << ", " << f2->get_size() << "/" << f2->get_label() << std::endl;
	swap (*f3.get(), *f4.get());
	std::cout << f1->get_size() << "/" << f1->get_label() << ", " << f2->get_size() << "/" << f2->get_label() << std::endl;
	std::cout << std::endl;
}


/**
 * main
 */
int main (int, char *[])
{
	move_c();
	move_d();
	move_p();
	move_f();
	return 0;
}

