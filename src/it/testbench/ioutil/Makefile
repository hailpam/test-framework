PACKAGE = it/testbench/ioutil

SRC_DIR = src
OBJ_DIR = ../../../../obj/${PACKAGE}
INC_DIR = ../../../../inc/${PACKAGE}
INC_TST = ../../../../inc/it/testbench
DST_DIR = ../../../../dist
TST_DIR = ../../../../test/${PACKAGE}
BIN_DIR = ../../../../bin
LOG_DIR = ../../../../log

CC      = g++
CCFLAGS  = -I${INC_DIR} -I${INC_TST}
LDFLAGS = -lrt

.PHONY: clean cleantest distributable runtest

all: ${OBJ_DIR}/rawfsmanager.o ${OBJ_DIR}/test_rawfsmanager.o ${BIN_DIR}/test_rawfsmanager

debug: CCFLAGS += -DDEBUG_PRINT_ENABLED -g3
debug: all

${BIN_DIR}/test_rawfsmanager: ${OBJ_DIR}/test_rawfsmanager.o ${OBJ_DIR}/rawfsmanager.o
	$(CC) -o test_rawfsmanager $^ $(LDFLAGS)
	mv test_rawfsmanager ${BIN_DIR}/
	cp ${TST_DIR}/test_rawfsmanager.txt ${BIN_DIR}/

${OBJ_DIR}/test_rawfsmanager.o: ${TST_DIR}/test_rawfsmanager.cpp ${OBJ_DIR}/rawfsmanager.o
	$(CC) -Wall -c $(CCFLAGS) $<
	mv test_rawfsmanager.o ${OBJ_DIR}/

${OBJ_DIR}/rawfsmanager.o: rawfsmanager.cpp ${INC_DIR}/rawfsmanager.h
	$(CC) -Wall -c $(CCFLAGS) $<
	mv rawfsmanager.o ${OBJ_DIR}/

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/${TARGET}.o
	mv *.a ${DST_DIR}/

clean:
	rm -f ${OBJ_DIR}/*.o

cleantest: clean
	rm -f ${BIN_DIR}/test_rawfsmanager ${BIN_DIR}/*.txt ${LOG_DIR}/*.log

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=test_rawfsmanager-valgrind.log  -v ${BIN_DIR}/test_rawfsmanager
	mv test_rawfsmanager-valgrind.log ${LOG_DIR}/

