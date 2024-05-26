COMPILER := gcc
CFLAGS := -Wall
OBJECT_FILES := main.o myport.o
OUTPUT_NAME := prog

all: ${OBJECT_FILES}
	${COMPILER} -o ${OUTPUT_NAME} ${OBJECT_FILES} ${CFLAGS}

${OUTPUT_NAME}: ${OBJECT_FILES}
	${COMPILER} -o prog ${OBJECT_FILES} ${CFLAGS}


main.o: main.c myport.h
	${COMPILER} -c main.c ${CFLAGS}

myport.o: myport.c myport.h
	${COMPILER} -c myport.c ${CFLAGS}