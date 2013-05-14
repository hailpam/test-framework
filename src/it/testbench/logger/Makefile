PACKAGE = it/testbench/logger

SRC_DIR = src
OBJ_DIR = ../../../../obj/${PACKAGE}
INC_DIR = ../../../../inc/${PACKAGE}
INC_TST = ../../../../inc/it/testbench
DST_DIR = ../../../../dist
TST_DIR = ../../../../test/${PACKAGE}
BIN_DIR = ../../../../bin
LOG_DIR = ../../../../log

CC	= g++
CCFLAGS	= -I${INC_DIR} -I${INC_TST}
LDFLAGS	= -lrt
DIST	= liblogger.a

.PHONY: clean cleantest distributable runtest

all: ${OBJ_DIR}/rawlogger.o ${OBJ_DIR}/test_rawlogger.o ${BIN_DIR}/test_rawlogger
	$(MAKE) distributable

debug: CCFLAGS += -DDEBUG_PRINT_ENABLED -g3
debug: all

${BIN_DIR}/test_rawlogger: ${OBJ_DIR}/test_rawlogger.o ${OBJ_DIR}/rawlogger.o
	$(CC) -o ${BIN_DIR}/test_rawlogger $^ $(LDFLAGS)

${OBJ_DIR}/test_rawlogger.o: ${TST_DIR}/test_rawlogger.cpp ${OBJ_DIR}/rawlogger.o
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/test_rawlogger.o

${OBJ_DIR}/rawlogger.o: rawlogger.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/rawlogger.o

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/rawlogger.o
	mv *.a ${DST_DIR}/

clean:
	rm -f ${OBJ_DIR}/rawlogger.o ${OBJ_DIR}/test_rawlogger.o

cleantest: clean cleandist
	rm -f ${BIN_DIR}/test_rawlogger ${BIN_DIR}/*.log ${LOG_DIR}/*.log

cleandist:
	rm -f ${DST_DIR}/${DIST}

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=test_rawlogger-valgrind.log  -v ${BIN_DIR}/test_rawlogger
	mv test_rawlogger-valgrind.log ${LOG_DIR}/

