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

Tuple* Tuple_new (Runtime* rt, int size)
{
	Tuple* self = (Tuple*) GC_ALLOCATE(rt, TUPLE);

	self->size  = size;
	self->items = malloc(size * sizeof(Value*));

	memset(self->items, 0, size * sizeof(Value*));

	return self;
}

void
Tuple_destroy (Tuple* self)
{
	if (self->items) {
		free(self->items);
	}
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
