#include "net.h"

void error(std::string msg) {
    std::cerr << msg << std::endl;
}

void errorf(std::string format, ...) {
    va_list vl;
    va_start(vl, format);
    fprintf(stderr, format.c_str(), vl);
    va_end(vl);
}

int start_server(udp_server_t & server, int port) {
    /* create a local socket */
    server.socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server.socket == -1) {
        error("Failed to create socket.");
        return -1;
    }
    /* create local address */
    sockaddr_in local_addr;
    /* reset local address to zeros */
    memset((char *) &local_addr, 0, sizeof(local_addr));
    local_addr.sin_family = AF_INET;
    local_addr.sin_port = htons(port);
    local_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    /* bind socket to local address */
    int status = bind(server.socket, (sockaddr *) &local_addr, sizeof(local_addr));
    if (status == -1) {
        errorf("failed to open socket on port %d.", port);
        return -1;
    }
}

int start_server(tcp_server_t & server, int port) {

}

int start_client(udp_client_t & client, int remote_port, std::string remote_ip) {

}

int start_client(tcp_client_t & client, int remote_port, std::string remote_ip) {

}

int update_server(udp_server_t & server, char * buffer, int buffer_len) {
    /* initialize set for select function */
    fd_set sockets;
    FD_SET(server.socket, &sockets);
    int event;
    do {
        /* wait for an event to happen... or time out */
        event = select(server.socket + 1, &sockets, 0, 0, &server.time_out);
    } while (event == -1 && errno == EINTR);
    if (event > 0 && FD_ISSET(server.socket, &sockets)) {
        udp_remote_t sender;
        /* attempt to receive data a from the socket */
        int len = recv_data(server.socket, buffer, buffer_len, sender);
        if (len > 0) {
            /* call the callback from server */
            server.on_recv_callback((remote_t *) &sender, buffer, len);
        } else if (len == 0) {
            /* socket closed */
            server.on_close_callback((remote_t *) &sender);
        } else {
            /* receive failed */
            return -1;
        }
    } else if (event < 0) {
        /* select failed */
        return -1;
    } else {
        /* select timed out */
        return 0;
    }
}

int update_server(tcp_server_t & server, char * buffer, int buffer_len) {
        
}

void add_client(udp_server_t & server, udp_remote_t & remote) {
    server.clients[server.client_count] = remote;
    server.client_count++;
}

void add_client(tcp_server_t & server, tcp_remote_t & remote) {
    server.clients[server.client_count] = remote;
    server.client_count++;
}

int send_data(int socket, udp_remote_t & remote, char * buffer, int buffer_len) {
    return sendto(socket, buffer, buffer_len, 0, (sockaddr *) &remote.addr, sizeof(remote.addr));
}

int send_data(int socket, tcp_remote_t & remote, char * buffer, int buffer_len) {

}

int recv_data(int socket, char * buffer, int buffer_len, udp_remote_t & remote) {
    socklen_t addr_len = sizeof(remote.addr);
    return recvfrom(socket, buffer, buffer_len, 0, (sockaddr *) &remote.addr, &addr_len);
}

int recv_data(int socket, char * buffer, int buffer_len, tcp_remote_t & remote) {
    
}

/* just for testing. remove on release */
int main() {
    
}
