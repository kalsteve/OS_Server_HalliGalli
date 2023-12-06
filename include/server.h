#ifndef _SERVER_H
#define _SERVER_H

/**
 * @brief 서버의 소켓 통신을 위한 헤더파일
 * 
 * @file server.h
 * @date 2018-05-21
 * 
 * @details 
 * 
*/

/**
 * types.h - 기본 자료형
 * socket.h - 소켓 프로그래밍 라이브러리
 * pthread.h - POSIX 쓰레드 라이브러리
 * netinet/in.h - 인터넷 프로토콜 라이브러리
 * unistd.h - 유닉스 표준 라이브러리
 * stdio.h - 표준 입출력 라이브러리
 * stdlib.h - 표준 라이브러리
 * string.h - 문자열 처리 라이브러리
 * errno.h - 에러 처리 라이브러리
*/

// 통신용 라이브러리를 불러온다.
#include <sys/types.h>  // for size_t
#include <sys/socket.h> // for socket(), connect(), send(), recv()
#include <netinet/in.h> // for sockaddr_in
#include <arpa/inet.h>  // for inet_addr()
#include <unistd.h>     // for close()
#include <pthread.h>    // for pthread_create(), pthread_join()
#include <sys/time.h>   // for gettimeofday()
#include <time.h>       // for time()

// 기본 라이브러리를 불러온다.
#include <stdio.h>      // for printf()
#include <stdlib.h>     // for exit()
#include <string.h>     // for memset()
#include <errno.h>      // for errno

#define MAX_BUFFER_SIZE 1024
#define MAX_CLIENT_NUM 6


int initSocket(const int port, const int client_num);
int createSocket(int socket);
int bindSocket(int socket_fd,struct sockaddr_in *serv_addr  , int addr_len, int port);
int listenSocket(int socket, int backlog);
int acceptSocket(int socket, struct sockaddr_in *cli_addr, int addr_len);
int recvSocket(int socket, char *buffer, int buffer_len);
int sendSocket(int socket, char *buffer, int buffer_len);
int closeSocket(int socket);

#endif
