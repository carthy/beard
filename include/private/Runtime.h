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

#ifndef BEARD_RUNTIME_H
#define BEARD_RUNTIME_H

#include <hash.h>

#include <public/Runtime.h>
#include <private/GC.h>

struct Runtime {
	GC* garbage_collector;

	struct {
		gmp_randstate_t fast;
		gmp_randstate_t slow;
	} random;

	struct {
		uint8_t siphash[16];
		hash_t  crapwow;
		hash_t  murmur3;
	} hash;
};

#define RUNTIME_FOR(value) \
	(((Value*) (value))->runtime)

#define GC_ALLOCATE(rt, type) \
	GC_allocate(rt->garbage_collector, VALUE_TYPE_##type)

#define GC_NEW_INTEGER(rt) \
	GC_get_integer(rt->garbage_collector)

#define GC_SAVE_INTEGER(rt, value) \
	GC_put_integer(rt->garbage_collector, value)

#define GC_NEW_FLOATING(rt) \
	GC_get_floating(rt->garbage_collector)

#define GC_SAVE_FLOATING(rt, value) \
	GC_put_floating(rt->garbage_collector, value)

#define GC_NEW_RATIONAL(rt) \
	GC_get_rational(rt->garbage_collector)

#define GC_SAVE_RATIONAL(rt, value) \
	GC_put_rational(rt->garbage_collector, value)

#define GC_NEW_COMPLEX(rt) \
	GC_get_complex(rt->garbage_collector)

#define GC_SAVE_COMPLEX(rt, value) \
	GC_put_complex(rt->garbage_collector, value)

#define CACHE(s) \
	(&(self->cache))

#define SIPHASH(runtime, buffer, length) \
	siphash((runtime)->hash.siphash, buffer, length)

#define SIPHASH_WITH(runtime, data) \
	siphash_with((runtime)->hash.siphash, data)

#define CRAPWOW(runtime, buffer, length) \
	crapwow((runtime)->hash.crapwow, buffer, length)

#define CRAPWOW_WITH(runtime, data) \
	crapwow_with((runtime)->hash.crapwow, data)

#define MURMUR3(runtime, buffer, length) \
	murmur3((runtime)->hash.murmur3, buffer, length)

#define MURMUR3_WITH(runtime, data) \
	murmur3_with((runtime)->hash.murmur3, data)

#define MURMUR3_INIT(runtime) \
	murmur3_init(murmur3_new(), (runtime)->hash.murmur3)

#define MURMUR3_UPDATE(state, buffer, length) \
	murmur3_update(state, buffer, length)

#define MURMUR3_UPDATE_WITH(state, data) \
	murmur3_update_with(state, data)

#define MURMUR3_FINAL(state) ({ \
	hash_t hash; \
\
	murmur3_final(state); \
	hash = murmur3_fetch(state); \
	murmur3_free(state); \
\
	hash; \
})

#endif
