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

#ifndef _DOT_VISITOR_H_
#define _DOT_VISITOR_H_

#include <sstream>
#include <stack>
#include <string>

#include "visitor.h"

/**
 * class DotVisitor
 */
class DotVisitor : public Visitor
{
public:
	DotVisitor (void);
	virtual ~DotVisitor();

	virtual bool visit_enter (CPtr& c);
	virtual bool visit_leave (void);

	virtual bool visit (CPtr& c);
	virtual bool visit (DPtr& d);
	virtual bool visit (PPtr& p);
	virtual bool visit (FPtr& f);

	std::string get_output (void);
	void run_dotty (const std::string& title);

protected:
	std::stack<std::string> parents;
	std::stringstream output;
};


#endif // _DOT_VISITOR_H_

