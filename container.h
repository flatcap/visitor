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
#include "backup.h"

/**
 * class Container
 */
class Container : public Backup
{
public:
	Container (void);
	Container (const Container &c);
	virtual ~Container();

	void * operator new (size_t size);
	void operator delete (void *ptr);

	static CPtr create (void);

	virtual CPtr backup (void);
	virtual void restore (void);

	int get_size (void);
	int set_size (int value);
	int add_child (CPtr child);
	void remove_child (size_t index);
	const std::vector<CPtr>& get_children (void);

	std::string name;
private:
	int size;
	std::vector<CPtr> children;
};


#endif // _CONTAINER_H_

