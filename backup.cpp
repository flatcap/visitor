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

#include <unistd.h>

class Container;

typedef std::shared_ptr<Container> CPtr;

std::vector<CPtr> pool;

/**
 * class Backup
 */
class Backup
{
public:
	void backup (void);
	void restore (void);
};

/**
 * class Container
 */
class Container : public Backup
{
public:
	Container (void) :
		size(0),
		seqnum(1)
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
		name = "Container";
	}

	virtual ~Container()
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
		for (auto c : children) {
			//std::cout << "delete " << c << "(" << c->name << ")" << std::endl;
			delete c;
		}
	}

	void *
	operator new (size_t size)
	{
		Container *c = (Container*) malloc (size);

		std::cout << "new object " << c << std::endl;

		pool.push_back(CPtr(c));

		return c;
	}

	void
	operator delete (void *ptr)
	{
		if (!ptr)
			return;

		Container *c = (Container *) (ptr);

		std::cout << "delete object " << c << std::endl;

		free (ptr);
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

	int get_seqnum (void)
	{
		return seqnum;
	}

	int add_child (Container *child)
	{
		children.push_back (child);
		changed();
		return children.size();
	}

	std::string name;

	std::vector<Container*> get_children (void)
	{
		return children;
	}

protected:
	void changed (void)
	{
		seqnum++;
	}

private:
	int size;
	int seqnum;
	std::vector<Container*> children;
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

	virtual ~Disk()
	{
		//std::cout << __PRETTY_FUNCTION__ << std::endl;
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

/**
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
 * dot_row (Container *)
 */
std::string
dot_row (const char *name, Container *value)
{
	std::stringstream output;
	std::string dest;

	output << "<tr>";
	output << "<td align=\"left\">" << name << "</td>";
	output << "<td>=</td>";
	if (value) {
		output << "<td align=\"left\">" << (void*) value << dest << "</td>";
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
dot_container (Container *c)
{
	std::stringstream output;

	output << dot_row ("size",   c->get_size());
	output << dot_row ("seqnum", c->get_seqnum());

	return output.str();
}


/**
 * dot_disk
 */
std::string
dot_disk (Disk *d)
{
	std::stringstream output;

	output << dot_container (dynamic_cast<Container *> (d));

	output << dot_row ("device", d->get_device());

	return output.str();
}

/**
 * dot_partition
 */
std::string
dot_partition (Partition *p)
{
	std::stringstream output;

	output << dot_container(dynamic_cast<Partition *> (p));

	output << dot_row ("id", p->get_id());

	return output.str();
}

/**
 * dot_filesystem
 */
std::string
dot_filesystem (Filesystem *f)
{
	std::stringstream output;

	output << dot_container(dynamic_cast<Container *> (f));

	output << dot_row ("label", f->get_label());

	return output.str();
}


/**
 * dump_dot_inner
 */
std::string
dump_dot_inner (const std::vector <Container*> &v)
{
	std::stringstream dot;

	for (auto c : v) {
		std::string name = c->name;

		dot << "\n";
		dot << "// " << c << "\n";

		std::string colour;
		if (name == "disk")
			colour = "#ffc0c0";
		else if (name == "partition")
			colour = "#80c080";
		else
			colour = "#d0d080";

		dot << "obj_" << (void*) c << " [fillcolor=\"" << colour << "\",label=<<table cellspacing=\"0\" border=\"0\">\n";
		dot << "<tr><td align=\"left\" bgcolor=\"white\" colspan=\"3\"><font color=\"#000000\" point-size=\"20\"><b>" << c->name << "</b></font> (" << (void*) c << ")</td></tr>\n";

		     if (name == "disk")          { dot << dot_disk          (dynamic_cast<Disk         *> (c)); }
		else if (name == "filesystem")    { dot << dot_filesystem    (dynamic_cast<Filesystem   *> (c)); }
		else if (name == "partition")     { dot << dot_partition     (dynamic_cast<Partition    *> (c)); }

		dot << "</table>>];\n";

		for (auto c2 : c->get_children()) {
			dot << "obj_" << (void*) c << " -> obj_" << (void*) c2 << ";\n";
		}

		dot << dump_dot_inner (c->get_children());
	}

	return dot.str();
}

/**
 * dump_dot
 */
std::string
dump_dot (std::vector <Container*> v)
{
	std::stringstream dot;

	dot << "digraph disks {\n";
	dot << "graph [ rankdir=\"TB\", color=\"white\",bgcolor=\"#000000\" ];\n";
	dot << "node [ shape=\"record\", color=\"black\", fillcolor=\"lightcyan\", style=\"filled\" ];\n";
	dot << "edge [ penwidth=3.0,color=\"#cccccc\" ];\n";
	dot << "\n";

	dot << dump_dot_inner (v);

	dot << "\n}";
	dot << "\n";

	return dot.str();
}

/**
 * display_dot
 */
void
display_dot (std::vector <Container*> v)
{
	if (v.size() == 0)
		return;

	std::string input = dump_dot(v);
	//std::cout << input << std::endl;

	execute_command ("dot -Tpng | display -resize 60% - &", input);
}


/**
 * main
 */
int main (int, char *[])
{
	std::vector <Container*> v;

	Disk       *d = new Disk();
	Partition  *p = new Partition();
	Filesystem *f = new Filesystem();

	d->set_size   (1234);
	d->set_device ("/dev/loop0");

	p->set_size   (632);
	p->set_id     (3);

	f->set_size   (630);
	f->set_label  ("wibble");

	v.push_back (d);
	d->add_child (p);
	p->add_child (f);

#if 0
	std::cout
		<< d << "(" << d->name << "), "
		<< p << "(" << p->name << "), "
		<< f << "(" << f->name << ")\n";
#endif

	display_dot (v);

	//std::cout << "delete " << d << "(" << d->name << ")" << std::endl;
	//delete d;

	return 0;
}


