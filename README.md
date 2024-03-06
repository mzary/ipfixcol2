## FreeBSD port for IPFIXcol2

This development repository contains ports required to build and install [CESNET/ipfixcol2](https://github.com/CESNET/ipfixcol2/tree/master)
on FreeBSD. It's work in progress, so far consisting of two ports:

### net-mgmt/ipfixcol2

Requirements for FreeBSD:

- net/librdkafka
- net-mgmt/libfds
- devel/libepoll-shim


### net-mgmt/libfds

Requirements for FreeBSD:

- textproc/libxml2
- archivers/zstd
- archivers/liblz4
