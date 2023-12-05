/**
 * socket.c - 소켓 프로그래밍
 * 
*/



#include "server.h"

int initSocket(const int port, const int client_num)
{
    int server_socket_fd;           // 서버 소켓 파일 디스크립터
    struct sockaddr_in serv_addr;
    
    server_socket_fd = createSocket(server_socket_fd);
    memset(&serv_addr, 0, sizeof(serv_addr)); //소켓 구조체 초기화
    server_socket_fd = bindSocket(server_socket_fd, &serv_addr, sizeof(serv_addr), port);

    return server_socket_fd;
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
        fprintf(stderr, "Failed to initialize socket\n");
        exit(EXIT_FAILURE);
    }
    return socket_fd;
}

// 소켓 연결 대기 함수
int bindSocket(int socket_fd, struct sockaddr_in* serv_addr, int addr_len, int port)
{
    // 소켓 설정
    serv_addr->sin_family = AF_INET; // IPv4
    serv_addr->sin_addr.s_addr = htonl(INADDR_ANY); // 32bit IPv4 주소
    serv_addr->sin_port = htons(port); // 16bit TCP/UDP 포트번호

    // 소켓에 주소 할당
    socket_fd = bind(socket_fd, (struct sockaddr *)serv_addr, addr_len);

    // 소켓에 주소 할당에 실패한 경우
    if (socket_fd < 0)
    {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    return socket_fd;
}

// 소켓 연결 수락 함수
int listenSocket(int socket_fd, int client_num)
{
    // 연결 요청 대기 큐 생성
    socket_fd = listen(socket_fd, client_num);

    // 연결 요청 대기 큐 생성에 실패한 경우
    if (socket_fd < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    return socket_fd;
}

// 클라이언트 연결 함수
int acceptSocket(int socket_fd, struct sockaddr_in *client_addr, int addr_len)
{
    int client_socket_fd; // 클라이언트 소켓 파일 디스크립터

    // 클라이언트 연결 수락
    client_socket_fd = accept(socket_fd, (struct sockaddr *)client_addr, &addr_len);
    // END: ed8c6549bwf9

    // 클라이언트 연결 수락에 실패한 경우
    if (client_socket_fd < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    return client_socket_fd;
}

int recvSocket(int socket, char *buffer, int buffer_len) {
    int recv_len = read(socket, buffer, buffer_len);;
    
    if(recv_len < 0) {
        perror("recv");
        exit(EXIT_FAILURE);
    }
    return recv_len;
}

int sendSocket(int socket, char *buffer, int buffer_len) {
    int send_len = write(socket, buffer, buffer_len);
    if(send_len < 0) {
        perror("send");
        exit(EXIT_FAILURE);
    }
    return send_len;
}

int closeSocket(int socket) {
    int close_status = close(socket);
    if(close_status < 0) {
        perror("close");
        exit(EXIT_FAILURE);
    }
    return close_status;
}