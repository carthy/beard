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
#include <private/Integer.h>
#include <public/Floating.h>
#include <public/Rational.h>
#include <private/common.h>

Integer*
Integer_new (GC* gc)
{
	Integer* self = (Integer*) GC_allocate(gc, VALUE_TYPE_INTEGER);

	self->type      = INTEGER_TYPE_LONG;
	self->value.s64 = 0;

	return self;
}

#define def(A, B, C, D) \
	Integer* \
	Integer_set_##A (Integer* self, B number) \
	{ \
		if (self->type == INTEGER_TYPE_GMP && self->value.gmp) { \
			GC_put_integer(self->descriptor.gc, self->value.gmp); \
		} \
		\
		self->type    = INTEGER_TYPE_##C; \
		self->value.D = number; \
		\
		return self; \
	}

def(s8,  int8_t, BYTE, s8);
def(s16, int16_t, SHORT, s16);
def(s32, int32_t, INT, s32);
def(s64, int64_t, LONG, s64);

def(u8,  uint8_t, UBYTE, u8);
def(u16, uint16_t, USHORT, u16);
def(u32, uint32_t, UINT, u32);
def(u64, uint64_t, ULONG, u64);

#undef def

Integer*
Integer_set_string (Integer* self, const char* string)
{
	assert(self);

	if (self->type == INTEGER_TYPE_GMP && !self->value.gmp) {
		self->value.gmp = GC_get_integer(self->descriptor.gc);
	}

	self->type = INTEGER_TYPE_GMP;

	mpz_set_str(*(self->value.gmp), string, 0);

	return self;
}

Integer*
Integer_set_string_with_base (Integer* self, const char* string, int base)
{
	if (self->type == INTEGER_TYPE_GMP && !self->value.gmp) {
		self->value.gmp = GC_get_integer(self->descriptor.gc);
	}

	self->type = INTEGER_TYPE_GMP;

	mpz_set_str(*(self->value.gmp), string, base);

	return self;
}

void
Integer_destroy (Integer* self)
{
	if (self->type == INTEGER_TYPE_GMP && self->value.gmp) {
		GC_put_integer(self->descriptor.gc, self->value.gmp);
	}
}

Value*
Integer_plus (Integer* self, Value* other)
{
	assert(IS_INTEGER(other) || IS_FLOATING(other) || IS_RATIONAL(other));

	if (IS_FLOATING(other)) {
		return (Value*) Floating_plus((Floating*) other, (Value*) self);
	}

	if (IS_RATIONAL(other)) {
		return (Value*) Rational_plus((Rational*) other, (Value*) self);
	}

	return NIL;
}

bool
Integer_is_odd (Integer* self)
{
	switch (self->type) {
		case INTEGER_TYPE_BYTE:
			return self->value.s8 % 2 != 0;

		case INTEGER_TYPE_SHORT:
			return self->value.s16 % 2 != 0;

		case INTEGER_TYPE_INT:
			return self->value.s32 % 2 != 0;

		case INTEGER_TYPE_LONG:
			return self->value.s64 % 2 != 0;

		case INTEGER_TYPE_UBYTE:
			return self->value.u8 % 2 != 0;

		case INTEGER_TYPE_USHORT:
			return self->value.u16 % 2 != 0;

		case INTEGER_TYPE_UINT:
			return self->value.u32 % 2 != 0;

		case INTEGER_TYPE_ULONG:
			return self->value.u64 % 2 != 0;

		case INTEGER_TYPE_GMP:
			return mpz_odd_p(*(self->value.gmp));
	}
}

bool
Integer_is_even (Integer* self)
{
	switch (self->type) {
		case INTEGER_TYPE_BYTE:
			return self->value.s8 % 2 == 0;

		case INTEGER_TYPE_SHORT:
			return self->value.s16 % 2 == 0;

		case INTEGER_TYPE_INT:
			return self->value.s32 % 2 == 0;

		case INTEGER_TYPE_LONG:
			return self->value.s64 % 2 == 0;

		case INTEGER_TYPE_UBYTE:
			return self->value.u8 % 2 == 0;

		case INTEGER_TYPE_USHORT:
			return self->value.u16 % 2 == 0;

		case INTEGER_TYPE_UINT:
			return self->value.u32 % 2 == 0;

		case INTEGER_TYPE_ULONG:
			return self->value.u64 % 2 == 0;

		case INTEGER_TYPE_GMP:
			return mpz_even_p(*(self->value.gmp));
	}
}
