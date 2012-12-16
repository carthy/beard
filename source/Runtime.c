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

#include <sys/time.h>

Runtime*
Runtime_new (void)
{
	Runtime* self = malloc(sizeof(Runtime));

	self->garbage_collector = GC_new(self);

	struct timeval tv;
	gettimeofday(&tv, NULL);

	gmp_randinit_mt(self->random.fast);
	gmp_randinit_lc_2exp_size(self->random.slow, 128);

	gmp_randseed_ui(self->random.fast, tv.tv_usec);
	gmp_randseed_ui(self->random.slow, tv.tv_usec);

	mpz_t rand;
	mpz_t max;

	mpz_inits(rand, max, NULL);
	mpz_set_ui(max, UINT8_MAX);

	for (uint8_t i = 0; i < sizeof(self->sip_key); i++) {
		mpz_urandomm(rand, self->random.slow, max);

		self->sip_key[i] = mpz_get_ui(rand);
	}

	mpz_clears(rand, max, NULL);

	return self;
}

void
Runtime_destroy (Runtime* self)
{
	assert(self);

	GC_destroy(self->garbage_collector);
}
