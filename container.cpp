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

#include "container.h"
#include "visitor.h"

/**
 * Container (copy)
 */
Container::Container (const Container& c) :
	Backup (c),
	name (c.name),
	size (c.size)
	//don't copy 'me'
{
	std::cout << __PRETTY_FUNCTION__ << " : " << c.name << std::endl;

	for (auto child : c.children) {
		children.push_back (child->copy());
	}
}

/**
 * operator=
 */
Container&
Container::operator= (const Container& c)
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Backup::operator= (c);

	name     = c.name;
	size     = c.size;
	children = c.children;
	//don't copy 'me'

	return *this;
}


/**
 * create (static)
 */
CPtr
Container::create (void)
{
	Container* c = new Container();

	c->name = "container";

	CPtr cp (c);

	c->me = cp;	// keep a weak pointer to myself

	return cp;
}


/**
 * visit_children
 */
bool
Container::visit_children (Visitor& v)
{
	CPtr c = me.lock();
	if (!v.visit_enter (c))
		return false;

	for (auto c : children) {
		if (!c->accept (v))
			return false;
	}

	if (!v.visit_leave())
		return false;

	return true;
}

/**
 * accept
 */
bool
Container::accept (Visitor& v)
{
	CPtr c = me.lock();
	if (!v.visit (c))
		return false;
	return visit_children (v);
}


/**
 * backup
 */
CPtr
Container::backup (void)
{
#if 0
	CPtr copy (create());

	*copy = this;

	return copy;
#endif
	CPtr old (new Container (*this));
	return old;
}

/**
 * restore
 */
void
Container::restore (void)
{
	Backup::restore();
	//std::cout << __PRETTY_FUNCTION__ << std::endl;

	changed();
	for (auto c : children) {
		c->restore();
	}
}


/**
 * clone
 */
Container*
Container::clone (void)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new Container (*this);
}

/**
 * copy
 */
CPtr
Container::copy (void)
{
	//std::cout << __PRETTY_FUNCTION__ << std::endl;
	Container *c = clone();

	CPtr cp (c);

	c->me = cp;	// keep a weak pointer to myself

	return cp;
}


/**
 * get_size
 */
int
Container::get_size (void) const
{
	return size;
}


/**
 * set_size
 */
int
Container::set_size (int value)
{
	int old = size;
	size = value;
	changed();
	return old;
}


/**
 * add_child
 */
int
Container::add_child (CPtr child)
{
	children.push_back (child);
	changed();
	return children.size();
}

/**
 * remove_child
 */
void
Container::remove_child (size_t index)
{
	if (index >= children.size())
		return;

	children.erase (children.begin()+index);
	changed();
}


/**
 * get_children
 */
const std::vector<CPtr>&
Container::get_children (void)
{
	return children;
}
