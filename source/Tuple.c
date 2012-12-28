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
#include <private/Tuple.h>
#include <private/common.h>

#include <stdarg.h>

Tuple*
Tuple_new (Runtime* rt, size_t size)
{
	Tuple* self = (Tuple*) GC_ALLOCATE(rt, TUPLE);

	self->size  = size;
	self->items = malloc(size * sizeof(Value*));

	memset(self->items, 0, size * sizeof(Value*));

	return self;
}

Tuple*
(Tuple_new_with) (Runtime* rt, size_t size, ...)
{
	Tuple* self = Tuple_new(rt, size);

	va_list args;
	va_start(args, size);
	for (size_t i = 0; i < size; i++) {
		self->items[i] = va_arg(args, Value*);
	}
	va_end(args);

	return self;
}

void
Tuple_destroy (Tuple* self)
{
	if (self->items) {
		free(self->items);
	}
}

Value*
Tuple_set (Tuple* self, size_t index, Value* value)
{
	assert(index < Tuple_size(self));

	self->items[index] = value;

	return value;
}

Value*
Tuple_get (Tuple* self, size_t index)
{
	assert(index < Tuple_size(self));

	return self->items[index];
}

Value**
Tuple_items (Tuple* self)
{
	return self->items;
}

size_t
Tuple_size (Tuple* self)
{
	return self->size;
}

hash_t
Tuple_hash (Tuple* self)
{
	murmur3_t* state = MURMUR3_INIT(RUNTIME_FOR(self));

	for (size_t i = 0, length = self->size; i < length; i++) {
		MURMUR3_UPDATE_WITH(state, hash_for(self->items[i]));
	}

	return MURMUR3_FINAL(state);
}
