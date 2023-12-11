#include "func_for_server.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("в: Повторите вход в приложение используя имя и номер машины\n");
    exit(1);
  }
  int howmany_trips = 0;
  int client = 0;
  struct sockaddr_in serv_addr;
  socklen_t address_length = sizeof(serv_addr);
  char buffer[BUFFER] = {0};
  if ((client = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("в: Ошибка создания сокета");
    exit(1);
  }

  memset(&serv_addr, 0, sizeof(struct sockaddr_in));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(7001);

  if ((inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)) == -1) {
    perror("в: Проблема с inet_pton");
    exit(1);
  }
  if (connect(client, (struct sockaddr *)&serv_addr,
              sizeof(struct sockaddr_in)) == -1) {
    perror("в: Нет коннекта");
    exit(1);
  }
  char message[BUFFER];
  snprintf(message, sizeof(message), "1.%s.%s", argv[1], argv[2]);
  if (sendto(client, message, strlen(message), 0, (struct sockaddr *)&serv_addr,
             address_length) < 0) {
    perror("в: Ошибка sendto client");
    exit(1);
  }

  while (1) {
    if (howmany_trips == MAX_TRIP) {
      if (sendto(client, "4.Я заканчиваю смену", BUFFER, 0,
                 (struct sockaddr *)&serv_addr, address_length) < 0) {
        perror("в: Ошибка sendto client");
        exit(1);
        break;
      }
    } else {
      memset(buffer, 0, BUFFER);
      if (recvfrom(client, buffer, BUFFER, 0, (struct sockaddr *)&serv_addr,
                   &address_length) < 0) {
        perror("в: Ошибка recvfrom");
        exit(1);
      }
      if (strlen(buffer) != 0) {
        printf("в: Message from server: %s\n", buffer);
      }
      if (strcmp(buffer, "В базе нет такого водителя") == 0) {
        break;
      }
      if (strcmp(buffer, "Для вас есть заказ, ждём подтверждения") == 0) {
        if (sendto(client, "Заказ подтверждаю", BUFFER, 0,
                   (struct sockaddr *)&serv_addr, address_length) < 0) {
          perror("в: Ошибка sendto client");
          exit(1);
        }
        sleep(TRAVEL_TIME);
        if (sendto(client, "3.Поездка завершена", BUFFER, 0,
                   (struct sockaddr *)&serv_addr, address_length) < 0) {
          perror("в: Ошибка sendto client");
          exit(1);
        } else {
          howmany_trips += 1;
        }
      }
    }
  }
  if (close(client) == -1) {
    perror("в: Ошибка close client");
    exit(1);
  }
  return 0;
}
