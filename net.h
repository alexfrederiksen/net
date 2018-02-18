#include <iostream>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/select.h>
#include <string.h>
#include <unistd.h>

#include <cstdio>
#include <cstdlib>
#include <cstdarg>

#define MAX_CLIENTS 10

#define NET_UDP 1
#define NET_TCP 2

struct remote_t {

};

typedef void (* on_recv_callback_t)(remote_t * remote, char * buffer, int buffer_len);
typedef void (* on_close_callback_t)(remote_t * remote);

struct udp_remote_t : public remote_t {
    sockaddr_in addr;
};

struct tcp_remote_t : public remote_t {
    int socket;
};

struct server_t {
    int socket;
    timeval time_out;
    on_recv_callback_t on_recv_callback;
    on_close_callback_t on_close_callback;
};

struct udp_server_t : public server_t {
    udp_remote_t clients[MAX_CLIENTS];
    int client_count;
};

struct tcp_server_t : public server_t {
    tcp_remote_t clients[MAX_CLIENTS];
    int client_count;
};

struct client_t {
    int socket;
    timeval time_out;
    on_recv_callback_t on_recv_callback;
    on_close_callback_t on_close_callback;
};

struct udp_client_t : public client_t {

};

struct tcp_client_t : public client_t {

};

/* prototypes */
void error(std::string msg);
void errorf(std::string format, ...);
int start_server(udp_server_t & server, int port);
int start_server(tcp_server_t & server, int port);
int start_client(udp_client_t & client, int remote_port, std::string remote_ip);
int start_client(tcp_client_t & client, int remote_port, std::string remote_ip);
int update_server(udp_server_t & server, char * buffer, int buffer_len);
int update_server(tcp_server_t & server, char * buffer, int buffer_len);
void add_client(udp_server_t & server, udp_remote_t & remote);
void add_client(tcp_server_t & server, tcp_remote_t & remote);
int send_data(int socket, udp_remote_t & remote, char * buffer, int buffer_len);
int send_data(int socket, tcp_remote_t & remote, char * buffer, int buffer_len);
int recv_data(int socket, char * buffer, int buffer_len, udp_remote_t & remote);
int recv_data(int socket, char * buffer, int buffer_len, tcp_remote_t & remote);
