/* Copyright (c) 2013 Richard Russon (FlatCap);
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

#ifndef _DOT_H_
#define _DOT_H_

#include <string>
#include <vector>

#include "pointers.h"

std::string dot_row (const char *name, bool value);
std::string dot_row (const char *name, int value);
std::string dot_row (const char *name, long value);
std::string dot_row (const char *name, const std::string &value);
std::string dot_row (const char *name, const std::stringstream &value);
std::string dot_row (const char *name, const char *value);
std::string dot_row (const char *name, unsigned int value);
std::string dot_row (const char *name, void *value);
std::string dot_row (const char *name, const CPtr &value);

std::string dot_container (const CPtr &c);
std::string dot_disk (const CPtr &c);
std::string dot_partition (const CPtr &c);
std::string dot_filesystem (const CPtr &c);
std::string dump_dot_inner (const std::vector <CPtr> &v);
std::string dump_dot (const std::vector <CPtr> &v);

void display_dot (const CPtr c, int offset, const std::string &title);
std::string dump_dot_small (const CPtr &c);

#endif // _DOT_H_

