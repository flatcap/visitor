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
#include "variant.h"

static int base_seqnum = 1000;

/**
 * create (static)
 */
CPtr
Container::create (void)
{
	Container* c = new Container();

	CPtr cp (c);

	c->weak = cp;	// keep a weak pointer to myself

	return cp;
}


/**
 * Container (default)
 */
Container::Container()
{
	set_type ("container");

	set_prop ("size", (long)0);

	seqnum = base_seqnum;
	std::cout << "Container ctor (default): " << seqnum << std::endl;
	base_seqnum += 1000;
}

/**
 * Container (copy)
 */
Container::Container (const Container& c) :
	name (c.name),
	props (c.props)
	//don't copy 'weak'
{
	std::cout << "Container ctor (copy)" << std::endl;

	for (auto child : c.children) {
		children.push_back (child->copy());
	}
}

/**
 * Container (move)
 */
Container::Container (Container&& c)
{
	std::cout << "Container ctor (move)" << std::endl;
	swap (c);
}


/**
 * operator= (copy)
 */
Container&
Container::operator= (const Container& c)
{
	std::cout << "Container assign (copy)" << std::endl;

	name     = c.name;
	children = c.children;
	//don't copy 'weak'

	return *this;
}

/**
 * operator= (move)
 */
Container&
Container::operator= (Container&& c)
{
	std::cout << "Container assign (move)" << std::endl;
	swap (c);
	return *this;
}


/**
 * swap (member)
 */
void
Container::swap (Container& c)
{
	std::cout << "Container swap (member)" << std::endl;
	std::swap (children, c.children);
	std::swap (this->props, c.props);
}

/**
 * swap (global)
 */
void swap (Container& lhs, Container& rhs)
{
	std::cout << "Container swap (global)" << std::endl;
	lhs.swap (rhs);
}


/**
 * clone
 */
Container*
Container::clone (void) const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	return new Container (*this);
}


/**
 * copy
 */
CPtr
Container::copy (void) const
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;
	Container *c = clone();

	CPtr cp (c);

	c->weak = cp;	// keep a weak pointer to myself

	return cp;
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


/**
 * changed
 */
void
Container::changed (void)
{
	if (seqnum < 1)
		return;

	std::cout << __PRETTY_FUNCTION__ << std::endl;
	seqnum++;
}

/**
 * get_seqnum
 */
int
Container::get_seqnum (void)
{
	return seqnum;
}


/**
 * operator<<
 */
std::ostream&
operator<< (std::ostream &stream, const CPtr &c)
{
	stream << "C[";
	for (auto i : c->props) {
		stream << "(" << i.first << "=" << (std::string) i.second << ")";
	}
	stream << "]";

	return stream;
}

