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

#include <private/FreeList.h>

static void*
_free_list_constructor (void)
{
	return malloc(sizeof(int));
}

static void
_free_list_destructor (void* thing)
{
	free(thing);
}

void
test_free_list_new (void* data)
{
	FreeList* fl = FreeList_new(_free_list_constructor, _free_list_destructor);
	FreeList_destroy(fl);

end:;
}

void
test_free_list_get (void* data)
{
	FreeList* fl;
	int*      n;

	fl = FreeList_new(_free_list_constructor, _free_list_destructor);
	n  = FreeList_get(fl);

	tt_assert(n != NULL);

	_free_list_destructor(n);
	FreeList_destroy(fl);

end:;
}

void
test_free_list_put (void* data)
{
	FreeList* fl;
	int*      n;

	fl = FreeList_new(_free_list_constructor, _free_list_destructor);
	n  = FreeList_get(fl);

	*n = 42;
	FreeList_put(fl, n);
	n = FreeList_get(fl);

	tt_int_op(*n, ==, 42);

	FreeList_put(fl, n);
	FreeList_destroy(fl);

end:;
}

void
test_free_list_limit (void* data)
{
	FreeList* fl;
	int*      n;

	fl = FreeList_new_with_limit(0, _free_list_constructor, _free_list_destructor);
	n  = FreeList_get(fl);

	*n = 42;
	FreeList_put(fl, n);
	n = FreeList_get(fl);

	tt_int_op(*n, !=, 42);

	FreeList_put(fl, n);
	FreeList_destroy(fl);

end:;
}

struct testcase_t free_list_tests[] = {
	{ "new", test_free_list_new },
	{ "get", test_free_list_get },
	{ "put", test_free_list_put },
	{ "limit", test_free_list_limit },

	END_OF_TESTCASES
};
