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
#include <private/Integer.h>
#include <public/Floating.h>
#include <public/Rational.h>
#include <private/common.h>

Integer*
Integer_new (Runtime* rt)
{
	Integer* self = (Integer*) GC_ALLOCATE(rt, INTEGER);

	self->type      = INTEGER_TYPE_NATIVE;
	self->as.native = 0;

	return self;
}

Integer*
Integer_set_native (Integer* self, long value)
{
	assert(self);

	if (INTEGER_IS_GMP(self) && INTEGER_GET_GMP(self)) {
		GC_SAVE_INTEGER(RUNTIME_FOR(self), INTEGER_GET_GMP(self));
	}

	self->type      = INTEGER_TYPE_NATIVE;
	self->as.native = value;

	return self;
}

Integer*
Integer_set_string (Integer* self, const char* string)
{
	assert(self);

	long value = strtol(string, NULL, 10);

	if ((value == LONG_MAX || value == LONG_MIN) && errno == ERANGE) {
		if (INTEGER_IS_NATIVE(self)) {
			self->as.gmp = GC_NEW_INTEGER(RUNTIME_FOR(self));
		}

		self->type = INTEGER_TYPE_GMP;
		mpz_set_str(*INTEGER_GET_GMP(self), string, 0);
	}
	else {
		self->type      = INTEGER_TYPE_NATIVE;
		self->as.native = value;
	}

	return self;
}

Integer*
Integer_set_string_with_base (Integer* self, const char* string, int base)
{
	assert(self);

	long value = strtol(string, NULL, base);

	if ((value == LONG_MAX || value == LONG_MIN) && errno == ERANGE) {
		if (INTEGER_IS_NATIVE(self)) {
			self->as.gmp = GC_NEW_INTEGER(RUNTIME_FOR(self));
		}

		self->type = INTEGER_TYPE_GMP;
		mpz_set_str(*INTEGER_GET_GMP(self), string, base);
	}
	else {
		self->type      = INTEGER_TYPE_NATIVE;
		self->as.native = value;
	}

	return self;
}

Integer*
Integer_set_gmp (Integer* self, mpz_t* gmp)
{
	if (INTEGER_IS_GMP(self) && INTEGER_GET_GMP(self)) {
		mpz_set(*INTEGER_GET_GMP(self), *gmp);

		GC_SAVE_INTEGER(RUNTIME_FOR(self), gmp);
	}
	else {
		self->as.gmp = gmp;
	}

	self->type = INTEGER_TYPE_GMP;

	return self;
}

void
Integer_destroy (Integer* self)
{
	if (INTEGER_IS_GMP(self) && INTEGER_GET_GMP(self)) {
		GC_SAVE_INTEGER(RUNTIME_FOR(self), INTEGER_GET_GMP(self));
	}
}

Integer*
Integer_neg (Integer* self)
{
	assert(self);

	Integer* result = Integer_new(RUNTIME_FOR(self));

	if (INTEGER_IS_NATIVE(self)) {
		if (NEG_OVERFLOW(INTEGER_GET_NATIVE(self))) {
			mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

			mpz_set_si(*value, INTEGER_GET_NATIVE(self));
			mpz_neg(*value, *value);

			Integer_set_gmp(result, value);
		}
		else {
			Integer_set_native(result, -INTEGER_GET_NATIVE(self));
		}
	}
	else {
		mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

		mpz_neg(*value, *INTEGER_GET_GMP(self));

		Integer_set_gmp(result, value);
	}

	return result;
}

Integer*
Integer_abs (Integer* self)
{
	assert(self);

	Integer* result = Integer_new(RUNTIME_FOR(self));

	if (INTEGER_IS_NATIVE(self)) {
		if (INTEGER_GET_NATIVE(self) == LONG_MIN) {
			mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

			mpz_set_si(*value, INTEGER_GET_NATIVE(self));
			mpz_abs(*value, *value);

			Integer_set_gmp(result, value);
		}
		else {
			Integer_set_native(result, abs(INTEGER_GET_NATIVE(self)));
		}
	}
	else {
		mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

		mpz_abs(*value, *INTEGER_GET_GMP(self));

		Integer_set_gmp(result, value);
	}

	return result;
}

bool
Integer_eq (Integer* self, Value* number)
{
	assert(IS_INTEGER(number) || IS_FLOATING(number) || IS_RATIONAL(number));

	if (IS_FLOATING(number)) {
		return Floating_eq((Floating*) number, (Value*) self);
	}

	if (IS_RATIONAL(number)) {
		return Rational_eq((Rational*) number, (Value*) self);
	}

	Integer* other = (Integer*) number;

	if (INTEGER_IS_NATIVE(self)) {
		if (INTEGER_IS_NATIVE(other)) {
			return INTEGER_GET_NATIVE(self) == INTEGER_GET_NATIVE(other);
		}
		else {
			return mpz_cmp_si(*INTEGER_GET_GMP(other), INTEGER_GET_NATIVE(self)) == 0;
		}
	}
	else {
		if (INTEGER_IS_NATIVE(other)) {
			return mpz_cmp_si(*INTEGER_GET_GMP(self), INTEGER_GET_NATIVE(other)) == 0;
		}
		else {
			return mpz_cmp(*INTEGER_GET_GMP(self), *INTEGER_GET_GMP(other)) == 0;
		}
	}
}

bool
Integer_lt (Integer* self, Value* number)
{
	assert(IS_INTEGER(number) || IS_FLOATING(number) || IS_RATIONAL(number));

	if (IS_FLOATING(number)) {
		return Floating_lt((Floating*) number, (Value*) self);
	}

	if (IS_RATIONAL(number)) {
		return Rational_lt((Rational*) number, (Value*) self);
	}

	Integer* other = (Integer*) number;

	if (INTEGER_IS_NATIVE(self)) {
		if (INTEGER_IS_NATIVE(other)) {
			return INTEGER_GET_NATIVE(self) < INTEGER_GET_NATIVE(other);
		}
		else {
			return mpz_cmp_si(*INTEGER_GET_GMP(other), INTEGER_GET_NATIVE(self)) < 0;
		}
	}
	else {
		if (INTEGER_IS_NATIVE(other)) {
			return mpz_cmp_si(*INTEGER_GET_GMP(self), INTEGER_GET_NATIVE(other)) < 0;
		}
		else {
			return mpz_cmp(*INTEGER_GET_GMP(self), *INTEGER_GET_GMP(other)) < 0;
		}
	}
}

bool
Integer_gt (Integer* self, Value* number)
{
	assert(IS_INTEGER(number) || IS_FLOATING(number) || IS_RATIONAL(number));

	if (IS_FLOATING(number)) {
		return Floating_gt((Floating*) number, (Value*) self);
	}

	if (IS_RATIONAL(number)) {
		return Rational_gt((Rational*) number, (Value*) self);
	}

	Integer* other = (Integer*) number;

	if (INTEGER_IS_NATIVE(self)) {
		if (INTEGER_IS_NATIVE(other)) {
			return INTEGER_GET_NATIVE(self) > INTEGER_GET_NATIVE(other);
		}
		else {
			return mpz_cmp_si(*INTEGER_GET_GMP(other), INTEGER_GET_NATIVE(self)) > 0;
		}
	}
	else {
		if (INTEGER_IS_NATIVE(other)) {
			return mpz_cmp_si(*INTEGER_GET_GMP(self), INTEGER_GET_NATIVE(other)) > 0;
		}
		else {
			return mpz_cmp(*INTEGER_GET_GMP(self), *INTEGER_GET_GMP(other)) > 0;
		}
	}
}

Value*
Integer_add (Integer* self, Value* number)
{
	assert(IS_INTEGER(number) || IS_FLOATING(number) || IS_RATIONAL(number));

	if (IS_FLOATING(number)) {
		return (Value*) Floating_add((Floating*) number, (Value*) self);
	}

	if (IS_RATIONAL(number)) {
		return (Value*) Rational_add((Rational*) number, (Value*) self);
	}

	Integer* other  = (Integer*) number;
	Integer* result = (Integer*) Integer_new(RUNTIME_FOR(self));

	if (INTEGER_IS_NATIVE(self) && INTEGER_IS_NATIVE(other)) {
		if (ADD_OVERFLOW(INTEGER_GET_NATIVE(self), INTEGER_GET_NATIVE(other))) {
			mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

			mpz_set_si(*value, INTEGER_GET_NATIVE(self));

			if (INTEGER_GET_NATIVE(other) >= 0) {
				mpz_add_ui(*value, *value, INTEGER_GET_NATIVE(other));
			}
			else {
				mpz_sub_ui(*value, *value, -INTEGER_GET_NATIVE(other));
			}

			Integer_set_gmp(result, value);
		}
		else {
			Integer_set_native(result, INTEGER_GET_NATIVE(self) + INTEGER_GET_NATIVE(other));
		}
	}
	else if (INTEGER_IS_GMP(self) && INTEGER_IS_GMP(other)) {
		mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

		mpz_add(*value, *INTEGER_GET_GMP(self), *INTEGER_GET_GMP(other));

		Integer_set_gmp(result, value);
	}
	else {
		Integer* a     = INTEGER_IS_GMP(self) ? self  : other;
		Integer* b     = INTEGER_IS_GMP(self) ? other : self;
		mpz_t*   value = GC_NEW_INTEGER(RUNTIME_FOR(self));

		mpz_set_si(*value, INTEGER_GET_NATIVE(b));
		mpz_add(*value, *INTEGER_GET_GMP(a), *value);

		Integer_set_gmp(result, value);
	}

	return (Value*) result;
}

Value*
Integer_sub (Integer* self, Value* number)
{
	assert(IS_INTEGER(number) || IS_FLOATING(number) || IS_RATIONAL(number));

	if (IS_FLOATING(number)) {
		return (Value*) Floating_sub((Floating*) number, (Value*) self);
	}

	if (IS_RATIONAL(number)) {
		return (Value*) Rational_sub((Rational*) number, (Value*) self);
	}

	Integer* other  = (Integer*) number;
	Integer* result = (Integer*) Integer_new(RUNTIME_FOR(self));

	if (INTEGER_IS_NATIVE(self) && INTEGER_IS_NATIVE(other)) {
		if (SUB_OVERFLOW(INTEGER_GET_NATIVE(self), INTEGER_GET_NATIVE(other))) {
			mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

			mpz_set_si(*value, INTEGER_GET_NATIVE(self));

			if (INTEGER_GET_NATIVE(other) >= 0) {
				mpz_sub_ui(*value, *value, INTEGER_GET_NATIVE(other));
			}
			else {
				mpz_add_ui(*value, *value, -INTEGER_GET_NATIVE(other));
			}

			Integer_set_gmp(result, value);
		}
		else {
			Integer_set_native(result, INTEGER_GET_NATIVE(self) - INTEGER_GET_NATIVE(other));
		}
	}
	else if (INTEGER_IS_GMP(self) && INTEGER_IS_GMP(other)) {
		mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

		mpz_sub(*value, *INTEGER_GET_GMP(self), *INTEGER_GET_GMP(other));

		Integer_set_gmp(result, value);
	}
	else {
		Integer* a     = INTEGER_IS_GMP(self) ? self  : other;
		Integer* b     = INTEGER_IS_GMP(self) ? other : self;
		mpz_t*   value = GC_NEW_INTEGER(RUNTIME_FOR(self));

		mpz_set_si(*value, INTEGER_GET_NATIVE(b));
		mpz_sub(*value, *INTEGER_GET_GMP(a), *value);

		Integer_set_gmp(result, value);
	}

	return (Value*) result;
}

bool
Integer_is_odd (Integer* self)
{
	if (INTEGER_IS_NATIVE(self)) {
		return (INTEGER_GET_NATIVE(self) & 1) != 0;
	}
	else {
		return mpz_odd_p(*INTEGER_GET_GMP(self));
	}
}

bool
Integer_is_even (Integer* self)
{
	if (INTEGER_IS_NATIVE(self)) {
		return (INTEGER_GET_NATIVE(self) & 1) == 0;
	}
	else {
		return mpz_even_p(*INTEGER_GET_GMP(self));
	}
}

int
Integer_get_bits (Integer* self)
{
	switch (self->type) {
		case INTEGER_TYPE_NATIVE:
			return sizeof(long);

		case INTEGER_TYPE_GMP:
			return mpz_sizeinbase(*INTEGER_GET_GMP(self), 2);
	}
}
