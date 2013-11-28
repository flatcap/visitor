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

#include <string>
#include <sstream>

#include "container.h"
#include "disk.h"
#include "partition.h"
#include "filesystem.h"

#include "utils.h"

/**
 * dot_row (bool)
 */
std::string
dot_row (const char *name, bool value)
{
	std::stringstream output;

	output << "<tr>";
	output << "<td align=\"left\">" << name << "</td>";
	output << "<td>=</td>";
	output << "<td align=\"left\">" << (value ? "true" : "false") << "</td>";
	output << "</tr>\n";

	return output.str();
}

/**
 * dot_row (int)
 */
std::string
dot_row (const char *name, int value)
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
 * dot_row (long)
 */
std::string
dot_row (const char *name, long value)
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
std::string
dot_row (const char *name, const std::string &value)
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
 * dot_row (std::stringstream)
 */
std::string
dot_row (const char *name, const std::stringstream &value)
{
	std::stringstream output;

	output << "<tr>";
	output << "<td align=\"left\">" << name << "</td>";
	output << "<td>=</td>";
	output << "<td align=\"left\">" << value.str() << "</td>";
	output << "</tr>\n";

	return output.str();
}

/**main
 * dot_row (char *)
 */
std::string
dot_row (const char *name, const char *value)
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
 * dot_row (unsigned int)
 */
std::string
dot_row (const char *name, unsigned int value)
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
 * dot_row (void *)
 */
std::string
dot_row (const char *name, void *value)
{
	std::stringstream output;

	output << "<tr>";
	output << "<td align=\"left\">" << name << "</td>";
	output << "<td>=</td>";
	if (value) {
		output << "<td align=\"left\">" << value << "</td>";
	} else {
		output << "<td align=\"left\">NULL</td>";
	}
	output << "</tr>\n";

	return output.str();
}

/**
 * dot_row (CPtr &)
 */
std::string
dot_row (const char *name, const CPtr &value)
{
	std::stringstream output;
	std::string dest;

	output << "<tr>";
	output << "<td align=\"left\">" << name << "</td>";
	output << "<td>=</td>";
	if (value) {
		output << "<td align=\"left\">" << value << dest << "</td>";
	} else {
		output << "<td align=\"left\">NULL</td>";
	}
	output << "</tr>\n";

	return output.str();
}


/**
 * dot_container
 */
std::string
dot_container (const CPtr &c)
{
	std::stringstream output;

	output << dot_row ("seqnum", c->get_seqnum());
	output << dot_row ("size",   c->get_size());

	return output.str();
}


/**
 * dot_disk
 */
std::string
dot_disk (const CPtr &c)
{
	std::stringstream output;

	output << dot_container (c);

	DPtr d = std::dynamic_pointer_cast<Disk> (c);

	output << dot_row ("device", d->get_device());

	return output.str();
}

/**
 * dot_partition
 */
std::string
dot_partition (const CPtr &c)
{
	std::stringstream output;

	output << dot_container (c);

	PPtr p = std::dynamic_pointer_cast<Partition> (c);

	output << dot_row ("id", p->get_id());

	return output.str();
}

/**
 * dot_filesystem
 */
std::string
dot_filesystem (const CPtr &c)
{
	std::stringstream output;

	output << dot_container (c);

	FPtr f = std::dynamic_pointer_cast<Filesystem> (c);

	output << dot_row ("label", f->get_label());

	return output.str();
}


/**
 * dump_dot_inner
 */
std::string
dump_dot_inner (const std::vector <CPtr> &v)
{
	std::stringstream dot;

	for (auto c : v) {
		std::string name = c->name;

		dot << "\n";
		dot << "// " << c << " " << c->name << "\n";

		std::string colour;
		     if (name == "disk")       colour = "#ffc0c0";	// red
		else if (name == "partition")  colour = "#d0d080";	// yellow
		else if (name == "filesystem") colour = "#80c080";	// green
		else                           colour = "#c0c0c0";	// grey

		dot << "obj_" << c << " [fillcolor=\"" << colour << "\",label=<<table cellspacing=\"0\" border=\"0\">\n";
		dot << "<tr><td align=\"left\" bgcolor=\"white\" colspan=\"3\"><font color=\"#000000\" point-size=\"20\"><b>" <<
			//c->name
			(char)toupper(name[0])
			<< "</b></font> (" << c << ")</td></tr>\n";

		     if (name == "disk")          { dot << dot_disk       (c); }
		else if (name == "filesystem")    { dot << dot_filesystem (c); }
		else if (name == "partition")     { dot << dot_partition  (c); }

		dot << "</table>>];\n";

		for (auto const &c2 : c->get_children()) {
			dot << "obj_" << c << " -> obj_" << c2 << ";\n";
		}

		dot << dump_dot_inner (c->get_children());
	}

	return dot.str();
}

/**
 * dump_dot
 */
std::string
dump_dot (const std::vector <CPtr> &v)
{
	std::stringstream dot;

	dot << "digraph disks {\n";
	dot << "graph [ rankdir=\"TB\", color=\"white\",bgcolor=\"#000000\" ];\n";
	dot << "node [ shape=\"record\", color=\"black\", fillcolor=\"lightcyan\", style=\"filled\" ];\n";
	dot << "edge [ penwidth=3.0,color=\"#cccccc\" ];\n";

	dot << dump_dot_inner (v);

	dot << "\n}";
	dot << "\n";

	return dot.str();
}

/**
 * display_dot
 */
void
display_dot (const CPtr c, int offset, const std::string &title)
{
	std::string input = dump_dot(c->get_children());
	//std::cout << input << std::endl;

	int screen_x = -1-(offset*400);

	std::string command = "dot -Tpng | display -title \"" + title + "\" -gravity NorthEast -geometry " + std::to_string(screen_x) + "-40 -resize 70% - &";

	execute_command (command, input);
}


/**
 * dump_dot_small
 */
std::string
dump_dot_small (const CPtr &c)
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

	for (auto const &child : c->get_children()) {
		dot << dump_dot_small (child);
		dot << "obj_" << c << " -> obj_" << child << ";\n";
	}

	return dot.str();
}


