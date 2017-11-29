/*
 * isr.S
 *
 *  Created on: 13 Nov, 2016
 *      Author: sylam
 */

#include <regdef.h>
#include <p32mx250f128d.h>

	.set		noreorder

#if 1
	.extern		t3ISR
	.section	.vector_12,"ax",@progbits
	.ent		_vector_12
_vector_12:
	j			t3ISR
	nop
	.end		_vector_12
#endif

	.set 		reorder



