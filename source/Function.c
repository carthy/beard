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
#include <private/Function.h>
#include <private/common.h>

Function*
Function_new (Runtime* rt)
{
	Function* self = (Function*) GC_ALLOCATE(rt, VALUE_TYPE_FUNCTION);

	self->array = NULL;

	self->rest.first   = 0;
	self->rest.address = 0;

	return self;
}

Function*
Function_add (Function* self, long arity, intptr_t address)
{
	assert(address);
	assert(!FUNCTION_HAS_REST(self));

	Word_t  ind = arity;
	Word_t* val = NULL;

	JLG(val, self->array, ind);
	assert(val == NULL);

	JLI(val, self->array, ind);
	*val = address;

	return self;
}

Function*
Function_add_rest (Function* self, long first, intptr_t address)
{
	assert(address);
	assert(!FUNCTION_HAS_REST(self));

	self->rest.first   = first;
	self->rest.address = address;
	
	return self;
}

intptr_t
Function_address_by_arity (Function* self, long arity)
{
	if (FUNCTION_HAS_REST(self)) {
		if (arity >= self->rest.first) {
			return self->rest.address;
		}
	}

	Word_t  ind = arity;
	Word_t* val = NULL;

	JLG(val, self->array, ind);

	return (val == NULL) ? 0 : (intptr_t) *val;
}
