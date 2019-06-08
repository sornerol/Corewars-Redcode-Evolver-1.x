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

#ifndef REDCODE_H
#define REDCODE_H

#define INSTRUCTIONS 15
#define MODIFIERS 7
#define ADDRESSMODES 8

const char* opcodes[] = {
"DAT","MOV","SPL","ADD","SUB",
"MUL","DIV","MOD","JMP","JMZ",
"JMN","SLT","SEQ","SNE","DJN" };
const char* modifiers[] = {
".A",".B",".AB",".BA",
".F",".X",".I" };
const char addressmodes[] = {
'#','$','@','<',
'>','*','{','}' };
#endif
