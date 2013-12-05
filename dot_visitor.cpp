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

#include "dot_visitor.h"

#include "container.h"
#include "disk.h"
#include "partition.h"
#include "filesystem.h"

#include "utils.h"

/**
 * DotVisitor
 */
DotVisitor::DotVisitor (void)
{
	output << "digraph disks {\n";
	output << "graph [ rankdir=\"TB\", color=\"white\",bgcolor=\"#000000\" ];\n";
	output << "node [ shape=\"record\", color=\"black\", fillcolor=\"lightcyan\", style=\"filled\" ];\n";
	output << "edge [ penwidth=3.0,color=\"#cccccc\" ];\n";
	output << "\n";
}

/**
 * ~DotVisitor
 */
DotVisitor::~DotVisitor()
{
}


/**
 * dot_row (int)
 */
static std::string
dot_row (const char* name, int value)
{
	std::stringstream output;

	output << "<tr>";
	output << "<td align=\"left\">" << name << "</td>";
	output << "<td>=</td>";
	output << "<td align=\"left\">" << value << "</td>";
	output << "</tr>\n";

	return output.str();
}

/**
 * dot_row (std::string)
 */
static std::string
dot_row (const char* name, const std::string& value)
{
	std::stringstream output;

	output << "<tr>";
	output << "<td align=\"left\">" << name << "</td>";
	output << "<td>=</td>";
	output << "<td align=\"left\">" << value << "</td>";
	output << "</tr>\n";

	return output.str();
}


/**
 * visit_enter
 */
bool
DotVisitor::visit_enter (CPtr& c)
{
	std::stringstream addr;
	addr << (void*) c.get();
	parents.push (addr.str());
	return true;
}

/**
 * visit_leave
 */
bool
DotVisitor::visit_leave (void)
{
	parents.pop();
	if (parents.empty()) {
		output << "\n}";
		output << "\n";
	}

	return true;
}


/**
 * visit (CPtr)
 */
bool
DotVisitor::visit (CPtr& c)
{
	output << "\n";
	output << "// " << (void*) c.get() << "\n";

	output << "obj_" << (void*) c.get() << " [fillcolor=\"#c0c0c0\",label=<<table cellspacing=\"0\" border=\"0\">\n";
	output << "<tr><td align=\"left\" bgcolor=\"white\" colspan=\"3\"><font color=\"#000000\" point-size=\"20\"><b>" << (char)toupper(c->name[0]) << "</b></font> (" << (void*) c.get() << ")<font color=\"#ff0000\" point-size=\"20\"><b> : " << c->get_seqnum() << "</b></font></td></tr>\n";

	output << dot_row ("size", c->get_size());

	output << "</table>>];\n";

	if (parents.size() > 0)
		output << "obj_" << parents.top() << " -> obj_" << (void*)c.get() << ";\n";

	return true;
}

/**
 * visit (DPtr)
 */
bool
DotVisitor::visit (DPtr& d)
{
	output << "\n";
	output << "// " << (void*) d.get() << "\n";

	output << "obj_" << (void*) d.get() << " [fillcolor=\"#ffc0c0\",label=<<table cellspacing=\"0\" border=\"0\">\n";
	output << "<tr><td align=\"left\" bgcolor=\"white\" colspan=\"3\"><font color=\"#000000\" point-size=\"20\"><b>" << (char)toupper(d->name[0]) << "</b></font> (" << (void*) d.get() << ")<font color=\"#ff0000\" point-size=\"20\"><b> : " << d->get_seqnum() << "</b></font></td></tr>\n";

	output << dot_row ("size",   d->get_size());
	output << dot_row ("device", d->get_device());

	output << "</table>>];\n";

	if (parents.size() > 0)
		output << "obj_" << parents.top() << " -> obj_" << (void*) d.get() << ";\n";

	return true;
}

/**
 * visit (PPtr)
 */
bool
DotVisitor::visit (PPtr& p)
{
	output << "\n";
	output << "// " << (void*) p.get() << "\n";

	output << "obj_" << (void*) p.get() << " [fillcolor=\"#d0d080\",label=<<table cellspacing=\"0\" border=\"0\">\n";
	output << "<tr><td align=\"left\" bgcolor=\"white\" colspan=\"3\"><font color=\"#000000\" point-size=\"20\"><b>" << (char)toupper(p->name[0]) << "</b></font> (" << (void*) p.get() << ")<font color=\"#ff0000\" point-size=\"20\"><b> : " << p->get_seqnum() << "</b></font></td></tr>\n";

	output << dot_row ("size", p->get_size());
	output << dot_row ("id",   p->get_id());

	output << "</table>>];\n";

	if (parents.size() > 0)
		output << "obj_" << parents.top() << " -> obj_" << (void*) p.get() << ";\n";

	return true;
}

/**
 * visit (FPtr)
 */
bool
DotVisitor::visit (FPtr& f)
{
	output << "\n";
	output << "// " << (void*) f.get() << "\n";

	output << "obj_" << (void*) f.get() << " [fillcolor=\"#80c080\",label=<<table cellspacing=\"0\" border=\"0\">\n";
	output << "<tr><td align=\"left\" bgcolor=\"white\" colspan=\"3\"><font color=\"#000000\" point-size=\"20\"><b>" << (char)toupper(f->name[0]) << "</b></font> (" << (void*) f.get() << ")<font color=\"#ff0000\" point-size=\"20\"><b> : " << f->get_seqnum() << "</b></font></td></tr>\n";

	output << dot_row ("size",  f->get_size());
	output << dot_row ("label", f->get_label());

	output << "</table>>];\n";

	if (parents.size() > 0)
		output << "obj_" << parents.top() << " -> obj_" << (void*) f.get() << ";\n";

	return true;
}


/**
 * get_output
 */
std::string
DotVisitor::get_output (void)
{
	return output.str();
}


/**
 * run_dotty
 */
void
DotVisitor::run_dotty (void)
{
	std::string command = "dot -Tpng | display -resize 70% - &";

	execute_command (command, output.str());
}

