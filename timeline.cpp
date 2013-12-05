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
#include <sstream>

#include "timeline.h"
#include "container.h"
#include "utils.h"

/**
 * Timeline
 */
Timeline::Timeline (void)
{
}

/**
 * ~Timeline
 */
Timeline::~Timeline()
{
}


/**
 * push
 */
void
Timeline::push (const Action& action)
{
	timeline.push_back (action);
}

/**
 * pop
 */
Action
Timeline::pop (void)
{
	Action a = timeline.back();
	timeline.pop_back();
	return a;
}


/**
 * backup
 */
CPtr
Timeline::backup (const CPtr& root, const std::string& desc)
{
	CPtr copy = root->backup();

	push (Action(root, copy, desc));

	return copy;
}

/**
 * restore
 */
void
Timeline::restore (void)
{
	CPtr        current;
	CPtr        old;
	std::string desc;

	std::tie (current, old, desc) = pop();

	*current = *old;	// copy the objects, not the smart pointers

	current->restore();
}


/**
 * dump
 */
void
Timeline::dump (void)
{
	std::cout << "Timeline:\n";
	for (auto a : timeline) {
		CPtr        current;
		CPtr        old;
		std::string desc;

		std::tie (current, old, desc) = a;

		std::cout << '\t' << current << ", " << old << ", " << desc << std::endl;
	}
	std::cout << std::endl;
}


/**
 * dump_dot_small
 */
std::string
dump_dot_small (const CPtr& c)
{
	// dump an instance
	// for each child
	//   dump child instance
	// link this and children

	std::stringstream dot;
	std::string name;

	name = c->name;
	if (name.empty())
		name = "c";

	dot << "\n";
	dot << "// " << c << "\n";

	std::string colour;
	     if (name == "disk")       colour = "#ffc0c0";	// red
	else if (name == "partition")  colour = "#d0d080";	// yellow
	else if (name == "filesystem") colour = "#80c080";	// green
	else                           colour = "#c0c0c0";	// grey

	dot << "obj_" << c << " [fillcolor=\"" << colour << "\",label=<<table cellspacing=\"0\" border=\"0\"><tr><td>\n";
	dot << "<font point-size=\"16\"><b>" << (char)toupper(name[0]) << "</b></font> (" << c->get_seqnum() << ")</td></tr><tr><td>\n";
	dot << "<font point-size=\"10\">" << c << "</font></td></tr></table>\n";
	dot << ">];\n";

	for (auto const& child : c->get_children()) {
		dot << dump_dot_small (child);
		dot << "obj_" << c << " -> obj_" << child << ";\n";
	}

	return dot.str();
}


/**
 * display
 */
void
Timeline::display (void)
{
	if (timeline.size() == 0)
		return;

	std::stringstream dot;
	std::string desc;
	int count = 1;

	dot << "digraph disks {\n";
	dot << "graph [ rankdir=\"TB\", color=\"white\",bgcolor=\"#000000\" ];\n";
	dot << "node [ shape=\"record\", color=\"black\", fillcolor=\"lightcyan\", style=\"filled\" ];\n";
	dot << "edge [ penwidth=3.0,color=\"#cccccc\" ];\n";
	dot << "\n";

	for (auto t : timeline) {
		CPtr c;

		std::tie (std::ignore, c, desc) = t;

		if (!c) {
			std::cout << "empty ptr\n";
			continue;
		}

		dot << "subgraph cluster_" << count++ << " { color=red;\n";
		dot << "fontcolor = \"white\";\n";
		dot << "label = \"" + desc + "\";\n";
		dot << dump_dot_small (c);
		dot << "}\n";
	}

	dot << "\n}";
	dot << "\n";

	std::string input = dot.str();
	//std::cout << input << std::endl;

	int offset = 0;
	int screen_x = -1-(offset*400);

	std::string command = "dot -Tpng | display -title \"timeline:" + std::to_string(count-1) + "\" -gravity NorthEast -geometry " + std::to_string(screen_x) + "+0 -resize 80% -& ";

	execute_command (command, input);
}


