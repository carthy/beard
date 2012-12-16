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

#include <private/common.h>

#include <private/Runtime.h>
#include <private/Integer.h>
#include <private/Floating.h>
#include <private/Rational.h>

Rational*
Rational_new (Runtime* rt)
{
	assert(rt);

	Rational* self = (Rational*) GC_ALLOCATE(rt, RATIONAL);

	self->value = GC_NEW_RATIONAL(rt);

	return self;
}

Rational*
(Rational_set_native) (Rational* self, long numerator, long denominator)
{
	assert(self);
	assert(denominator != 0);

	if (denominator < 0) {
		mpq_set_si(*self->value, -numerator, -denominator);
	}
	else {
		mpq_set_si(*self->value, numerator, denominator);
	}

	return self;
}

Rational*
(Rational_set_integer) (Rational* self, Integer* numerator, Integer* denominator)
{
	assert(self);
	assert(numerator);
	assert(denominator);

	if (IS_NIL(denominator)) {
		if (INTEGER_IS_GMP(numerator)) {
			mpq_set_z(*self->value, *INTEGER_GET_GMP(numerator));
		}
		else {
			mpq_set_si(*self->value, INTEGER_GET_NATIVE(numerator), 1);
		}

		return self;
	}

	if (INTEGER_IS_NATIVE(numerator)) {
		if (INTEGER_IS_NATIVE(denominator)) {
			assert(INTEGER_GET_NATIVE(denominator) != 0);

			if (INTEGER_GET_NATIVE(denominator) < 0) {
				mpq_set_si(*self->value, -INTEGER_GET_NATIVE(numerator), -INTEGER_GET_NATIVE(denominator));
			}
			else {
				mpq_set_si(*self->value, INTEGER_GET_NATIVE(numerator), INTEGER_GET_NATIVE(denominator));
			}
		}
		else {
			mpq_t* tmp = GC_NEW_RATIONAL(RUNTIME_FOR(self));

			mpq_set_si(*self->value, INTEGER_GET_NATIVE(numerator), 1);
			mpq_set_z(*tmp, *INTEGER_GET_GMP(denominator));
			mpq_div(*self->value, *self->value, *tmp);

			GC_SAVE_RATIONAL(RUNTIME_FOR(self), tmp);
		}
	}
	else {
		if (INTEGER_IS_NATIVE(denominator)) {
			mpq_t* tmp = GC_NEW_RATIONAL(RUNTIME_FOR(self));

			mpq_set_si(*self->value, INTEGER_GET_NATIVE(denominator), 1);
			mpq_set_z(*tmp, *INTEGER_GET_GMP(numerator));
			mpq_div(*self->value, *tmp, *self->value);

			GC_SAVE_RATIONAL(RUNTIME_FOR(self), tmp);
		}
		else {
			mpq_t* tmp = GC_NEW_RATIONAL(RUNTIME_FOR(self));

			mpq_set_z(*self->value, *INTEGER_GET_GMP(numerator));
			mpq_set_z(*tmp, *INTEGER_GET_GMP(denominator));
			mpq_div(*self->value, *self->value, *tmp);

			GC_SAVE_RATIONAL(RUNTIME_FOR(self), tmp);
		}
	}

	return self;
}

Rational*
Rational_set_string (Rational* self, const char* string)
{
	assert(self);
	assert(string);

	mpq_set_str(*self->value, string, 0);

	return self;
}

Rational*
Rational_set_string_with_base (Rational* self, const char* string, int base)
{
	assert(self);
	assert(string);

	mpq_set_str(*self->value, string, base);

	return self;
}

void
Rational_destroy (Rational* self)
{
	GC_SAVE_RATIONAL(RUNTIME_FOR(self), self->value);
}

Integer*
Rational_numerator (Rational* self)
{
	mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));
	mpz_set(*value, mpq_numref(*self->value));

	return Integer_set_gmp(Integer_new(RUNTIME_FOR(self)), value);
}

Integer*
Rational_denominator (Rational* self)
{
	mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));
	mpz_set(*value, mpq_denref(*self->value));

	return Integer_set_gmp(Integer_new(RUNTIME_FOR(self)), value);
}

bool
Rational_eq (Rational* self, Value* other)
{
	return NIL;
}

bool
Rational_lt (Rational* self, Value* other)
{
	return NIL;
}

bool
Rational_gt (Rational* self, Value* other)
{
	return NIL;
}

Value*
Rational_add (Rational* self, Value* number)
{
	return NIL;
}

Value*
Rational_sub (Rational* self, Value* other)
{
	return NIL;
}

Value*
Rational_mul (Rational* self, Value* other)
{
	return NIL;
}

Value*
Rational_div (Rational* self, Value* other)
{
	return NIL;
}
