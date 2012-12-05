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
	Map* vec = Map_new(runtime);

	tt_assert(vec);

end:
	Map_destroy(vec);
}

void
test_map_set (void* data)
{
	Map* vec = Map_new(runtime);
	Map_put(vec, 0, TRUE);

end:
	Map_destroy(vec);
}

void
test_map_get (void* data)
{
	Map* vec = Map_new(runtime);
	Map_put(vec, 0, TRUE);
	tt_assert(is_boolean(Map_get(vec, 0)));

end:
	Map_destroy(vec);
}

struct testcase_t map_tests[] = {
	{ "new", test_map_new },
	{ "set", test_map_set },
	{ "get", test_map_get },

	END_OF_TESTCASES
};
