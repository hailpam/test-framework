PACKAGE = it/testbench/formatter

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
DIST	= libformatter.a

OBJS	= ${OBJ_DIR}/formatter_manager.o ${OBJ_DIR}/console_functor.o ${OBJ_DIR}/csv_functor.o ${OBJ_DIR}/json_functor.o \
		${OBJ_DIR}/txt_functor.o ${OBJ_DIR}/xml_functor.o
TEST_OBJS = ${OBJ_DIR}/test_formatter.o
TEST	= test_formatter

.PHONY: clean cleantest distributable runtest

all: ${OBJS} ${TEST_OBJS} ${BIN_DIR}/${TEST}
	$(MAKE) distributable

debug: CCFLAGS += -DDEBUG_PRINT_ENABLED -g3
debug: all

${BIN_DIR}/${TEST}: ${OBJS} ${TEST_OBJS} ${DST_DIR}/libdata.a
	$(CC) -o $@ $^ $(LDFLAGS)

${OBJ_DIR}/test_formatter.o: ${TST_DIR}/test_formatter.cpp ${OBJS}
	$(CC) -Wall -c $(CCFLAGS) $< -o $@

${OBJ_DIR}/formatter_manager.o: formatter_manager.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o $@

${OBJ_DIR}/console_functor.o: console_functor.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o $@

${OBJ_DIR}/csv_functor.o: csv_functor.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o $@

${OBJ_DIR}/json_functor.o: json_functor.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o $@

${OBJ_DIR}/txt_functor.o: txt_functor.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o $@

${OBJ_DIR}/xml_functor.o: xml_functor.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o $@

distributable:
	ar -cvq ${DIST} ${OBJS}
	mv ${DIST} ${DST_DIR}/

clean:
	rm -f ${OBJS} ${TEST_OBJS}

cleantest: clean
	rm -f ${BIN_DIR}/${TEST}

cleandist: cleantest
	rm -f ${DST_DIR}/${DIST}

runtest:
	valgrind --tool=memcheck --leak-check=yes --log-file=${TEST}-valgrind.log  -v ${BIN_DIR}/${TEST}
	mv ${TEST}-valgrind.log ${LOG_DIR}/

