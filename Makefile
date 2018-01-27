########## CONSTANTS ##########
SERVER_IP	= 144.166.207.144
CLIENT_IP	= 144.166.207.143
ECHO_PORT	= 30200
PROJECT_PORT= 30201
###############################

default: client debug

client: Project1Client.c NetworkHeader.h DieWithError.c
	gcc -Wall -o Project1Client Project1Client.c DieWithError.c

debug: Project1Client
	./Project1Client -s $(SERVER_IP):$(ECHO_PORT) -f DAVID -l BRAKMAN

run: Project1Client
	./Project1Client -s $(SERVER_IP):$(PROJECT_PORT) -f DAVID -l BRAKMAN

clean:
	rm *.o Project1Client
