PORTNAME=		ipfixcol2
DISTVERSIONPREFIX=      v
DISTVERSION=	2.4.1
CATEGORIES=		net-mgmt

MAINTAINER=	zarychtam@plan-b.pwste.edu.pl
COMMENT=	NetFlow v5/v9 and IPFIX flow (RFC 7011) data collector
WWW=		https://github.com/CESNET/ipfixcol2

LICENSE=		GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

LIB_DEPENDS=	 librdkafka.so:net/librdkafka \
			 libepoll-shim.so:devel/libepoll-shim \
			 libfds.so:net-mgmt/libfds

BUILD_DEPENDS= rst2man:textproc/py-docutils

USES=		cmake pkgconfig

USE_GITHUB=	yes
GH_ACCOUNT=	CESNET
USE_RC_SUBR=${PORTNAME}
PORTEXAMPLES=	*

LDFLAGS+=	 -rdynamic
CXXFLAGS+=	 -D_GNU_SOURCE

OPTIONS_DEFINE= EXAMPLES

post-install:
	${MKDIR} ${STAGEDIR}${ETCDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/data/configs/multiOutput.xml ${STAGEDIR}${ETCDIR}/startup.xml.sample

post-install-EXAMPLES-on:
	cd ${WRKSRC}/doc/data && ${COPYTREE_SHARE} "configs" ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>
