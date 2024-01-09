testing: main.c misc.c server.c
	gcc -Wall -Wpedantic -o main main.c misc.c
	gcc -Wall -Wpedantic -o server server.c misc.c
