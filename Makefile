EXECS=dcooke_analyzer
CC=gcc
MYFILE=Quinten_Project1.c

all: ${EXECS}

${EXECS}: ${MYFILE}
	${CC} -o ${EXECS} ${MYFILE}

clean:
	rm -f ${EXECS}
