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

#include <private/Vector.h>

void
test_vector_new (void* data)
{
	Vector* vec = Vector_new(runtime);

	tt_assert(vec);

end:
	Vector_destroy(vec);
}

void
test_vector_conj (void* data)
{
	Vector* vec = Vector_new(runtime);

	Vector_conj(vec, NIL);

	tt_int_op(Vector_length(vec), ==, 1);

end:
	Vector_destroy(vec);
}

void
test_vector_set (void* data)
{
	Vector* vec = Vector_new(runtime);
	Vector_conj(vec, NIL);

	Vector_set(vec, 0, TRUE);

end:
	Vector_destroy(vec);
}

void
test_vector_get (void* data)
{
	Vector* vec = Vector_new(runtime);
	Vector_conj(vec, NIL);

	Vector_set(vec, 0, TRUE);
	tt_assert(is_boolean(Vector_get(vec, 0)));

end:
	Vector_destroy(vec);
}

struct testcase_t vector_tests[] = {
	{ "new", test_vector_new },
	{ "conj", test_vector_conj },
	{ "set", test_vector_set },
	{ "get", test_vector_get },

	END_OF_TESTCASES
};
