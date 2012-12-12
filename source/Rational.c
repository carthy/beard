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
#include <private/Rational.h>
#include <private/Integer.h>
#include <private/Floating.h>
#include <private/common.h>

Rational*
Rational_new (Runtime* rt)
{
	assert(rt);

	Rational* self = (Rational*) GC_ALLOCATE(rt, VALUE_TYPE_RATIONAL);

	self->value = GC_NEW_RATIONAL(rt);

	return self;
}

void
Rational_destroy (Rational* self)
{
	GC_SAVE_RATIONAL(RUNTIME_FOR(self), self->value);
}

Rational*
Rational_add (Rational* self, Value* other)
{
	return NIL;
}

Rational*
Rational_sub (Rational* self, Value* other)
{
	return NIL;
}

Rational*
Rational_minus (Rational* self, Value* other)
{
	return NIL;
}
