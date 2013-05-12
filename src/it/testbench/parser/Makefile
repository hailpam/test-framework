PACKAGE = it/testbench/parser
ROOT_PKG = it/testbench

SRC_DIR = src
OBJ_DIR = ../../../../obj/${PACKAGE}
INC_DIR = ../../../../inc/${PACKAGE}
DST_DIR = ../../../../dist
TST_DIR = ../../../../test/${PACKAGE}
BIN_DIR = ../../../../bin

DATA_INC= ${INC_DIR}/../data
IOUT_INC= ${INC_DIR}/../ioutil
LOGR_INC= ${INC_DIR}/../logger
ROOT_INC= ../../../../inc/${ROOT_PKG}

DATA_OBJ= ${OBJ_DIR}/../data
IOUT_OBJ= ${OBJ_DIR}/../ioutil
LOGR_OBJ= ${OBJ_DIR}/../logger

CC      = g++
CCFLAGS  = -I${INC_DIR} -I${DATA_INC} -I${IOUT_INC} -I${LOGR_INC} -I${ROOT_INC} -DTEST_DEBUG
LDFLAGS = -lrt -L${DST_DIR}

TARGET  = parser
FSM	= fsmparser
TEST    = test_parser
DIST	= libparser.a

DEP	= data

.PHONY: clean cleantest distributable runtest

all: ${OBJ_DIR}/${TARGET}.o ${OBJ_DIR}/${FSM}.o ${OBJ_DIR}/${TEST}.o ${TEST}
	$(MAKE) distributable

debug: CCFLAGS += -DDEBUG_PRINT_ENABLED -DDATA_DEBUG_ENABLED -g3 
debug: all

${TEST}: ${OBJ_DIR}/${TARGET}.o ${OBJ_DIR}/${FSM}.o ${OBJ_DIR}/${TEST}.o 
	$(CC) -o $@ $^ $(LDFLAGS) -l${DEP}
	mv ${TEST} ${BIN_DIR}/

${OBJ_DIR}/${TARGET}.o: ${TARGET}.cpp ${INC_DIR}/${TARGET}.h
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TARGET}.o

${OBJ_DIR}/${FSM}.o: ${FSM}.cpp ${INC_DIR}/${FSM}.h
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${FSM}.o

${OBJ_DIR}/${TEST}.o: ${TST_DIR}/${TEST}.cpp ${OBJ_DIR}/${TARGET}.o
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TEST}.o

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/${TARGET}.o
	mv *.a ${DST_DIR}/

clean:
	rm -f ${OBJ_DIR}/${TARGET}.o
	rm -f ${OBJ_DIR}/${FSM}.o
	rm -f ${OBJ_DIR}/${TEST}.o

cleantest: clean cleandist
	rm -f ${BIN_DIR}/${TEST}

cleandist:
	rm -f ${DST_DIR}/${DIST}	

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=${TEST}-valgrind.log  -v ${BIN_DIR}/${TEST}
	mv ${TEST}-valgrind.log ${LOG_DIR}/

