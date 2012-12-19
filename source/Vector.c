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
#include <private/Vector.h>
#include <private/common.h>

Vector* Vector_new (Runtime* rt)
{
	Vector* self = (Vector*) GC_ALLOCATE(rt, VECTOR);

	self->items  = NULL;
	self->length = 0;

	return self;
}

void
Vector_destroy (Vector* self)
{
	if (self->items) {
		free(self->items);
	}
}

Vector*
Vector_resize (Vector* self, uint64_t length)
{
	if (length > self->length) {
		self->items = realloc(self->items, length * sizeof(Value*));

		memset(self->items + length, 0, (length - self->length) * sizeof(Value*));
	}
	else {
		self->items = realloc(self->items, length * sizeof(Value*));
	}

	self->length = length;

	return self;
}

Value*
Vector_set (Vector* self, uint64_t index, Value* value)
{
	assert(index < Vector_length(self));

	self->items[index] = value;

	return value;
}

Value*
Vector_get (Vector* self, uint64_t index)
{
	assert(index < Vector_length(self));

	return self->items[index];
}

Value**
Vector_items (Vector* self)
{
	assert(self);

	return self->items;
}

Vector*
Vector_insert (Vector* self, Value* value, uint64_t index)
{
	assert(self);
	assert(index == 0 || index <= self->length);

	self->items = realloc(self->items, (self->length + 1) * sizeof(Value*));
	memmove(self->items + index + 1, self->items + index, (self->length - index) * sizeof(Value*));

	self->length++;
	self->items[index] = value;

	return self;
}

Vector*
Vector_insert_first (Vector* self, Value* value)
{
	return Vector_insert(self, value, 0);
}

Vector*
Vector_insert_last (Vector* self, Value* value)
{
	return Vector_insert(self, value, self->length);
}

uint64_t
Vector_length (Vector* self)
{
	assert(self);

	return self->length;
}
