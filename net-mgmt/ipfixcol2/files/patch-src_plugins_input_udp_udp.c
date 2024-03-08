--- src/plugins/input/udp/udp.c.orig	2024-03-07 22:02:06 UTC
+++ src/plugins/input/udp/udp.c
@@ -55,6 +55,10 @@
 #include <sys/ioctl.h>
 #include "config.h"
 
+#ifdef __FreeBSD__
+#include <err.h>
+#endif
+
 /** Identification of an invalid socket descriptor                                               */
 #define INVALID_FD        (-1)
 /** Timeout for a getter operation - i.e. epoll_wait timeout [in milliseconds]                   */
@@ -446,6 +450,22 @@ listener_init(struct udp_data *instance)
     const char *err_str;
 
     // Get maximum socket receive buffer size (in bytes)
+#ifdef __FreeBSD__
+    int sock_rmax = 0;
+    unsigned long space = 0;
+    size_t n = sizeof(space);
+    int sock = socket(PF_INET, SOCK_DGRAM, 0);
+    if (sock < 0) {
+        err(1, "socket(2)");
+    }
+    if (getsockopt(sock, SOL_SOCKET, SO_RCVBUF, &space, (socklen_t*)&n) != 0) {
+        err(1, "getsockopt(2)");
+        sock_rmax = 0; 
+    } else {
+        sock_rmax = (int) space; 
+    }
+    instance->listen.rmem_size = sock_rmax;
+#else
     FILE *f;
     int sock_rmax = 0;
     static const char *sys_cfg = "/proc/sys/net/core/rmem_max";
@@ -461,6 +481,7 @@ listener_init(struct udp_data *instance)
     if (f != NULL) {
         fclose(f);
     }
+#endif
 
     if (sock_rmax != 0 && sock_rmax < UDP_RMEM_REQ) {
         IPX_CTX_WARNING(instance->ctx, "The maximum socket receive buffer size is too small "
