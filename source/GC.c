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

#include <private/Runtime.h>
#include <private/common.h>

#include <private/Integer.h>
#include <private/Floating.h>
#include <private/Rational.h>
#include <private/Regexp.h>
#include <private/String.h>
#include <private/List.h>
#include <private/Vector.h>
#include <private/Map.h>

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
GC_new (Runtime* rt)
{
	assert(rt);

	GC* self = malloc(sizeof(GC));

	self->runtime = rt;

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

// TODO: actual garbage collection
Value*
GC_allocate (GC* self, ValueType type)
{
	Value* value = NULL;

	switch (type) {
		case VALUE_TYPE_NIL:
			assert(false);

		case VALUE_TYPE_BOOLEAN:
			assert(false);

		case VALUE_TYPE_INTEGER:
			value = malloc(sizeof(Integer));
			break;

		case VALUE_TYPE_FLOATING:
			value = malloc(sizeof(Floating));
			break;

		case VALUE_TYPE_RATIONAL:
			value = malloc(sizeof(Rational));
			break;

		case VALUE_TYPE_REGEXP:
			value = malloc(sizeof(Regexp));
			break;

		case VALUE_TYPE_STRING:
			value = malloc(sizeof(String));
			break;

		case VALUE_TYPE_LIST:
			value = malloc(sizeof(List));
			break;

		case VALUE_TYPE_VECTOR:
			value = malloc(sizeof(Vector));
			break;

		case VALUE_TYPE_MAP:
			value = malloc(sizeof(Map));
			break;
	}

	value->type    = type;
	value->meta    = NIL;
	value->runtime = self->runtime;

	return value;
}

mpz_t*
GC_get_integer (GC* self)
{
	return FreeList_get(self->integer);
}

void
GC_put_integer (GC* self, mpz_t* value)
{
	FreeList_put(self->integer, value);
}

mpf_t*
GC_get_floating (GC* self)
{
	return FreeList_get(self->floating);
}

void
GC_put_floating (GC* self, mpf_t* value)
{
	FreeList_put(self->floating, value);
}

mpq_t*
GC_get_rational (GC* self)
{
	return FreeList_get(self->rational);
}

void
GC_put_rational (GC* self, mpq_t* value)
{
	FreeList_put(self->rational, value);
}
