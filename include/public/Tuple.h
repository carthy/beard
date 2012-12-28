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

typedef struct Tuple Tuple;

Tuple* Tuple_new (Runtime* rt, size_t size);

Tuple* Tuple_new_with (Runtime* rt, size_t size, ...);

#define Tuple_new_with(rt, ...) \
	Tuple_new_with(rt, ARGS_LENGTH(__VA_ARGS__), __VA_ARGS__)

Value* Tuple_set (Tuple* self, size_t index, Value* value);

Value* Tuple_get (Tuple* self, size_t index);

Value** Tuple_items (Tuple* self);

size_t Tuple_size (Tuple* self);

hash_t Tuple_hash (Tuple* self);
