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

#include <private/Tuple.h>

void
test_tuple_new (void* data)
{
	Tuple* tup = Tuple_new(runtime, 2);

	tt_assert(tup);
	tt_int_op(Tuple_size(tup), ==, 2);

end:
	Tuple_destroy(tup);
}

void
test_tuple_new_with (void* data)
{
	Tuple* tup = Tuple_new_with(runtime, TRUE, FALSE);

	tt_assert(tup);
	tt_int_op(Tuple_size(tup), ==, 2);

end:
	Tuple_destroy(tup);
}

struct testcase_t tuple_tests[] = {
	{ "new", test_tuple_new },
	{ "new_with", test_tuple_new_with },

	END_OF_TESTCASES
};
