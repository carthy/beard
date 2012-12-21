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

#include <private/Floating.h>

void
test_floating_new (void* data)
{
	Floating* num  = Floating_new(runtime);
	Floating* num2 = Floating_set_positive_infinity(Floating_new(runtime));
	Floating* num3 = Floating_set_negative_infinity(Floating_new(runtime));
	Floating* num4 = Floating_set_double(Floating_new(runtime), 2);

	tt_assert(num);
	tt_assert(Floating_is_nan(num));

	tt_assert(num2);
	tt_assert(Floating_is_infinity(num2) && Floating_is_positive(num2));

	tt_assert(num3);
	tt_assert(Floating_is_infinity(num3) && Floating_is_negative(num3));

	tt_assert(num4);
	tt_assert(Floating_is_regular(num4));

end:
	Floating_destroy(num);
	Floating_destroy(num2);
	Floating_destroy(num3);
}

void
test_floating_add (void* data)
{

end:;
}

void
test_floating_hash (void* data)
{
	Floating* num = Floating_new(runtime);

	tt_int_op(Floating_hash(Floating_set_double(num, 2)), ==, Floating_hash(Floating_set_double(num, 2)));
	tt_int_op(Floating_hash(Floating_set_string(num, "2.3498583948580303")), ==, Floating_hash(Floating_set_string(num, "2.3498583948580303")));
	tt_int_op(Floating_hash(Floating_set_string(num, "23.498583948580303")), ==, Floating_hash(Floating_set_string(num, "23.498583948580303")));

	tt_int_op(Floating_hash(Floating_set_string(num, "23.498583948580303")), !=, Floating_hash(Floating_set_string(num, "2.3498583948580303")));

end:
	Floating_destroy(num);
}

struct testcase_t floating_tests[] = {
	{ "new", test_floating_new },
	{ "add", test_floating_add },
	{ "hash", test_floating_hash },

	END_OF_TESTCASES
};
