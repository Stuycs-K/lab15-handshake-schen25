all: basic_client basic_server persistant

compile: basic_client forking

client: basic_client
	./basic_client

server: forking
	./forking

basic_client: basic_client.o pipe_networking.o
	gcc -o client basic_client.o pipe_networking.o

basic_server: basic_server.o pipe_networking.o
	gcc -o server basic_server.o pipe_networking.o

persistant: persistant_server.o pipe_networking.o
	gcc -o persistant persistant_server.o pipe_networking.o

forking: forking_server.o pipe_networking.o
	gcc -o forking forking_server.o pipe_networking.o

persistant_server.o: persistant_server.c pipe_networking.h
	gcc -c persistant_server.c

forking_server.o: forking_server.c pipe_networking.h
	gcc -c forking_server.c

basic_client.o: basic_client.c pipe_networking.h
	gcc -c basic_client.c

basic_server.o: basic_server.c pipe_networking.h
	gcc -c basic_server.c

pipe_networking.o: pipe_networking.c pipe_networking.h
	gcc -c pipe_networking.c

clean:
	rm *.o
	rm *~
