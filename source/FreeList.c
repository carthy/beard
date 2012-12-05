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

#include <private/FreeList.h>
#include <private/common.h>

FreeList*
FreeList_new (FreeListConstructor constructor, FreeListDestructor destructor)
{
	return FreeList_new_with_limit(4096, constructor, destructor);
}

FreeList*
FreeList_new_with_limit (int limit, FreeListConstructor constructor, FreeListDestructor destructor)
{
	FreeList* self = malloc(sizeof(FreeList));

	self->array       = NULL;
	self->limit       = limit;
	self->constructor = constructor;
	self->destructor  = destructor;

	return self;
}

void
FreeList_set_limit (FreeList* self, int limit)
{
	assert(self);

	self->limit = limit;
}

int
FreeList_get_limit (FreeList* self)
{
	assert(self);

	return self->limit;
}

void
FreeList_destroy (FreeList* self)
{
	assert(self);

	Word_t  index = 0;
	Word_t* value;
	Word_t  freed;

	JLF(value, self->array, index);
	while (value) {
		self->destructor((void*) *value);

		index++;
		JLN(value, self->array, index);
	}

	JLFA(freed, self->array);
	free(self);
}

void
FreeList_put (FreeList* self, void* thing)
{
	assert(self);
	assert(thing);

	Word_t size;
	JLC(size, self->array, 0, -1);

	if (size >= self->limit) {
		self->destructor(thing);

		return;
	}

	Word_t  start = 0;
	Word_t  index;
	Word_t* value;

	JLFE(index, self->array, start);
	JLI(value, self->array, index);

	*value = (Word_t) thing;
}

void*
FreeList_get (FreeList* self)
{
	assert(self);

	Word_t  index = 0;
	Word_t* value;
	void*   thing;

	JLF(value, self->array, index);

	if (value) {
		Word_t found;
		thing = (void*) *value;

		JLD(found, self->array, index);
	}
	else {
		thing = self->constructor();
	}

	return thing;
}
