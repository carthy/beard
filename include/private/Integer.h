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

#ifndef BEARD_INTEGER_H
#define BEARD_INTEGER_H

#include <private/Value.h>
#include <public/Integer.h>

#include <stdint.h>
#include <gmp.h>

typedef enum IntegerType {
	INTEGER_TYPE_BYTE,
	INTEGER_TYPE_SHORT,
	INTEGER_TYPE_INT,
	INTEGER_TYPE_LONG,

	INTEGER_TYPE_UBYTE,
	INTEGER_TYPE_USHORT,
	INTEGER_TYPE_UINT,
	INTEGER_TYPE_ULONG,

	INTEGER_TYPE_GMP
} IntegerType;

typedef union IntegerValue {
	int8_t  s8;
	int16_t s16;
	int32_t s32;
	int64_t s64;

	uint8_t  u8;
	uint16_t u16;
	uint32_t u32;
	uint64_t u64;

	mpz_t* gmp;
} IntegerValue;

struct Integer {
	Value descriptor;

	IntegerType  type;
	IntegerValue value;
};

void Integer_destroy (Integer* self);

#define IS_NATIVE(i)   (i->type != INTEGER_TYPE_GMP)
#define IS_SIGNED(i)   (i->type >= INTEGER_TYPE_BYTE && i->type <= INTEGER_TYPE_LONG)
#define IS_UNSIGNED(i) (i->type >= INTEGER_TYPE_UBYTE && i->type <= INTEGER_TYPE_ULONG)

inline int64_t Integer_get_native_signed (Integer* self);

inline uint64_t Integer_get_native_unsigned (Integer* self);

inline mpz_t* Integer_get_gmp (Integer* self);

inline int Integer_get_bits (Integer* self);

#endif
