LDFLAGS= -lSDL -lboost_filesystem -lboost_thread -lSDL_image
CXX=g++
BASE=${CURDIR}
SRC=${BASE}/src
INCLUDE=${BASE}/include
BIN=${BASE}/bin
TMP=${BASE}/tmp
CXXFLAGS= -I${BASE}/include/ -I${BASE}/include/utils/ -O3
export LDFLAGS
export CXXFLAGS
export BIN
export CXX
export TMP
export BASE
export SRC
export INCLUDE
RTTT: torgiren creammy czaju ${BIN}/main.o
	${CXX} ${BIN}/*.o ${BIN}/utils/*.o -o $@ ${LDFLAGS}
${BIN}/main.o: ${SRC}/main.cpp
	${CXX} ${SRC}/main.cpp -c -o $@ ${CXXFLAGS}
torgiren:
	${MAKE} -f src/Makefile.torgiren
torgiren_run: torgiren
	./tmp/main.torgiren
czaju:
	${MAKE} -f src/Makefile.czaju
czaju_run: czaju
	./tmp/main.czaju
creammy:
	${MAKE} -f src/Makefile.creammy
creammy_run: creammy
	./tmp/main.creammy
docs:
	doxygen Doxyfile
	make -C docs/latex
	cp docs/latex/refman.pdf ./
clean:
	rm -fr ${BIN}/*.o ${BIN}/utils/*.o

.PHONY: torgiren creammy czaju clean docs
