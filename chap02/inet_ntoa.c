//
// Created by user on 2024-03-16.
//
/*
 * 함수 inet_ntoa()
 * -> 네트워크 바이트 순서로 정렬된 '정수형 IP 주소' 정보를 '문자열' 형태로 변환
 * -> 성공 시 변환된 문자열의 "주소 값", 실패 시 -1 반환
 */

#include "stdio.h"
#include "string.h"
#include "arpa/inet.h"

int main() {
    struct sockaddr_in addr1, addr2;
    char *str_ptr;
    char str_arr[20];

    addr1.sin_addr.s_addr = htonl(0x1020304);   // 정수형 IP 주소 할당
    addr2.sin_addr.s_addr = htonl(0x1010101);

    str_ptr = inet_ntoa(addr1.sin_addr);
    strcpy(str_arr, str_ptr);   // 반환된 메모리 상 문자열 값을 문자열 배열로 복사
    printf("Dotted-Decimal notation1: %s \n", str_ptr);

    inet_ntoa(addr2.sin_addr);
    printf("Dotted-Decimal notation2: %s \n", str_ptr);
    printf("Dotted-Decimal notation3: %s \n", str_ptr);

    printf("-> First dotted-decimal data: %s \n", str_arr);

    return 0;
}