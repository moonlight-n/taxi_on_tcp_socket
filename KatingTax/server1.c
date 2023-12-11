#include "func_for_server.h"
passengers *delete_passengers(passengers *head_p, int driver_me) {
  printf("Зашли в функцию удаления head_p = %s, driver_me = %d\n", head_p,
         driver_me);

  passengers *prev = head_p, *current = head_p->next;
  if (head_p == NULL) {
    return NULL;
  }
  printf("prev = %s, prev->whos_driving_me = %d\n", prev,
         prev->whos_driving_me);
  printf("current = %s, current->next = %s\n", current, current->next);
  while (current && current->next) {
    printf("Зашли в while, prev = %s, prev->whos_driving_me = %d", prev,
           prev->whos_driving_me);
    prev = current;
    current = current->next;
    printf("Мы ищем %d, пытаемся удалить %d\n", driver_me, current);
    if (current && current->whos_driving_me == driver_me) {
      prev->next = current->next;
      printf("Удаляем %d\n", current);
      free(current);
    }
  }
  return head_p;
}
void add_new_passengers(passengers *head_p, char *street_p_, int socket_p_) {
  passengers *p = (passengers *)malloc(sizeof(passengers));
  snprintf(p->street_p, sizeof(p->street_p), "%s", street_p_);
  p->socket_p = socket_p_;
  p->whos_driving_me = 0;
  p->next = NULL;
  passengers *tmp = head_p;
  while (tmp->next != NULL) {
    tmp = tmp->next;
  }
  tmp->next = p;
}

void poezdka(drivers *d) {
  printf("\n\nERROR\n\n");
  if (strcmp(d->street_d, "B") == 0) {
    snprintf(d->street_d, sizeof(d->street_d), "A");
  } else if (strcmp(d->street_d, "A") == 0) {
    snprintf(d->street_d, sizeof(d->street_d), "B");
  }

  d->status = 1;
  d->trips = d->trips + 1;
}

drivers *research_driver(drivers *head, char *street) {
  drivers *d = head;

  while (d != NULL) {
    if (d->status == 1 &&
        (strcmp(street, d->street_d) && d->trips < MAX_TRIP) == 0) {
      return d;
      break;
    }
    d = d->next;
  }
  return NULL;
}

int driver_in_the_database(drivers *head, char *holding_message) {
  char str[1024] = {};
  char sep[10] = ".";
  char *h_name_driver, *h_number_car, *i;
  strcpy(str, holding_message);
  drivers *p = head;

  i = strtok(str, sep);
  h_name_driver = strtok(NULL, sep);
  h_number_car = strtok(NULL, sep);

  while (p != NULL) {
    if ((strcmp(h_name_driver, p->driver_name) == 0) && (p->socket_d == 0) &&
        (strcmp(h_number_car, p->number_car)) == 0) {
      return p->number;
      break;
    }
    p = p->next;
  }
  return 0;
}

drivers *create_d() {
  drivers *head = NULL;
  drivers *p = NULL;
  // заполним односвязный список
  head = (drivers *)malloc(sizeof(drivers));
  p = head;
  p->next = NULL;
  // создаем список водителей в базе сервера
  p->number = 1;
  snprintf(p->driver_name, sizeof(p->driver_name), "Геннадий");
  snprintf(p->number_car, sizeof(p->number_car), "х777хх");
  snprintf(p->street_d, sizeof(p->street_d), "A");
  p->status = 0;
  p->socket_d = 0;
  p->trips = 0;
  p->next = (drivers *)malloc(sizeof(drivers));
  p = p->next;
  p->number = 2;
  snprintf(p->driver_name, sizeof(p->driver_name), "Арсен");
  snprintf(p->number_car, sizeof(p->number_car), "о456го");
  snprintf(p->street_d, sizeof(p->street_d), "A");
  p->status = 0;
  p->socket_d = 0;
  p->trips = 0;
  p->next = (drivers *)malloc(sizeof(drivers));
  p = p->next;
  p->number = 3;
  snprintf(p->driver_name, sizeof(p->driver_name), "Низамидин");
  snprintf(p->number_car, sizeof(p->number_car), "к955ау");
  snprintf(p->street_d, sizeof(p->street_d), "A");
  p->status = 0;
  p->socket_d = 0;
  p->trips = 0;
  p->next = (drivers *)malloc(sizeof(drivers));
  p = p->next;
  p->number = 4;
  snprintf(p->driver_name, sizeof(p->driver_name), "Галина");
  snprintf(p->number_car, sizeof(p->number_car), "у511ум");
  snprintf(p->street_d, sizeof(p->street_d), "A");
  p->status = 0;
  p->socket_d = 0;
  p->trips = 0;
  return head;
}

passengers *create_p() {
  passengers *head = NULL;
  passengers *p = NULL;
  // заполним односвязный список
  head = (passengers *)malloc(sizeof(passengers));
  p = head;
  p->next = NULL;
  snprintf(p->street_p, sizeof(p->street_p), " ");
  p->socket_p = 0;
  p->whos_driving_me = 0;
  return head;
}

void print_list_pass(passengers *head) {
  passengers *p = head;
  int i = 1;
  printf("\n\t\t пассажиры \t\t\n");
  while (p != NULL) {
    printf("%d. ", i);
    printf("%s \t", p->street_p);
    printf("%d \t", p->socket_p);
    printf("%d \n", p->whos_driving_me);
    // шагнуть вперед !!!
    p = p->next;
    i = i + 1;
  }
}

// распечатаем односвязный список водителей
void print_list(drivers *head) {
  drivers *p = head;
  while (p != NULL) {
    // распечатать структуру данных
    printf("%d.", p->number);
    printf("%s  \t", p->driver_name);
    printf("%s \t", p->number_car);
    printf("%s \t", p->street_d);
    printf("%d \t", p->status);
    printf("%d \t", p->socket_d);
    printf("%d \n", p->trips);
    // шагнуть вперед !!!
    p = p->next;
  }
}
int main() {
  drivers *head_d = create_d();
  passengers *head_p = create_p();
  int yes = 1;  // для использования порта заново
  int server = 0, client = 0;
  struct sockaddr_in server_addr, client_addr;
  socklen_t address_length;
  char receive_message[BUFFER] = {0};
  int who = 0;
  char *uk_who;
  // для select()
  fd_set read_fds;
  struct timeval timeout;
  int ret = 0;
  int max_socket = 0;

  if ((server = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("с: Проблема с созданием сокета");
    exit(1);
  }

  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(7001);
  server_addr.sin_addr.s_addr = INADDR_ANY;

  setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &yes,
             sizeof(int));  // для использования порта заново

  if (bind(server, (struct sockaddr *)&server_addr, sizeof(server_addr)) ==
      -1) {
    perror("с: Проблема с bind");
    exit(1);
  }

  if (listen(server, 20) == -1) {
    perror("c: Проблема с listen");
    exit(1);
  }

  while (1) {
    timeout.tv_sec = 2;
    timeout.tv_usec = 0;
    max_socket = 0;
    FD_ZERO(&read_fds);
    // FD_SET(client, &read_fds);
    // if (max_socket < client) max_socket = client;
    FD_SET(server, &read_fds);
    max_socket = max(max_socket, server);
    drivers *d = head_d;
    while (d != NULL) {
      if (d->socket_d != 0) {
        FD_SET(d->socket_d, &read_fds);
        max_socket = max(max_socket, d->socket_d);
      }
      d = d->next;
    }

    if ((ret = select(max_socket + 1, &read_fds, NULL, NULL, &timeout)) == -1) {
      perror("c: select ошибка");
      exit(1);
    } else if (ret == 0) {
      continue;
    }

    if (FD_ISSET(server, &read_fds)) {
      if ((client = accept(server, (struct sockaddr *)&client_addr,
                           &address_length)) == -1) {
        perror("c: Accept ошибка");
        exit(1);
      }

      printf("Подключился клиент новый клиент [%s]!\n",
             inet_ntoa(client_addr.sin_addr));
    } else {
      drivers *d = head_d;
      while (d != NULL) {
        if (d->socket_d != 0 && FD_ISSET(d->socket_d, &read_fds)) {
          client = d->socket_d;
          break;
        }
        d = d->next;
      }
    }

    memset(receive_message, 0, sizeof(receive_message));
    if (recv(client, receive_message, BUFFER, 0) == -1) {
      perror("c: Ошибка recv");
      exit(1);
    }

    printf("receive_message = %s от %d\n", receive_message, client);

    char strk[BUFFER];
    strcpy(strk, receive_message);
    uk_who = strtok(strk, ".");
    who = atoi(uk_who);

    switch (who) {
      case 1:
        int check_numbercar = driver_in_the_database(
            head_d, receive_message);  // проверка водителей

        if (check_numbercar > 0 && check_numbercar <= 4) {
          drivers *d = head_d;
          while (d && d->number != check_numbercar) {
            d = d->next;
          }
          d->socket_d = client;
          d->status = 1;

          if (send(d->socket_d, "Добро пожаловать на смену", BUFFER, 0) == -1) {
            perror("c: Ошибка send");
            exit(1);
          }
        } else if (check_numbercar == 0) {
          if (send(client, "В базе нет такого водителя", BUFFER, 0) == -1) {
            perror("c: Ошибка send");
            exit(1);
          }
          if (close(client) == -1) {
            perror("c: Ошибка close client");
            exit(1);
          }
        }
        continue;

      case 2:
        passengers *p = head_p;
        print_list_pass(head_p);
        char *street_where_p = strtok(NULL, ".");
        add_new_passengers(head_p, street_where_p, client);
        snprintf(p->street_p, sizeof(p->street_p), street_where_p);
        print_list_pass(head_p);
        while (p != NULL && p->socket_p != client) {
          p = p->next;
        }

        if (send(p->socket_p, "Заказ принят, идёт поиск машины", BUFFER, 0) ==
            -1) {
          perror("c: Ошибка send");
          exit(1);
        }
        drivers *d = research_driver(head_d, street_where_p);
        if (d == NULL) {
          if (send(p->socket_p, "Подходящей машины нет, попробуйте позже",
                   BUFFER, 0) == -1) {
            perror("c: Ошибка send");
            exit(1);
          }
          if (close(client) == -1) {
            perror("c: Ошибка close client");
            exit(1);
          }
        } else {
          if (send(d->socket_d, "Для вас есть заказ, ждём подтверждения",
                   BUFFER, 0) == -1) {
            perror("c: Ошибка send");
            exit(1);
          }
          if (recv(d->socket_d, receive_message, BUFFER, 0) == -1) {
            perror("c: Ошибка recv");
            exit(1);
          }
          if (strcmp(receive_message, "Заказ подтверждаю") == 0) {
            printf("%s заказ подтвердил\n", d->driver_name);
            d->status = 0;
            p->whos_driving_me = d->socket_d;
            printf("Поездка началась, статус водителя %s :%d\n", d->driver_name,
                   d->status);

            print_list(head_d);
            char message[BUFFER];
            snprintf(message, sizeof message, "Вас повезет %s, номер машины %s",
                     d->driver_name, d->number_car);

            if (send(p->socket_p, message, BUFFER, 0) == -1) {
              perror("c: Ошибка send");
              exit(1);
            }
          }
        }
        continue;

      case 3:
        d = head_d;
        printf("\n ДО ОКОНЧАНИЯ ПОЕЗДКИ\n");
        print_list(head_d);
        print_list_pass(head_p);
        printf("сокет водителя = %d\n", client);
        while (d != NULL && d->socket_d != client) {
          d = d->next;
        }
        if (d == NULL) printf("poshel nahui\n");
        poezdka(d);
        printf("\n ВО ВРЕМЯ ПОЕЗДКИ\n");
        print_list(head_d);
        print_list_pass(head_p);
        delete_passengers(head_p, d->socket_d);
        printf("\n ПОСЛЕ ОКОНЧАНИЯ ПОЕЗДКИ\n");
        print_list(head_d);
        print_list_pass(head_p);
        continue;
      case 4:
        drivers *y = head_d;
        while (y->socket_d != client) {
          y = y->next;
        }
        y->status = 0;
        printf("Водитель %s закончил смену\n", d->driver_name);
        if (close(client) == -1) {
          perror("c: Ошибка close client");
          exit(1);
        }
        y->socket_d = 0;
        print_list(head_d);
        continue;

      default:
        if (close(client) == -1) {
          perror("c: Ошибка close client");
          exit(1);
        }
        break;
    }
    print_list(head_d);
  }

  if (close(server) == -1) {
    perror("c: Ошибка close server");
    exit(1);
  }
  printf("c: finish\n");
  return 0;
}