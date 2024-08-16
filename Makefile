#.PHONY: all clean dist dvi install uninstall
RUN = gcc -Wall -Werror -Wextra -O2 -std=c11 --pedantic
ifeq ($(shell uname),Linux)
	OS = -lcheck -lm -lrt -lpthread -lsubunit -lncursesw -lgcov
else
	OS = -lcheck -lm -lpthread -lncursesw -lgcov
endif
all:	clean tetris.a test gcov_report
s21_tetris.a:	tetris.o
	ar rcs tetris.a *.o
	ranlib tetris.a
s21_tetris.o:	tetris/*.c gui/cli/*.c *.h
	$(RUN) *.c *.c -c
clean:
	rm -rf testresult *.gcda *.gcno *.o *.info *.a tests/*.gcno *.tar.gz tests/report test.dSYM docs/html docs/latex report
s21_tetris_install.o:	*.c *.h
tetris:	s21_tetris_install.o
	$(RUN) *.c -o tetris $(OS)
install:	tetris
	mkdir tetris_game
	install tetris tetris_game
play:
	./tetris
uninstall:
	rm -rf tetris_game
