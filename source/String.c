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

#include <private/Runtime.h>
#include <private/String.h>
#include <private/common.h>

static inline const UChar*
find_non_ascii (const UChar* start, const UChar* end)
{
	while (start != end) {
		if (!ONIGENC_IS_MBC_ASCII(start)) {
			return start;
		}

		start++;
	}

	return NULL;
}

#define ONIGENC_CONSTRUCT_MBCLEN_CHARFOUND(n)   (n)
#define ONIGENC_MBCLEN_CHARFOUND_P(r)           (0 < (r))
#define ONIGENC_MBCLEN_CHARFOUND_LEN(r)         (r)

#define ONIGENC_CONSTRUCT_MBCLEN_INVALID()      (-1)
#define ONIGENC_MBCLEN_INVALID_P(r)             ((r) == -1)

#define ONIGENC_CONSTRUCT_MBCLEN_NEEDMORE(n)    (-1 - (n))
#define ONIGENC_MBCLEN_NEEDMORE_P(r)            ((r) < -1)
#define ONIGENC_MBCLEN_NEEDMORE_LEN(r)          (-1 - (r))

static inline int
precise_mbclen (const UChar* start, const UChar* end, OnigEncoding encoding)
{
	if (end <= start) {
		return ONIGENC_CONSTRUCT_MBCLEN_NEEDMORE(1);
	}

	int len = ONIGENC_MBC_ENC_LEN(encoding, start);

	if (end - start < len) {
		return ONIGENC_CONSTRUCT_MBCLEN_NEEDMORE(len - (int) (end - start));
	}

	return len;
}

static inline void
check_encoding_if_needed (String* self)
{
	if (self->encoding.checked) {
		return;
	}

	self->encoding.checked = true;

	if (self->encoding.type == ENCODING_NONE) {
		self->encoding.valid  = true;
		self->encoding.at7bit = false;
	}
	else if (self->encoding.type == ENCODING_ASCII) {
		self->encoding.valid  = true;
		self->encoding.at7bit = NULL == find_non_ascii(self->buffer, self->buffer + self->bytes);
	}
	else if (String_encoding_is_ascii_compatible(self)) {
		const UChar* start = self->buffer;
		const UChar* end   = self->buffer + self->bytes;

		start = find_non_ascii(start, end);

		if (start == NULL) {
			self->encoding.valid  = true;
			self->encoding.at7bit = true;
		}
		else {
			OnigEncoding encoding = String_get_onigenc(self);

			self->encoding.at7bit = false;
			self->encoding.valid  = true;

			while (start < end) {
				int len = precise_mbclen(start, end, encoding);

				if (!ONIGENC_MBCLEN_CHARFOUND_P(len)) {
					self->encoding.valid  = false;

					break;
				}

				start += ONIGENC_MBCLEN_CHARFOUND_LEN(len);

				if (start < end) {
					start = find_non_ascii(start, end);

					if (start == NULL) {
						break;
					}
				}
				else {
					self->encoding.valid = false;

					break;
				}
			}
		}
	}
	else {
		const UChar* start    = self->buffer;
		const UChar* end      = self->buffer + self->bytes;
		OnigEncoding encoding = String_get_onigenc(self);

		self->encoding.at7bit = false;
		self->encoding.valid  = true;

		while (start < end) {
			int len = precise_mbclen(start, end, encoding);

			if (!ONIGENC_MBCLEN_CHARFOUND_P(len)) {
				self->encoding.valid = false;

				break;
			}

			start += ONIGENC_MBCLEN_CHARFOUND_LEN(len);

			if (end < start) {
				self->encoding.valid = false;

				break;
			}
		}
	}
}

String*
String_new (Runtime* rt)
{
	assert(rt);

	String* self = (String*) GC_ALLOCATE(rt, VALUE_TYPE_STRING);

	self->length = 0;
	self->bytes  = 0;
	self->hash   = 0;

	self->encoding.type    = ENCODING_UTF8;
	self->encoding.checked = true;
	self->encoding.valid   = true;
	self->encoding.at7bit  = true;

	self->buffer = NULL;

	return self;
}

String*
String_new_with_encoding (Runtime* rt, Encoding encoding)
{
	assert(rt);

	String* self = String_new(rt);

	self->encoding.checked = false;
	self->encoding.type    = encoding;

	return self;
}

void
String_destroy (String* self)
{
	if (self->buffer) {
		free(self->buffer);
	}
}

String*
String_set_cstr (String* self, const char* str)
{
	assert(self);

	String_destroy(self);

	self->length = strlen(str);
	self->bytes  = self->length;
	self->hash   = 0;

	self->buffer = malloc(self->bytes + 1);
	memcpy(self->buffer, str, self->bytes);
	self->buffer[self->bytes] = 0;

	return self;
}

String*
String_set_cstr_with_encoding (String* self, const char* str, Encoding encoding)
{
	assert(self);

	String_destroy(self);

	self->encoding.checked = false;
	self->encoding.type    = encoding;

	self->bytes  = strlen(str);
	self->length = onigenc_strlen_null(String_get_onigenc(self), (UChar*) str);
	self->hash   = 0;

	self->buffer = malloc(self->bytes + 1);
	memcpy(self->buffer, str, self->bytes);
	self->buffer[self->bytes] = 0;

	return self;
}

String*
String_set_buffer (String* self, const void* buffer, uint64_t length)
{
	assert(self);

	String_destroy(self);

	self->length = length;
	self->bytes  = length;
	self->hash   = 0;

	self->encoding.checked = false;
	self->encoding.type    = ENCODING_NONE;

	self->buffer = malloc(length + 1);
	memcpy(self->buffer, buffer, length);
	self->buffer[self->bytes] = 0;

	return self;
}

String*
String_set_buffer_with_encoding (String* self, const void* buffer, uint64_t length, Encoding encoding)
{
	assert(self);

	String_destroy(self);

	self->encoding.checked = false;
	self->encoding.type    = encoding;

	self->length = onigenc_strlen(String_get_onigenc(self), (UChar*) buffer, ((UChar*) buffer) + length);
	self->bytes  = length;
	self->hash   = 0;

	self->buffer = malloc(length + 1);
	memcpy(self->buffer, buffer, length);
	self->buffer[self->bytes] = 0;

	return self;
}

uint64_t
String_length (String* self)
{
	return self->length;
}

uint64_t
String_bytes (String* self)
{
	return self->bytes;
}

uint64_t
String_hash (String* self)
{
	if (self->hash) {
		return self->hash;
	}

	int encoding = String_get_encoding(self);

	if (encoding && String_is_ascii_only(self)) {
		encoding = 0;
	}

	self->hash = siphash(RUNTIME_FOR(self)->sip_key, self->buffer, self->bytes) ^ encoding;

	return self->hash;
}

Encoding
String_get_encoding (String* self)
{
	return self->encoding.type;
}

bool
String_encoding_is_ascii_compatible (String* self)
{
	return String_get_onigenc(self)->min_enc_len == 1;
}

bool
String_is_ascii_only (String* self)
{
	if (!String_encoding_is_ascii_compatible(self)) {
		return false;
	}

	check_encoding_if_needed(self);

	return self->encoding.at7bit;
}

bool
String_is_valid (String* self)
{
	check_encoding_if_needed(self);

	return self->encoding.valid;
}

OnigEncoding
String_get_onigenc (String* self)
{
	switch (self->encoding.type) {
		case ENCODING_NONE:
			return (OnigEncoding) 0;

		case ENCODING_ASCII:
			return ONIG_ENCODING_ASCII;

		case ENCODING_ISO_8859_1:
			return ONIG_ENCODING_ISO_8859_1;

		case ENCODING_ISO_8859_2:
			return ONIG_ENCODING_ISO_8859_2;

		case ENCODING_ISO_8859_3:
			return ONIG_ENCODING_ISO_8859_3;

		case ENCODING_ISO_8859_4:
			return ONIG_ENCODING_ISO_8859_4;

		case ENCODING_ISO_8859_5:
			return ONIG_ENCODING_ISO_8859_5;

		case ENCODING_ISO_8859_6:
			return ONIG_ENCODING_ISO_8859_6;

		case ENCODING_ISO_8859_7:
			return ONIG_ENCODING_ISO_8859_7;

		case ENCODING_ISO_8859_8:
			return ONIG_ENCODING_ISO_8859_8;

		case ENCODING_ISO_8859_9:
			return ONIG_ENCODING_ISO_8859_9;

		case ENCODING_ISO_8859_10:
			return ONIG_ENCODING_ISO_8859_10;

		case ENCODING_ISO_8859_11:
			return ONIG_ENCODING_ISO_8859_11;

		case ENCODING_ISO_8859_13:
			return ONIG_ENCODING_ISO_8859_13;

		case ENCODING_ISO_8859_14:
			return ONIG_ENCODING_ISO_8859_14;

		case ENCODING_ISO_8859_15:
			return ONIG_ENCODING_ISO_8859_15;

		case ENCODING_ISO_8859_16:
			return ONIG_ENCODING_ISO_8859_16;

		case ENCODING_UTF8:
			return ONIG_ENCODING_UTF8;

		case ENCODING_UTF16_BE:
			return ONIG_ENCODING_UTF16_BE;

		case ENCODING_UTF16_LE:
			return ONIG_ENCODING_UTF16_LE;

		case ENCODING_UTF32_BE:
			return ONIG_ENCODING_UTF32_BE;

		case ENCODING_UTF32_LE:
			return ONIG_ENCODING_UTF32_LE;

		case ENCODING_EUC_JP:
			return ONIG_ENCODING_EUC_JP;

		case ENCODING_EUC_TW:
			return ONIG_ENCODING_EUC_TW;

		case ENCODING_EUC_KR:
			return ONIG_ENCODING_EUC_KR;

		case ENCODING_EUC_CN:
			return ONIG_ENCODING_EUC_CN;

		case ENCODING_SJIS:
			return ONIG_ENCODING_SJIS;

		case ENCODING_CP932:
			return ONIG_ENCODING_CP932;

		case ENCODING_KOI8:
			// this isn't compiling currently, so let's give KOI8_R
			// return ONIG_ENCODING_KOI8;

		case ENCODING_KOI8_R:
			return ONIG_ENCODING_KOI8_R;

		case ENCODING_CP1251:
			return ONIG_ENCODING_CP1251;

		case ENCODING_BIG5:
			return ONIG_ENCODING_BIG5;

		case ENCODING_GB18030:
			return ONIG_ENCODING_GB18030;
	}
}
