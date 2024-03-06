--- src/plugins/output/json/src/Sender.cpp.orig	2024-03-02 20:28:34 UTC
+++ src/plugins/output/json/src/Sender.cpp
@@ -44,6 +44,7 @@
 #include <time.h>
 #include <unistd.h>
 #include <inttypes.h>
+#include <cerrno>
 
 #include <sys/types.h>
 #include <sys/socket.h>
@@ -230,7 +231,12 @@ Sender::send(const char *str, size_t len)
 
             // Connection failed
             char buffer[128];
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+            char *err_str = buffer;
+            strerror_r(errno, buffer, 128);
+#else
             const char *err_str = strerror_r(errno, buffer, 128);
+#endif
             IPX_CTX_INFO(_ctx, "(Send output) Destination '%s:%" PRIu16 "' disconnected: %s",
                 params.addr.c_str(), params.port, err_str);
             return SEND_FAILED;
@@ -257,4 +263,4 @@ Sender::send(const char *str, size_t len)
     std::string tmp(ptr, todo);
     msg_rest.assign(tmp);
     return SEND_WOULDBLOCK;
-}
\ No newline at end of file
+}
