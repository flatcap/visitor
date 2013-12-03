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

#include "container.h"

/**
 * class Disk
 */
class Disk : public Container
{
public:
	Disk (void);
	virtual ~Disk() = default;

	void accept_visitor (Visitor& v);

	std::string get_device (void);
	std::string set_device (std::string value);

private:
	std::string device;
};


#endif // _DISK_H_

