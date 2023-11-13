all :  server driver passengers        

server : server1.o
	gcc server1.o -o server
	
server1.o : server1.c
	gcc -c -g -Wall -Wextra -std=c99 server1.c
	
driver : driver.o
	gcc driver.o -o driver
	
driver.o : driver.c
	gcc -c -g -Wall -Wextra -std=c99 driver.c

passengers : passengers.o
	gcc passengers.o -o passengers
	
passengers.o : passengers.c
	gcc -c -g -Wall -Wextra -std=c99 passengers.c
	
clean:
	rm -f server1 driver passengers *.o