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

#ifndef _VISITOR_H_
#define _VISITOR_H_

#include "pointers.h"

/**
 * class Visitor
 */
class Visitor
{
public:
	virtual bool visit_enter (CPtr& c) { return true; }
	virtual bool visit_leave (void)    { return true; }

	virtual bool visit (CPtr& c) = 0;

	virtual bool visit (DPtr& d) { return visit ((CPtr&) d); }
	virtual bool visit (PPtr& p) { return visit ((CPtr&) p); }
	virtual bool visit (FPtr& f) { return visit ((CPtr&) f); }
};


#endif // _VISITOR_H_

