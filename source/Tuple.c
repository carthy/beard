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

Tuple* Tuple_new (Runtime* rt)
{
	Tuple* self = (Tuple*) GC_ALLOCATE(rt, VALUE_TYPE_TUPLE);

	self->size  = 0;
	self->items = NULL;

	return self;
}

Tuple* Tuple_new_with_size (Runtime* rt, int size)
{
	Tuple* self = Tuple_new(rt);

	return Tuple_resize(self, size);
}

void
Tuple_destroy (Tuple* self)
{
	if (self->items) {
		free(self->items);
	}
}

Tuple*
Tuple_resize (Tuple* self, int size)
{
	assert(self);
	assert(size != self->size);

	self->items = realloc(self->items, size * sizeof(Value*));

	if (size > self->size) {
		memset(self->items + self->size, 0, (size - self->size) * sizeof(Value*));
	}

	self->size = size;

	return self;
}

Value**
Tuple_items (Tuple* self)
{
	return self->items;
}

int
Tuple_size (Tuple* self)
{
	return self->size;
}
