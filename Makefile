LDFLAGS= -lSDL
CXX=g++
BASE=${CURDIR}
SRC=${BASE}/src
INCLUDE=${BASE}/include
BIN=${BASE}/bin
TMP=${BASE}/tmp
CXXFLAGS= -I${BASE}/include/ 
export LDFLAGS
export CXXFLAGS
export BIN
export CXX
export TMP
export BASE
export SRC
export INCLUDE
RTTT: torgiren creammy czaju
	${CXX} ${BIN}/*.o -o $@ ${LDFLAGS}
torgiren:
	${MAKE} -f src/Makefile.torgiren
czaju:
	${MAKE} -f src/Makefile.czaju
creammy:
	${MAKE} -f src/Makefile.creammy
clean:
	rm -f ${BIN}/*
