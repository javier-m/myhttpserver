SRC = src/myhttpserver.c src/parseArgs.c src/connectionHTTP.c src/child_process.c
OBJ = src/myhttpserver.o src/parseArgs.o src/connectionHTTP.o src/child_process.o

PROG = myhttpserver

$(PROG): $(OBJ)
	gcc $(SRC) -o $(PROG)

$(OBJ): $(SRC)
