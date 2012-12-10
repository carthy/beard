/* Copyleft (¿) meh. - http://meh.schizofreni.co
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

typedef struct String String;

typedef enum Encoding {
	ENCODING_NONE,
	ENCODING_ASCII,
	ENCODING_ISO_8859_1,
	ENCODING_ISO_8859_2,
	ENCODING_ISO_8859_3,
	ENCODING_ISO_8859_4,
	ENCODING_ISO_8859_5,
	ENCODING_ISO_8859_6,
	ENCODING_ISO_8859_7,
	ENCODING_ISO_8859_8,
	ENCODING_ISO_8859_9,
	ENCODING_ISO_8859_10,
	ENCODING_ISO_8859_11,
	ENCODING_ISO_8859_13,
	ENCODING_ISO_8859_14,
	ENCODING_ISO_8859_15,
	ENCODING_ISO_8859_16,
	ENCODING_UTF8,
	ENCODING_UTF16_BE,
	ENCODING_UTF16_LE,
	ENCODING_UTF32_BE,
	ENCODING_UTF32_LE,
	ENCODING_EUC_JP,
	ENCODING_EUC_TW,
	ENCODING_EUC_KR,
	ENCODING_EUC_CN,
	ENCODING_SJIS,
	ENCODING_CP932,
	ENCODING_KOI8,
	ENCODING_KOI8_R,
	ENCODING_CP1251,
	ENCODING_BIG5,
	ENCODING_GB18030
} Encoding;

String* String_new (Runtime* rt);

String* String_new_with_encoding (Runtime* rt, Encoding encoding);

String* String_set_cstr (String* self, const char* str);

String* String_set_cstr_with_encoding (String* self, const char* str, Encoding encoding);

String* String_set_buffer (String* self, const void* buffer, uint64_t length);

String* String_set_buffer_with_encoding (String* self, const void* buffer, uint64_t length, Encoding encoding);

uint64_t String_length (String* self);

uint64_t String_bytes (String* self);

uint64_t String_hash (String* self);

Encoding String_get_encoding (String* self);
