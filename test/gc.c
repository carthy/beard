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

#include <private/Runtime.h>

void
test_gc_get_integer (void* data)
{
	mpz_t* num = GC_NEW_INTEGER(runtime);

	mpz_set_ui(*num, 19);
	mpz_add_ui(*num, *num, 23);

	tt_assert(mpz_cmp_ui(*num, 42) == 0);

end:;
}

void
test_gc_get_floating (void* data)
{
	mpf_t* num  = GC_NEW_FLOATING(runtime);
	mpf_t* num2 = GC_NEW_FLOATING(runtime);

	mpf_set_d(*num, 2.3);
	mpf_set_d(*num, 4.2);
	mpf_add(*num, *num, *num2);

	tt_assert(mpf_cmp_d(*num, 4.2) == 0);

end:;
}

void
test_gc_get_rational (void* data)
{
	mpq_t* num  = GC_NEW_RATIONAL(runtime);
	mpq_t* num2 = GC_NEW_RATIONAL(runtime);

	mpq_set_ui(*num, 2, 3);
	mpq_set_ui(*num2, 2, 3);
	mpq_add(*num, *num, *num2);

	tt_assert(mpq_cmp_ui(*num, 4, 3) == 0);

end:;
}

struct testcase_t gc_tests[] = {
	{ "get_integer", test_gc_get_integer },
	{ "get_floating", test_gc_get_floating },
	{ "get_rational", test_gc_get_rational },

	END_OF_TESTCASES
};
