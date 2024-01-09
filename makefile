all: rebuild_all
clean_all:
	-rm -r bin
debug: client.c server.c misc.c
	mkdir bin
	mkdir bin/dbg
	gcc client.c misc.c -g -O0 -o bin/dbg/client
	gcc server.c misc.c -g -O0 -o bin/dbg/server
release: client.c server.c misc.c
	mkdir bin
	mkdir bin/dbg
	gcc client.c misc.c -o bin/dbg/client
	gcc server.c misc.c -o bin/dbg/server
build_all: debug release
rebuild_all: clean_all build_all
