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
#include <time.h>
#include "globals.h"

int main(void)
{
	int selection;

	srand((unsigned)time(NULL));
	while (1)
	{
		puts("C O R E W A R S   R E D C O D E   E V O L V E R");
		puts("Version 1.2 <<<BETA>>>");
		puts("This software is released under the terms of the GNU GPL.");
		read_globals();
		show_globals();
		selection = text_menu("Use these options\0Use custom options\0Exit CRE\0");
		switch (selection)
		{
			case 1:
			{
				evolve();
				break;
			}
			case 2:
			{
				define_globals();
				save_globals();
				break;
			}
			case 3:
			{
				return 0;
			}
		}
	}
}

void init_globals(void)
{
	CORE = 80;
	CYCLES = 800;
	THREADS = 80;
	DISTANCE = 5;
	WARRIORS = 100;
	SIZE = 5;
	INSERT = 10;
	DELETE = 20;
	MUTATION = 35;
	MPL = 2;
	BATTLES = 50;
	STOP = 100;
	return;
}

void show_globals(void)
{
	puts("Current options:\n");
	printf("Core size: %i\n", CORE);
	printf("Cycles per battle: %i\n", CYCLES);
	printf("Threads per warrior: %i\n", THREADS);
	printf("Distance between warriors: %i\n", DISTANCE);
	printf("Population size: %i\n", WARRIORS);
	printf("Maximum size of warrior: %i\n", SIZE);
	printf("Insert rate: %i\n", INSERT);
	printf("Delete rate: %i\n", DELETE - INSERT);
	printf("Mutation rate: %i\n", MUTATION - DELETE);
	printf("Mutations per line: %i\n", MPL);
	printf("Battles per pair: %i\n", BATTLES);
	if (STOP > 0)printf("Stop evolution at %i evolution cycles\n", STOP);
	else puts("Infinite evolution\n");
	putchar('\n');
	return;
}

void define_globals(void)
{
	printf("Core size (2+): ");
	scanf("%i", &CORE);
	printf("Cycles per battle (1+): ");
	scanf("%i", &CYCLES);
	printf("Threads per warrior (1+): ");
	scanf("%i", &THREADS);
	printf("Distance between warriors (1+): ");
	scanf("%i", &DISTANCE);
	printf("Population size (2+): ");
	scanf("%i", &WARRIORS);
	printf("Maximum size of warrior (1+): ");
	scanf("%i", &SIZE);
	printf("Insert rate (0-100): ");
	scanf("%i", &INSERT);
	printf("Delete rate (0-100): ");
	scanf("%i", &DELETE);
	DELETE += INSERT;
	printf("Mutation rate (0-100): ");
	scanf("%i", &MUTATION);
	MUTATION += DELETE;
	printf("Mutatios per line (1-6): ");
	scanf("%i", &MPL);
	printf("Battles per pair (1+): ");
	scanf("%i", &BATTLES);
	printf("Evolution cycles (1+, or -1 for no limit): ");
	scanf("%i", &STOP);
	putchar('\n');
	return;
}

void save_globals(void)
{
	FILE* global_params;

	global_params = fopen("globals.dat", "wb");
	fwrite(&globals, sizeof(globals), 1, global_params);
	fclose(global_params);
	return;
}

void read_globals(void)
{
	FILE* global_params;

	global_params = fopen("globals.dat", "rb");
	if (!global_params)
	{
		init_globals();
		return;
	}
	fread(&globals, sizeof(globals), 1, global_params);
	fclose(global_params);
	return;
}

int random(int start, int end)
{
	return (int)((((double)rand() / (double)(RAND_MAX + 1)) * end) + start);
}
