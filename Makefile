LDFLAGS= -lSDL
CXXFLAGS= -Iinclude/ 
BIN=bin
CXX=g++
export LDFLAGS
export CXXFLAGS
export BIN
export CXX
RTTT: torgiren creammy czaju
	${CXX} ${BIN}/*.o -o $@ ${LDFLAGS}
torgiren:
	${MAKE} -f Makefile.torgiren
czaju:
	${MAKE} -f Makefile.czaju
creammy:
	${MAKE} -f Makefile.creammy
