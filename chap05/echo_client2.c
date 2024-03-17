//
// Created by user on 2024-03-17.
//
/* 서버에서 전송한 xx bytes 를 수신할 때까지 반복해서 read() 함수 호출하도록 기능 구현 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"
#define BUF_SIZE 1024
void error_handling(char *message) ;

int main(int argc, char *argv[]) {
    int sock;
    char message[BUF_SIZE];
    int str_len, recv_len, recv_cnt;
    struct sockaddr_in serv_adr;

    if(argc != 3) {
        printf("Usage : %s <IP> <port> \n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        error_handling("socket() error! \n");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_adr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("connect() error! \n");
    } else {
        puts("Connected .......... ");
    }

    // 서버로 전송할 메시지 입력 받음.
    while (1) {
        fputs("Input message(Q to quit): ", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message, "q\n") || !strcmp(message, "Q\n")) {
            break;
        }

        // 입력받은 message 를 서버로 전송하기 위한 파일디스크립터 sock 에 기록!
        str_len = write(sock, message, strlen(message));

        // 전송한 메시지를 그래도 수신할 것이니. 동일한 크기의 데이터 수신!
        recv_len = 0;
        while (recv_len < str_len) {
            recv_cnt = read(sock, &message[recv_len], BUF_SIZE - 1);
            if (recv_cnt == -1) {
                error_handling("read() error! \n");
            }
            recv_len += recv_cnt;
        }

        message[recv_len] = 0 ;
        printf("Message from server : %s \n", message);
    }

    close(sock);

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}