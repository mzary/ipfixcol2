--- src/plugins/output/json/src/Syslog.cpp.orig	2024-03-02 20:38:00 UTC
+++ src/plugins/output/json/src/Syslog.cpp
@@ -54,6 +54,12 @@
 /** How ofter to report statistics (seconds) */
 #define STATS_DELAY   (1)
 
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+    #ifndef HOST_NAME_MAX
+        #define HOST_NAME_MAX 255
+    #endif
+#endif
+
 static void
 get_time(timespec &ts)
 {
