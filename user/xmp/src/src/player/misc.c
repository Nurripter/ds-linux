/* Extended Module Player
 * Copyright (C) 1996-2007 Claudio Matsuoka and Hipolito Carraro Jr
 *
 * $Id: misc.c,v 1.15 2007/12/06 20:22:56 cmatsuoka Exp $
 *
 * This file is part of the Extended Module Player and is distributed
 * under the terms of the GNU General Public License. See doc/COPYING
 * for more information.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include "xmpi.h"

int report(char *fmt, ...)
{
	va_list a;
	int n;

	va_start(a, fmt);
	n = vfprintf(stderr, fmt, a);
	va_end(a);

	return n;
}

int reportv(struct xmp_context *ctx, int v, char *fmt, ...)
{
	va_list a;
	int n;
	struct xmp_options *o = &ctx->o;

	if (o->verbosity <= v)
		return 0;

	va_start(a, fmt);
	n = vfprintf(stderr, fmt, a);
	va_end(a);

	return n;
}

char *str_adj(char *s)
{
	int i;

	for (i = 0; i < strlen(s); i++)
		if (!isprint(s[i]) || ((uint8) s[i] > 127))
			s[i] = ' ';

	while (*s && (s[strlen(s) - 1] == ' '))
		s[strlen(s) - 1] = 0;

	return s;
}

int get_temp_dir(char *buf, int size)
{
#if defined WIN32
	char *def = "C:\\WINDOWS\\TEMP";
	char *tmp = getenv("TEMP");

	strncpy(buf, tmp ? tmp : def, size);
	strncat(buf, "\\", size);
#elif defined __AMIGA__
	char *def = "T:";

	strncpy(buf, def, size);
#else
	char *def = "/tmp";
	char *tmp = getenv("TMPDIR");

	strncpy(buf, tmp ? tmp : def, size);
	strncat(buf, "/", size);
#endif

	return 0;
}

