#include "drivers.h"

#include "main.h"

#define BUFFER 1024

int main(int argc, char *argv[]) {
  struct sockaddr_in serv_addr;
  if (argc != 3) {
    printf("в: Повторите вход в приложение используя имя и номер машины");
    exit(1);
  } else {
    int k = socket_create(serv_addr);

    char message[BUFFER] = "в: Всё четко";
    socklen_t address_length = sizeof(serv_addr);

    socket_com(k, message, serv_addr, address_length);
    close_socket(k);
  }
  return 0;
}

int socket_create(struct sockaddr_in serv_addr) {
  int client = 0;
  socklen_t address_length = sizeof(serv_addr);

  if ((client = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
    perror("в: Ошибка создания сокета");
    exit(1);
  }
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(7001);

  if ((inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)) == -1) {
    perror("в: Проблема с inet_pton");
    exit(1);
  }
  return client;
}

int close_socket(int num_socket) {
  if (close((num_socket) == -1)) {
    perror("в: Ошибка close client");
    exit(1);
  }
  return 0;
}

int socket_com(int client, char *message, struct sockaddr_in serv_addr,
               socklen_t address_length) {
  // Отправляем
  char buffer[BUFFER] = {0};
  if (sendto(client, message, strlen(message), 0, (struct sockaddr *)&serv_addr,
             address_length) == -1) {
    perror("в: Ошибка sendto client");
    exit(1);
  }
  printf("в: Message \"%s\" sent\n", message);

  memset(buffer, 0, BUFFER);
  recvfrom(client, buffer, BUFFER, 0, (struct sockaddr *)&serv_addr,
           &address_length);
  printf("в: Message from server: %s\n", buffer);
  return 0;
}