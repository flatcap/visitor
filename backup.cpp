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
#include <vector>
#include <string>
#include <memory>
#include <sstream>
#include <typeinfo>
#include <deque>
#include <tuple>
#include <new>

class Timeline;
class Container;
class Disk;
class Partition;
class Filesystem;

typedef std::shared_ptr<Timeline>   TPtr;
typedef std::shared_ptr<Container>  CPtr;
typedef std::shared_ptr<Disk>       DPtr;
typedef std::shared_ptr<Partition>  PPtr;
typedef std::shared_ptr<Filesystem> FPtr;

int cc = 0;
int cd = 0;
int cp = 0;
int cf = 0;

std::vector<CPtr> pool;

typedef std::tuple<CPtr, CPtr, std::string> Action;	// Current, Old, Description

/**
 * class Timeline
 */
class Timeline
{
public:
	Timeline (void)
	{
	}

	virtual ~Timeline()
	{
	}

	void push (const Action &action)
	{
		timeline.push_back (action);
	}

	Action pop (void)
	{
		Action a = timeline.back();
		timeline.pop_back();
		return a;
	}

	void dump (void)
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

	std::deque<Action> timeline;
protected:
};

/**
 * class Backup
 */
class Backup
{
public:
	Backup() :
		seqnum(1)
	{
	}

	virtual ~Backup()
	{
	}

	virtual CPtr backup (void)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		seqnum = (seqnum+100)/100*100;

		return nullptr;
	}

	virtual void restore (void)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
		seqnum = (seqnum+100)/100*100;
	}

	int get_seqnum (void)
	{
		return seqnum;
	}

protected:
	void changed (void)
	{
		seqnum++;
	}

private:
	int seqnum;
};

/**
 * class Container
 */
class Container : public Backup
{
public:
	Container (void) :
		size(0)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	Container (const Container &c) :
		name (c.name),
		size (c.size)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		for (auto child : c.children) {
			children.push_back (child->backup());
		}
	}

	virtual ~Container()
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	virtual CPtr backup (void)
	{
		//Backup::backup();
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		CPtr old (new Container (*this));
		cc++;
		return old;
	}

	virtual void restore (void)
	{
		Backup::restore();
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	static CPtr create (void)
	{
		CPtr c (new Container);

		pool.push_back(c);

		cc++;
		return c;
	}

	void *
	operator new (size_t size)
	{
		Container *c = (Container*) ::operator new (size);

#if 0
		std::cout << "new object " << c << std::endl;
#endif

		return c;
	}

	void
	operator delete (void *ptr)
	{
		if (!ptr)
			return;

#if 0
		Container *c = (Container *) (ptr);
		std::cout << "delete object " << c << std::endl;
#endif

		::operator delete (ptr);
	}

	int get_size (void)
	{
		return size;
	}

	int set_size (int value)
	{
		int old = size;
		size = value;
		changed();
		return old;
	}

	int add_child (CPtr child)
	{
		children.push_back (child);
		changed();
		return children.size();
	}

	std::string name;

	const std::vector<CPtr>& get_children (void)
	{
		return children;
	}

private:
	int size;
	std::vector<CPtr> children;
};

/**
 * class Disk
 */
class Disk : public Container
{
public:
	Disk (void)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
		name = "disk";
	}

	Disk (const Disk &d) :
		Container (d),
		device (d.device)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	virtual ~Disk()
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	virtual CPtr backup (void)
	{
		//Container::backup();
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		CPtr old (new Disk (*this));
		cd++;
		return old;
	}

	virtual void restore (void)
	{
		Container::restore();
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	static DPtr create (void)
	{
		DPtr d (new Disk);

		pool.push_back(d);

		cd++;
		return d;
	}

	std::string get_device (void)
	{
		return device;
	}

	std::string set_device (std::string value)
	{
		std::string old = device;
		device = value;
		changed();
		return old;
	}

private:
	std::string device;
};

/**
 * class Partition
 */
class Partition : public Container
{
public:
	Partition (void) :
		id(0)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
		name = "partition";
	}

	virtual ~Partition()
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	Partition (const Partition &p) :
		Container (p),
		id (p.id)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	virtual CPtr backup (void)
	{
		//Container::backup();
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		CPtr old (new Partition (*this));
		cp++;
		return old;
	}

	virtual void restore (void)
	{
		Container::restore();
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	static PPtr create (void)
	{
		PPtr p (new Partition);

		pool.push_back(p);

		cp++;
		return p;
	}

	int get_id (void)
	{
		return id;
	}

	int set_id (int value)
	{
		int old = id;
		id = value;
		changed();
		return old;
	}

private:
	int id;
};

/**
 * class Filesystem
 */
class Filesystem : public Container
{
public:
	Filesystem (void)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
		name = "filesystem";
	}

	virtual ~Filesystem()
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	Filesystem (const Filesystem &f) :
		Container (f),
		label (f.label)
	{
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	virtual CPtr backup (void)
	{
		//Container::backup();
		std::cout << __PRETTY_FUNCTION__ << std::endl;

		CPtr old (new Filesystem (*this));
		cf++;
		return old;
	}

	virtual void restore (void)
	{
		Container::restore();
		std::cout << __PRETTY_FUNCTION__ << std::endl;
	}

	static FPtr create (void)
	{
		FPtr f (new Filesystem);

		pool.push_back(f);

		cf++;
		return f;
	}

	std::string get_label (void)
	{
		return label;
	}

	std::string set_label (const std::string &value)
	{
		std::string old = label;
		label = value;
		changed();
		return old;
	}

private:
	std::string label;
};


/**
 * execute_command
 */
unsigned int
execute_command (const std::string &command, std::string &input)
{
	FILE *file = nullptr;
	int count = 0;

	file = popen (command.c_str(), "we");
	if (file == nullptr) {
		printf ("popen failed");
		return -1;
	}

	count = fprintf (file, "%s\n", input.c_str());

	if (pclose (file) == -1) {
		printf ("pclose failed");
		return -1;
	}

	return count;
}


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
		if (name == "disk")
			colour = "#ffc0c0";	// red
		else if (name == "partition")
			colour = "#d0d080";	// yellow
		else if (name == "filesystem")
			colour = "#80c080";	// green
		else
			colour = "#c0c0c0";	// grey

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
 * display_pool
 */
void
display_pool (int offset)
{
	if (pool.size() == 0)
		return;

	std::stringstream dot;

	dot << "digraph disks {\n";
	dot << "graph [ rankdir=\"LR\", color=\"white\",bgcolor=\"#000000\" ];\n";
	dot << "node [ shape=\"record\", color=\"black\", fillcolor=\"lightcyan\", style=\"filled\" ];\n";
	dot << "edge [ penwidth=3.0,color=\"#cccccc\" ];\n";
	dot << "\n";

	for (auto p : pool) {
		std::string name = p->name;
		if (name.empty())
			continue;

		dot << "\n";
		dot << "// " << p << "\n";

		std::string colour;
		if (name == "disk")
			colour = "#ffc0c0";
		else if (name == "partition")
			colour = "#d0d080";
		else
			colour = "#80c080";

		dot << "obj_" << p << " [fillcolor=\"" << colour << "\",label=<<table cellspacing=\"0\" border=\"0\">\n";
		dot << "<tr><td align=\"left\" colspan=\"3\"><font color=\"#000000\" point-size=\"16\"><b>" << p << "</b></font> (" << p->get_seqnum() << ")</td></tr>\n";
		dot << "</table>>];\n";
	}

	dot << "\n}";
	dot << "\n";

	std::string input = dot.str();
	//std::cout << input << std::endl;

	int screen_x = -1-(offset*400);

	std::string command = "dot -Tpng | display -title objects -gravity NorthEast -geometry " + std::to_string(screen_x) + "+0 -resize 70% - &";

	execute_command (command, input);
}


/**
 * display_tl_instance
 */
std::string display_tl_instance (const CPtr &c)
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
	if (name == "disk")
		colour = "#ffc0c0";	// red
	else if (name == "partition")
		colour = "#d0d080";	// yellow
	else if (name == "filesystem")
		colour = "#80c080";	// green
	else
		colour = "#c0c0c0";	// grey

	dot << "obj_" << c << " [fillcolor=\"" << colour << "\",label=<<table cellspacing=\"0\" border=\"0\"><tr><td>\n";
	dot << "<font point-size=\"16\"><b>" << (char)toupper(name[0]) << "</b></font> (" << c.use_count() << ")</td></tr><tr><td>\n";
	dot << "<font point-size=\"10\">" << c << "</font></td></tr></table>\n";
	dot << ">];\n";

	for (auto const &child : c->get_children()) {
		dot << display_tl_instance (child);
		dot << "obj_" << c << " -> obj_" << child << ";\n";
	}

	return dot.str();
}

/**
 * display_timeline
 */
void
display_timeline (const Timeline &tl)
{
	if (tl.timeline.size() == 0)
		return;

	std::stringstream dot;
	std::string desc;
	int count = 1;

	dot << "digraph disks {\n";
	dot << "graph [ rankdir=\"TB\", color=\"white\",bgcolor=\"#000000\" ];\n";
	dot << "node [ shape=\"record\", color=\"black\", fillcolor=\"lightcyan\", style=\"filled\" ];\n";
	dot << "edge [ penwidth=3.0,color=\"#cccccc\" ];\n";
	dot << "\n";

	for (auto t : tl.timeline) {
		CPtr c;

		std::tie (std::ignore, c, desc) = t;

		if (!c) {
			std::cout << "empty ptr\n";
			continue;
		}

		dot << "subgraph cluster_" << count++ << " { color=red;\n";
		dot << "fontcolor = \"white\";\n";
		dot << "label = \"" + desc + "\";\n";
		dot << display_tl_instance (c);
		dot << "}\n";
	}

	dot << "\n}";
	dot << "\n";

	std::string input = dot.str();
	//std::cout << input << std::endl;

	int offset = 0;
	int screen_x = -1-(offset*400);

	std::string command = "dot -Tpng | display -title \"timeline:" + std::to_string(count-1) + "\" -gravity NorthEast -geometry " + std::to_string(screen_x) + "+0 -resize 80% - &";

	execute_command (command, input);
}


/**
 * main
 */
int main (int, char *[])
{
	CPtr c  = Container::create();

	DPtr d  = Disk::create();
	PPtr p1 = Partition::create();
	PPtr p2 = Partition::create();
	FPtr f1 = Filesystem::create();
	FPtr f2 = Filesystem::create();

	d->set_size   (1234);
	d->set_device ("/dev/loop0");

	p1->set_size   (632);
	p1->set_id     (2);

	p2->set_size   (243);
	p2->set_id     (4);

	f1->set_size   (630);
	f1->set_label  ("wibble");

	f2->set_size   (240);
	f2->set_label  ("hatstand");

	Timeline tl;
	CPtr old;

	old = c->backup();
	tl.push (Action(c, old, "add disk"));
	c->add_child (d);

	old = d->backup();
	tl.push (Action(c, old, "add partition"));
	d->add_child (p1);

	old = p1->backup();
	tl.push (Action(c, old, "add filesystem"));
	p1->add_child (f1);

	old = d->backup();
	tl.push (Action(c, old, "add sibling"));
	d->add_child (p2);
	p2->add_child (f2);

	old = f2->backup();
	tl.push (Action(c, old, "set label"));
	f2->set_label ("new label");

	std::cout << "count:\n"
		<< "\t" << cc << "\tcontainers\n"
		<< "\t" << cd << "\tdisks\n"
		<< "\t" << cp << "\tpartitions\n"
		<< "\t" << cf << "\tfilesystems\n";

	display_dot (c, 1, "objects");

	tl.dump();
	display_timeline (tl);

	return 0;
}


