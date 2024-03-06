--- src/core/context.c.orig	2023-04-20 07:02:30 UTC
+++ src/core/context.c
@@ -45,7 +45,11 @@
 #include <pthread.h>
 #include <errno.h>
 #include <signal.h>
+#if defined(__FreeBSD__) || defined(__OpenBSD__)
+#include	<pthread_np.h>
+#else
 #include <sys/prctl.h>
+#endif
 
 #include "context.h"
 #include "extension.h"
@@ -633,13 +637,16 @@ static inline void
  * \param[in] ident New identification
  */
 static inline void
-thread_set_name(const char *ident)
+thread_set_name(struct ipx_ctx *ctx)
 {
     static const size_t size = 16; // i.e. 15 characters + '\0'
     char name[size];
-    strncpy(name, ident, size - 1);
+    strncpy(name, ctx->name, size - 1);
     name[size - 1] = '\0';
 
+#if defined(__FreeBSD__) || defined (__OpenBSD__)
+    pthread_set_name_np(ctx->thread_id, name);
+#else
     int rc = prctl(PR_SET_NAME, name, 0, 0, 0);
     if (rc == -1) {
         const char *err_str;
@@ -647,6 +654,7 @@ thread_set_name(const char *ident)
         IPX_WARNING(comp_str, "Failed to set the name of a thread. prctl() failed: %s",
             err_str);
     }
+#endif
 }
 
 /**
@@ -654,8 +662,11 @@ static inline void
  * \param[out] ident Current identification
  */
 static inline void
-thread_get_name(char ident[16])
+thread_get_name(struct ipx_ctx *ctx, char ident[16])
 {
+#if defined(__FreeBSD__) || defined (__OpenBSD__)
+    pthread_get_name_np(ctx->thread_id, ident, 16);
+#else
     int rc = prctl(PR_GET_NAME, ident, 0, 0, 0);
     if (rc == -1) {
         const char *err_str;
@@ -664,6 +675,7 @@ thread_get_name(char ident[16])
             err_str);
         ident[0] = '\0';
     }
+#endif
 }
 
 int
@@ -739,8 +751,8 @@ ipx_ctx_init(ipx_ctx_t *ctx, const char *params)
      * new threads and we want to preserve correct inheritance of these configurations
      */
     char old_ident[16];  // Up to 16 bytes can be stored based on the manual page of prctl
-    thread_get_name(old_ident);
-    thread_set_name(ctx->name);
+    thread_get_name(ctx, old_ident);
+    thread_set_name(ctx);
 
     sigset_t set_new, set_old;
     sigfillset(&set_new);
@@ -758,7 +770,8 @@ ipx_ctx_init(ipx_ctx_t *ctx, const char *params)
 
     // Restore the previous thread identification and signal mask
     pthread_sigmask(SIG_SETMASK, &set_old, NULL);
-    thread_set_name(old_ident);
+    strlcpy(ctx->name, old_ident, 16);
+    thread_set_name(ctx);
 
     if (rc != IPX_OK) {
         IPX_CTX_ERROR(ctx, "Initialization function of the instance failed!", '\0');
@@ -892,7 +905,7 @@ thread_input(void *arg)
 {
     struct ipx_ctx *ctx = (struct ipx_ctx *) arg;
     assert(ctx->type == IPX_PT_INPUT);
-    thread_set_name(ctx->name);
+    thread_set_name(ctx);
 
     const char *plugin_name = ctx->plugin_cbs->info->name;
     IPX_CTX_DEBUG(ctx, "Instance thread of the input plugin '%s' has started!", plugin_name);
@@ -934,7 +947,7 @@ thread_intermediate(void *arg)
 {
     struct ipx_ctx *ctx = (struct ipx_ctx *) arg;
     assert(ctx->type == IPX_PT_INTERMEDIATE || ctx->type == IPX_PT_OUTPUT_MGR);
-    thread_set_name(ctx->name);
+    thread_set_name(ctx);
 
     const char *plugin_name = ctx->plugin_cbs->info->name;
     IPX_CTX_DEBUG(ctx, "Instance thread of the intermediate plugin '%s' has started!", plugin_name);
@@ -1018,7 +1031,7 @@ thread_output(void *arg)
 {
     struct ipx_ctx *ctx = (struct ipx_ctx *) arg;
     assert(ctx->type == IPX_PT_OUTPUT);
-    thread_set_name(ctx->name);
+    thread_set_name(ctx);
 
     const char *plugin_name = ctx->plugin_cbs->info->name;
     IPX_CTX_DEBUG(ctx, "Instance thread of the output plugin '%s' has started!", plugin_name);
