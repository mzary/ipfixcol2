PORTNAME=		ipfixcol2
DISTVERSION=	g20240404
CATEGORIES=		net-mgmt

MAINTAINER=	zarychtam@plan-b.pwste.edu.pl
COMMENT=	NetFlow v5/v9 and IPFIX flow (RFC 7011) data collector
WWW=		https://github.com/CESNET/ipfixcol2

LICENSE=		GPLv2
LICENSE_FILE=	${WRKSRC}/LICENSE

PKGNAMESUFFIX=	-devel
DISTNAME=		bsd-support

LIB_DEPENDS= 	librdkafka.so:net/librdkafka \
			 libepoll-shim.so:devel/libepoll-shim \
			 libfds.so:net-mgmt/libfds

BUILD_DEPENDS= rst2man:textproc/py-docutils

USES=		cmake localbase:ldflags pkgconfig

USE_GITHUB=	yes
GH_ACCOUNT=	CESNET
GH_TAGNAME= 8bf2adccb0c6f1a9a6ed04d460d272de5d217727
USE_RC_SUBR=${PORTNAME}
USERS=	${PORTNAME}
GROUPS=	${PORTNAME}
PORTEXAMPLES=	*

LDFLAGS+=	 -rdynamic
CXXFLAGS+=	 -D_GNU_SOURCE

OPTIONS_DEFINE= EXAMPLES

post-install:
	${MKDIR} ${STAGEDIR}${ETCDIR} ${STAGEDIR}/var/run/${PORTNAME}
	${INSTALL_DATA} ${WRKSRC}/doc/data/configs/udp2json.xml ${STAGEDIR}${ETCDIR}/startup.xml.sample

post-install-EXAMPLES-on:
	cd ${WRKSRC}/doc/data && ${COPYTREE_SHARE} "configs" ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>
