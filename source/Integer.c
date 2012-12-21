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

static inline Integer*
invalidate_cache (Integer* self)
{
	CACHE(self)->hash = 0;

	return self;
}

Integer*
Integer_new (Runtime* rt)
{
	Integer* self = (Integer*) GC_ALLOCATE(rt, INTEGER);

	self->type      = INTEGER_TYPE_NATIVE;
	self->as.native = 0;

	invalidate_cache(self);

	return self;
}

Integer*
Integer_dup (Integer* self)
{
	Integer* dup = Integer_new(RUNTIME_FOR(self));

	if (INTEGER_IS_NATIVE(self)) {
		Integer_set_native(dup, INTEGER_GET_NATIVE(self));
	}
	else {
		mpz_t* gmp = GC_NEW_INTEGER(RUNTIME_FOR(self));
		mpz_set(*gmp, *INTEGER_GET_GMP(self));

		Integer_set_gmp(dup, gmp);
	}

	return dup;
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

	invalidate_cache(self);

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

	invalidate_cache(self);

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

	invalidate_cache(self);

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

	invalidate_cache(self);

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

Value*
Integer_mul (Integer* self, Value* number)
{
	assert(IS_INTEGER(number) || IS_FLOATING(number) || IS_RATIONAL(number));

	if (IS_FLOATING(number)) {
		return (Value*) Floating_mul((Floating*) number, (Value*) self);
	}

	if (IS_RATIONAL(number)) {
		return (Value*) Rational_mul((Rational*) number, (Value*) self);
	}

	Integer* other  = (Integer*) number;
	Integer* result = (Integer*) Integer_new(RUNTIME_FOR(self));

	if (INTEGER_IS_NATIVE(self)) {
		if (INTEGER_IS_NATIVE(other)) {
			if (MUL_OVERFLOW(INTEGER_GET_NATIVE(self), INTEGER_GET_NATIVE(other))) {
				mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

				mpz_set_si(*value, INTEGER_GET_NATIVE(self));
				mpz_mul_si(*value, *value, INTEGER_GET_NATIVE(other));

				Integer_set_gmp(result, value);
			}
			else {
				Integer_set_native(result, INTEGER_GET_NATIVE(self) * INTEGER_GET_NATIVE(other));
			}
		}
		else {
			mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

			mpz_mul_si(*value, *INTEGER_GET_GMP(other), INTEGER_GET_NATIVE(self));

			Integer_set_gmp(result, value);
		}
	}
	else {
		mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));

		mpz_mul(*value, *INTEGER_GET_GMP(self), *INTEGER_GET_GMP(other));

		Integer_set_gmp(result, value);
	}

	return (Value*) result;
}

Value*
Integer_div (Integer* self, Value* number)
{
	assert(IS_INTEGER(number) || IS_FLOATING(number) || IS_RATIONAL(number));

	if (IS_FLOATING(number)) {
		return (Value*) Floating_div((Floating*) number, (Value*) self);
	}

	if (IS_RATIONAL(number)) {
		return (Value*) Rational_div((Rational*) number, (Value*) self);
	}

	Integer* other = (Integer*) number;
	Value*   result;

	if (INTEGER_IS_NATIVE(other)) {
		assert(INTEGER_GET_NATIVE(other) != 0);
	}
	else {
		assert(mpz_cmp_si(*INTEGER_GET_GMP(other), 0) != 0);
	}

	if (INTEGER_IS_NATIVE(self)) {
		if (INTEGER_IS_NATIVE(other)) {
			if (DIV_OVERFLOW(INTEGER_GET_NATIVE(self), INTEGER_GET_NATIVE(other))) {
				mpz_t* tmp = GC_NEW_INTEGER(RUNTIME_FOR(self));
				mpz_set_si(*tmp, INTEGER_GET_NATIVE(self));

				if (mpz_divisible_ui_p(*tmp, abs(INTEGER_GET_NATIVE(other)))) {
					mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));
					mpz_set_si(*value, INTEGER_GET_NATIVE(other));
					mpz_divexact(*value, *tmp, *value);

					result = (Value*) Integer_set_gmp(Integer_new(RUNTIME_FOR(self)), value);
				}
				else {
					result = (Value*) Rational_set(Rational_new(RUNTIME_FOR(self)),
						INTEGER_GET_NATIVE(self), INTEGER_GET_NATIVE(other));
				}

				GC_SAVE_INTEGER(RUNTIME_FOR(self), tmp);
			}
			else {
				if (INTEGER_GET_NATIVE(self) % abs(INTEGER_GET_NATIVE(other)) == 0) {
					result = (Value*) Integer_set_native(Integer_new(RUNTIME_FOR(self)),
						INTEGER_GET_NATIVE(self) / INTEGER_GET_NATIVE(other));
				}
				else {
					result = (Value*) Rational_set(Rational_new(RUNTIME_FOR(self)),
						INTEGER_GET_NATIVE(self), INTEGER_GET_NATIVE(other));
				}
			}
		}
		else {
			mpz_t* tmp = GC_NEW_INTEGER(RUNTIME_FOR(self));
			mpz_set_si(*tmp, INTEGER_GET_NATIVE(self));

			if (mpz_divisible_p(*tmp, *INTEGER_GET_GMP(other))) {
				mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));
				mpz_divexact(*value, *tmp, *INTEGER_GET_GMP(other));

				Integer_set_gmp(Integer_new(RUNTIME_FOR(self)), value);
			}
			else {
				result = (Value*) Rational_set(Rational_new(RUNTIME_FOR(self)), self, other);
			}

			GC_SAVE_INTEGER(RUNTIME_FOR(self), tmp);
		}
	}
	else {
		if (INTEGER_IS_NATIVE(other)) {
			if (mpz_divisible_ui_p(*INTEGER_GET_GMP(self), abs(INTEGER_GET_NATIVE(other)))) {
				mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));
				mpz_set_si(*value, INTEGER_GET_NATIVE(other));
				mpz_divexact(*value, *INTEGER_GET_GMP(self), *value);

				result = (Value*) Integer_set_gmp(Integer_new(RUNTIME_FOR(self)), value);
			}
			else {
				result = (Value*) Rational_set(Rational_new(RUNTIME_FOR(self)), self, other);
			}
		}
		else {
			if (mpz_divisible_p(*INTEGER_GET_GMP(self), *INTEGER_GET_GMP(other))) {
				mpz_t* value = GC_NEW_INTEGER(RUNTIME_FOR(self));
				mpz_divexact(*value, *INTEGER_GET_GMP(self), *INTEGER_GET_GMP(other));

				result = (Value*) Integer_set_gmp(Integer_new(RUNTIME_FOR(self)), value);
			}
			else {
				result = (Value*) Rational_set(Rational_new(RUNTIME_FOR(self)), self, other);
			}
		}
	}

	return result;
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

uint64_t
Integer_hash (Integer* self)
{
	if (CACHE(self)->hash) {
		return CACHE(self)->hash;
	}

	if (INTEGER_IS_NATIVE(self)) {
		CACHE(self)->hash = SIPHASH(RUNTIME_FOR(self), &INTEGER_GET_NATIVE(self), sizeof(INTEGER_GET_NATIVE(self)));
	}
	else {
		size_t size   = mpz_sizeinbase(*INTEGER_GET_GMP(self), 32) + 2;
		char*  string = malloc(size);

		mpz_get_str(string, 32, *INTEGER_GET_GMP(self));
		CACHE(self)->hash = SIPHASH(RUNTIME_FOR(self), string, size);

		free(string);
	}

	return CACHE(self)->hash;
}
