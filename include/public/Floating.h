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

typedef struct Floating Floating;

Floating* Floating_new (Runtime* rt);

Floating* Floating_new_with_precision (Runtime* rt, unsigned long precision);

unsigned long Floating_set_precision (Floating* self, unsigned long precision);

unsigned long Floating_get_precision (Floating* self);

#define Floating_set(X) _Generic((X), \
	double: Floating_set_double, \
\
	default: Floating_set_string \
)(X)

Floating* Floating_set_double (Floating* self, double number);

Floating* Floating_set_string (Floating* self, const char* number);

Floating* Floating_set_string_with_base (Floating* self, const char* number, int base);

Floating* Floating_add (Floating* self, Value* other);

Floating* Floating_sub (Floating* self, Value* other);
