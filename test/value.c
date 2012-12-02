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

#include <private/Value.h>

void
test_value_is_nil (void* data)
{
	tt_assert(is_nil(NIL));
	tt_assert(!is_nil(TRUE));
	tt_assert(!is_nil(FALSE));

end:;
}

void
test_value_is_false (void* data)
{
	tt_assert(is_false(NIL));
	tt_assert(is_false(FALSE));
	tt_assert(!is_false(TRUE));

end:;
}

void
test_value_is_true (void* data)
{
	tt_assert(is_true(TRUE));
	tt_assert(!is_true(FALSE));
	tt_assert(!is_true(NIL));

end:;
}

void
test_value_type_of (void* data)
{
	tt_assert(type_of(NIL) == VALUE_TYPE_NIL);
	tt_assert(type_of(FALSE) == VALUE_TYPE_BOOLEAN);
	tt_assert(type_of(TRUE) == VALUE_TYPE_BOOLEAN);

end:;
}

struct testcase_t value_tests[] = {
	{ "is_nil", test_value_is_nil },
	{ "is_false", test_value_is_false },
	{ "is_true", test_value_is_true },
	{ "type_of", test_value_type_of },

	END_OF_TESTCASES
};
