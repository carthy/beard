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

bool Map_has (Map* self, uint64_t hash);

Tuple* Map_put (Map* self, uint64_t hash, Value* key, Value* value);

Tuple* Map_put_pair (Map* self, uint64_t hash, Tuple* pair);

Value* Map_get_value (Map* self, uint64_t hash);

Value* Map_get_key (Map* self, uint64_t hash);

Tuple* Map_get_pair (Map* self, uint64_t hash);

Tuple* Map_delete (Map* self, uint64_t hash);

Vector* Map_pairs (Map* self);

Vector* Map_keys (Map* self);

Vector* Map_values (Map* self);

uint64_t Map_length (Map* self);

uint64_t Map_hash (Map* self);
