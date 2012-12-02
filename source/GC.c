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

#include <private/GC.h>
#include <private/common.h>

static void*
_mpz_constructor (void)
{
	mpz_t* value = malloc(sizeof(mpz_t));
	mpz_init(*value);

	return value;
}

static void
_mpz_destructor (void* value)
{
	mpz_clear(*(mpz_t*) value);
	free(value);
}

static void*
_mpf_constructor (void)
{
	mpf_t* value = malloc(sizeof(mpf_t));
	mpf_init(*value);

	return value;
}

static void
_mpf_destructor (void* value)
{
	mpf_clear(*(mpf_t*) value);
	free(value);
}

static void*
_mpq_constructor (void)
{
	mpq_t* value = malloc(sizeof(mpq_t));
	mpq_init(*value);

	return value;
}

static void
_mpq_destructor (void* value)
{
	mpq_clear(*(mpq_t*) value);
	free(value);
}

GC*
GC_new (void)
{
	GC* self = malloc(sizeof(GC));

	self->integer  = FreeList_new(_mpz_constructor, _mpz_destructor);
	self->floating = FreeList_new(_mpf_constructor, _mpf_destructor);
	self->rational = FreeList_new(_mpq_constructor, _mpq_destructor);

	return self;
}

void
GC_destroy (GC* self)
{
	FreeList_destroy(self->integer);
	FreeList_destroy(self->floating);
	FreeList_destroy(self->rational);

	free(self);
}

void*
GC_allocate (ValueType type)
{

}

mpz_t*
GC_get_integer (GC* self)
{
	return FreeList_get(self->integer);
}

mpf_t*
GC_get_floating (GC* self)
{
	return FreeList_get(self->floating);
}

mpq_t*
GC_get_rational (GC* self)
{
	return FreeList_get(self->rational);
}
