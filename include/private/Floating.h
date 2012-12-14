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

#ifndef BEARD_FLOATING_H
#define BEARD_FLOATING_H

#include <public/Floating.h>

struct Floating {
	Value descriptor;

	mpf_t* value;
};

#define NAN ((mpf_t*) 0)

#define POSITIVE_INFINITY ((mpf_t*) 1)

#define NEGATIVE_INFINITY ((mpf_t*) 2)

#define INFINITY POSITIVE_INFINITY

#define FLOATING_IS_NAN(f) ((f)->value == NAN)

#define FLOATING_IS_POSITIVE_INFINITY(f) ((f)->value == POSITIVE_INFINITY)

#define FLOATING_IS_NEGATIVE_INFINITY(f) ((f)->value == NEGATIVE_INFINITY)

#define FLOATING_IS_INFINITY(f) FLOATING_IS_POSITIVE_INFINITY(f)

#define FLOATING_IS_GMP(f) !(FLOATING_IS_NAN(f) || FLOATING_IS_POSITIVE_INFINITY(f) || FLOATING_IS_NEGATIVE_INFINITY(f))

void Floating_destroy (Floating* self);

#endif
