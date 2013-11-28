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

#ifndef _TIMELINE_H_
#define _TIMELINE_H_

#include <tuple>
#include <deque>
#include <string>

#include "pointers.h"

typedef std::tuple<CPtr, CPtr, std::string> Action;	// Current, Old, Description

/**
 * class Timeline
 */
class Timeline
{
public:
	Timeline (void);
	virtual ~Timeline();

	void push (const Action &action);
	Action pop (void);

	CPtr backup (const CPtr &root, const std::string &desc);

	void dump (void);
	void display (void);

protected:
	std::deque<Action> timeline;
};


#endif // _TIMELINE_H_

