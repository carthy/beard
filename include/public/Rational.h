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

#define Rational_set(...) Rational_set_(ARGS_LENGTH(__VA_ARGS__)) (__VA_ARGS__)
#define Rational_set_(nargs)  Rational_set__(nargs)
#define Rational_set__(nargs) Rational_set##nargs

#define Rational_set2(self, X) _Generic((X), \
	long:     Rational_set_native,  \
	Integer*: Rational_set_integer, \
\
	default: Rational_set_string \
)(self, X)

#define Rational_set3(self, X, Y) _Generic((X), \
	long:     Rational_set_native, \
	Integer*: Rational_set_integer \
)(self, X, Y)

Rational* Rational_set_native (Rational* self, long numerator, long denominator);

#define Rational_set_native(...) \
	((ARGS_LENGTH(__VA_ARGS__) == 2) ? \
		Rational_set_native(ARGS_FIRST(__VA_ARGS__), ARGS_SECOND(__VA_ARGS__), 1) : \
		Rational_set_native(ARGS_FIRST(__VA_ARGS__), ARGS_SECOND(__VA_ARGS__), ARGS_THIRD(__VA_ARGS__)))

Rational* Rational_set_integer (Rational* self, Integer* numerator, Integer* denominator);

#define Rational_set_integer(...) \
	((ARGS_LENGTH(__VA_ARGS__) == 2) ? \
		Rational_set_native(ARGS_FIRST(__VA_ARGS__), ARGS_SECOND(__VA_ARGS__), NIL) : \
		Rational_set_native(ARGS_FIRST(__VA_ARGS__), ARGS_SECOND(__VA_ARGS__), ARGS_THIRD(__VA_ARGS__)))

#define Rational_set_numerator(self, X) _Generic((X), \
	long:     Rational_set_numerator_native,  \
	Integer*: Rational_set_numerator_integer  \
)(self, X)

Rational* Rational_set_numerator_native (Rational* self, long numerator);

Rational* Rational_set_numerator_integer (Rational* self, Integer* numerator);

#define Rational_set_denominator(self, X) _Generic((X), \
	long:     Rational_set_denominator_native,  \
	Integer*: Rational_set_denominator_integer  \
)(self, X)

Rational* Rational_set_denominator_native (Rational* self, long denominator);

Rational* Rational_set_denominator_integer (Rational* self, Integer* denominator);

Rational* Rational_set_string (Rational* self, const char* string);

Rational* Rational_set_string_with_base (Rational* self, const char* string, int base);

Integer* Rational_numerator (Rational* self);

Integer* Rational_denominator (Rational* self);

bool Rational_eq (Rational* self, Value* other);

bool Rational_lt (Rational* self, Value* other);

bool Rational_gt (Rational* self, Value* other);

Value* Rational_add (Rational* self, Value* other);

Value* Rational_sub (Rational* self, Value* other);

Value* Rational_mul (Rational* self, Value* other);

Value* Rational_div (Rational* self, Value* other);

uint64_t Rational_hash (Rational* self);
