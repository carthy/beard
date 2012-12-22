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

#include <public/Runtime.h>
#include <private/GC.h>

struct Runtime {
	GC* garbage_collector;

	struct {
		gmp_randstate_t fast;
		gmp_randstate_t slow;
	} random;

	uint8_t sip_key[16];
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
	siphash((runtime)->sip_key, (const unsigned char*) buffer, length)

#endif
