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
	int8_t:  Integer_set_s8, \
	int16_t: Integer_set_s16, \
	int32_t: Integer_set_s32, \
	int64_t: Integer_set_s64, \
\
	uint8_t:  Integer_set_u8, \
	uint16_t: Integer_set_u16, \
	uint32_t: Integer_set_u32, \
	uint64_t: Integer_set_u64, \
\
	default: Integer_set_string \
)(self, X)

Integer* Integer_set_s8  (Integer* self, int8_t number);
Integer* Integer_set_s16 (Integer* self, int16_t number);
Integer* Integer_set_s32 (Integer* self, int32_t number);
Integer* Integer_set_s64 (Integer* self, int64_t number);

Integer* Integer_set_u8  (Integer* self, uint8_t number);
Integer* Integer_set_u16 (Integer* self, uint16_t number);
Integer* Integer_set_u32 (Integer* self, uint32_t number);
Integer* Integer_set_u64 (Integer* self, uint64_t number);

Integer* Integer_set_string (Integer* self, const char* string);
Integer* Integer_set_string_with_base (Integer* self, const char* string, int base);

void Integer_destroy (Integer* self);

Value* Integer_plus (Integer* self, Value* other);

bool Integer_is_odd (Integer* self);
bool Integer_is_even (Integer* self);
