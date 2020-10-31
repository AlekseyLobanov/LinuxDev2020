GENERATES = preloader.so testfile testFIXfile
TRASH = *.o *~ o.*

all: lib test

lib:
	gcc -g -fPIC -shared  preloader.c -o preloader.so -ldl

test:
	touch testfile
	LD_PRELOAD="./preloader.so" rm testfile
	[ ! -f testfile ]
	touch testFIXfile
	-LD_PRELOAD="./preloader.so" rm testFIXfile
	[ -f testFIXfile ]
	rm testFIXfile

clean:
	rm -f $(TRASH)

distclean: clean
	rm -rf $(GENERATES)