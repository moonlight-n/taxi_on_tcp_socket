#ifndef FUNC_FOR_SERVER_H
#define FUNC_FOR_SERVER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#define BUFFER 1024

typedef struct drivers_s {
  int number;             // порядковый номер водителя
  char driver_name[100];  // имя водителя
  char number_car[100];   // номер машины
  char street_d[4];  // улица "A" или "B" (A/B английские)
  int status;  // 1 - может получить заказ, 0 - не работает/занят
  int socket_d;  // сокета
  int trips;     // количество поездок
  struct drivers_s *next;
} drivers;

typedef struct passenger_s {
  char street_p[4];  // улица с которой уезжает пассажир
  int socket_p;      // сокет пассажира
  struct passengers_s *next;
} passengers;

#endif /*FUNC_FOR_SERVER_H*/