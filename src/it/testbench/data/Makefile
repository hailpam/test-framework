PACKAGE = it/testbench/data

SRC_DIR = src
OBJ_DIR = ../../../../obj/${PACKAGE}
INC_DIR = ../../../../inc/${PACKAGE}
INC_TST = ../../../../inc/it/testbench
DST_DIR = ../../../../dist
TST_DIR = ../../../../test/${PACKAGE}
BIN_DIR = ../../../../bin

CC      = g++
CCFLAGS  = -I${INC_DIR} -I${INC_TST} -I${TST_DIR}
LDFLAGS = -lrt

TARGET  = data
TGT_1   = report
TGT_2   = observer
TGT_3   = testitem
TGT_4   = testbench
TEST    = test_data
TEST_1  = fake_observer
TEST_2  = concrete_ctxobject
TEST_3  = custom_testitems
DIST	= libdata.a

.PHONY: clean cleantest distributable runtest

all: ${OBJ_DIR}/${TARGET}.o ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_3}.o ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${TEST}.o ${OBJ_DIR}/${TEST_1}.o ${OBJ_DIR}/${TEST_2}.o ${OBJ_DIR}/${TEST_3}.o ${TEST}

${TEST}: ${OBJ_DIR}/${TARGET}.o ${OBJ_DIR}/${TGT_1}.o ${OBJ_DIR}/${TGT_2}.o ${OBJ_DIR}/${TGT_3}.o  ${OBJ_DIR}/${TGT_4}.o ${OBJ_DIR}/${TEST}.o ${OBJ_DIR}/${TEST_1}.o ${OBJ_DIR}/${TEST_2}.o ${OBJ_DIR}/${TEST_3}.o
	$(CC) -o $@ $^ $(LDFLAGS)
	mv ${TEST} ${BIN_DIR}/

${OBJ_DIR}/${TARGET}.o: ${TARGET}.cpp ${INC_DIR}/${TARGET}.h
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${OBJ_DIR}/${TGT_1}.o: ${TGT_1}.cpp ${INC_DIR}/support.h
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${OBJ_DIR}/${TGT_2}.o: ${TGT_2}.cpp ${INC_DIR}/${TGT_2}.h
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${OBJ_DIR}/${TGT_3}.o: ${TGT_3}.cpp ${INC_DIR}/${TGT_3}.h
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${OBJ_DIR}/${TGT_4}.o: ${TGT_4}.cpp ${INC_DIR}/${TGT_4}.h
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${OBJ_DIR}/${TEST}.o: ${TST_DIR}/${TEST}.cpp ${OBJ_DIR}/${TARGET}.o
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${OBJ_DIR}/${TEST_1}.o: ${TST_DIR}/${TEST_1}.cpp ${OBJ_DIR}/${TARGET}.o
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${OBJ_DIR}/${TEST_2}.o: ${TST_DIR}/${TEST_2}.cpp ${OBJ_DIR}/${TARGET}.o
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${OBJ_DIR}/${TEST_3}.o: ${TST_DIR}/${TEST_3}.cpp ${OBJ_DIR}/${TARGET}.o
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/${TARGET}.o
	mv *.a ${DST_DIR}/

clean:
	rm -f ${OBJ_DIR}/*.o

cleantest: clean
	rm -f ${BIN_DIR}/${TEST}

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=${TEST}-valgrind.log  -v ${BIN_DIR}/${TEST}
	mv ${TEST}-valgrind.log ${LOG_DIR}/

