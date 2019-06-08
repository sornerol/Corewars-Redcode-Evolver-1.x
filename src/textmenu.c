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

/*text_menu()
 *
 *Displays a menu with the choices provided by arg 1
 *Choices are separated by NULL bytes
 *The last choice must end with a NULL byte
 *Returns a number between 1 and the number of choices
 *Returns 0 on error
 *
 *example: result=text_menu("Choice1\0Choice2\0Choice3\0Choice4\0");
 */

#include <stdio.h>

int text_menu(char* choices)
{
	int choice = 0;
	int ret;
	if (*choices == '\0')
	{
		return 0;
	}
	do
	{
		printf("%i: ", choice + 1);
		while (*choices != '\0')
		{
			putchar(*choices);
			choices++;
		}
		choice++;
		choices++;
		putchar('\n');
	} while (*choices != '\0');
	do
	{
		printf("Your choice: ");
		scanf("%i", &ret);
		putchar('\n');
	} while (ret < 0 && ret >= choice);
	return ret;
}
