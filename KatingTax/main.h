#ifndef MAIN_H
#define MAIN_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct drivers_s {
  int number;
  char driver_name[15];
  char number_car[10];
  char street[4];
  int status;
  struct drivers_s *next;
} drivers;
drivers *create_d();
int socket_com(int client, char *message, struct sockaddr_in serv_addr,
               socklen_t address_length);
void socket_communication1();
void print_list(drivers *p_begin);
int socket_create(struct sockaddr_in serv_addr);
int socket_server_create(struct sockaddr_in serv_addr);
int close_socket(int num_socket);
#endif /*MAIN_H*/
