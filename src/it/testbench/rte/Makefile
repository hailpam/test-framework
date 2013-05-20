PACKAGE = it/testbench/rte
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

TST_EXT_INT = ../../../../test/${ROOT_PKG}/ext/inc

DATA_OBJ= ${OBJ_DIR}/../data
IOUT_OBJ= ${OBJ_DIR}/../ioutil
LOGR_OBJ= ${OBJ_DIR}/../logger


CC      = g++
CCFLAGS  = -I${INC_DIR} -I${DATA_INC} -I${IOUT_INC} -I${LOGR_INC} -I${ROOT_INC} -I${TST_EXT_INT} -DTEST_DEBUG
LDFLAGS = -lrt -L${DST_DIR}

TGT_0   = syncqueue
TGT_1   = thread
TGT_2	= job
TGT_3	= jobprod
TGT_4	= jobcons
TGT_5	= reportcons
TGT_6	= rte

TEST    = test_rte
DIST	= librte.a

DEP		= data
DEP_1	= ioutil
DEP_2	= logger
DEP_3   = test_ext

.PHONY: clean cleantest runtest distributable


all:  ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_3}.o ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${TGT_5}.o ${OBJ_DIR}/${TGT_6}.o ${OBJ_DIR}/${TEST}.o ${TEST}
	$(MAKE) distributable

debug: CCFLAGS += -DDEBUG_PRINT_ENABLED -DDATA_DEBUG_ENABLED -g3
debug: all

${TEST}: ${OBJ_DIR}/${TEST}.o ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_3}.o ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${TGT_5}.o ${OBJ_DIR}/${TGT_6}.o  
	$(CC) -o $@ $^ $(LDFLAGS) -l${DEP} -l${DEP_1} -l${DEP_2} -l${DEP_3}
	mv ${TEST} ${BIN_DIR}/

${OBJ_DIR}/${TGT_1}.o: ${TGT_1}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_1}.o

${OBJ_DIR}/${TGT_2}.o: ${TGT_2}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_2}.o

${OBJ_DIR}/${TGT_3}.o: ${TGT_3}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_3}.o

${OBJ_DIR}/${TGT_4}.o: ${TGT_4}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_4}.o

${OBJ_DIR}/${TGT_5}.o: ${TGT_5}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_5}.o

${OBJ_DIR}/${TGT_6}.o: ${TGT_6}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_6}.o

${OBJ_DIR}/${TEST}.o: ${TST_DIR}/${TEST}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TEST}.o

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_3}.o ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${TGT_5}.o
	mv *.a ${DST_DIR}/

clean:
	rm -f ${OBJ_DIR}/${TGT_0}.o
	rm -f ${OBJ_DIR}/${TGT_1}.o
	rm -f ${OBJ_DIR}/${TGT_2}.o
	rm -f ${OBJ_DIR}/${TGT_3}.o
	rm -f ${OBJ_DIR}/${TGT_4}.o
	rm -f ${OBJ_DIR}/${TGT_5}.o
	rm -f ${OBJ_DIR}/${TGT_6}.o
	rm -f ${OBJ_DIR}/${TEST}.o

cleantest: clean cleandist
	rm -f ${BIN_DIR}/${TEST}

cleandist:
	rm -f ${DST_DIR}/${DIST}

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=${TEST}-valgrind.log  -v ${BIN_DIR}/${TEST}
	mv ${TEST}-valgrind.log ${LOG_DIR}/

