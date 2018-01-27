default: client
	
client: Project1Client.c
	gcc -Wall -o Project1Client Project1Client.c

clean:
	rm *.o Project1Client
