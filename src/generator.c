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
#include <string.h>
#include "redcode.h"
#include "globals.h"

int r0, r1, r2, r3, r4, r5;
void mutate_line(char* line);

void populate(void)
{
	int warrior, insn;
	char w_name[15];
	FILE* w_code;

	puts("Creating population...");
	for (warrior = 0; warrior < WARRIORS; warrior++)
	{
		sprintf(w_name, "cre_%i.red", warrior);
		w_code = fopen(w_name, "r");
		if (w_code)
		{
			printf("Found %s\n", w_name);
			fclose(w_code);
			continue;
		}
		w_code = fopen(w_name, "w");
		fprintf(w_code, ";redcode-94\n");
		fprintf(w_code, ";name %s\n", w_name);
		fprintf(w_code, ";author Loren Jamison\n");
		fprintf(w_code, ";assert CORESIZE==%i\n", CORE);
		fprintf(w_code, ";strategy generated by CRE v1.2\n;strategy by Loren Jamison\n");
		for (insn = 0; insn < SIZE; insn++)
		{
			r0 = random(0, INSTRUCTIONS);
			r1 = random(0, MODIFIERS);
			r2 = random(0, ADDRESSMODES);
			r3 = random(0, CORE);
			r4 = random(0, ADDRESSMODES);
			r5 = random(0, CORE);
			fprintf(w_code, "%s%s %c%i, %c%i\n", opcodes[r0],
				modifiers[r1], addressmodes[r2], r3, addressmodes[r4], r5);
		}
		fprintf(w_code, "END 0");
		fclose(w_code);
		printf("Created %s\n", w_name);
	}
	return;
}

void reproduce(int src, int dest)
{
	char srcname[26], destname[26], temp[256];
	FILE* srcfile, * destfile;
	int rnd, lineno;
	struct warriorcode
	{
		char line[256];
		struct warriorcode* next;
	}*first, * current, * new;

	first = current = new = (struct warriorcode*)NULL;
	sprintf(srcname, "cre_%i.red", src);
	srcfile = fopen(srcname, "r");
	new = (struct warriorcode*)malloc(sizeof(struct warriorcode));
	first = current = new;
	while (strcmp(fgets(temp, 255, srcfile), "END 0") != 0)
	{
		if (temp[0] == ';')continue;
		memset(current->line, 0, sizeof(current->line));
		strcpy(current->line, temp);
		new = (struct warriorcode*)malloc(sizeof(struct warriorcode));
		current->next = new;
		current = new;
		memset(temp, 0, sizeof(temp));
	}
	current->line[0] = '\n';
	current->next = (struct warriorcode*)NULL;
	fclose(srcfile);
	sprintf(destname, "cre_%i.red", dest);
	destfile = fopen(destname, "w");
	fprintf(destfile, ";redcode-94\n");
	fprintf(destfile, ";name %s\n", destname);
	fprintf(destfile, ";author Loren Jamison\n");
	fprintf(destfile, ";assert CORESIZE==%i\n", CORE);
	fprintf(destfile, ";strategy generated by CRE v1.2\n;strategy by Loren Jamison\n");
	current = first;
	lineno = 0;
	while (current->line[0] != '\n' && lineno < SIZE)
	{
		rnd = random(0, 100);
		if (rnd < INSERT && lineno < (SIZE - 1))
		{
			if (random(0, 1))fprintf(destfile, "%s", current->line);
			else
			{
				r0 = random(0, INSTRUCTIONS);
				r1 = random(0, MODIFIERS);
				r2 = random(0, ADDRESSMODES);
				r3 = random(0, CORE);
				r4 = random(0, ADDRESSMODES);
				r5 = random(0, CORE);
				fprintf(destfile, "%s%s %c%i, %c%i\n", opcodes[r0],
					modifiers[r1], addressmodes[r2], r3, addressmodes[r4], r5);
			}
			lineno++;
		}
		else if (rnd < DELETE && (lineno > 0 || current->next->line[0] != '\n'))current = current->next;
		else if (rnd < MUTATION)
		{
			mutate_line(current->line);
			fprintf(destfile, "%s", current->line);
			current = current->next;
			lineno++;
		}
		else
		{
			fprintf(destfile, "%s", current->line);
			current = current->next;
			lineno++;
		}
	}
	fprintf(destfile, "END 0");
	fclose(destfile);
	current = first;
	while (current != (struct warriorcode*)NULL)
	{
		new = current->next;
		free(current);
		current = new;
	}
	return;
}

void mutate_line(char* line)
{
	int m, x, y; //m- mutations, x and y- track current position in line during importing process
	int rnd;
	unsigned int num;
	char op[4], mod[4], a1, a2, num1[6], num2[6];

	/*first, import the current line*/
	for (x = 0; x < 3; x++)
	{
		op[x] = line[x];
	}
	op[3] = '\0';
	for (y = 0; line[x] != ' '; y++)
	{
		mod[y] = line[x];
		x++;
	}
	mod[y] = '\0';
	x++;
	a1 = line[x];
	x++;
	for (y = 0; line[x] != ','; y++)
	{
		num1[y] = line[x];
		x++;
	}
	num1[y] = '\0';
	x += 2;
	a2 = line[x];
	x++;
	for (y = 0; line[x] != '\n'; y++)
	{
		num2[y] = line[x];
		x++;
	}
	num2[y] = '\0';
	/*Next, perform mutations*/
	for (m = 0; m < MPL; m++)
	{
		switch (random(0, 5))
		{
		case 0:
		{
			sprintf(op, "%s", opcodes[random(0, INSTRUCTIONS)]);
			break;
		}
		case 1:
		{
			sprintf(mod, "%s", modifiers[random(0, MODIFIERS)]);
			break;
		}
		case 2:
		{
			a1 = addressmodes[random(0, ADDRESSMODES)];
			break;
		}
		case 3:
		{
			sprintf(num1, "%i", random(0, CORE));
			break;
		}
		case 4:
		{
			a2 = addressmodes[random(0, ADDRESSMODES)];
			break;
		}
		case 5:
		{
			sprintf(num2, "%i", random(0, CORE));
			break;
		}
		}
	}
	memset(line, 0, sizeof(line));
	sprintf(line, "%s%s %c%s, %c%s\n", op, mod, a1, num1, a2, num2);
	return;
}