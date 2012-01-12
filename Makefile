LDFLAGS= -lSDL
CXXFLAGS= -Iinclude/ 
BIN=bin/
export LDFLAGS
export CXXFLAGS
export BIN
RTTT: torgiren creammy czaju
	g++ bin/*.o -o RTTT ${LDFLAGS}
torgiren:
	${MAKE} -f Makefile.torgiren
czaju:
	${MAKE} -f Makefile.czaju
creammy:
	${MAKE} -f Makefile.creammy
