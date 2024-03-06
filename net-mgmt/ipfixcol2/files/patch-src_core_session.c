--- src/core/session.c.orig	2024-03-02 20:00:18 UTC
+++ src/core/session.c
@@ -47,6 +47,9 @@
 #include <ipfixcol2.h>
 #include <stdlib.h>
 #include <inttypes.h>
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+#include	<libgen.h>
+#endif
 
 /**
  * \brief Create a source description string from a Network Session structure
@@ -190,4 +193,4 @@ ipx_session_destroy(struct ipx_session *session)
     }
 
     free(session);
-}
\ No newline at end of file
+}
