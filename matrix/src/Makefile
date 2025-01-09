CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11
SPECIALFLAGS = -lcheck
BACK_P = $(wildcard tests/s21_*.c)
OS := $(shell uname -s)
TARGET = s21_matrix_tests
SRCS = $(wildcard s21_*.c) $(wildcard s21_matrix_tests/s21_*.c) 
SRCS2 = $(wildcard s21_*.o) $(wildcard s21_matrix_tests/s21_*.o)
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

s21_matrix.a: $(OBJS)
	ar rcs s21_matrix.a $(OBJS)
	rm -rf $(SRCS2)

$(TARGET): s21_matrix.a
	$(CC) $(CFLAGS) -o s21_matrix_tests $(SRCS) $(BACK_P) $(SPECIALFLAGS)

gcov_report: clean
	$(CC) $(CFLAGS) -o s21_gcovtest $(SRCS) $(BACK_P) $(SPECIALFLAGS) $(GCOV_FLAGS)
	./s21_gcovtest
	mkdir -p unit_tests
	mv *.gcda *.gcno unit_tests
	lcov  -t s21_gcovtest -o s21_gcovtest.info -c -d .
	genhtml -o report s21_gcovtest.info
	$(OPEN_CMD) ./report/index.html
	
clean: rm clear
	
rm:
	rm -rf *.o
	rm -rf *.a
	rm -f s21_matrix_tests
	rm -rf *.o *.gch
	rm -rf *.dSYM
	rm -rf *.gcda *.gcno *.gcov
	rm -rf unit_tests
	rm -rf s21_gcovtest
	rm -rf s21_gcovtest.info
	rm -rf test_report
	rm -rf report
	rm -f libs21_matrix
	rm -rf .out
	rm -rf $(SRCS2)
	rm -rf Doxyfile latex html


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

test: $(TARGET)
	./$(TARGET)

clang:
	clang-format -style=Google -i $(SRCS)
	clang-format -style=Google -i ./*.h
	clang-format -style=Google -i tests/*.c

check:
	clang-format -style=Google -n $(SRCS)
	clang-format -style=Google -n ./*.h
	clang-format -style=Google -n tests/*.c

doxygen:
	doxygen -g
	doxygen Doxyfile

clear:
	clear

.PHONY: clear doxygen gcov_report install_brew lcov leaks test valgrind clean all rebuild clang check brew s21_matrix.a rm