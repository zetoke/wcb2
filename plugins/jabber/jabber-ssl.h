#ifndef __EKG_JABBER_SSL_H
#define __EKG_JABBER_SSL_H

#include <ekg2-config.h>

#ifdef JABBER_HAVE_GNUTLS
# define JABBER_HAVE_SSL 1
# undef JABBER_HAVE_OPENSSL	/* na wszelki wypadek */
#else
#ifdef JABBER_HAVE_OPENSSL
# define JABBER_HAVE_SSL 1
# warning "You want to use OpenSSL library as ssl transport layer for jabber, it have bugs and is not well tested.. It's better if you use gnutls"
#endif
#endif

#ifdef JABBER_HAVE_SSL

#ifdef JABBER_HAVE_GNUTLS		/* HAVE_GNUTLS */
# include <gnutls/gnutls.h>


# define SSL_SESSION		gnutls_session

static int __attribute__((unused)) SSL_SET_FD(SSL_SESSION session, long int fd) {
	gnutls_transport_set_ptr(session, (gnutls_transport_ptr)(fd));
	return 1;	/* always success */
} 

# define SSL_INIT(session)		gnutls_init((&session), GNUTLS_CLIENT)
# define SSL_DEINIT(session)		gnutls_deinit(session)
# define SSL_HELLO(session)		gnutls_handshake(session)
# define SSL_BYE(session)		gnutls_bye(session, GNUTLS_SHUT_RDWR)
# define SSL_GLOBAL_INIT()		gnutls_global_init()
# define SSL_GLOBAL_DEINIT()		gnutls_global_deinit()
# define SSL_ERROR(retcode)		gnutls_strerror(retcode)
# define SSL_E_AGAIN(ret)		((ret == GNUTLS_E_INTERRUPTED) || (ret == GNUTLS_E_AGAIN))

# define SSL_SEND(session, str, len)	gnutls_record_send(session, str, len)
# define SSL_RECV(session, buf, size)	gnutls_record_recv(session, buf, size)

# define SSL_GET_FD(session, fd)		(long int) gnutls_transport_get_ptr(session)
# define SSL_WRITE_DIRECTION(session, ret)	gnutls_record_get_direction(session)

#else				/* HAVE_OPENSSL */
# include <openssl/ssl.h>
# include <openssl/err.h>

extern SSL_CTX *jabberSslCtx;	/* jabber.c */

# define SSL_SESSION		SSL *

# define SSL_INIT(session)		!(session = SSL_new(jabberSslCtx))

# define SSL_HELLO(session)		SSL_connect(session)
# define SSL_BYE(session)		SSL_shutdown(session)
# define SSL_DEINIT(session)		SSL_free(session)
# define SSL_GLOBAL_INIT()		SSL_library_init(); jabberSslCtx = SSL_CTX_new(SSLv23_client_method())
# define SSL_GLOBAL_DEINIT()		SSL_CTX_free(jabberSslCtx)
# define SSL_ERROR(retcode)		ERR_error_string(retcode, NULL)		/* retcode need be value from SSL_get_error(session, res) */
# define SSL_E_AGAIN(ret)		((ret == SSL_ERROR_WANT_READ || ret == SSL_ERROR_WANT_WRITE))

# define SSL_SEND(session, str, len)	SSL_write(session, str, len)
# define SSL_RECV(session, buf, size)	SSL_read(session, buf, size)

# define SSL_SET_FD(session, fd)	SSL_set_fd(session, fd)
# define SSL_GET_FD(session, fd)		fd
# define SSL_WRITE_DIRECTION(session, ret)	(ret != SSL_ERROR_WANT_READ)

#endif				/* ... */

#endif		/* JABBER_HAVE_SSL */
#endif		/* __EKG_JABBER_SSL_H */

