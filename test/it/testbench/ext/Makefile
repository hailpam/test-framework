PACKAGE = it/testbench/ext

SRC_DIR = src
OBJ_DIR = obj
INC_DIR = inc

INC_DEP1 = ../../../../inc/it/testbench/data
INC_DEP2 = ../../../../inc/it/testbench

DST_DIR = ../../../../dist

CC      = g++
CCFLAGS = -I${INC_DIR} -I${INC_DEP1} -I${INC_DEP2} -DTEST_DEBUG
LDFLAGS = -lrt

EXT_1   = fake_observer
EXT_2   = concrete_ctxobject
EXT_3   = custom_testitems
EXT_4   = concrete_testbuilder

DIST	= libtest_ext.a

.PHONY: clean distributable

all: ${EXT_1}.o ${EXT_2}.o ${EXT_3}.o ${EXT_4}.o
	$(MAKE) distributable

debug: CCFLAGS += -DDEBUG_PRINT_ENABLED -DDATA_DEBUG_ENABLED -g3
debug: all

${EXT_1}.o: ${SRC_DIR}/${EXT_1}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${EXT_1}.o

${EXT_2}.o: ${SRC_DIR}/${EXT_2}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${EXT_2}.o

${EXT_3}.o: ${SRC_DIR}/${EXT_3}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${EXT_3}.o

${EXT_4}.o: ${SRC_DIR}/${EXT_4}.cpp
	$(CC) -Wall -c $(CCFLAGS) $< -o ${OBJ_DIR}/${EXT_4}.o

distributable:
	ar -cvq ${DIST} ${OBJ_DIR}/${EXT_1}.o ${OBJ_DIR}/${EXT_2}.o ${OBJ_DIR}/${EXT_3}.o ${OBJ_DIR}/${EXT_4}.o
	mv *.a ${DST_DIR}/

clean: cleandist
	rm -f ${OBJ_DIR}/${EXT_1}.o
	rm -f ${OBJ_DIR}/${EXT_2}.o
	rm -f ${OBJ_DIR}/${EXT_3}.o
	rm -f ${OBJ_DIR}/${EXT_4}.o

cleandist:
	rm -f ${DST_DIR}/${DIST}

