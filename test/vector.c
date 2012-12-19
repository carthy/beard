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
test_vector_set (void* data)
{
	Vector* vec = Vector_new(runtime);
	Vector_resize(vec, 1);

	Vector_set(vec, 0, TRUE);

end:
	Vector_destroy(vec);
}

void
test_vector_get (void* data)
{
	Vector* vec = Vector_new(runtime);
	Vector_resize(vec, 1);

	Vector_set(vec, 0, TRUE);
	tt_assert(is_boolean(Vector_get(vec, 0)));

end:
	Vector_destroy(vec);
}

void
test_vector_insert (void* data)
{
	Vector* vec = Vector_new(runtime);

	Vector_insert(vec, TRUE, 0);
	Vector_insert(vec, FALSE, 1);
	Vector_insert(vec, NIL, 1);

	tt_assert(is_true(Vector_get(vec, 0)));
	tt_assert(is_nil(Vector_get(vec, 1)));
	tt_assert(is_false(Vector_get(vec, 2)));

end:
	Vector_destroy(vec);
}

void
test_vector_insert_first (void* data)
{
	Vector* vec = Vector_new(runtime);

	Vector_insert_first(vec, TRUE);
	Vector_insert_first(vec, FALSE);

	tt_assert(is_true(Vector_get(vec, 1)));
	tt_assert(is_false(Vector_get(vec, 0)));

end:
	Vector_destroy(vec);
}

void
test_vector_insert_last (void* data)
{
	Vector* vec = Vector_new(runtime);

	Vector_insert_last(vec, TRUE);
	Vector_insert_last(vec, FALSE);

	tt_assert(is_true(Vector_get(vec, 0)));
	tt_assert(is_false(Vector_get(vec, 1)));

end:
	Vector_destroy(vec);
}

struct testcase_t vector_tests[] = {
	{ "new", test_vector_new },
	{ "set", test_vector_set },
	{ "get", test_vector_get },
	{ "insert", test_vector_insert },
	{ "insert_first", test_vector_insert_first },
	{ "insert_last", test_vector_insert_first },

	END_OF_TESTCASES
};
