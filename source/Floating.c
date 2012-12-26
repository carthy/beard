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

static inline Floating*
invalidate_cache (Floating* self)
{
	CACHE(self)->hash = 0;

	return self;
}

Floating*
Floating_new (Runtime* rt)
{
	Floating* self = (Floating*) GC_ALLOCATE(rt, FLOATING);

	self->value = GC_NEW_FLOATING(rt);

	invalidate_cache(self);

	return self;
}

Floating*
Floating_new_with_precision (Runtime* rt, unsigned long precision)
{
	Floating* self = Floating_new(rt);

	Floating_set_precision(self, precision);

	return self;
}

Floating*
Floating_set_nan (Floating* self)
{
	mpfr_set_nan(*self->value);

	invalidate_cache(self);

	return self;
}

Floating*
Floating_set_infinity (Floating* self)
{
	return Floating_set_positive_infinity(self);
}

Floating*
Floating_set_positive_infinity (Floating* self)
{
	mpfr_set_inf(*self->value, 1);

	invalidate_cache(self);

	return self;
}

Floating*
Floating_set_negative_infinity (Floating* self)
{
	mpfr_set_inf(*self->value, -1);

	invalidate_cache(self);

	return self;
}

Floating*
Floating_set_zero (Floating* self)
{
	return Floating_set_positive_zero(self);
}

Floating*
Floating_set_positive_zero (Floating* self)
{
	mpfr_set_zero(*self->value, 1);

	invalidate_cache(self);

	return self;
}

Floating*
Floating_set_negative_zero (Floating* self)
{
	mpfr_set_zero(*self->value, -1);

	invalidate_cache(self);

	return self;
}

unsigned long
Floating_set_precision (Floating* self, unsigned long precision)
{
	mpfr_set_prec(*self->value, precision);

	invalidate_cache(self);

	return precision;
}

unsigned long
Floating_get_precision (Floating* self)
{
	return mpfr_get_prec(*self->value);
}

Floating*
Floating_set_double (Floating* self, double number)
{
	assert(self);

	mpfr_set_d(*self->value, number, MPFR_RNDN);

	invalidate_cache(self);

	return self;
}

Floating*
Floating_set_string (Floating* self, const char* string)
{
	assert(self);

	mpfr_set_str(*self->value, string, 0, MPFR_RNDN);

	invalidate_cache(self);

	return self;
}

Floating*
Floating_set_string_with_base (Floating* self, const char* string, int base)
{
	assert(self);

	mpfr_set_str(*self->value, string, base, MPFR_RNDN);

	invalidate_cache(self);

	return self;
}

void
Floating_destroy (Floating* self)
{
	GC_SAVE_FLOATING(RUNTIME_FOR(self), self->value);
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

Floating*
Floating_mul (Floating* self, Value* other)
{
	return NIL;
}

Floating*
Floating_div (Floating* self, Value* other)
{
	return NIL;
}

bool
Floating_is_nan (Floating* self)
{
	return mpfr_nan_p(*self->value);
}

bool
Floating_is_infinity (Floating* self)
{
	return mpfr_inf_p(*self->value);
}

bool
Floating_is_zero (Floating* self)
{
	return mpfr_zero_p(*self->value);
}

bool
Floating_is_number (Floating* self)
{
	return mpfr_number_p(*self->value);
}

bool
Floating_is_regular (Floating* self)
{
	return mpfr_regular_p(*self->value);
}

bool
Floating_is_positive (Floating* self)
{
	return mpfr_sgn(*self->value) > 0;
}

bool
Floating_is_negative (Floating* self)
{
	return mpfr_sgn(*self->value) < 0;
}

int
Floating_sign (Floating* self)
{
	return mpfr_sgn(*self->value);
}

hash_t
Floating_hash (Floating* self)
{
	if (CACHE(self)->hash) {
		return CACHE(self)->hash;
	}

	murmur3_t* state = MURMUR3_INIT(RUNTIME_FOR(self));

	MURMUR3_UPDATE_WITH(state, VALUE_TYPE_FLOATING);

	mpfr_exp_t exp;
	char*      string = mpfr_get_str(NULL, &exp, 32, 0, *self->value, MPFR_RNDN);
	size_t     size   = strlen(string);

	MURMUR3_UPDATE_WITH(state, exp);
	MURMUR3_UPDATE(state, string, size);

	CACHE(self)->hash = MURMUR3_FINAL(state);

	free(string);

	return CACHE(self)->hash;
}
