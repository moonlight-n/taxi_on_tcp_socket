#ifndef FUNC_FOR_SERVER_H

#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>
#define BUFFER 1024
#define MAX_TRIP 2
#define TRAVEL_TIME 10
#define max(x, y) ((x) > (y) ? (x) : (y))

enum {
  START_OF_DRIVER_SHIFT = 1,
  PASSENGER_LOOKS_FOR_DRIVER,
  TRIP_IS_COMPLETED,
  END_OF_DRIVER_SHIFT
};

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
  int whos_driving_me;  // сохранение водителя, который вез
  struct passengers_s *next;
} passengers;

// server
void print_list(drivers *head);  // вывод на экран водителей
void print_list_pass(passengers *head);  // вывод на экран пассажиров
passengers *create_p();  // создание первого элемента списка пассажиров
drivers *create_d();     // весь список водителей
int driver_in_the_database(
    drivers *head,
    char *holding_message);  // проверка водителей по по наличию в списке
drivers *research_driver(drivers *head,
                         char *street);  // поиск водителя по улице и статусу
void trip_with_driver(drivers *d);  // поездка для водителя
void add_new_passengers(passengers *head_p, char *street_p_,
                        int socket_p_);  // добавление в список пассажиров
passengers *delete_passengers(passengers *head_p,
                              int driver_me);  // удаление пассажиров из списка

#endif /*FUNC_FOR_SERVER_H*/