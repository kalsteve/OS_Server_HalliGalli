/**
 * socket.c - 소켓 프로그래밍
 * 
*/
#include "server.h"

int initSocket(const int port, const int client_num)
{
    int server_socket_fd;
    struct sockaddr_in serv_addr;
    
    
    server_socket_fd = createSocket(server_socket_fd);
    server_socket_fd = bindSocket(server_socket_fd, &serv_addr, sizeof(serv_addr), port);
    server_socket_fd = listenSocket(server_socket_fd, client_num);
    
}

// 소켓 생성 함수
int createSocket(int socket_fd)
{
    // 소켓 생성
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // 소켓 생성에 실패한 경우
    if (socket_fd < 0 )
    {
        perror("socket");
        exit(EXIT_FAILURE);
    }
    return socket_fd;
}

// 소켓 연결 대기 함수
int bindSocket(int socket_fd,struct sockaddr_in *serv_addr  , int addr_len, int port)
{
    memset(&serv_addr, 0, sizeof(serv_addr)); //소켓 구조체 초기화

    serv_addr->sin_family = AF_INET; // IPv4
    serv_addr->sin_addr.s_addr = htonl(INADDR_ANY); // 32bit IPv4 주소
    serv_addr->sin_port = htons(port); // 16bit TCP/UDP 포트번호

    // 소켓에 주소 할당
    socket_fd = bind(socket_fd, (struct sockaddr *) &serv_addr, addr_len);

    // 소켓에 주소 할당에 실패한 경우
    if (socket_fd < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    return socket_fd;
}