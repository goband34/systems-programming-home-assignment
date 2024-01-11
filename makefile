all: rebuild_all
clean_all:
	-rm -r bin
debug: client.c server.c misc.c logging.c
	-mkdir bin
	-mkdir bin/dbg
	-mkdir bin/dbg/logs
	gcc client.c logging.c misc.c -g -D ROOT_DIR='"$(PWD)/bin/dbg"' -O0 -o bin/dbg/client
	gcc server.c logging.c misc.c -g -D ROOT_DIR='"$(PWD)/bin/dbg"' -O0 -o bin/dbg/server
release: client.c server.c misc.c logging.c
	-mkdir bin
	-mkdir bin/rel
	-mkdir bin/rel/logs
	gcc client.c logging.c misc.c -D ROOT_DIR='"$(PWD)/bin/rel"' -o bin/rel/client
	gcc server.c logging.c misc.c -D ROOT_DIR='"$(PWD)/bin/rel"' -o bin/rel/server
build_all: debug release
rebuild_all: clean_all build_all
