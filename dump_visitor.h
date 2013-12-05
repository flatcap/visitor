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

#ifndef _DUMP_VISITOR_H_
#define _DUMP_VISITOR_H_

#include "visitor.h"

/**
 * class DumpVisitor
 */
class DumpVisitor : public Visitor
{
public:
	DumpVisitor (void);
	virtual ~DumpVisitor();

	virtual bool visit_enter (CPtr& c);
	virtual bool visit_leave (void);

	virtual bool visit (CPtr& c);
	virtual bool visit (DPtr& d);
	virtual bool visit (PPtr& p);
	virtual bool visit (FPtr& f);

protected:
	int depth = 0;
};


#endif // _DUMP_VISITOR_H_

