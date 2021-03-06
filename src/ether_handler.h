/*
 * Copyright (c) 2010-2015 SURFnet bv
 * Copyright (c) 2015 Roland van Rijswijk-Deij
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of SURFnet bv nor the names of its contributors 
 *    may be used to endorse or promote products derived from this 
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER
 * IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*
 * The Extensible Ethernet Monitor (EEMO)
 * Ethernet packet handling
 */

#ifndef _EEMO_ETHER_HANDLER_H
#define _EEMO_ETHER_HANDLER_H

#include "config.h"
#include <pcap.h>
#include "eemo.h"
#include "eemo_packet.h"

/* Raw Ethernet packet header */
#pragma pack(push, 1)
typedef struct
{
	u_char 	eth_dest[6];
	u_char	eth_source[6];
	u_short	eth_type;
}
eemo_hdr_raw_ether;
#pragma pack(pop)

/* Ethernet packet info */
typedef struct
{
	char eth_source[18];
	char eth_dest[18];
	struct timeval ts;
}
eemo_ether_packet_info;

/* Defines a handler for raw Ethernet packets */
typedef eemo_rv (*eemo_ether_handler_fn) (const eemo_packet_buf*, eemo_ether_packet_info);

/* Defines an Ethernet handler record */
typedef struct eemo_ether_handler
{
	u_short				which_eth_type; /* which Ethernet types are handled by this module */
	eemo_ether_handler_fn		handler_fn;	/* handler function */

	/* Administrativia */
	unsigned long			handle;		/* handle for this entry */
	struct eemo_ether_handler*	next;		/* to create a linked list */
}
eemo_ether_handler;

/* Register an Ethernet handler */
typedef eemo_rv (*eemo_reg_ether_handler_fn) (u_short, eemo_ether_handler_fn, unsigned long*);

eemo_rv eemo_reg_ether_handler(u_short which_eth_type, eemo_ether_handler_fn handler_fn, unsigned long* handle);

/* Unregister an Ethernet handler */
typedef eemo_rv (*eemo_unreg_ether_handler_fn) (unsigned long);

eemo_rv eemo_unreg_ether_handler(unsigned long handle);

/* Handle an Ethernet packet */
eemo_rv eemo_handle_ether_packet(const eemo_packet_buf* packet, struct timeval ts);

/* Initialise Ethernet handling */
eemo_rv eemo_init_ether_handler(void);

/* Clean up */
void eemo_ether_handler_cleanup(void);

#endif /* !_EEMO_ETHER_HANDLER_H */

