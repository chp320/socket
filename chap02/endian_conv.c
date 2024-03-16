//
// Created by user on 2024-03-16.
//
/*
 * CPU 가 데이터를 저장하는 방식은 크게 두 가지로 나뉜다.
 * - 빅 엔디안 방식: 상위 바이트 값을 작은 번지수(가장 앞)에 저장하는 방식
 * - 리틀 엔디안 방식: 상위 바이트 값을 큰 번지수(가장 뒤)에 저장하는 방식 (=> 보통 인텔/AMD 계열 CPU 는 '리틀 엔디안' 방식으로 데이터 저장함)
 * * 동일 데이터를 '빅 엔디안' 방식에서 '리틀 엔디안' 방식의 시스템으로 전송하는 경우 다른 의미로 해석될 수 있기 때문에
 *   네트워크 상 송수신은 '빅 엔디안' 방식으로 "통일"함
 * * ex. htons : h(host 바이트 순서), n(network 바이트 순서), to(to), s(short형) // 참고로 l(long형)
 *               -> short 형 데이터를 host 바이트 순서에서 network 바이트 순서로 변환!
 */

#include <netinet/in.h>
#include "stdio.h"

int main(int argc, char* argv[]) {
    unsigned short host_port = 0x1234;      // 2바이트 데이터 저장
    unsigned short net_port ;
    unsigned long host_addr = 0x12345678;   // 4바이트 데이터 저장
    unsigned long net_addr ;

    net_port = htons(host_port);    // short형 데이터 host 바이트 순서 -> network 바이트 순서 로 변환
    net_addr = htonl(host_addr);    // long형 데이터 host 바이트 순서 -> network 바이트 순서 로 변환

    printf("Host ordered port: %#x \n", host_port);
    printf("Network ordered port: %#x \n", net_port);
    printf("Host ordered address: %#lx \n", host_addr);
    printf("Network ordered address: %#lx \n", net_addr);

    return 0;
}