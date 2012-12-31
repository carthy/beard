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

typedef struct Value Value;

typedef enum ValueType {
	VALUE_TYPE_NIL,
	VALUE_TYPE_BOOLEAN,
	VALUE_TYPE_INTEGER,
	VALUE_TYPE_FLOATING,
	VALUE_TYPE_RATIONAL,
	VALUE_TYPE_COMPLEX,
	VALUE_TYPE_REGEXP,
	VALUE_TYPE_STRING,
	VALUE_TYPE_BITMAP,
	VALUE_TYPE_TUPLE,
	VALUE_TYPE_VECTOR,
	VALUE_TYPE_MAP,

	VALUE_TYPE_FUNCTION
} ValueType;

#define NIL   ((Value*) 0)
#define TRUE  ((Value*) 1)
#define FALSE ((Value*) 2)

bool is_nil      (Value* self);
bool is_false    (Value* self);
bool is_true     (Value* self);
bool is_boolean  (Value* self);
bool is_integer  (Value* self);
bool is_floating (Value* self);
bool is_rational (Value* self);
bool is_complex  (Value* self);
bool is_regexp   (Value* self);
bool is_string   (Value* self);
bool is_bitmap   (Value* self);
bool is_tuple    (Value* self);
bool is_vector   (Value* self);
bool is_map      (Value* self);
bool is_function (Value* self);

bool is_falsy (Value* self);
bool is_truthy (Value* self);

ValueType type_of (Value* self);

bool   is_frozen (Value* self);
Value* freeze (Value* self);

hash_t hash_for (Value* value);
