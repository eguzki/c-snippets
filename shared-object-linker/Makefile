
build:
	mkdir build

liba/a.o: liba/a.c liba/a.h
	cd liba && gcc -c -Wall -Werror -fPIC a.c

libb/b.o: libb/b.c libb/b.h liba/a.h
	cd libb && gcc -c -Wall -Werror -fPIC b.c -I ../liba

libc/c.o: libc/c.c libc/c.h libb/b.h
	cd libc && gcc -c -Wall -Werror -fPIC c.c -I ../libb

build/liba.a: build liba/a.o
	ar qc $@ liba/a.o

build/libb.a: build libb/b.o
	ar qc $@ libb/b.o

build/libc-all-symbols.so: libc/c.o build/liba.a build/libb.a
	gcc -shared -o $@ libc/c.o build/libb.a build/liba.a

build/libc-missing-symbols.so: libc/c.o build/liba.a build/libb.a
	# order in which objects are added matters
	# https://gcc.gnu.org/onlinedocs/gcc/Link-Options.html
	# It makes a difference where in the command you write this option; the linker searches and processes libraries and object files in the order they are specified. Thus, ‘foo.o -lz bar.o’ searches library ‘z’ after file foo.o but before bar.o. If bar.o refers to functions in ‘z’, those functions may not be loaded.
	# First A, then B. But since B refers to functions in A, A methods will be undefined
	gcc -shared -o $@ libc/c.o build/liba.a build/libb.a

.PHONY: liba
liba: build/liba.a

.PHONY: libb
libb: build/libb.a

.PHONY: libb
test: build/libc.so
	nm -g $^

.PHONY: clean
clean:
	rm -rf build
	rm -rf liba/*.o
	rm -rf libb/*.o
