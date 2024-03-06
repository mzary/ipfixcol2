--- src/tools/ipfixsend/siso.c.orig	2024-03-02 21:41:55 UTC
+++ src/tools/ipfixsend/siso.c
@@ -48,6 +48,7 @@
 #include <unistd.h>
 #include <sys/types.h>
 #include <sys/socket.h>
+#include <netinet/in.h>
 
 #include <sys/time.h>
 #include <time.h>
