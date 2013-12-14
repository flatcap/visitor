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

#ifndef _CONTAINER_H_
#define _CONTAINER_H_

#include <map>
#include <set>
#include <string>
#include <vector>

#include "pointers.h"
#include "variant.h"

/**
 * class Container
 */
class Container
{
public:
	static CPtr create (void);
	Container (Container&& c);
	virtual ~Container() = default;

	Container& operator= (const Container& c);
	Container& operator= (Container&& c);

	void swap (Container& c);
	friend void swap (Container& lhs, Container& rhs);

	CPtr copy (void) const;

	int add_child (CPtr child);
	void remove_child (size_t index);

	const std::vector<CPtr>& get_children (void);

	std::string name;

	int get_seqnum (void);

	void set_type (std::string&& name)
	{
		type.insert (std::move (name));
	}

	void set_prop (const std::string &name, Variant value)
	{
		std::cout << "new prop: " << name << " = " << (std::string) value << std::endl;
		props[name] = std::move (value);
	}

	void dump_props(void) {
		std::cout << "Properties:\n";
		for (auto p : props) {
			std::cout << '\t' << p.first << " = " << (std::string) p.second << '\n';
		}
	}

#if 0
	const Variant& get_prop (const std::string& name) const
	{
		if (props.count (name) == 0)
			throw "bugger";

		auto& p = const_cast<std::map<std::string,Variant>&>(props);

		return p[name];
	}
#endif
	Variant& get_prop (const std::string& name)
	{
		if (props.count (name) == 0)
			throw "bugger";

		return props[name];
	}

	friend std::ostream & operator<< (std::ostream &stream, const CPtr &c);

protected:
	Container (void);
	Container (const Container& c);

	virtual Container* clone (void) const;

	void changed (void);

	std::weak_ptr<Container> weak;

private:
	std::vector<CPtr> children;
	std::map<std::string,Variant> props;
	std::set<std::string> type;

	int seqnum = 1;
};


#endif // _CONTAINER_H_

