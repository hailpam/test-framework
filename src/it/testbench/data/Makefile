PACKAGE = it/testbench/data

SRC_DIR = src
OBJ_DIR = ../../../../obj/${PACKAGE}
INC_DIR = ../../../../inc/${PACKAGE}
INC_TST = ../../../../inc/it/testbench
DST_DIR = ../../../../dist
TST_DIR = ../../../../test/${PACKAGE}
BIN_DIR = ../../../../bin
DST_DIR = ../../../../dist

CC      = g++
CCFLAGS  = -I${INC_DIR} -I${INC_TST} -I${TST_DIR} -DTEST_DEBUG
LDFLAGS = -lrt -L${DST_DIR}

TGT_1   = report
TGT_2   = observer
TGT_3   = testitem
TGT_4   = testbench
EXCPT   = tfexception

TEST_1  = fake_observer
TEST_2  = concrete_ctxobject
TEST_3  = custom_testitems
TEST_4  = concrete_testbuilder

TEST    = test_data

DIST	= libdata.a

.PHONY: clean cleantest distributable runtest

all: ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_3}.o ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${EXCPT}.o \
	 ${OBJ_DIR}/${TEST_1}.o ${OBJ_DIR}/${TEST_2}.o ${OBJ_DIR}/${TEST_3}.o ${OBJ_DIR}/${TEST_4}.o ${OBJ_DIR}/${TEST}.o \
	 ${TEST}
	$(MAKE) distributable

debug: CCFLAGS += -DDEBUG_PRINT_ENABLED -DDATA_DEBUG_ENABLED -g3
debug: all

${TEST}: ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_3}.o ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${EXCPT}.o \
	  ${OBJ_DIR}/${TEST}.o
	$(CC) -o ${BIN_DIR}/$@ $^ $(LDFLAGS) -ltest_ext

${OBJ_DIR}/${EXCPT}.o: ${EXCPT}.cpp 
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${EXCPT}.o

${OBJ_DIR}/${TGT_1}.o: ${TGT_1}.cpp 
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_1}.o

${OBJ_DIR}/${TGT_2}.o: ${TGT_2}.cpp 
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_2}.o

${OBJ_DIR}/${TGT_3}.o: ${TGT_3}.cpp 
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_3}.o

${OBJ_DIR}/${TGT_4}.o: ${TGT_4}.cpp 
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TGT_4}.o

${OBJ_DIR}/${TEST}.o: ${TST_DIR}/${TEST}.cpp 
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TEST}.o

${OBJ_DIR}/${TEST_1}.o: ${TST_DIR}/${TEST_1}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TEST_1}.o

${OBJ_DIR}/${TEST_2}.o: ${TST_DIR}/${TEST_2}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TEST_2}.o

${OBJ_DIR}/${TEST_3}.o: ${TST_DIR}/${TEST_3}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TEST_3}.o

${OBJ_DIR}/${TEST_4}.o: ${TST_DIR}/${TEST_4}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${TEST_4}.o

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_3}.o ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${EXCPT}.o
	mv *.a ${DST_DIR}/

clean:
	rm -f ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_3}.o ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${EXCPT}.o \
		${OBJ_DIR}/${TEST_1}.o ${OBJ_DIR}/${TEST_2}.o ${OBJ_DIR}/${TEST_3}.o ${OBJ_DIR}/${TEST_4}.o ${OBJ_DIR}/${TEST}.o

cleantest: clean cleandist
	rm -f ${BIN_DIR}/${TEST} 

cleandist:
	rm -f ${DST_DIR}/${DIST}

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=${TEST}-valgrind.log  -v ${BIN_DIR}/${TEST}
	mv ${TEST}-valgrind.log ${LOG_DIR}/

