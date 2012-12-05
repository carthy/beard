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
#include <private/String.h>
#include <private/common.h>

String*
String_new (GC* gc)
{
	assert(gc);

	String* self = (String*) GC_allocate(gc, VALUE_TYPE_STRING);

	self->length   = 0;
	self->bytes    = 0;
	self->encoding = ENCODING_UTF8;
	self->buffer   = NULL;

	return self;
}

String*
String_new_with_encoding (GC* gc, Encoding encoding)
{
	assert(gc);

	String* self = String_new(gc);

	self->encoding = encoding;

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

	self->encoding = encoding;

	self->bytes  = strlen(str);
	self->length = onigenc_strlen_null(String_get_onig_enc(self), (UChar*) str);

	self->buffer = malloc(self->bytes + 1);
	memcpy(self->buffer, str, self->bytes);
	self->buffer[self->bytes] = 0;

	return self;
}

String*
String_set_buffer (String* self, const void* buffer, size_t length)
{
	assert(self);

	String_destroy(self);

	self->length = length;
	self->bytes  = length;

	self->encoding = ENCODING_NONE;

	self->buffer = malloc(length + 1);
	memcpy(self->buffer, buffer, length);
	self->buffer[self->bytes] = 0;

	return self;
}

String*
String_set_buffer_with_encoding (String* self, const void* buffer, size_t length, Encoding encoding)
{
	assert(self);

	String_destroy(self);

	self->encoding = encoding;

	self->length = onigenc_strlen(String_get_onig_enc(self), (UChar*) buffer, ((UChar*) buffer) + length);
	self->bytes  = length;

	self->buffer = malloc(length + 1);
	memcpy(self->buffer, buffer, length);
	self->buffer[self->bytes] = 0;

	return self;
}

size_t
String_length (String* self)
{
	return self->length;
}

size_t
String_bytes (String* self)
{
	return self->bytes;
}

Encoding
String_get_encoding (String* self)
{
	return self->encoding;
}

OnigEncoding
String_get_onig_enc (String* self)
{
	switch (self->encoding) {
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
			// this isn't compiling currently
			assert(false); // return ONIG_ENCODING_KOI8;

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
