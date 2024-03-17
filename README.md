# TCP/IP 소켓 프로그래밍

## 환경
- 윈도우 10 Pro (버전: 22H2, 빌드: 19045.4170)
- WSL (Ubuntu 18.04.6)
- CLion (2023.3.4)

## 개요
- 네트워크 프로그래밍 중 소켓 통신에 대한 이해를 높이고자 '윤성우 TCP/IP 소켓 프로그래밍' 도서를 참고하여 학습하기 위한 자료

### 참고1
- 최초 CMakeLists.txt 내용 백업 (WSL 내 cmake 버전과 상이하여 동일하게 일치시킴)
- 백업 내용 :
cmake_minimum_required(VERSION 3.27)
project(socket C)

set(CMAKE_C_STANDARD 11)

add_executable(socket
chap01/hello_server.c)

### 참고2
- 본 프로젝트 내 '99.answer_sheets', '99.org_codes' 는 출판사 블로그(https://blog.naver.com/oedu/223011209880) 에서 제공하는 코드로 원본은 출판사 블로그에 있음.
