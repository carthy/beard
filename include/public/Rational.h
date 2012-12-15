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

typedef struct Rational Rational;

Rational* Rational_new (Runtime* rt);

Rational* Rational_set_native (Rational* self, long nominator, long denominator);

Rational* Rational_set_integer (Rational* self, Integer* value);

Rational* Rational_set_string (Rational* self, const char* string);

Rational* Rational_set_string_with_base (Rational* self, const char* string, int base);

bool Rational_eq (Rational* self, Value* other);

bool Rational_lt (Rational* self, Value* other);

bool Rational_gt (Rational* self, Value* other);

Rational* Rational_add (Rational* self, Value* other);

Rational* Rational_sub (Rational* self, Value* other);
