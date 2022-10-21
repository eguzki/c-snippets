build:
	mkdir build

liba/a.o: liba/a.c liba/a.h
	cd liba && gcc -c -Wall -Werror -fPIC a.c

libb/b.o: libb/b.c libb/b.h liba/a.h
	cd libb && gcc -c -Wall -Werror -fPIC b.c -I ../liba

libd/d.o: libd/d.c libd/d.h libb/b.h
	cd libd && gcc -c -Wall -Werror -fPIC d.c -I ../libb

build/liba.so: build liba/a.o
	gcc -shared -o $@ liba/a.o

build/libb.so: build libb/b.o build/liba.so
	gcc -shared -o $@ libb/b.o -L ./build -la

build/libd.so: libd/d.o build/libb.so
	gcc -shared -o $@ libd/d.o -L ./build -lb

.PHONY: liba
liba: build/liba.a

.PHONY: libb
libb: build/libb.a

.PHONY: libb
test: build/libd.so
	nm -g $^
	LD_LIBRARY_PATH=`pwd`/build:$LD_LIBRARY_PATH ldd build/liba.so
	LD_LIBRARY_PATH=`pwd`/build:$LD_LIBRARY_PATH ldd build/libb.so
	LD_LIBRARY_PATH=`pwd`/build:$LD_LIBRARY_PATH ldd build/libd.so

.PHONY: clean
clean:
	rm -rf build
	rm -rf liba/*.o
	rm -rf libb/*.o
