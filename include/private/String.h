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

#ifndef BEARD_STRING_H
#define BEARD_STRING_H

#include <public/String.h>

#include <oniguruma.h>
#include <regenc.h>

struct String {
	Value descriptor;

	uint64_t length;
	uint64_t bytes;
	uint64_t hash;

	struct {
		Encoding type : 8;

		bool checked : 1;
		bool valid   : 1;
		bool at7bit  : 1;
	} encoding;

	UChar* buffer;
};

void String_destroy (String* self);

inline OnigEncoding String_get_onigenc (String* self);

bool String_encoding_is_ascii_compatible (String* self);

bool String_is_ascii_only (String* self);

#endif
