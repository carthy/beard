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

#include <private/Runtime.h>
#include <public/Tuple.h>
#include <public/Vector.h>
#include <private/Map.h>
#include <private/common.h>

Map* Map_new (Runtime* rt)
{
	Map* self = (Map*) GC_ALLOCATE(rt, MAP);

	self->array = NULL;

	return self;
}

void
Map_destroy (Map* self)
{
	Word_t freed;

	JLFA(freed, self->array);
}

bool
Map_has (Map* self, uint64_t hash)
{
	Word_t  ind = hash;
	Word_t* val = NULL;

	JLG(val, self->array, ind);

	return val != NULL;
}

Tuple*
Map_put (Map* self, uint64_t hash, Value* key, Value* value)
{
	return Map_put_tuple(self, hash, Tuple_new_with(RUNTIME_FOR(self), key, value));
}

Tuple*
Map_put_tuple (Map* self, uint64_t hash, Tuple* pair)
{
	Word_t  ind = hash;
	Word_t* val = NULL;
	
	JLI(val, self->array, ind);
	assert(val);

	*val = (Word_t) pair;

	return pair;
}

Value*
Map_get_value (Map* self, uint64_t hash)
{
	return Tuple_get(Map_get_tuple(self, hash), 1);
}

Value*
Map_get_key (Map* self, uint64_t hash)
{
	return Tuple_get(Map_get_tuple(self, hash), 0);
}

Tuple*
Map_get_tuple (Map* self, uint64_t hash)
{
	Word_t  ind = hash;
	Word_t* val = NULL;

	JLG(val, self->array, ind);
	assert(val);

	return (Tuple*) *val;
}

Tuple*
Map_delete (Map* self, uint64_t hash)
{
	Word_t  ind = hash;
	Word_t  res = 0;
	Word_t* val = NULL;

	JLG(val, self->array, ind);
	JLD(res, self->array, ind);

	assert(res == 1);

	return (Tuple*) *val;
}

Vector*
Map_tuples (Map* self)
{
	Vector* result = Vector_new(RUNTIME_FOR(self));
	Word_t  size   = 0;
	Word_t  index  = 0;
	Word_t* value  = NULL;

	JLC(size, self->array, 0, -1);
	Vector_resize(result, size);

	JLF(value, self->array, index);
	for (uint64_t i = 0; value != NULL; i++) {
		Vector_set(result, i, (Value*) *value);

		JLN(value, self->array, index);
	}

	return result;
}

Vector*
Map_keys (Map* self)
{
	Vector* result = Map_tuples(self);

	for (uint64_t i = 0, length = Vector_length(result); i < length; i++) {
		Vector_set(result, i, Tuple_get((Tuple*) Vector_get(result, i), 0));
	}

	return result;
}

Vector*
Map_values (Map* self)
{
	Vector* result = Map_tuples(self);

	for (uint64_t i = 0, length = Vector_length(result); i < length; i++) {
		Vector_set(result, i, Tuple_get((Tuple*) Vector_get(result, i), 1));
	}

	return result;
}

uint64_t
Map_length (Map* self)
{
	Word_t size;

	JLC(size, self->array, 0, -1);

	return size;
}
