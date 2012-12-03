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

#include <private/Integer.h>

void
test_integer_is_odd (void* data)
{
	GC*      gc   = GC_new();
	Integer* num  = Integer_set(Integer_new(gc), 32L);
	Integer* num2 = Integer_set(Integer_new(gc), 31L);

	tt_assert(!Integer_is_odd(num));
	tt_assert(Integer_is_odd(num2));

end:
	Integer_destroy(num);
	Integer_destroy(num2);

	GC_destroy(gc);
}

struct testcase_t integer_tests[] = {
	{ "is_odd", test_integer_is_odd },

	END_OF_TESTCASES
};
