#include "func_for_driver.h"

int main(int argc, char *argv[]) {
  if (!(argc == 2 &&
        (strcmp(argv[1], "A") == 0 || strcmp(argv[1], "B") == 0))) {
    printf("Войдите с использованием улицы, на которой находитесь(A/B)");
    exit(1);
  }
  int client = 0;
  struct sockaddr_in serv_addr;
  socklen_t address_length = sizeof(serv_addr);
  char buffer[BUFFER] = {0};
  if ((client = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
    perror("п: Ошибка создания сокета");
    exit(1);
  }

  memset(&serv_addr, 0, sizeof(struct sockaddr_in));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(7001);

  if ((inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)) == -1) {
    perror("п: Проблема с inet_pton");
    exit(1);
  }
  if (connect(client, (struct sockaddr *)&serv_addr,
              sizeof(struct sockaddr_in)) == -1) {
    perror("п: Нет коннекта");
    exit(1);
  }

  char message[BUFFER];
  snprintf(message, sizeof message, "2.%s", argv[1]);
  if (sendto(client, message, strlen(message), 0, (struct sockaddr *)&serv_addr,
             address_length) == -1) {
    perror("п: Ошибка sendto client");
    exit(1);
  }
  printf("п: Message \"%s\" sent\n", message);

  while (1) {
    char message[BUFFER] = {0};
    if (strlen(message) != 0) {
      if (sendto(client, message, strlen(message), 0,
                 (struct sockaddr *)&serv_addr, address_length) < 0) {
        perror("п: Ошибка sendto client");
        exit(1);
      }
    }

    memset(buffer, 0, BUFFER);
    if (recvfrom(client, buffer, BUFFER, 0, (struct sockaddr *)&serv_addr,
                 &address_length) < 0) {
      perror("п: Ошибка recvfrom");
      exit(1);
    }

    if (strlen(buffer) != 0) {
      printf("п: Message from server: %s\n", buffer);
    }
    if (strcmp(buffer, "Подходящей машины нет, попробуйте позже") == 0) {
      continue;
    }
    if (strcmp(buffer, "Поездка завершена") == 0) {
      continue;
    }
  }

  if (close(client) == -1) {
    perror("п: Ошибка close client");
    exit(1);
  }
}
