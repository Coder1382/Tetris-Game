RUN = gcc -Wall -Werror -Wextra -O2 -std=c11 --pedantic
ifeq ($(shell uname),Linux)
	OS = -lcheck -lm -lrt -lpthread -lsubunit -lncursesw
else
	OS = -lcheck -lm -lpthread -lncursesw
endif
all:	clean install
tetris.a:	tetris.o
	ar rcs tetris.a *.o
	ranlib tetris.a
tetris.o:	*.c *.h
	$(RUN) *.c -c
clean:
	rm -rf Tetris *.gcda *.gcno *.o *.info *.a *.tar.gz docs/html
tetris:	tetris.o
	$(RUN) *.c -o tetris $(OS)
install:	clean tetris
	mkdir Tetris && mv tetris Tetris
	./Tetris/tetris
uninstall:
	rm -rf Tetris
dist:
	tar czvf tetris.tar.gz --ignore-failed-read Makefile
dvi:
	$(shell which firefox || which xdg-open || which open || which x-www-browser) docs/html/index.html
