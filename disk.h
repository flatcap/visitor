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

#ifndef _DISK_H_
#define _DISK_H_

#include <string>

#include "container.h"

/**
 * class Disk
 */
class Disk : public Container
{
public:
	static DPtr create (void);

	Disk (Disk&& d);
	virtual ~Disk() = default;

	Disk& operator= (const Disk& d);
	Disk& operator= (Disk&& d);

	void swap (Disk& d);
	friend void swap (Disk& lhs, Disk& rhs);

	friend std::ostream & operator<< (std::ostream &stream, const DPtr &c);

protected:
	Disk (void) = default;
	Disk (const Disk& d);

	virtual Disk* clone (void) const;

private:
	int _a;
	int _b;
	int _c;
};


#endif // _DISK_H_

