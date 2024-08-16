#.PHONY: all clean dist dvi install uninstall
RUN = gcc -Wall -Werror -Wextra -O2 -std=c11 --pedantic
ifeq ($(shell uname),Linux)
	OS = -lcheck -lm -lrt -lpthread -lsubunit -lncursesw -lgcov
else
	OS = -lcheck -lm -lpthread -lncursesw -lgcov
endif
all:	clean s21_tetris.a test gcov_report
s21_tetris.a:	s21_tetris.o
	ar rcs s21_tetris.a *.o
	ranlib s21_tetris.a
s21_tetris.o:	brick_game/tetris/s21*.c gui/cli/s21*.c brick_game/tetris/s21*.h
	$(RUN) brick_game/tetris/s21*.c gui/cli/s21*.c -c
test:	clean
	$(RUN) --coverage brick_game/tetris/s21*.c gui/cli/s21*.c tests/s21*.c -o testresult $(OS)
	./testresult
gcov_report:	test
	lcov -t "tetris_test" -o tetris.info -c -d .
	lcov --remove tetris.info /usr/include/* -o tetris.info
	genhtml -o report tetris.info
	open report/index.html
	rm -rf *.gcno *gcda *.gcov
clang:
	clang-format -style=Google -n brick_game/tetris/*.c gui/cli/*.c brick_game/tetris/*.h tests/*.c tests/*.h
style:
	clang-format -style=Google -i brick_game/tetris/*.c gui/cli/*.c brick_game/tetris/*.h tests/*.c tests/*.h
clean:
	rm -rf testresult *.gcda *.gcno *.o *.info *.a tests/*.gcno *.tar.gz tests/report test.dSYM docs/html docs/latex report
valgrind:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose make tetris
s21_tetris_install.o:	brick_game/tetris/*.c gui/cli/*.c brick_game/tetris/*.h
tetris:	s21_tetris_install.o
	$(RUN) brick_game/tetris/*.c gui/cli/*.c -o tetris $(OS)
install:	tetris
	install tetris /usr/local/bin/tetris
uninstall:
	rm -rf /usr/local/bin/tetris
dist:
	tar czvf tetris.tar.gz --ignore-failed-read brick_game gui tests Makefile Doxyfile menu.md chart.jpg
dvi:
	@doxygen
	$(shell which firefox || which xdg-open || which open || which x-www-browser) docs/html/index.html