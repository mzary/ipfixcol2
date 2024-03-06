--- src/plugins/output/forwarder/src/Config.cpp.orig	2024-03-02 21:10:41 UTC
+++ src/plugins/output/forwarder/src/Config.cpp
@@ -46,6 +46,7 @@
 #include <cstring>
 #include <netdb.h>
 #include <unistd.h>
+#include <netinet/in.h>
 
 ///
 /// Config schema definition
@@ -304,4 +305,4 @@ Config::can_resolve_host(HostConfig host)
     } else {
         return false;
     }
-}
\ No newline at end of file
+}
