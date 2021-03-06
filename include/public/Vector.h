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

typedef struct Vector Vector;

Vector* Vector_new (Runtime* rt);

Vector* Vector_resize (Vector* self, size_t size);

Value* Vector_set (Vector* self, size_t index, Value* value);

Value* Vector_get (Vector* self, size_t index);

Vector* Vector_insert (Vector* self, Value* value, size_t index);

Vector* Vector_insert_first (Vector* self, Value* value);

Vector* Vector_insert_last (Vector* self, Value* value);

size_t Vector_length (Vector* self);

hash_t Vector_hash (Vector* self);
