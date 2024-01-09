all :  server driver passengers        

server : server.o
	gcc server.o -o server
	
server.o : server.c
	gcc -c -g -std=c99 server.c
	
driver : driver.o
	gcc driver.o -o driver
	
driver.o : driver.c
	gcc -c -g -Wall -Wextra -std=c99 driver.c

passengers : passengers.o
	gcc passengers.o -o passengers
	
passengers.o : passengers.c
	gcc -c -g -Wall -Wextra -std=c99 passengers.c
	
clean:
	rm -f server driver passengers *.o
