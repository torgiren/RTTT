LDFLAGS= -lSDL
RTTT: torgiren creammy czaju
	g++ bin/*.o -o RTTT ${LDFLAGS}
torgiren:
	${MAKE} -f Makefile.torgiren
czaju:
	${MAKE} -f Makefile.czaju
creammy:
	${MAKE} -f Makefile.creammy
