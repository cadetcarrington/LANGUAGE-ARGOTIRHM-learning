EXECS=mpihelloworld
MPICC?=mpicxx

all: ${EXECS}

mpihelloworld: mpihelloworld.cpp
	${MPICC} -o mpihelloworld mpihelloworld.cpp

clean:
	rm ${EXECS}
