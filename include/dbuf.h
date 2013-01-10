/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  dbuf.h: A header for the dynamic buffers functions.
 *
 *  Copyright (C) 2002 by the past and present ircd coders, and others.
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307
 *  USA
 *
 */

#ifndef __DBUF_H_INCLUDED
#define __DBUF_H_INCLUDED
#include "tools.h"

#define DBUF_BLOCK_SIZE 512

#define dbuf_length(x) ((x)->total_size)
#define dbuf_clear(x) dbuf_delete(x, dbuf_length(x))

struct dbuf_block
{
	int refs;
	size_t size;
	char data[DBUF_BLOCK_SIZE];
};

struct dbuf_queue
{
	dlink_list blocks;
	size_t total_size;
	size_t pos;
};

extern void dbuf_init(void);
extern void dbuf_add(struct dbuf_queue *, struct dbuf_block *);
extern void dbuf_delete(struct dbuf_queue *, size_t);

extern struct dbuf_block *dbuf_alloc();
extern void dbuf_ref_free(struct dbuf_block *);
extern void dbuf_put(struct dbuf_block *, const char *, ...);
extern void dbuf_put_args(struct dbuf_block *, const char *, va_list);
extern void dbuf_put_raw(struct dbuf_queue *, const char *, size_t);

#endif
