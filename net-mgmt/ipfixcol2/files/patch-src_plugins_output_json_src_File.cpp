--- src/plugins/output/json/src/File.cpp.orig	2024-03-02 20:16:16 UTC
+++ src/plugins/output/json/src/File.cpp
@@ -53,6 +53,7 @@
 #include <unistd.h>
 #include <climits>
 #include <zlib.h>
+#include <pthread.h>
 
 /**
  * \brief Class constructor
@@ -110,6 +111,7 @@ File::File(const struct cfg_file &cfg, ipx_ctx_t *ctx)
         throw std::runtime_error("(File output) Rwlockattr initialization failed!");
     }
 
+#if !defined (__FreeBSD__) && !defined (__OpenBSD__)
     if (pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP) != 0) {
         if (_thread->m_calg == calg::GZIP) {
             gzclose((gzFile)_thread->file);
@@ -120,6 +122,7 @@ File::File(const struct cfg_file &cfg, ipx_ctx_t *ctx)
         delete _thread;
         throw std::runtime_error("(File output) Rwlockattr setkind failed!");
     }
+#endif
 
     if (pthread_rwlock_init(&_thread->rwlock, &attr) != 0) {
         if (_thread->m_calg == calg::GZIP) {
@@ -341,7 +344,12 @@ File::dir_create(ipx_ctx_t *ctx, const std::string &pa
         default:
             // Other errors
             char buffer[128];
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+	    char *err_str = buffer;
+	    strerror_r(errno, buffer, 128);
+#else
             const char *err_str = strerror_r(errno, buffer, 128);
+#endif
             IPX_CTX_ERROR(ctx, "(File output) Failed to create a directory %s (%s).",
                 aux_str.c_str(), err_str);
             return 1;
@@ -356,7 +364,12 @@ File::dir_create(ipx_ctx_t *ctx, const std::string &pa
         if (mkdir(aux_str.c_str(), mask) != 0) {
             // Failed to create directory
             char buffer[128];
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+	    char *err_str = buffer;
+	    strerror_r(errno, buffer, 128);
+#else
             const char *err_str = strerror_r(errno, buffer, 128);
+#endif
             IPX_CTX_ERROR(ctx, "(File output) Failed to create a directory %s (%s).",
                 aux_str.c_str(), err_str);
             return 1;
@@ -418,7 +431,12 @@ File::file_create(ipx_ctx_t *ctx, const std::string &t
     if (!file) {
         // Failed to create a flow file
         char buffer[128];
+#if defined (__FreeBSD__) || defined (__OpenBSD__)
+	    char *err_str = buffer;
+	    strerror_r(errno, buffer, 128);
+#else
         const char *err_str = strerror_r(errno, buffer, 128);
+#endif
         IPX_CTX_ERROR(ctx, "Failed to create a flow file '%s' (%s).", file_name.c_str(), err_str);
         return NULL;
     }
