/*	in_pcb.c	4.25	82/04/10	*/

#include "../h/param.h"
#include "../h/systm.h"
#include "../h/dir.h"
#include "../h/user.h"
#include "../h/mbuf.h"
#include "../h/socket.h"
#include "../h/socketvar.h"
#include "../net/in.h"
#include "../net/in_systm.h"
#include "../net/if.h"
#include "../net/route.h"
#include "../net/in_pcb.h"
#include "../h/protosw.h"

/*
 * Routines to manage internet protocol control blocks.
 *
 * At PRU_ATTACH time a protocol control block is allocated in
 * in_pcballoc() and inserted on a doubly-linked list of such blocks
 * for the protocol.  A port address is either requested (and verified
 * to not be in use) or assigned at this time.  We also allocate
 * space in the socket sockbuf structures here, although this is
 * not a clearly correct place to put this function.
 *
 * A connectionless protocol will have its protocol control block
 * removed at PRU_DETACH time, when the socket will be freed (freeing
 * the space reserved) and the block will be removed from the list of
 * blocks for its protocol.
 *
 * A connection-based protocol may be connected to a remote peer at
 * PRU_CONNECT time through the routine in_pcbconnect().  In the normal
 * case a PRU_DISCONNECT occurs causing a in_pcbdisconnect().
 * It is also possible that higher-level routines will opt out of the
 * relationship with the connection before the connection shut down
 * is complete.  This often occurs in protocols like TCP where we must
 * hold on to the protocol control block for a unreasonably long time
 * after the connection is used up to avoid races in later connection
 * establishment.  To handle this we allow higher-level routines to
 * disassociate themselves from the socket, marking it SS_USERGONE while
 * the disconnect is in progress.  We notice that this has happened
 * when the disconnect is complete, and perform the PRU_DETACH operation,
 * freeing the socket.
 *
 * TODO:
 *	use hashing
 */
struct	in_addr zeroin_addr;

/*
 * Allocate a protocol control block, space
 * for send and receive data, and local host information.
 * Return error.  If no error make socket point at pcb.
 */
in_pcbattach(so, head, sndcc, rcvcc, sin)
	struct socket *so;
	struct inpcb *head;
	int sndcc, rcvcc;
	struct sockaddr_in *sin;
{
	struct mbuf *m;
	register struct inpcb *inp;
	u_short lport = 0;

COUNT(IN_PCBATTACH);
	if (ifnet == 0)
		return (EADDRNOTAVAIL);
	if (sin) {
		if (sin->sin_family != AF_INET)
			return (EAFNOSUPPORT);
		if (sin->sin_addr.s_addr) {
			int tport = sin->sin_port;

			sin->sin_port = 0;		/* yech... */
			if (if_ifwithaddr((struct sockaddr *)sin) == 0)
				return (EADDRNOTAVAIL);
			sin->sin_port = tport;
		}
		lport = sin->sin_port;
		if (lport) {
			u_short aport = lport;
			int wild = 0;
#if vax
			aport = htons(aport);
#endif
			/* GROSS */
			if (aport < IPPORT_RESERVED && u.u_uid != 0)
				return (EPERM);
			if ((so->so_proto->pr_flags & PR_CONNREQUIRED) == 0 ||
			    (so->so_options & SO_ACCEPTCONN) == 0)
				wild = INPLOOKUP_WILDCARD;
			if (in_pcblookup(head,
			    zeroin_addr, 0, sin->sin_addr, lport, wild))
				return (EADDRINUSE);
		}
	}
	m = m_getclr(M_DONTWAIT);
	if (m == 0)
		return (ENOBUFS);
	if (sbreserve(&so->so_snd, sndcc) == 0)
		goto bad;
	if (sbreserve(&so->so_rcv, rcvcc) == 0)
		goto bad2;
	inp = mtod(m, struct inpcb *);
	inp->inp_head = head;
	if (sin)
		inp->inp_laddr = sin->sin_addr;
	if (lport == 0)
		do {
			if (head->inp_lport++ < IPPORT_RESERVED)
				head->inp_lport = IPPORT_RESERVED;
			lport = htons(head->inp_lport);
		} while (in_pcblookup(head,
			    zeroin_addr, 0, inp->inp_laddr, lport, 0));
	inp->inp_lport = lport;
	inp->inp_socket = so;
	insque(inp, head);
	so->so_pcb = (caddr_t)inp;
	return (0);
bad2:
	sbrelease(&so->so_snd);
bad:
	(void) m_free(m);
	return (ENOBUFS);
}

/*
 * Connect from a socket to a specified address.
 * Both address and port must be specified in argument sin.
 * If don't have a local address for this socket yet,
 * then pick one.
 */
in_pcbconnect(inp, sin)
	struct inpcb *inp;
	struct sockaddr_in *sin;
{
	struct ifnet *ifp;
	struct sockaddr_in *ifaddr;

COUNT(IN_PCBCONNECT);
	if (sin->sin_family != AF_INET)
		return (EAFNOSUPPORT);
	if (sin->sin_addr.s_addr == 0 || sin->sin_port == 0)
		return (EADDRNOTAVAIL);
	if (inp->inp_laddr.s_addr == 0) {
		ifp = if_ifonnetof(sin->sin_addr.s_net);
		if (ifp == 0) {
			ifp = if_ifwithaf(AF_INET);
			if (ifp == 0)
				return (EADDRNOTAVAIL);		/* XXX */
		}
		ifaddr = (struct sockaddr_in *)&ifp->if_addr;
	}
	if (in_pcblookup(inp->inp_head,
	    sin->sin_addr,
	    sin->sin_port,
	    inp->inp_laddr.s_addr ? inp->inp_laddr : ifaddr->sin_addr,
	    inp->inp_lport,
	    0))
		return (EADDRINUSE);
	if (inp->inp_laddr.s_addr == 0)
		inp->inp_laddr = ifaddr->sin_addr;
	inp->inp_faddr = sin->sin_addr;
	inp->inp_fport = sin->sin_port;
	return (0);
}

in_pcbdisconnect(inp)
	struct inpcb *inp;
{

COUNT(IN_PCBDISCONNECT);
	inp->inp_faddr.s_addr = 0;
	inp->inp_fport = 0;
	if (inp->inp_socket->so_state & SS_USERGONE)
		in_pcbdetach(inp);
}

in_pcbdetach(inp)
	struct inpcb *inp;
{
	struct socket *so = inp->inp_socket;

	so->so_pcb = 0;
	sofree(so);
	if (inp->inp_route.ro_rt)
		rtfree(inp->inp_route.ro_rt);
	remque(inp);
	(void) m_free(dtom(inp));
}

in_setsockaddr(sin, inp)
	register struct sockaddr_in *sin;
	register struct inpcb *inp;
{
	if (sin == 0 || inp == 0)
		panic("setsockaddr_in");
	bzero((caddr_t)sin, sizeof (*sin));
	sin->sin_family = AF_INET;
	sin->sin_port = inp->inp_lport;
	sin->sin_addr = inp->inp_laddr;
}

/*
 * SHOULD ALLOW MATCH ON MULTI-HOMING ONLY
 */
struct inpcb *
in_pcblookup(head, faddr, fport, laddr, lport, flags)
	struct inpcb *head;
	struct in_addr faddr, laddr;
	u_short fport, lport;
	int flags;
{
	register struct inpcb *inp, *match = 0;
	int matchwild = 3, wildcard;

	for (inp = head->inp_next; inp != head; inp = inp->inp_next) {
		if (inp->inp_lport != lport)
			continue;
		wildcard = 0;
		if (inp->inp_laddr.s_addr != 0) {
			if (laddr.s_addr == 0)
				wildcard++;
			else if (inp->inp_laddr.s_addr != laddr.s_addr)
				continue;
		} else {
			if (laddr.s_addr != 0)
				wildcard++;
		}
		if (inp->inp_faddr.s_addr != 0) {
			if (faddr.s_addr == 0)
				wildcard++;
			else if (inp->inp_faddr.s_addr != faddr.s_addr ||
			    inp->inp_fport != fport)
				continue;
		} else {
			if (faddr.s_addr != 0)
				wildcard++;
		}
		if (wildcard && (flags & INPLOOKUP_WILDCARD) == 0)
			continue;
		if (wildcard < matchwild) {
			match = inp;
			matchwild = wildcard;
			if (matchwild == 0)
				break;
		}
	}
	return (match);
}
