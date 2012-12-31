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

typedef struct Bitmap Bitmap;

Bitmap* Bitmap_new (Runtime* rt);

Bitmap* Bitmap_set (Bitmap* self, size_t index);

Bitmap* Bitmap_unset (Bitmap* self, size_t index);

Bitmap* Bitmap_put (Bitmap* self, size_t index, bool value);

bool Bitmap_get (Bitmap* self, size_t index);

size_t Bitmap_bits (Bitmap* self);

hash_t Bitmap_hash (Bitmap* self);
