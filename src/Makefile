FLAG=-Werror -Wall -Wextra -lm
FLAG_TEST=-lcheck
FLAG_GCOV=-fprofile-arcs -ftest-coverage
DFLAG=-Werror -Wall -Wextra -g -std=c11 -lm
FLAGS_TEST_LM=`pkg-config --cflags --libs check` -lm

ALL_FILES=s21_compare_dec.c s21_arithmetic_dec.c s21_convert_dec.c s21_other_dec.c s21_support_dec.c s21_support_test.c s21_decimal.h s21_test.c test.c

SRC_FILES=s21_compare_dec.c s21_arithmetic_dec.c s21_convert_dec.c s21_other_dec.c s21_support_dec.c
SRC1_FILES=s21_compare_dec.c s21_arithmetic_dec.c s21_convert_dec.c s21_other_dec.c s21_support_dec.c s21_support_test.c

TST_FILES=s21_test.c s21_support_test.c
EXEC_FILE=s21_test

all: nstyle s21_decimal.a test gcov_report

db:
	gcc $(DFLAG) $(SRC1_FILES) test.c -lm
	./a.out

cs:
	dotnet run --project test_cs/ >> test.tst

tcs:
	dotnet run --project test_cs/

clean:
	rm -rf $(EXEC_FILE) lcover_rep
	rm *.o *.a *.out *.gcov *.gcno *.gcda *.gch *.info #$(TEST_FILES)

test:
	gcc -c $(TST_FILES) -lcheck
	gcc s21_support_test.o s21_test.o s21_decimal.a -o $(EXEC_FILE) -lcheck
	./$(EXEC_FILE)

test_l:
	gcc $(FLAG) $(SRC_FILES) $(TST_FILES) -o $(EXEC_FILE) $(FLAGS_TEST_LM)
	./$(EXEC_FILE)

s21_decimal.a:
	gcc $(FLAG) -c $(SRC_FILES)
	ar rc s21_decimal.a s21_arithmetic_dec.o s21_compare_dec.o s21_convert_dec.o s21_other_dec.o s21_support_dec.o

gcov_report:
	gcc $(FLAG) $(FLAG_TEST) $(FLAG_GCOV) $(SRC_FILES) $(TST_FILES) -o $(EXEC_FILE)
	./$(EXEC_FILE)
	gcov $(SRC_FILES)


lcov_report:
	lcov --capture --directory . --output-file lcover.info
	genhtml lcover.info --output-directory lcover_rep
	open lcover_rep/index.html

brew_a:
	sh t.sh
	#eval "$(/opt/goinfre/littleca/homebrew/bin/brew shellenv)"
	#chmod -R go-w "$(brew --prefix)/share/zsh"

istyle:
	clang-format -i --style=google $(ALL_FILES)

nstyle:
	clang-format -n --style=google $(ALL_FILES)

lcov:
	brew install lcov

val:
	valgrind --leak-check=full --show-leak-kinds=all --leak-resolution=high --undef-value-errors=yes --log-file=testlog.log -s -v ./a.out

leaks:
	leaks -atExit -- ./s21_test

brew:
	#cd ~/goinfre
	#git clone https://github.com/Homebrew/brew homebrew
	#eval "$(~/goinfre/littleca/homebrew/bin/brew shellenv)"

dotnet:
	brew install dotnet
