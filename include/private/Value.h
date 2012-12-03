/* Copyleft (ɔ) meh. - http://meh.schizofreni.co
 *
 * This file is part of beard - https://github.com/carthy/beard
 *
 * beard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * beard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with beard. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef BEARD_VALUE_H
#define BEARD_VALUE_H

#include <public/Value.h>

struct GC;

struct Value {
	ValueType  type;
	struct GC* gc;
};

#define IS_NIL(v)      ((v) == (Value*) 0)
#define IS_FALSE(v)    ((v) == (Value*) 2 || IS_NIL(v))
#define IS_TRUE(v)     (!IS_FALSE(v))
#define IS_BOOLEAN(v)  ((v) == (Value*) 1 || (v) == (Value*) 2)
#define IS_INTEGER(v)  (!(IS_NIL(v) || IS_BOOLEAN(v)) && ((v)->type == VALUE_TYPE_INTEGER))
#define IS_FLOATING(v) (!(IS_NIL(v) || IS_BOOLEAN(v)) && ((v)->type == VALUE_TYPE_FLOATING))
#define IS_RATIONAL(v) (!(IS_NIL(v) || IS_BOOLEAN(v)) && ((v)->type == VALUE_TYPE_RATIONAL))
#define IS_REGEXP(v)   (!(IS_NIL(v) || IS_BOOLEAN(v)) && ((v)->type == VALUE_TYPE_REGEXP))
#define IS_STRING(v)   (!(IS_NIL(v) || IS_BOOLEAN(v)) && ((v)->type == VALUE_TYPE_STRING))
#define IS_LIST(v)     (!(IS_NIL(v) || IS_BOOLEAN(v)) && ((v)->type == VALUE_TYPE_LIST))
#define IS_VECTOR(v)   (!(IS_NIL(v) || IS_BOOLEAN(v)) && ((v)->type == VALUE_TYPE_VECTOR))
#define IS_MAP(v)      (!(IS_NIL(v) || IS_BOOLEAN(v)) && ((v)->type == VALUE_TYPE_MAP))

#endif
