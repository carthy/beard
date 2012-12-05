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

#ifndef BEARD_FREELIST_H
#define BEARD_FREELIST_H

#include <Judy.h>

typedef void* (*FreeListConstructor) (void);
typedef void (*FreeListDestructor) (void*);

typedef struct FreeList {
	Pvoid_t array;
	int     limit;

	FreeListConstructor constructor;
	FreeListDestructor  destructor;
} FreeList;

FreeList* FreeList_new (FreeListConstructor constructor, FreeListDestructor destructor);

FreeList* FreeList_new_with_limit (int limit, FreeListConstructor constructor, FreeListDestructor destructor);

void FreeList_set_limit (FreeList* self, int limit);

int FreeList_get_limit (FreeList* self);

void FreeList_destroy (FreeList* self);

void FreeList_put (FreeList* self, void* thing);

void* FreeList_get (FreeList* self);

#endif
