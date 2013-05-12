PACKAGE = it/testbench/ioutil

SRC_DIR = src
OBJ_DIR = ../../../../obj/${PACKAGE}
OBJ_DATA = ${OBJ_DIR}/../data
INC_DIR = ../../../../inc/${PACKAGE}
INC_TST = ../../../../inc/it/testbench
INC_DATA = ${INC_TST}/data
DST_DIR = ../../../../dist
TST_DIR = ../../../../test/${PACKAGE}
BIN_DIR = ../../../../bin
LOG_DIR = ../../../../log

CC      = g++
CCFLAGS = -I${INC_DIR} -I${INC_TST} -I${INC_DATA}
LDFLAGS = -lrt
DIST	= libioutil.a

.PHONY: clean cleantest distributable runtest

all: ${OBJ_DIR}/rawfsmanager.o ${OBJ_DIR}/test_rawfsmanager.o ${OBJ_DIR}/test_stubfsmanager.o ${BIN_DIR}/test_rawfsmanager
	$(MAKE) distributable

debug: CCFLAGS += -DDEBUG_PRINT_ENABLED -g3
debug: all

${BIN_DIR}/test_rawfsmanager: ${OBJ_DIR}/test_rawfsmanager.o ${OBJ_DIR}/rawfsmanager.o ${OBJ_DIR}/test_stubfsmanager.o \
				${DST_DIR}/libdata.a
	$(CC) -o ${BIN_DIR}/test_rawfsmanager $^ $(LDFLAGS)
	cp ${TST_DIR}/test_rawfsmanager.txt ${BIN_DIR}/

${OBJ_DIR}/test_rawfsmanager.o: ${TST_DIR}/test_rawfsmanager.cpp ${OBJ_DIR}/rawfsmanager.o ${OBJ_DIR}/test_stubfsmanager.o
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/test_rawfsmanager.o

${OBJ_DIR}/test_stubfsmanager.o: ${TST_DIR}/test_stubfsmanager.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/test_stubfsmanager.o

${OBJ_DIR}/rawfsmanager.o: rawfsmanager.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/rawfsmanager.o

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/rawfsmanager.o
	mv *.a ${DST_DIR}/

clean:
	rm -f ${OBJ_DIR}/rawfsmanager.o ${OBJ_DIR}/test_rawfsmanager.o ${OBJ_DIR}/test_stubfsmanager.o

cleantest: clean
	rm -f ${BIN_DIR}/test_rawfsmanager ${BIN_DIR}/*.txt ${LOG_DIR}/*.log ${DST_DIR}/${DIST}

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=test_rawfsmanager-valgrind.log  -v ${BIN_DIR}/test_rawfsmanager
	mv test_rawfsmanager-valgrind.log ${LOG_DIR}/

