/*
This file is part of Corewars Redcode Evolver (CRE).

CRE is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

CRE is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with CRE; if not, write to the Free Software
Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/
#include <stdio.h>
#include <stdlib.h>
#include "exhaust/exhaust.h"
#include "exhaust/sim.h"
#include "exhaust/asm.h"
#include "globals.h"

#define WIN 3
#define TIE 1

void fight(int wa1, int wa2)
{
	warrior_t w1, w2;
	insn_t* core;
	int battle, pos, result;
	char name1[25], name2[25];

	core = sim_alloc_bufs(2, CORE, THREADS, CYCLES);
	wa1_score = 0;
	wa2_score = 0;
	sprintf(name1, "cre_%i.red", wa1);
	sprintf(name2, "cre_%i.red", wa2);
	asm_fname(name1, &w1, CORE);
	asm_fname(name2, &w2, CORE);
	for (battle = 0; battle < BATTLES; battle++)
	{
		sim_clear_core();
		sim_load_warrior(0, &(w1.code[0]), w1.len);
		pos = random(0, (CORE - (DISTANCE * 2)) + DISTANCE);
		sim_load_warrior(pos, &(w2.code[0]), w2.len);
		result = sim(2, w1.start, w2.start + pos, CYCLES, NULL);
		switch (result)
		{
			case 0:
			{
				wa1_score += WIN;
				break;
			}
			case 1:
			{
				wa2_score += WIN;
				break;
			}
			case 2:
			{
				wa1_score += TIE;
				wa2_score += TIE;
				break;
			}
		}
	}
	sim_free_bufs();
	return;
}
