CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c11
SPECIALFLAGS = -lcheck
BACK_P = s21_string/s21_*.c tests/s21_*.c s21_sprintf/s21_*.c s21_sscanf/s21_*.c
HEADER = s21_string/s21_*.h s21_sprintf/s21_*.h s21_sscanf/s21_*.h
OS := $(shell uname -s)
TARGET = s21_string_tests
SRCS = $(wildcard s21_string/s21_*.c) $(wildcard s21_sprintf/s21_*.c) $(wildcard s21_sscanf/s21_*.c)
OBJS = $(SRCS:.c=.o)
GCOV_FLAGS = -fprofile-arcs -ftest-coverage
GCOV_LDFLAGS= -L/usr/local/lib -I/usr/local/include

ifeq ($(OS), Linux)
	OPEN_CMD = xdg-open 
	SPECIALFLAGS += -lpthread -lrt -lsubunit -lm
	BREW = .
else
	OPEN_CMD = open
	BREW := ${HOME}/homebrew
endif

all: clean $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ $(SPECIALFLAGS)

s21_string.a: $(OBJS)
	ar rcs s21_string.a $(OBJS)
	rm -rf s21_string/*.o tests/*.o s21_sscanf/*.o s21_sprintf/*.o
	

$(TARGET): s21_string.a
	$(CC) $(CFLAGS) -o s21_string_tests $(BACK_P) $(SPECIALFLAGS)

clean:
	rm -rf *.o *.gch
	rm -rf *.a
	rm -rf s21_string/*.o tests/*.o s21_sprintf/*.o s21_sscanf/*.o
	rm -rf tests/*.gcov
	rm -f *.out
	rm -f s21_string_tests
	rm -rf *.dSYM
	rm -rf *.gcda *.gcno *.gcov
	rm -rf unit_tests
	rm -rf s21_gcovtest
	rm -rf s21_gcovtest.info
	rm -rf test_report
	rm -rf report
	rm -f libs21_string

rebuild: clean all

valgrind: $(TARGET)
	valgrind --trace-children=yes --track-fds=yes --track-origins=yes --leak-check=full --show-leak-kinds=all --verbose ./$(TARGET)

leaks: $(TARGET)
	leaks --atExit -- ./$(TARGET)

gcov_report: check clean 
	$(CC) $(CFLAGS) $(GCOV_LDFLAGS) $(GCOV_FLAGS) $(BACK_P) -o s21_gcovtest $(SPECIALFLAGS)
	./s21_gcovtest
	mkdir -p unit_tests
	mv *.gcda *.gcno unit_tests
	lcov  -t s21_gcovtest -o s21_gcovtest.info -c -d .
	genhtml -o report s21_gcovtest.info
	$(OPEN_CMD) ./report/index.html

check:
ifeq ("", "$(shell which lcov)")
	$(error "lcov not found, please install it.")
endif
ifeq ($(OS), Linux)
ifeq ("", "$(shell which xdg-open)")
	$(error "xdg-open not found, please install it.")
endif
endif

test: $(TARGET)
	./$(TARGET)
	clang-format -style=Google -n s21_string/*.c
	clang-format -style=Google -n s21_sprintf/*.c
	clang-format -style=Google -n s21_sscanf/*.c
	clang-format -style=Google -n s21_*.h
	clang-format -style=Google -n tests/*.c

clang:
	clang-format -style=Google -i s21_sprintf/*.c
	clang-format -style=Google -i s21_string/*.c
	clang-format -style=Google -i s21_sscanf/*.c
	clang-format -style=Google -i s21_*.h
	clang-format -style=Google -i tests/*.c

.PHONY: clean rebuild clang valgrind leaks test s21_string.a gcov_report check
