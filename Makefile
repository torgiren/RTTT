LDFLAGS= -lSDL
CXXFLAGS= -I./../include/ 
BIN=./../bin
CXX=g++
TMP=./../tmp
export LDFLAGS
export CXXFLAGS
export BIN
export CXX
export TMP
RTTT: torgiren creammy czaju
	${CXX} ${BIN}/*.o -o $@ ${LDFLAGS}
torgiren:
	${MAKE} -f src/Makefile.torgiren
czaju:
	${MAKE} -f src/Makefile.czaju
creammy:
	${MAKE} -f src/Makefile.creammy
