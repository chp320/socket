//
// Created by user on 2024-03-16.
//
/* 클라이언트가 전송하는 문자열 데이터를 그대로 재전송하는 '에코(echo)' 역할의 에코 서버 구현 => interative 서버라 지칭 */

#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "unistd.h"
#include "arpa/inet.h"
#include "sys/socket.h"

#define BUF_SIZE 1024

void error_handling(char *message);

int main(int argc, char *argv[]) {
    int serv_sock, clnt_sock;
    char message[BUF_SIZE];
    int str_len, i;

    struct sockaddr_in serv_adr, clnt_adr;
    socklen_t clnt_adr_sz;

    if(argc != 2) {
        printf("Usage : %s <port> \n", argv[0]);
        exit(1);
    }

    // 소켓 생성
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1) {
        error_handling("socket() error! \n");
    }

    memset(&serv_adr, 0, sizeof(serv_adr));
    serv_adr.sin_family = AF_INET;
    serv_adr.sin_addr.s_addr = htonl(INADDR_ANY);       // 서버의 IP 주소 자동 할당
    serv_adr.sin_port = htons(atoi(argv[1]));

    // IP 및 PORT 정보 초기화
    if(bind(serv_sock, (struct sockaddr*)&serv_adr, sizeof(serv_adr)) == -1) {
        error_handling("bind() error! \n");
    }

    // 요청대기 상태 설정
    if(listen(serv_sock, 5) == -1) {
        error_handling("listen() error! \n");
    }

    clnt_adr_sz = sizeof(clnt_adr);

    // 요청대기 처리를 5개까지만!
    for (i = 0; i < 5; ++i) {
        // 요청대기 상태 중인 클라이언트에서 요청 수락. 클라이언트 주소정보 길이 확인
        clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_adr, &clnt_adr_sz);
        if(clnt_sock == -1) {
            error_handling("accept() error! \n");
        } else {
            printf("Connected client %d \n", i + 1);
        }

        while( (str_len = read(clnt_sock, message, BUF_SIZE)) != 0) {
            write(clnt_sock, message, str_len);
        }

        printf("-> closed! \n");
        close(clnt_sock);
    }

    close(serv_sock);

    return 0;

}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);

    exit(1);
}