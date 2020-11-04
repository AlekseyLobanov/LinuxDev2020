GENERATES = main libbuf.so tester *.gcov
TRASH = *.o *~ o.* *.gcdna *.gcno *.gcda

all: lib main tester


lib:
	gcc -shared -fPIC -c buf.c -o libbuf.so

main: lib
	gcc -L. main.c -lbuf -o main

tester:
	# Запускаем без библиотеки для показа результатов покрытия
	gcc -fprofile-arcs -ftest-coverage -O0 -g -L. tests.c buf.c -o tester
	./tester
	gcov -b -c buf.c

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

