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

#include <private/GC.h>
#include <private/Floating.h>
#include <public/Integer.h>
#include <public/Rational.h>
#include <private/common.h>

Floating*
Floating_new (GC* gc)
{
	Floating* self = (Floating*) GC_allocate(gc, VALUE_TYPE_FLOATING);

	self->value = GC_get_floating(self->descriptor.gc);

	return self;
}

Floating*
Floating_new_with_precision (GC* gc, unsigned long precision)
{
	return Floating_set_precision(Floating_new(gc), precision);
}

Floating*
Floating_set_precision (Floating* self, unsigned long precision)
{
	mpf_set_prec(*self->value, precision);

	return self;
}

unsigned long
Floating_get_precision (Floating* self)
{
	return mpf_get_prec(*self->value);
}

Floating*
Floating_set_double (Floating* self, double number)
{
	assert(self);

	mpf_set_d(*(self->value), number);

	return self;
}

Floating*
Floating_set_string (Floating* self, const char* string)
{
	assert(self);

	mpf_set_str(*(self->value), string, 0);

	return self;
}

Floating*
Floating_set_string_with_base (Floating* self, const char* string, int base)
{
	assert(self);

	mpf_set_str(*(self->value), string, base);

	return self;
}

Floating*
Floating_plus (Floating* self, Value* other)
{
	return NIL;
}
