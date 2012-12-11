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
};

Integer* Integer_set_gmp (Integer* self, mpz_t* gmp);

void Integer_destroy (Integer* self);

#define IS_NATIVE(i) ((i)->type == INTEGER_TYPE_NATIVE)
#define IS_GMP(i)    ((i)->type == INTEGER_TYPE_GMP)

#define GET_GMP(i)    ((i)->as.gmp)
#define GET_NATIVE(i) ((i)->as.native)

inline int Integer_get_bits (Integer* self);

#endif
