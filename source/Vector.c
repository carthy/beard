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
	Vector* self = (Vector*) GC_ALLOCATE(rt, VALUE_TYPE_VECTOR);

	self->array = NULL;

	return self;
}

void
Vector_destroy (Vector* self)
{
	Word_t freed;

	JLFA(freed, self->array);
}

Value*
Vector_set (Vector* self, uint64_t index, Value* value)
{
	if (Vector_length(self) <= index) {
		assert(false);
	}

	Word_t  ind = index;
	Word_t* val = NULL;
	
	JLI(val, self->array, ind);
	assert(val);

	*val = (Word_t) value;

	return value;
}

Value*
Vector_get (Vector* self, uint64_t index)
{
	if (Vector_length(self) <= index) {
		assert(false);
	}

	Word_t  ind = index;
	Word_t* val = NULL;

	JLG(val, self->array, ind);

	assert(val);

	return (Value*) *val;
}

Vector*
Vector_conj (Vector* self, Value* value)
{
	Word_t  ind = Vector_length(self);
	Word_t* val = NULL;

	JLI(val, self->array, ind);
	assert(val);

	*val = (Word_t) value;

	return self;
}

uint64_t
Vector_length (Vector* self)
{
	Word_t size;

	JLC(size, self->array, 0, -1);

	return size;
}
