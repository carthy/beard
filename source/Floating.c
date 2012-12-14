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
#include <private/Floating.h>
#include <private/Integer.h>
#include <private/Rational.h>
#include <private/common.h>

Floating*
Floating_new (Runtime* rt)
{
	Floating* self = (Floating*) GC_ALLOCATE(rt, VALUE_TYPE_FLOATING);

	self->value = NAN;

	return self;
}

Floating*
Floating_new_with_precision (Runtime* rt, unsigned long precision)
{
	Floating* self = Floating_set_double(Floating_new(rt), 0);

	Floating_set_precision(self, precision);

	return self;
}

Floating*
Floating_set_nan (Floating* self)
{
	if (FLOATING_IS_GMP(self)) {
		GC_SAVE_FLOATING(RUNTIME_FOR(self), self->value);
	}

	self->value = NAN;

	return self;
}

Floating*
Floating_set_infinity (Floating* self)
{
	if (FLOATING_IS_GMP(self)) {
		GC_SAVE_FLOATING(RUNTIME_FOR(self), self->value);
	}

	self->value = INFINITY;

	return self;
}

Floating*
Floating_set_positive_infinity (Floating* self)
{
	if (FLOATING_IS_GMP(self)) {
		GC_SAVE_FLOATING(RUNTIME_FOR(self), self->value);
	}

	self->value = POSITIVE_INFINITY;

	return self;
}

Floating*
Floating_set_negative_infinity (Floating* self)
{
	if (FLOATING_IS_GMP(self)) {
		GC_SAVE_FLOATING(RUNTIME_FOR(self), self->value);
	}

	self->value = NEGATIVE_INFINITY;

	return self;
}

unsigned long
Floating_set_precision (Floating* self, unsigned long precision)
{
	if (!FLOATING_IS_GMP(self)) {
		return 0;
	}

	mpf_set_prec(*self->value, precision);

	return precision;
}

unsigned long
Floating_get_precision (Floating* self)
{
	if (!FLOATING_IS_GMP(self)) {
		return 0;
	}

	return mpf_get_prec(*self->value);
}

Floating*
Floating_set_double (Floating* self, double number)
{
	assert(self);

	if (!FLOATING_IS_GMP(self)) {
		self->value = GC_NEW_FLOATING(RUNTIME_FOR(self));
	}

	mpf_set_d(*(self->value), number);

	return self;
}

Floating*
Floating_set_string (Floating* self, const char* string)
{
	assert(self);

	if (!FLOATING_IS_GMP(self)) {
		self->value = GC_NEW_FLOATING(RUNTIME_FOR(self));
	}

	mpf_set_str(*(self->value), string, 0);

	return self;
}

Floating*
Floating_set_string_with_base (Floating* self, const char* string, int base)
{
	assert(self);

	if (!FLOATING_IS_GMP(self)) {
		self->value = GC_NEW_FLOATING(RUNTIME_FOR(self));
	}

	mpf_set_str(*(self->value), string, base);

	return self;
}

void
Floating_destroy (Floating* self)
{
	if (FLOATING_IS_GMP(self)) {
		GC_SAVE_FLOATING(RUNTIME_FOR(self), self->value);
	}
}

bool
Floating_eq (Floating* self, Value* other)
{
	return NIL;
}

bool
Floating_lt (Floating* self, Value* other)
{
	return NIL;
}

bool
Floating_gt (Floating* self, Value* other)
{
	return NIL;
}

Floating*
Floating_add (Floating* self, Value* other)
{
	return NIL;
}

Floating*
Floating_sub (Floating* self, Value* other)
{
	return NIL;
}

bool
Floating_is_nan (Floating* self)
{
	return FLOATING_IS_NAN(self);
}

bool
Floating_is_infinity (Floating* self)
{
	return FLOATING_IS_INFINITY(self);
}

bool
Floating_is_positive_infinity (Floating* self)
{
	return FLOATING_IS_POSITIVE_INFINITY(self);
}

bool
Floating_is_negative_infinity (Floating* self)
{
	return FLOATING_IS_NEGATIVE_INFINITY(self);
}
