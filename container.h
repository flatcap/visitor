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

#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <vector>

#include "pointers.h"

/**
 * class Container
 */
class Container
{
public:
	static CPtr create (void);
	Container (Container&& c);
	virtual ~Container() = default;

	Container& operator= (const Container& c);
	Container& operator= (Container&& c);

	void swap (Container& c);
	friend void swap (Container& lhs, Container& rhs);

	CPtr copy (void);

	int get_size (void) const;
	int set_size (int value);

	int add_child (CPtr child);
	void remove_child (size_t index);

	const std::vector<CPtr>& get_children (void);

	std::string name;

	int get_seqnum (void);

protected:
	Container (void);
	Container (const Container& c);

	virtual Container* clone (void);

	std::weak_ptr<Container> me;

	void changed (void);

	friend std::ostream & operator<< (std::ostream &stream, const CPtr &c);

private:
	int p;
	int q;
	int size = 0;
	std::vector<CPtr> children;

	int seqnum = 1;
	int r;
	int s;
};


#endif // _CONTAINER_H_

