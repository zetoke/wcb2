ekg2_headers = commands.h debug.h dynstuff.h dynstuff_inline.h plugins.h queries.h recode.h sessions.h strings.h stuff.h themes.h userlist.h vars.h windows.h xmalloc.h ../ekg2-config.h

bin_PROGRAMS = ekg2-remote

ekg2_remote_SOURCES = ekg-remote.c commands.c dynstuff.c plugins.c recode.c remote.c sessions.c stuff.c themes.c userlist.c vars.c windows.c xmalloc.c strings.c $(ekg2_headers) remote-ssl.h

ekg2_remote_LDADD = $(top_builddir)/compat/libcompat.a @DLLIB@ $(REMOTE_SSL_LIBS)
ekg2_remote_LDFLAGS = -export-dynamic
ekg2_remote_DEPENDENCIES = $(top_builddir)/compat/libcompat.a
ekg2_remote_CPPFLAGS = $(REMOTE_SSL_CPPFLAGS) $(AM_CPPFLAGS)

INCLUDES = -DPLUGINDIR=\"$(plugindir)\"

$(top_builddir)/compat/libcompat.a:
	make -C $(top_builddir)/compat
