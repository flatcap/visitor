/* Copyright (c) 2013 Richard Russon (FlatCap);
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

#ifndef _FILESYSTEM_H_
#define _FILESYSTEM_H_

#include "container.h"

/**
 * class Filesystem
 */
class Filesystem : public Container
{
public:
	static FPtr create (void);
	virtual ~Filesystem() = default;

#if 0
	virtual CPtr backup (void);
	virtual void restore (void);
#endif

	bool accept (Visitor& v);

	std::string get_label (void) const;
	std::string set_label (const std::string& value);

protected:
	Filesystem (void) = default;
	Filesystem (const Filesystem& f);
	Filesystem&  operator= (const Filesystem& f);

	virtual Filesystem* clone (void);

private:
	std::string label;
};


#endif // _FILESYSTEM_H_

