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

typedef struct Integer Integer;

Integer* Integer_new (Runtime* rt);

Integer* Integer_dup (Integer* self);

#define Integer_set(self, X) _Generic((X), \
	char:  Integer_set_native, \
	short: Integer_set_native, \
	int:   Integer_set_native, \
	long:  Integer_set_native, \
\
	unsigned char:  Integer_set_native, \
	unsigned short: Integer_set_native, \
\
	default: Integer_set_string \
)(self, X)

Integer* Integer_set_native (Integer* self, long number);

Integer* Integer_set_string (Integer* self, const char* string);

Integer* Integer_set_string_with_base (Integer* self, const char* string, int base);

Integer* Integer_neg (Integer* self);

Integer* Integer_abs (Integer* self);

bool Integer_eq (Integer* self, Value* other);

bool Integer_lt (Integer* self, Value* other);

bool Integer_gt (Integer* self, Value* other);

Value* Integer_add (Integer* self, Value* other);

Value* Integer_sub (Integer* self, Value* other);

Value* Integer_mul (Integer* self, Value* other);

Value* Integer_div (Integer* self, Value* other);

Value* Integer_pow (Integer* self, Integer* exponent);

bool Integer_is_odd (Integer* self);

bool Integer_is_even (Integer* self);

uint64_t Integer_hash (Integer* self);
