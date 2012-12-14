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
test_integer_new (void* data)
{
	Integer* num = Integer_new(runtime);

	tt_assert(num);
	tt_assert(INTEGER_IS_NATIVE(num));
	tt_assert(INTEGER_GET_NATIVE(num) == 0);

end:
	Integer_destroy(num);
}

void
test_integer_eq (void* data)
{
	Integer* num1 = Integer_set(Integer_new(runtime), 23);
	Integer* num2 = Integer_set(Integer_new(runtime), 23);

	tt_assert(Integer_eq(num1, (Value*) num2));

end:
	Integer_destroy(num1);
	Integer_destroy(num2);
}

void
test_integer_lt (void* data)
{
	Integer* num1 = Integer_set(Integer_new(runtime), 0L);
	Integer* num2 = Integer_set(Integer_new(runtime), LONG_MAX);

	tt_assert(Integer_lt(num1, (Value*) num2));

end:
	Integer_destroy(num1);
	Integer_destroy(num2);
}

void
test_integer_gt (void* data)
{
	Integer* num1 = Integer_set(Integer_new(runtime), LONG_MAX);
	Integer* num2 = Integer_set(Integer_new(runtime), 0L);

	tt_assert(Integer_gt(num1, (Value*) num2));

end:
	Integer_destroy(num1);
	Integer_destroy(num2);
}

void
test_integer_add (void* data)
{
	Integer* num  = Integer_set(Integer_new(runtime), 250L);
	Integer* num2 = Integer_set(Integer_new(runtime), "10");

	Integer* result = (Integer*) Integer_add(num, (Value*) num2);

	tt_assert(IS_INTEGER(result));
	tt_assert(INTEGER_IS_NATIVE(result));
	tt_assert(INTEGER_GET_NATIVE(result) == 260);

end:
	Integer_destroy(num);
	Integer_destroy(num2);
}

void
test_integer_sub (void* data)
{
	Integer* num  = Integer_set(Integer_new(runtime), LONG_MAX);
	Integer* num2 = Integer_set(Integer_new(runtime), -2);
	Integer* num3 = (Integer*) Integer_sub(num, (Value*) num2); Integer_set(num2, 2);
	Integer* num4 = (Integer*) Integer_add(num, (Value*) num2);

	tt_assert(IS_GMP(num3));
	tt_assert(Integer_eq(num3, (Value*) num4));

end:
	Integer_destroy(num);
	Integer_destroy(num2);
	Integer_destroy(num3);
	Integer_destroy(num4);
}

void
test_integer_is_odd (void* data)
{
	Integer* num  = Integer_set(Integer_new(runtime), 32L);
	Integer* num2 = Integer_set(Integer_new(runtime), 31L);

	tt_assert(!Integer_is_odd(num));
	tt_assert(Integer_is_odd(num2));

end:
	Integer_destroy(num);
	Integer_destroy(num2);
}

void
test_integer_is_even (void* data)
{
	Integer* num  = Integer_set(Integer_new(runtime), 32L);
	Integer* num2 = Integer_set(Integer_new(runtime), 31L);

	tt_assert(Integer_is_even(num));
	tt_assert(!Integer_is_even(num2));

end:
	Integer_destroy(num);
	Integer_destroy(num2);
}

void
test_integer_neg (void* data)
{
	Integer* num = Integer_set(Integer_new(runtime), LONG_MIN);
	Integer* num2 = Integer_neg(num);

	tt_assert(INTEGER_IS_GMP(num2));

end:
	Integer_destroy(num);
	Integer_destroy(num2);
}

struct testcase_t integer_tests[] = {
	{ "new", test_integer_new },
	{  "eq", test_integer_eq  },
	{  "lt", test_integer_lt  },
	{  "gt", test_integer_gt  },
	{ "add", test_integer_add },
	{ "sub", test_integer_sub },
	{ "neg", test_integer_neg },
	{ "is_odd", test_integer_is_odd },
	{ "is_even", test_integer_is_even },

	END_OF_TESTCASES
};
