/* Copyleft (ɔ) meh. - http://meh.schizofreni.co
 *
 * This file is part of libtor - https://github.com/libtor/libtor
 *
 * libtor is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * libtor is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with libtor. If not, see <http://www.gnu.org/licenses/>.
 */

#include <private/String.h>

void
test_string_new (void* data)
{
	String* str = String_new(runtime);

	tt_assert(str);

end:;
}

void
test_string_set_cstr (void* data)
{
	String* str  = String_set_cstr(String_new(runtime), "æ");
	String* str2 = String_set_cstr_with_encoding(String_new(runtime), "æ", ENCODING_UTF8);

	tt_assert(str->length == 2);
	tt_assert(str->bytes == 2);

	tt_assert(str2->length == 1);
	tt_assert(str2->bytes == 2);

end:
	String_destroy(str);
	String_destroy(str2);
}

struct testcase_t string_tests[] = {
	{ "new", test_string_new },
	{ "set_cstr", test_string_set_cstr },

	END_OF_TESTCASES
};
