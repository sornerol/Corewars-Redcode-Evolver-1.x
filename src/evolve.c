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
#include "globals.h"

void evolve(void)
{
	int wa1, wa2, s_temp, temp;
	int* score_t;
	int* war_t;

	ROUND = 1;
	populate();
	score_t = (int*)malloc(sizeof(int) * WARRIORS);
	war_t = (int*)malloc(sizeof(int) * WARRIORS);
	for (wa1 = 0; wa1 < WARRIORS; wa1++)
	{
		war_t[wa1] = wa1;
	}
	while (ROUND < STOP)
	{
		printf("Round %i\n", ROUND);
		for (wa1 = 0; wa1 < WARRIORS; wa1++)
		{
			score_t[wa1] = 0;
		}
		for (wa1 = 0; wa1 < WARRIORS; wa1++)
		{
			for (wa2 = wa1 + 1; wa2 < WARRIORS; wa2++)
			{
				fight(war_t[wa1], war_t[wa2]);
				score_t[wa1] += wa1_score;
				score_t[wa2] += wa2_score;
			}
		}
		for (wa1 = 0; wa1 < WARRIORS; wa1++)
		{
			for (wa2 = wa1 + 1; wa2 < WARRIORS; wa2++)
			{
				if (score_t[wa2] > score_t[wa1])
				{
					s_temp = score_t[wa2];
					score_t[wa2] = score_t[wa1];
					score_t[wa1] = s_temp;

					temp = war_t[wa2];
					war_t[wa2] = war_t[wa1];
					war_t[wa1] = temp;
				}
			}
		}
		for (wa1 = 0; wa1 < WARRIORS / 2; wa1++)
		{
			reproduce(war_t[wa1], war_t[(WARRIORS / 2) + wa1]);
		}

		ROUND++;
	}
	printf("Successfully completed %i evolution cycles\n\n", STOP);
	free(score_t);
	free(war_t);
	return;
}
