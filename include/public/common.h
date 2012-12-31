/* Copyleft (ɔ) meh. - http://meh.schizofreni.co
 *
 * This file is part of beard - https://github.com/carthy/beard
 *
 * beard is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published
 * by the Free Software Foundation, either version 3 of the License,
 * or (at your option) any later version.
 *
 * beard is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with beard. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>

typedef unsigned long hash_t;
typedef unsigned long word_t;

#define __SIZEOF_HASH__ __SIZEOF_LONG__
#define __SIZEOF_WORD__ __SIZEOF_LONG__

#define HASH_BIT (__SIZEOF_HASH__ * CHAR_BIT)
#define WORD_BIT (__SIZEOF_WORD__ * CHAR_BIT)
