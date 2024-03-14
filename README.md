## FreeBSD port for IPFIXcol2

This development repository contains ports required to build and install [CESNET/ipfixcol2](https://github.com/CESNET/ipfixcol2/tree/master)
on FreeBSD. It's work in progress, so far consisting of three ports:

### net-mgmt/ipfixcol2

High-performance NetFlow v5/v9 and IPFIX collector (RFC7011). Stable version of the port.
Requirements for FreeBSD:

- net/librdkafka
- net-mgmt/libfds
- devel/libepoll-shim

### net-mgmt/ipfixcol2-devel

High-performance NetFlow v5/v9 and IPFIX collector (RFC7011). The most recent version of the port.
Requirements for FreeBSD:

- net/librdkafka
- net-mgmt/libfds
- devel/libepoll-shim

### net-mgmt/libfds

Flow Data Storage library.
Requirements for FreeBSD:

- textproc/libxml2
- archivers/zstd
- archivers/liblz4
