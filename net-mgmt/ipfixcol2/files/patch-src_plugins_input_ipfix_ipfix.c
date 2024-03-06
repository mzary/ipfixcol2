--- src/plugins/input/ipfix/ipfix.c.orig	2024-03-02 19:09:39 UTC
+++ src/plugins/input/ipfix/ipfix.c
@@ -131,6 +131,9 @@ files_list_get(ipx_ctx_t *ctx, const char *pattern, gl
 static inline int
 files_list_get(ipx_ctx_t *ctx, const char *pattern, glob_t *list)
 {
+#ifndef GLOB_TILDE_CHECK
+#define GLOB_TILDE_CHECK GLOB_TILDE
+#endif
     size_t file_cnt;
     int glob_flags = GLOB_MARK | GLOB_BRACE | GLOB_TILDE_CHECK;
     int rc = glob(pattern, glob_flags, NULL, list);
