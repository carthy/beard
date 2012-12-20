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

#include <private/Map.h>

void
test_map_new (void* data)
{
	Map* map = Map_new(runtime);

	tt_assert(map);

end:
	Map_destroy(map);
}

void
test_map_put (void* data)
{
	Map*   map  = Map_new(runtime);
	Tuple* pair = Map_put(map, hash_for(TRUE), TRUE, FALSE);

	tt_assert(is_true(Tuple_get(pair, 0)));
	tt_assert(is_false(Tuple_get(pair, 1)));

	pair = Map_put(map, hash_for(TRUE), TRUE, NIL);

	tt_assert(is_true(Tuple_get(pair, 0)));
	tt_assert(is_nil(Tuple_get(pair, 1)));

end:
	Map_destroy(map);
}

void
test_map_get (void* data)
{
	Map*   map  = Map_new(runtime);
	Tuple* pair = Map_put(map, hash_for(TRUE), TRUE, FALSE);

	tt_assert(is_true(Tuple_get(pair, 0)));
	tt_assert(is_false(Tuple_get(pair, 1)));

	pair = Map_put(map, hash_for(TRUE), TRUE, NIL);

	tt_assert(is_true(Tuple_get(pair, 0)));
	tt_assert(is_nil(Tuple_get(pair, 1)));

	tt_assert(is_true(Map_get_key(map, hash_for(TRUE))));
	tt_assert(is_nil(Map_get_value(map, hash_for(TRUE))));

end:
	Map_destroy(map);
}

void
test_map_delete (void* data)
{
	Map*   map  = Map_new(runtime);
	Tuple* pair = Map_put(map, hash_for(TRUE), TRUE, FALSE);

	tt_assert(is_true(Tuple_get(pair, 0)));
	tt_assert(is_false(Tuple_get(pair, 1)));

	pair = Map_delete(map, hash_for(TRUE));

	tt_assert(is_true(Tuple_get(pair, 0)));
	tt_assert(is_false(Tuple_get(pair, 1)));

	tt_assert(!Map_has(map, hash_for(TRUE)));

end:
	Map_destroy(map);
}

struct testcase_t map_tests[] = {
	{ "new", test_map_new },
	{ "put", test_map_put },
	{ "get", test_map_get },
	{ "delete", test_map_delete },

	END_OF_TESTCASES
};
