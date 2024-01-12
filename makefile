all: rebuild_all
clean_all:
	-rm -r bin
debug: client.c server.c misc.c logging.c
	-mkdir bin
	-mkdir bin/dbg
	-mkdir bin/dbg/logs
	gcc client.c logging.c response_model.c misc.c -g -D DEFAULT_LOG_FILE_PATH='"$(PWD)/bin/dbg/logs/all.log"' -O0 -o bin/dbg/client_demo
	gcc client.c logging.c response_model.c misc.c -g -D DEFAULT_LOG_FILE_PATH='"$(PWD)/bin/dbg/logs/all.log"' -DFULL_VERSION -O0 -o bin/dbg/client_full_version
	gcc server.c logging.c response_model.c misc.c -g -D DEFAULT_LOG_FILE_PATH='"$(PWD)/bin/dbg/logs/all.log"' -O0 -o bin/dbg/server
release: client.c server.c misc.c logging.c
	-mkdir bin
	-mkdir bin/rel
	-mkdir bin/rel/logs
	gcc client.c logging.c response_model.c misc.c -D DEFAULT_LOG_FILE_PATH='"$(PWD)/bin/rel/logs/all.log"' -o bin/rel/client_demo
	gcc client.c logging.c response_model.c misc.c -D DEFAULT_LOG_FILE_PATH='"$(PWD)/bin/rel/logs/all.log"' -DFULL_VERSION -o bin/rel/client_full_version
	gcc server.c logging.c response_model.c misc.c -D DEFAULT_LOG_FILE_PATH='"$(PWD)/bin/rel/logs/all.log"' -o bin/rel/server
build_all: debug release
rebuild_all: clean_all build_all
