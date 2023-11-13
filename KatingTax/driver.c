#include "func_for_driver.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("в: Повторите вход в приложение используя имя и номер машины\n");
    exit(1);
  }
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
  snprintf(message, sizeof message, "1.%s.%s", argv[1], argv[2]);
  if (sendto(client, message, strlen(message), 0, (struct sockaddr *)&serv_addr,
             address_length) == -1) {
    perror("в: Ошибка sendto client");
    exit(1);
  }

  while (1) {
    char message[BUFFER] = {0};

    memset(buffer, 0, BUFFER);
    if (recvfrom(client, buffer, BUFFER, 0, (struct sockaddr *)&serv_addr,
                 &address_length) == -1) {
      perror("в: Ошибка recvfrom");
      exit(1);
    }
    if (strcmp(buffer, "В базе нет такого водителя") == 0) {
      break;
    }
    if (strcmp(buffer, "Для вас есть заказ, ждём подтверждения") == 0) {
      if (sendto(client, "Заказ подтверждаю", strlen(message), 0,
                 (struct sockaddr *)&serv_addr, address_length) == -1) {
        perror("в: Ошибка sendto client");
        exit(1);
      }
      printf("в: Message sent\n");

      /*  if (sendto(client, "Поездка завершена", strlen(message), 0,
                   (struct sockaddr *)&serv_addr, address_length) == -1) {
          perror("в: Ошибка sendto client");
          exit(1);
        }
        printf("в: Message sent\n");

      */
    }
    if (strlen(buffer) != 0) {
      printf("в: Message from server: %s\n", buffer);
    }
  }

  if (close(client) == -1) {
    perror("в: Ошибка close client");
    exit(1);
  }
}
