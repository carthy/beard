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

#define DEF(A, B, C, D) \
	Integer* \
	Integer_set_##A (Integer* self, B number) \
	{ \
		if (!IS_NATIVE(self) && Integer_get_gmp(self)) { \
			GC_put_integer(self->descriptor.gc, Integer_get_gmp(self)); \
		} \
		\
		self->type    = INTEGER_TYPE_##C; \
		self->value.D = number; \
		\
		return self; \
	}

DEF(s8,  int8_t, BYTE, s8);
DEF(s16, int16_t, SHORT, s16);
DEF(s32, int32_t, INT, s32);
DEF(s64, int64_t, LONG, s64);

DEF(u8,  uint8_t, UBYTE, u8);
DEF(u16, uint16_t, USHORT, u16);
DEF(u32, uint32_t, UINT, u32);
DEF(u64, uint64_t, ULONG, u64);

#undef DEF

Integer*
Integer_set_string (Integer* self, const char* string)
{
	assert(self);

	if (IS_NATIVE(self) || !Integer_get_gmp(self)) {
		self->value.gmp = GC_get_integer(self->descriptor.gc);
	}

	self->type = INTEGER_TYPE_GMP;

	mpz_set_str(*(self->value.gmp), string, 0);

	return self;
}

Integer*
Integer_set_string_with_base (Integer* self, const char* string, int base)
{
	if (IS_NATIVE(self) || !Integer_get_gmp(self)) {
		self->value.gmp = GC_get_integer(self->descriptor.gc);
	}

	self->type = INTEGER_TYPE_GMP;

	mpz_set_str(*(self->value.gmp), string, base);

	return self;
}

void
Integer_destroy (Integer* self)
{
	if (!IS_NATIVE(self) && Integer_get_gmp(self)) {
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

	Integer* number = (Integer*) other;
	Integer* result = (Integer*) Integer_new(self->descriptor.gc);

	if (!IS_NATIVE(self)) {
		mpz_t* value = GC_get_integer(self->descriptor.gc);

		if (!IS_NATIVE(number)) {
			mpz_add(*value, *Integer_get_gmp(self), *Integer_get_gmp(number));
		}
		else {
			Integer* a = IS_NATIVE(self) ? number : self;
			Integer* b = IS_NATIVE(self) ? self  : number;

			if (IS_SIGNED(b)) {
				mpz_set_si(*value, Integer_get_native_signed(b));
				mpz_add(*value, *Integer_get_gmp(a), *value);
			}
			else {
				mpz_add_ui(*value, *Integer_get_gmp(a), Integer_get_native_signed(b));
			}
		}

		result->type      = INTEGER_TYPE_GMP;
		result->value.gmp = value;

		return (Value*) result;
	}

	if (!IS_NATIVE(number)) {
		if (IS_SIGNED(self)) {
			assert(mpz_fits_slong_p(*Integer_get_gmp(number)));
		}
		else {
			assert(mpz_fits_ulong_p(*Integer_get_gmp(number)));
		}
	}

	switch (self->type) {
		#define ADD(name, other) \
			if (IS_NATIVE(other)) { \
				if (IS_SIGNED(other)) { \
					name += Integer_get_native_signed(other); \
				} \
				else { \
					name += Integer_get_native_unsigned(other); \
				} \
			} \
			else { \
				name += mpz_get_si(*Integer_get_gmp(other)); \
			}

		case INTEGER_TYPE_BYTE: {
			int8_t value = self->value.s8;

			ADD(value, number);

			result->type     = INTEGER_TYPE_BYTE;
			result->value.s8 = value;
		} break;

		case INTEGER_TYPE_SHORT: {
			int16_t value = self->value.s16;

			ADD(value, number);

			result->type      = INTEGER_TYPE_SHORT;
			result->value.s16 = value;

		} break;

		case INTEGER_TYPE_INT: {
			int32_t value = self->value.s32;

			ADD(value, number);

			result->type      = INTEGER_TYPE_INT;
			result->value.s32 = value;

		} break;

		case INTEGER_TYPE_LONG: {
			int64_t value = self->value.s64;

			ADD(value, number);

			result->type      = INTEGER_TYPE_LONG;
			result->value.s64 = value;

		} break;

		#undef ADD

		#define ADD(name, other) \
			if (IS_NATIVE(other)) { \
				if (IS_SIGNED(other)) { \
					name += Integer_get_native_signed(other); \
				} \
				else { \
					name += Integer_get_native_unsigned(other); \
				} \
			} \
			else { \
				name += mpz_get_ui(*Integer_get_gmp(other)); \
			}

		case INTEGER_TYPE_UBYTE: {
			uint8_t value = self->value.u8;

			ADD(value, number);

			result->type     = INTEGER_TYPE_UBYTE;
			result->value.u8 = value;

		} break;

		case INTEGER_TYPE_USHORT: {
			uint16_t value = self->value.u16;

			ADD(value, number);

			result->type      = INTEGER_TYPE_USHORT;
			result->value.u16 = value;

		} break;

		case INTEGER_TYPE_UINT: {
			uint32_t value = self->value.u32;

			ADD(value, number);

			result->type      = INTEGER_TYPE_UINT;
			result->value.u32 = value;

		} break;

		case INTEGER_TYPE_ULONG: {
			uint64_t value = self->value.u64;

			ADD(value, number);

			result->type      = INTEGER_TYPE_ULONG;
			result->value.u64 = value;

		} break;

		#undef ADD

		case INTEGER_TYPE_GMP:
			assert(false);
	}

	return (Value*) result;
}

bool
Integer_is_odd (Integer* self)
{
	if (IS_NATIVE(self)) {
		if (IS_SIGNED(self)) {
			return (Integer_get_native_signed(self) & 1) != 0;
		}
		else {
			return (Integer_get_native_unsigned(self) & 1) != 0;
		}
	}
	else {
		return mpz_odd_p(*(self->value.gmp));
	}
}

bool
Integer_is_even (Integer* self)
{
	if (IS_NATIVE(self)) {
		if (IS_SIGNED(self)) {
			return (Integer_get_native_signed(self) & 1) == 0;
		}
		else {
			return (Integer_get_native_unsigned(self) & 1) == 0;
		}
	}
	else {
		return mpz_even_p(*(self->value.gmp));
	}
}

int64_t
Integer_get_native_signed (Integer* self)
{
	switch (self->type) {
		case INTEGER_TYPE_BYTE:
			return self->value.s8;

		case INTEGER_TYPE_SHORT:
			return self->value.s16;

		case INTEGER_TYPE_INT:
			return self->value.s32;

		case INTEGER_TYPE_LONG:
			return self->value.s64;

		default:
			assert(false);
	}
}

uint64_t
Integer_get_native_unsigned (Integer* self)
{
	switch (self->type) {
		case INTEGER_TYPE_UBYTE:
			return self->value.u8;

		case INTEGER_TYPE_USHORT:
			return self->value.u16;

		case INTEGER_TYPE_UINT:
			return self->value.u32;

		case INTEGER_TYPE_ULONG:
			return self->value.u64;

		default:
			assert(false);
	}
}

mpz_t*
Integer_get_gmp (Integer* self)
{
	switch (self->type) {
		case INTEGER_TYPE_GMP:
			return self->value.gmp;

		default:
			assert(false);
	}
}

int
Integer_get_bits (Integer* self)
{
	switch (self->type) {
		case INTEGER_TYPE_BYTE:
		case INTEGER_TYPE_UBYTE:
			return 8;

		case INTEGER_TYPE_SHORT:
		case INTEGER_TYPE_USHORT:
			return 16;

		case INTEGER_TYPE_INT:
		case INTEGER_TYPE_UINT:
			return 32;

		case INTEGER_TYPE_LONG:
		case INTEGER_TYPE_ULONG:
			return 64;

		case INTEGER_TYPE_GMP:
			return mpz_sizeinbase(*Integer_get_gmp(self), 2);
	}
}
