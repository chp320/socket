//
// Created by user on 2024-03-16.
//
/*
 * 문자열 정보를 32비트 정수형 변환 & 네트워크 바이트 순서로 변환
 * -> inet_addr() 함수 이용!
 * -> 성공 시 빅 엔디안으로 변환된 '32비트 정수값', 실패 시 INADDR_NONE 반환
 */

#include "stdio.h"
#include "arpa/inet.h"

int main(int argc, char* argv[]) {
    char *addr1 = "1.2.3.4";
    char *addr2 = "1.2.3.256";      // 1 바이트당 표현 가능한 최대 크기 정수는 255 이므로 .256 은 잘못된 IP 주소임.

    unsigned long conv_addr = inet_addr(addr1);     // 문자열 IP주소를 32비트 정수형 && network 바이트 순서로 저장
    if(conv_addr == INADDR_NONE) {
        printf("Error occured! \n");
    } else {
        printf("Network ordered integer addr: %#lx (org: %s) \n", conv_addr, addr1);
    }

    conv_addr = inet_addr(addr2);       // 잘못된 문자열 IP 주소가 inet_addr() 로 변환됨
    if(conv_addr == INADDR_NONE) {
        printf("Error occured! \n");
    } else {
        printf("Network ordered integer addr: %#lx (org: %s) \n", conv_addr, addr1);
    }

    return 0;
}