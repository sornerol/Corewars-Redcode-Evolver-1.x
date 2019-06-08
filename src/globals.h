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

#ifndef GLOBALS_H
#define GLOBALS_H


int random(int start, int end);
void init_globals(void);
void show_globals(void);
void define_globals(void);
void save_globals(void);
void read_globals(void);
void populate(void);
void evolve(void);

unsigned long rnd;

struct globals
{
	int core;
	int cycles;
	int threads;
	int distance;
	int warriors;
	int max_size;
	int insert_rate;
	int delete_rate;
	int mutation_rate;
	int mutations_per_line;
	int battles;
	int battle_cycles;
}globals;

#define ROUND rnd

#define CORE globals.core
#define CYCLES globals.cycles
#define THREADS globals.threads
#define DISTANCE globals.distance
#define WARRIORS globals.warriors
#define SIZE globals.max_size
#define INSERT globals.insert_rate
#define DELETE globals.delete_rate
#define MUTATION globals.mutation_rate
#define MPL globals.mutations_per_line
#define BATTLES globals.battles
#define STOP globals.battle_cycles

int wa1_score, wa2_score;

#endif
