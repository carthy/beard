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

typedef struct Map Map;

Map* Map_new (Runtime* rt);

bool Map_has (Map* self, uint64_t key);

Value* Map_put (Map* self, uint64_t key, Value* value);

Value* Map_get (Map* self, uint64_t key);

Value* Map_get_with_default (Map* self, uint64_t key, Value* value);

Value* Map_delete (Map* self, uint64_t key);

Value* Map_delete_with_default (Map* self, uint64_t key, Value* value);

uint64_t Map_length (Map* self);
