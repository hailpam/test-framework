PACKAGE = it/testbench/parser

SRC_DIR = src
OBJ_DIR = ../../../../obj/${PACKAGE}
INC_DIR = ../../../../inc/${PACKAGE}
DST_DIR = ../../../../dist
TST_DIR = ../../../../test/${PACKAGE}
BIN_DIR = ../../../../bin/

CC      = g++
CCFLAGS  = -I${INC_DIR}
LDFLAGS = -lrt

TARGET  = parser
TEST    = test_parser
DIST	= libparser.a

all: ${TARGET}.o ${TEST}.o ${TEST}

${TEST}: ${OBJ_DIR}/${TEST}.o ${OBJ_DIR}/${TARGET}.o
	$(CC) -o $@ $^ $(LDFLAGS)
	mv ${TEST} ${BIN_DIR}/

${TARGET}.o: ${TARGET}.cpp ${INC_DIR}/${TARGET}.h
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

${TEST}.o: ${TST_DIR}/${TEST}.cpp ${OBJ_DIR}/${TARGET}.o
	$(CC) -Wall -c $(CCFLAGS) $<
	mv *.o ${OBJ_DIR}/

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/${TARGET}.o
	mv *.a ${DST_DIR}/

clean:
	rm ${OBJ_DIR}/*.o

cleantest: clean
	rm ${BIN_DIR}/${TEST}

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=${TEST}-valgrind.log  -v ${BIN_DIR}/${TEST}
	mv ${TEST}-valgrind.log ${LOG_DIR}/

