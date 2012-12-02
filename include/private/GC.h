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

#ifndef BEARD_GC_H
#define BEARD_GC_H

#include <private/Value.h>
#include <public/GC.h>
#include <private/FreeList.h>

#include <gmp.h>

struct GC {
	FreeList* integer;
	FreeList* floating;
	FreeList* rational;
};

mpz_t* GC_get_integer (GC* self);
mpf_t* GC_get_floating (GC* self);
mpq_t* GC_get_rational (GC* self);

#endif
