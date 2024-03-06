--- src/tools/fdsdump/src/common/ipaddr.cpp.orig	2024-03-02 22:06:15 UTC
+++ src/tools/fdsdump/src/common/ipaddr.cpp
@@ -1,6 +1,11 @@
 
 #include <stdexcept>
 #include "ipaddr.hpp"
+#if defined(__FreeBSD__) || defined (__OpenBSD__)
+  #include <sys/types.h>
+  #include <sys/socket.h>
+  #include <netinet/in.h>
+#endif
 
 namespace fdsdump {
 
