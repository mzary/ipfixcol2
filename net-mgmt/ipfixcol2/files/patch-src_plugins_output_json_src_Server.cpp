--- src/plugins/output/json/src/Server.cpp.orig	2024-03-02 20:49:42 UTC
+++ src/plugins/output/json/src/Server.cpp
@@ -40,6 +40,7 @@
 #include "Server.hpp"
 #include <stdexcept>
 #include <cstring>
+#include <cerrno>
 
 #include <unistd.h>
 #include <sys/types.h>
@@ -202,7 +203,12 @@ Server::thread_accept(void *context)
             }
 
             char buffer[128];
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+            char *err_str = buffer;
+            strerror_r(errno, buffer, 128);
+#else
             const char *err_str = strerror_r(errno, buffer, 128);
+#endif
             IPX_CTX_ERROR(acc->ctx, "(Server output) select() - failed (%s)", err_str);
             break;
         }
@@ -215,7 +221,12 @@ Server::thread_accept(void *context)
         new_fd = accept(acc->socket_fd, (struct sockaddr *) &client_addr, &sin_size);
         if (new_fd == -1) {
             char buffer[128];
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+            char *err_str = buffer;
+            strerror_r(errno, buffer, 128);
+#else
             const char *err_str = strerror_r(errno, buffer, 128);
+#endif
             IPX_CTX_ERROR(acc->ctx, "(Server output) accept() - failed (%s)", err_str);
             continue;
         }
@@ -271,7 +282,12 @@ Server::msg_send(const char *data, ssize_t len, client
 
             // Connection failed
             char buffer[128];
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+            char *err_str = buffer;
+            strerror_r(errno, buffer, 128);
+#else
             const char *err_str = strerror_r(errno, buffer, 128);
+#endif
             IPX_CTX_INFO(_ctx, "(Server output) Client disconnected: %s (%s)",
                 get_client_desc(client.info).c_str(), err_str);
             return SEND_FAILED;
