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

#include <tinytest.h>
#include <tinytest_macros.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>

#include <private/common.h>

#include "value.c"
#include "free_list.c"
#include "gc.c"
#include "integer.c"

struct testgroup_t groups[] = {
	{ "value/", value_tests },
	{ "free_list/", free_list_tests },
	{ "gc/", gc_tests },
	{ "integer/", integer_tests },

	END_OF_GROUPS
};

int
main (int argc, const char* argv[])
{
	return tinytest_main(argc, argv, groups);
}
