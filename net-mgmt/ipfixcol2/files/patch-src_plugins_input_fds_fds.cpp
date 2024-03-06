--- src/plugins/input/fds/fds.cpp.orig	2024-03-02 19:04:55 UTC
+++ src/plugins/input/fds/fds.cpp
@@ -110,6 +110,9 @@ file_list_init(Instance *inst, const char *pattern)
 void
 file_list_init(Instance *inst, const char *pattern)
 {
+#ifndef GLOB_TILDE_CHECK
+#define GLOB_TILDE_CHECK GLOB_TILDE
+#endif
     int glob_flags = GLOB_MARK | GLOB_BRACE | GLOB_TILDE_CHECK;
     size_t file_cnt;
     int ret;
