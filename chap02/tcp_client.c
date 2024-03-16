//
// Created by user on 2024-03-16.
//
/*
 * 프로토콜 (IPv4 기준)
 * TCP: 연결지향형 (SOCK_STREAM, 전송 간 데이터 유실x, 전송 순서 대로 수신됨 -> 전송 횟수와 수신 횟수 동일)
 * UDP: 비연결지향형 (SOCK_DGRAM, 전송 간 데이터 유실 가능, 전송 순서와 무관하게 수신, 한 번에 전송 가능한 데이터 크기 제한됨)
 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
void error_handling(char* message);

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len = 0;
    int idx = 0, read_len = 0;

    // 입력된 인자가 바이너리 포함 3개가 아니면 usage 출력 후 종료한다.
    if(argc != 3) {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        error_handling("socket() error!");
    }

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error!");
    }

    while (read_len = read(sock, &message[idx++], 1)) {
        if(read_len == -1) {
            error_handling("read() error!");
        }
        str_len += read_len;
    }

    printf("Message from server: %s \n", message);
    printf("Function read call count: %d \n", str_len);
    close(sock);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}