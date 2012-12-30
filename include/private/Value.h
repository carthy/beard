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
#include <public/Runtime.h>

struct Value {
	ValueType type   : 8;
	bool      frozen : 1;

	struct Runtime* runtime;
};

#define IS_NIL(v)      (((Value*) v) == (Value*) 0)
#define IS_TRUE(v)     (((Value*) v) == (Value*) 1)
#define IS_FALSE(v)    (((Value*) v) == (Value*) 2)
#define IS_BOOLEAN(v)  (IS_TRUE(v) || IS_FALSE(v))
#define IS_INTEGER(v)  (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_INTEGER))
#define IS_FLOATING(v) (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_FLOATING))
#define IS_RATIONAL(v) (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_RATIONAL))
#define IS_COMPLEX(v)  (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_COMPLEX))
#define IS_REGEXP(v)   (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_REGEXP))
#define IS_STRING(v)   (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_STRING))
#define IS_BITMAP(v)   (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_BITMAP))
#define IS_TUPLE(v)    (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_TUPLE))
#define IS_VECTOR(v)   (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_VECTOR))
#define IS_MAP(v)      (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_MAP))
#define IS_FUNCTION(v) (!(IS_NIL(v) || IS_BOOLEAN(v)) && (((Value*) (v))->type == VALUE_TYPE_FUNCTION))

#define IS_FALSY(v)  (IS_NIL(v) || IS_FALSE(v))
#define IS_TRUTHY(v) (!IS_FALSY(v))

#define IS_FROZEN(v) (((Value*) (v))->frozen)

#endif
