/*******************************************************************
(C) 2011 by Radu Stefan
radu124@gmail.com

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; version 2 of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.
*******************************************************************/

#include <cstring>
#include "confrw.h"

void CONFREAD_GLfloat(char *&s, GLfloat &v)
{
	v=atof(s);
	//DBG(CONFIG," value GLfloat %f (from:%s)\n" ,v ,s);
}

void CONFREAD_int(char *&s, int &v)
{
	v=atoi(s);
	//DBG(CONFIG," value int %d (from:%s)\n" ,v ,s);
}

void CONFREAD_string(char *&s, std::string &v)
{
	v=std::string(s);
	//DBG(CONFIG," value string '%s'\n" ,v);
}

/**
 * return the value of the given hexadecimal digit or 0
 * if the character is not a hexadecimal digit
 * @param c input hexadecimal digit
 * @return the value of the digit
 */
int hexdigit(char c)
{
	if (c>='0' && c<='9') return c-'0';
	if (c>='a' && c<='f') return c-'a'+10;
	if (c>='A' && c<='F') return c-'A'+10;
	return 0;
}

/**
 * return the value of a two-digit hexadecimal number
 * @param c the input number (char *) string
 * @return the value of the hexadecimal number
 */
int hexbyte(const char *c)
{
	return 16*hexdigit(c[0])+hexdigit(c[1]);
}

int multiplechoice(const char *s, const char *choices)
{
	const char *cc=choices;
	int len;
	int cnt=0;
	const char *nc;
	while (1)
	{
		nc=std::strchr(cc,',');
		if (nc) {
			len=nc-cc;
		} else len=std::strlen(cc);
		//DBG(CONFIG,"MULTICHOICE %s %d -match:%s\n" &cc &len &s);
		if (0==std::strncmp(cc,s,len)) return cnt;
		cnt++;
		if (!nc) break;
		cc=nc+1;
	}
	return 0;
}



