PORTNAME=		ipfixcol2
DISTVERSION=	g20240321
DISTNAME=		bsd-support
PKGNAMESUFFIX=	-devel
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

USES=		cmake localbase:ldflags pkgconfig

USE_GITHUB=	yes
GH_ACCOUNT=	CESNET
GH_TAGNAME= 0d2e6f67ee8f2650abc33daf780f9cf783aad232
USE_RC_SUBR=${PORTNAME}
PORTEXAMPLES=	*

LDFLAGS+=	 -rdynamic
CFLAGS+=	 -rdynamic -L${LOCALBASE}/lib -lepoll-shim
CXXFLAGS+=	 -D_GNU_SOURCE -rdynamic -L${LOCALBASE}/lib -lepoll-shim

OPTIONS_DEFINE= EXAMPLES

post-install:
	${MKDIR} ${STAGEDIR}${ETCDIR}
	${INSTALL_DATA} ${WRKSRC}/doc/data/configs/multiOutput.xml ${STAGEDIR}${ETCDIR}/startup.xml.sample

post-install-EXAMPLES-on:
	cd ${WRKSRC}/doc/data && ${COPYTREE_SHARE} "configs" ${STAGEDIR}${EXAMPLESDIR}

.include <bsd.port.mk>
