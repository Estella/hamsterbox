/*
 *  ircd-hybrid: an advanced Internet Relay Chat Daemon(ircd).
 *  channel_mode.h: The ircd channel mode header.
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
 *  $Id: channel_mode.h 435 2006-08-18 15:25:17Z jon $
 */


#ifndef INCLUDED_channel_mode_h
#define INCLUDED_channel_mode_h

#include "ircd_defs.h"		/* buffer sizes */

#define MODEBUFLEN    200

/* Maximum mode changes allowed per client, per server is different */
#define MAXMODEPARAMS 4

/* can_send results */
#define CAN_SEND_NO	    0
#define CAN_SEND_NONOP      1
#define CAN_SEND_OPV	    2
#define CAN_SEND_NOREGNICK -1
#define CAN_SEND_NOCTRLS   -2
#define CAN_SEND_NOCTCP    -3

/* Channel related flags */
#define CHFL_OWNER      0x0001	/* Channel owner */
#define CHFL_PROTECTED  0x0002	/* Protected user */
#define CHFL_CHANOP     0x0004	/* Channel operator   */
#define CHFL_HALFOP     0x0008	/* Channel half op    */
#define CHFL_VOICE      0x0010	/* the power to speak */
#define CHFL_DEOPPED    0x0020	/* deopped by us, modes need to be bounced */
#define CHFL_BAN        0x0040	/* ban channel flag */
#define CHFL_EXCEPTION  0x0080	/* exception to ban channel flag */
#define CHFL_INVEX      0x0100

/* channel modes ONLY */
#define MODE_PRIVATE    0x0001
#define MODE_SECRET     0x0002
#define MODE_MODERATED  0x0004
#define MODE_TOPICLIMIT 0x0008
#define MODE_INVITEONLY 0x0010
#define MODE_NOPRIVMSGS 0x0020
#define MODE_REGONLY    0x0040
#define MODE_NOCTRL     0x0080
#define MODE_OPERONLY   0x0100
#define MODE_MODREG     0x0200
#define MODE_SSLONLY    0x0400
#define MODE_BWSAVER    0x0800
#define MODE_NONOTICES  0x1000
#define MODE_PERSIST	0x2000
#define MODE_NOCTCP     0x4000

/* cache flags for silence on ban */
#define CHFL_BAN_CHECKED  0x0080
#define CHFL_BAN_SILENCED 0x0100

#define MODE_QUERY  0
#define MODE_ADD    1
#define MODE_DEL   -1

#define CHACCESS_NOTONCHAN  -1
#define CHACCESS_PEON       0
#define CHACCESS_HALFOP     1
#define CHACCESS_CHANOP     2
#define CHACCESS_PROTECTED  3
#define CHACCESS_OWNER      4
#define CHACCESS_REMOTE     5

/* name invisible */
#define SecretChannel(x)        (((x)->mode.mode & MODE_SECRET))
#define PubChannel(x)           (!SecretChannel(x))
/* knock is forbidden, halfops can't kick/deop other halfops.
 * +pi means paranoid and will generate notices on each invite */
#define PrivateChannel(x)       (((x)->mode.mode & MODE_PRIVATE))

#define BwSaverChannel(x)       (((x)->mode.mode & MODE_BWSAVER))

#define PersistChannel(x)       (((x)->mode.mode & MODE_PERSIST))	

struct channel_mode
{
	void (*func) (struct Client * client_p, struct Client * source_p,
		      struct Channel * chptr, int parc, int *parn, char **parv,
		      int *errors, int alev, int dir, char c, const struct channel_mode *mode, const char *chname);
	unsigned int mode;
	unsigned char letter;
	int *enabled;
};

struct ChModeChange
{
	char letter;
	const char *arg;
	const char *id;
	int dir;
	int caps;
	int nocaps;
	int mems;
	struct Client *client;
};

struct ChCapCombo
{
	int count;
	int cap_yes;
	int cap_no;
};

extern struct channel_mode channel_mode_info[];
extern const char *build_chanmode_string();
extern int add_id(struct Client *, struct Channel *, char *, int);
extern void set_channel_mode(struct Client *, struct Client *, struct Channel *,
			     struct Membership *, int, char **, char *);
extern void clear_ban_cache(struct Channel *);
extern void clear_ban_cache_client(struct Client *);
extern void init_chcap_usage_counts(void);
extern void set_chcap_usage_counts(struct Client *);
extern void unset_chcap_usage_counts(struct Client *);

extern int del_id(struct Channel *, char *, int);
extern void send_mode_changes(struct Client *, struct Client *, struct Channel *, char *);
extern int get_channel_access(struct Client *source_p, struct Membership *member);
extern struct ChModeChange mode_changes[IRCD_BUFSIZE];
extern int mode_count;

#endif /* INCLUDED_channel_mode_h */
