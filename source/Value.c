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

#include <private/common.h>
#include <private/Value.h>

#include <public/Integer.h>
#include <public/Floating.h>
#include <public/Rational.h>
#include <public/String.h>
#include <public/Tuple.h>
#include <public/Vector.h>
#include <public/Map.h>

bool
is_nil (Value* self)
{
	return IS_NIL(self);
}

bool
is_false (Value* self)
{
	return IS_FALSE(self);
}

bool
is_true (Value* self)
{
	return IS_TRUE(self);
}

bool
is_boolean (Value* self)
{
	return IS_BOOLEAN(self);
}

bool
is_integer (Value* self)
{
	return IS_INTEGER(self);
}

bool
is_floating (Value* self)
{
	return IS_FLOATING(self);
}

bool
is_rational (Value* self)
{
	return IS_RATIONAL(self);
}

bool
is_complex (Value* self)
{
	return IS_COMPLEX(self);
}

bool
is_regexp (Value* self)
{
	return IS_REGEXP(self);
}

bool
is_string (Value* self)
{
	return IS_STRING(self);
}

bool
is_tuple (Value* self)
{
	return IS_TUPLE(self);
}

bool
is_vector (Value* self)
{
	return IS_VECTOR(self);
}

bool
is_map (Value* self)
{
	return IS_MAP(self);
}

bool
is_function (Value* self)
{
	return IS_FUNCTION(self);
}

bool
is_falsy (Value* self)
{
	return IS_FALSY(self);
}

bool
is_truthy (Value* self)
{
	return IS_TRUTHY(self);
}

ValueType
type_of (Value* self)
{
	if (IS_NIL(self)) {
		return VALUE_TYPE_NIL;
	}
	else if (IS_BOOLEAN(self)) {
		return VALUE_TYPE_BOOLEAN;
	}
	else {
		return self->type;
	}
}

uint64_t
hash_for (Value* value)
{
	if (IS_NIL(value) || IS_BOOLEAN(value)) {
		return (uint64_t) value;
	}
	else {
		switch (value->type) {
			case VALUE_TYPE_INTEGER:
				return Integer_hash((Integer*) value);

			case VALUE_TYPE_FLOATING:
				return Floating_hash((Floating*) value);

			case VALUE_TYPE_RATIONAL:
				return Rational_hash((Rational*) value);

			case VALUE_TYPE_STRING:
				return String_hash((String*) value);

			case VALUE_TYPE_TUPLE:
				return Tuple_hash((Tuple*) value);

			case VALUE_TYPE_VECTOR:
				return Vector_hash((Vector*) value);

			case VALUE_TYPE_MAP:
				return Map_hash((Map*) value);

			default:
				assert(false);
		}
	}
}
