CARGS = gcc -std=c++17 -g -Wall -Werror -Wextra
GCOVFLAGS = -fprofile-arcs -ftest-coverage
OS = $(shell uname)

FILES = calcModel.cc tests/tests.cc calcExpression.cc calcModel.cc calcParser.cc symbolStruct.cc

APP_ARCHIVE = Archive_SmartCalc_v2.0

ifeq ($(OS), Linux)
	CHECK_FLAGS = -lgtest -lgtest_main -lrt -lm -lstdc++ -pthread
else
	CHECK_FLAGS = -lgtest -lgtest_main -lm -lpthread  -lstdc++
endif

ifeq ($(OS),Linux)
	OPEN_CMD = xdg-open
endif
ifeq ($(OS),Darwin)
	OPEN_CMD = open
endif

all: install

calc_backend.a:
	$(CARGS) -c $(FILES)
	ar rcs calc_backend.a *.o
	rm -rf *.o

test: calc_backend.a
	$(CARGS) tests/tests.cc calc_backend.a $(CHECK_FLAGS) -o unit_test
	./unit_test

gcov_report: calc_backend.a
	$(CARGS) $(GCOVFLAGS) $(FILES) $(CHECK_FLAGS) -o gcov_test
	./gcov_test
	gcov $(FILES)
	lcov -t "test" -o test.info -c -d .
	genhtml -o report/ test.info
	rm -rf *.o *.gcno *.gcda
	$(OPEN_CMD) ./report/index.html

install: uninstall
	mkdir ../build;
	cp Calculator_x.pro ../build/Calculator_x.pro
	cd ../build; qmake Calculator_x.pro; make
	

uninstall:
	rm -rf ../build

open:
	open ../build/Calculator_x.app

run: install open

dist:
	rm -rf $(APP_ARCHIVE)/
	mkdir $(APP_ARCHIVE)
	mkdir $(APP_ARCHIVE)/src/
	cp -r ../build/Calculator_x.app $(APP_ARCHIVE)/src/Calculator_x.app
	tar -cvzf $(APP_ARCHIVE).tgz $(APP_ARCHIVE)/
	rm -rf $(APP_ARCHIVE)

dvi:
	$(OPEN_CMD) dvi.txt

leaks: test
	CK_FORK=no leaks --atExit -- ./unit_test

valgrind: test
	CK_FORK=no valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all ./unit_test

clean:
	rm -rf ../build*
	rm -rf *.o *.gcno *.gcda *.a *.info report .clang-format *.out *.dSYM *.Identifier *.stash
	rm -rf $(APP_ARCHIVE).tgz
	rm -f unit_test
	rm -f gcov_test
	rm -f out
	rm -f *.gcov