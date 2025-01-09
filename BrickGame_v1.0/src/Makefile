CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
SPECIALFLAGS = -lcheck
OS := $(shell uname -s)
TARGET = tetris
SRCS = $(wildcard brick_game/tetris/*.c) $(wildcard gui/cli/*.c) 
SRCS2 = $(wildcard brick_game/tetris/*.o) $(wildcard gui/cli/*.*.o)
SRCS_TEST = $(wildcard tests/s21_*.c) $(wildcard gui/cli/*.c) brick_game/tetris/fsm.c brick_game/tetris/tetris_backend.c
OBJS = $(SRCS:.c=.o)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
GCOV_LDFLAGS= -L/usr/local/lib -I/usr/local/include
USERNAME=$(shell whoami)

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open 
	SPECIALFLAGS += -lpthread -lrt -lsubunit -lm
	BREW = .
else
	OPEN_CMD = open
	BREW := ${HOME}/homebrew
endif

all: $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(TARGET): 
	$(CC) $(CFLAGS) -o tetris $(SRCS) $(SPECIALFLAGS) -lncurses

gcov_report: clean
	$(CC) $(CFLAGS) -o s21_gcovtest $(SRCS_TEST) $(SPECIALFLAGS) $(GCOV_FLAGS) -lncurses
	./s21_gcovtest
	mkdir -p unit_tests
	mv *.gcda *.gcno unit_tests
	lcov -t s21_gcovtest -o s21_gcovtest.info -c -d .
	genhtml -o report s21_gcovtest.info
	$(OPEN_CMD) ./report/index.html

install: clean $(TARGET)
	mkdir game
	cp tetris game

uninstall:
	rm -rf game

clean: rm clear
	
rm:
	rm -f tetris
	rm -rf *.o *.gch
	rm -rf *.dSYM
	rm -rf *.gcda *.gcno *.gcov
	rm -rf unit_tests
	rm -rf s21_gcovtest
	rm -rf s21_gcovtest.info
	rm -rf test_report
	rm -rf report
	rm -rf $(SRCS2)
	rm -rf Doxyfile latex html
	rm -rf game


rebuild: clean all
	
valgrind: $(TARGET)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose ./$(TARGET)

leaks: $(TARGET)
	leaks --atExit -- ./$(TARGET)

install_brew:
	git clone https://github.com/Homebrew/brew ~/../../opt/goinfre/$(USERNAME)/homebrew

brew:
	brew

lcov:
	brew install lcov

test:
	$(CC) $(CFLAGS) -o s21_gcovtest $(SRCS_TEST) $(SPECIALFLAGS) $(GCOV_FLAGS) -lncurses
	./s21_gcovtest

clang:
	clang-format -style=Google -i ./**/**/*.h
	clang-format -style=Google -i tests/*.c
check:
	clang-format -style=Google -n ./**/**/*.h
	clang-format -style=Google -n tests/*.c

dvi: clean doxygen
	$(OPEN_CMD) ./html/index.html

doxygen:
	doxygen -g
	doxygen

clear:
	clear

.PHONY: clear doxygen gcov_report install_brew lcov leaks test valgrind clean all rebuild clang check brew s21_matrix.a rm
