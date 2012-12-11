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

#define Integer_set(self, X) _Generic((X), \
	int8_t:  Integer_set_native, \
	int16_t: Integer_set_native, \
	int32_t: Integer_set_native, \
	int64_t: Integer_set_native, \
\
	uint8_t:  Integer_set_native, \
	uint16_t: Integer_set_native, \
	uint32_t: Integer_set_native, \
	uint64_t: Integer_set_native, \
\
	default: Integer_set_string \
)(self, X)

Integer* Integer_set_native (Integer* self, long number);
Integer* Integer_set_string (Integer* self, const char* string);
Integer* Integer_set_string_with_base (Integer* self, const char* string, int base);

Value* Integer_plus (Integer* self, Value* other);

bool Integer_is_odd (Integer* self);
bool Integer_is_even (Integer* self);
