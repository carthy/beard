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

Value*
Map_put (Map* self, uint64_t key, Value* value)
{
	Word_t  ind = key;
	Word_t* val = NULL;
	
	JLI(val, self->array, ind);
	assert(val);

	*val = (Word_t) value;

	return value;
}

Value*
Map_get (Map* self, uint64_t key)
{
	Word_t  ind = key;
	Word_t* val = NULL;

	JLG(val, self->array, ind);

	assert(val);

	return (Value*) *val;
}

uint64_t
Map_length (Map* self)
{
	Word_t size;

	JLC(size, self->array, 0, -1);

	return size;
}
