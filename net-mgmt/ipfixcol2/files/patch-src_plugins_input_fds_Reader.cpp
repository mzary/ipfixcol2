--- src/plugins/input/fds/Reader.cpp.orig	2024-03-02 19:25:02 UTC
+++ src/plugins/input/fds/Reader.cpp
@@ -97,11 +97,14 @@ Reader::session_from_sid(fds_file_sid_t sid)
     memset(&session_net, 0, sizeof(session_net));
     session_net.port_src = desc->port_src;
     session_net.port_dst = desc->port_dst;
+#if !defined (__FreeBSD__) && !defined (__OpenBSD__)
     if (IN6_IS_ADDR_V4MAPPED(desc->ip_src) && IN6_IS_ADDR_V4MAPPED(desc->ip_dst)) {
         session_net.l3_proto = AF_INET;
         session_net.addr_src.ipv4 = *reinterpret_cast<const struct in_addr *>(&desc->ip_src[12]);
         session_net.addr_dst.ipv4 = *reinterpret_cast<const struct in_addr *>(&desc->ip_dst[12]);
-    } else {
+    } else 
+#endif
+    {
         session_net.l3_proto = AF_INET6;
         session_net.addr_src.ipv6 = *reinterpret_cast<const struct in6_addr *>(&desc->ip_src[0]);
         session_net.addr_dst.ipv6 = *reinterpret_cast<const struct in6_addr *>(&desc->ip_dst[0]);
