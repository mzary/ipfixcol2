--- include/libfds/converters.h.orig	2024-03-02 17:19:21.089388000 +0100
+++ include/libfds/converters.h	2024-03-02 17:20:04.755920000 +0100
@@ -55,6 +55,7 @@
 #include <assert.h>    // static_assert
 #include <arpa/inet.h> // inet_ntop
 #include <endian.h>    // htobe64, be64toh
+#include <sys/socket.h>
 
 #include "iemgr.h"
 #include <libfds/api.h>
