/************************************************************************
 *   IRC - Internet Relay Chat
 *   Copyright (C) 2011 Plexus Development Team
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 1, or (at your option)
 *   any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
 *
 *   $Id$
 */

#ifndef INCLUDED_dnsbl_h
#define INCLUDED_dnsbl_h

struct DnsblInfo
{
	struct Client *cptr;
	struct DNSQuery query;
	dlink_node node;
	char *dnsbl_host;
	int duration;
	char *reason;
};

extern void start_dnsbl_lookup(struct Client *);
extern void clear_dnsbl_lookup(struct Client *);

#endif /* INCLUDED_dnsbl_h */

