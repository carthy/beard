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

#ifndef BEARD_RATIONAL_H
#define BEARD_RATIONAL_H

#include <public/Rational.h>

struct Rational {
	Value descriptor;

	mpq_t* value;

	struct {
		hash_t hash;
	} cache;
};

void Rational_destroy (Rational* self);

Rational* Rational_set_numerator_gmp (Rational* self, mpz_t* numerator);

Rational* Rational_set_denominator_gmp (Rational* self, mpz_t* denominator);

#endif
