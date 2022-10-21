
build:
	mkdir build

liba/a.o: liba/a.c liba/a.h
	cd liba && gcc -c -Wall -Werror -fPIC a.c

libb/b.o: libb/b.c libb/b.h liba/a.h
	cd libb && gcc -c -Wall -Werror -fPIC b.c -I ../liba

libd/d.o: libd/d.c libd/d.h libb/b.h liba/a.h
	cd libd && gcc -c -Wall -Werror -fPIC d.c -I ../libb -I ../liba

build/liba.so: build liba/a.o
	gcc -shared -o $@ liba/a.o

build/libb.so: build libb/b.o build/liba.so
	gcc -shared -o $@ libb/b.o -L ./build -la

build/libd.so: libd/d.o build/libb.so
	# gcc -shared -o $@ libd/d.o -L ./build -lb -la
	# no need to link -la because the dependency is already in the -lb
	gcc -shared -o $@ libd/d.o -L ./build -lb

.PHONY: liba
liba: build/liba.a

.PHONY: libb
libb: build/libb.a

.PHONY: libb
test: build/libd.so
	nm -g $^
	ldd build/liba.so
	ldd build/libb.so
	ldd build/libd.so

.PHONY: clean
clean:
	rm -rf build
	rm -rf liba/*.o
	rm -rf libb/*.o
