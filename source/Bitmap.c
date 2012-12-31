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

#include <private/common.h>
#include <private/Runtime.h>
#include <private/Bitmap.h>

Bitmap*
Bitmap_new (Runtime* rt)
{
	Bitmap* self = (Bitmap*) GC_ALLOCATE(rt, BITMAP);

	self->array = NULL;

	return self;
}

void
Bitmap_destroy (Bitmap* self)
{
	Word_t freed;

	J1FA(freed, self->array);
}

Bitmap*
Bitmap_set (Bitmap* self, size_t index)
{
	Word_t ind = index;
	Word_t res;

	J1S(res, self->array, ind);

	return self;
}

Bitmap*
Bitmap_unset (Bitmap* self, size_t index)
{
	Word_t ind = index;
	Word_t res;

	J1U(res, self->array, ind);

	return self;
}

Bitmap*
Bitmap_put (Bitmap* self, size_t index, bool value)
{
	return value ? Bitmap_set(self, index) : Bitmap_unset(self, index);
}

bool
Bitmap_get (Bitmap* self, size_t index)
{
	Word_t res;

	J1T(res, self->array, index);

	return res;
}

size_t
Bitmap_bits (Bitmap* self)
{
	Word_t size;

	J1C(size, self->array, 0, -1);

	return size;
}
