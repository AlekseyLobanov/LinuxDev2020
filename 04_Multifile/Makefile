GENERATES = prog prog-a prog-so README libout.a libout.so
TRASH = *.o *~ o.*

%.o: %.c
	cc $< -c -o $@

fun.o: outlib.h

all: README prog prog-a

prog: const.o fun.o prog.o
	cc $^ -o $@

prog-a: libout.a prog.o
	cc -L. prog.o -lout -o prog-a

libout.a: const.o fun.o
	ar -rcs libout.a const.o fun.o


prog-so: libout.so prog.o
	cc -L. prog.o -lout -o prog-so

libout.so: const.c fun.c outlib.h
	cc fun.c -c -fPIC -o fun-pic.o
	cc const.c -c -fPIC -o const-pic.o
	cc -shared fun-pic.o const-pic.o -o libout.so


test: prog prog-a prog-so
	./prog hello 2>&1 > prog.test.o
	./prog-a hello 2>&1 > prog-a.test.o
	LD_LIBRARY_PATH=`pwd` ./prog-so hello 2>&1 > prog-so.test.o
	cmp prog.test.o prog-a.test.o
	cmp prog-a.test.o prog-so.test.o

	./prog hell o world 2>&1 > prog.test.o
	./prog-a hell o world 2>&1 > prog-a.test.o
	LD_LIBRARY_PATH=`pwd` ./prog-so hell o world 2>&1 > prog-so.test.o
	cmp prog.test.o prog-a.test.o
	cmp prog-a.test.o prog-so.test.o



README: prog
	./$< 2> $@

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)

