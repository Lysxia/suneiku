CC=gcc -lncurses
HDR=mainmenu.h
SRC=mainmenu.c
EXE=suneiku

suneiku: $(HDR) $(SRC)
	$(CC) -o $(EXE) $(HDR) $(SRC)

clean:
	rm -rf *~ *.gch

cleanall: clean
	rm suneiku
