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
#include <private/FreeList.h>

#include <gmp.h>
#include <mpfr.h>

typedef struct GC {
	Runtime* runtime;

	FreeList* integer;
	FreeList* floating;
	FreeList* rational;
} GC;

GC* GC_new (Runtime* rt);

void GC_destroy (GC* self);

Value* GC_allocate (GC* self, ValueType type);

void GC_run (GC* self);

mpz_t* GC_get_integer (GC* self);

void GC_put_integer (GC* self, mpz_t* value);

mpfr_t* GC_get_floating (GC* self);

void GC_put_floating (GC* self, mpfr_t* value);

mpq_t* GC_get_rational (GC* self);

void GC_put_rational (GC* self, mpq_t* value);

#endif
