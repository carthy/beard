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
	INTEGER_TYPE_NATIVE,
	INTEGER_TYPE_GMP
} IntegerType;

typedef union IntegerValue {
	long   native;
	mpz_t* gmp;
} IntegerValue;

struct Integer {
	Value descriptor;

	IntegerType  type;
	IntegerValue as;

	struct {
		uint64_t hash;
	} cache;
};

Integer* Integer_set_gmp (Integer* self, mpz_t* gmp);

void Integer_destroy (Integer* self);

#define INTEGER_IS_NATIVE(i) ((i)->type == INTEGER_TYPE_NATIVE)
#define INTEGER_IS_GMP(i)    ((i)->type == INTEGER_TYPE_GMP)

#define INTEGER_GET_GMP(i)    ((i)->as.gmp)
#define INTEGER_GET_NATIVE(i) ((i)->as.native)

#define LONG_BIT (sizeof(long) * CHAR_BIT)

#define ADD_OVERFLOW(s1, s2) ( \
	(((s2) > 0) && ((s1) > (LONG_MAX - (s2)))) || \
	(((s2) < 0) && ((s1) < (LONG_MIN - (s2)))) \
)

#define SUB_OVERFLOW(s1, s2) ( \
	(((s2) > 0) && ((s1) < (LONG_MIN) + (s2))) || \
	(((s2) < 0) && ((s1) > (LONG_MAX + (s2)))) \
)

#define MUL_OVERFLOW(s1, s2) ( \
	((s1) > 0) ? \
		(((s2) > 0) ? \
		 ((s1) > (LONG_MAX / (s2))) : \
		 ((s2) < (LONG_MIN / (s1)))) : \
		(((s2) > 0) ? \
		 ((s1) < (LONG_MIN / (s2))) : \
		 (((s1) != 0) && ((s2) < (LONG_MAX / (s1))))) \
)

#define DIV_OVERFLOW(s1, s2) \
	(((s1) == LONG_MIN) && ((s2) == -1))

#define NEG_OVERFLOW(s1) \
	((s1) == LONG_MIN)

#define SHL_OVERFLOW(s1, s2) ( \
	((s1) < 0) || ((s2) < 0) || \
	((s2) >= LONG_BIT) || \
	((s1) > (LONG_MAX >> (s2))) \
)

inline int Integer_get_bits (Integer* self);

#endif
