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
#include <private/Rational.h>
#include <public/Integer.h>
#include <public/Floating.h>
#include <private/common.h>

Rational*
Rational_new (GC* gc)
{
	Rational* self = (Rational*) GC_allocate(gc, VALUE_TYPE_RATIONAL);

	self->value = GC_get_rational(self->descriptor.gc);

	return self;
}

Rational*
Rational_plus (Rational* self, Value* other)
{
	return NIL;
}
