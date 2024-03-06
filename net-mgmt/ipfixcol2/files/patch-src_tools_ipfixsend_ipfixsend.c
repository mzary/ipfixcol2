--- src/tools/ipfixsend/ipfixsend.c.orig	2024-03-02 21:32:56 UTC
+++ src/tools/ipfixsend/ipfixsend.c
@@ -46,12 +46,18 @@
 #include <stdbool.h>
 #include <errno.h>
 #include <sys/ioctl.h>
+#ifdef __linux__
 #include <linux/sockios.h>
+#endif
 #include <time.h>
 
 #include "siso.h"
 #include "reader.h"
 #include "sender.h"
+
+#ifndef SIOCOUTQ
+#define SIOCOUTQ TIOCOUTQ
+#endif
 
 /** Default destination IP                 */
 #define DEFAULT_IP "127.0.0.1"
