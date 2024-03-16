//
// Created by user on 2024-03-16.
//
/*
 * inet_addr() 과 동일 기능의 inet_aton() 함수.
 * -> 성공 시 1(true), 실패 시 0(false) 반환
 */

#include "stdio.h"
#include "stdlib.h"
#include "arpa/inet.h"

void error_handling(char *message);

int main(int argc, char *argv[]) {
    char *addr = "127.232.124.79";
    struct sockaddr_in addr_inet;

    if(!inet_aton(addr, &addr_inet.sin_addr)) {
        error_handling("Conversion error!");
    } else {
        printf("Network ordered integer addr: %#x \n", addr_inet.sin_addr.s_addr);
    }

    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}