/* Copyleft (¿) meh. - http://meh.schizofreni.co
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

Value* Vector_set (Vector* self, uint64_t index, Value* value);

Value* Vector_get (Vector* self, uint64_t index);

Vector* Vector_conj (Vector* self, Value* value);

uint64_t Vector_length (Vector* self);
