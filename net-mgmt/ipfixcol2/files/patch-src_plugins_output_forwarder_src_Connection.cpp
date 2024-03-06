--- src/plugins/output/forwarder/src/Connection.cpp.orig	2024-03-02 19:19:49 UTC
+++ src/plugins/output/forwarder/src/Connection.cpp
@@ -52,6 +52,7 @@
 #include <netdb.h>
 #include <unistd.h>
 #include <arpa/inet.h>
+#include <sys/socket.h>
 
 #include <libfds.h>
 
