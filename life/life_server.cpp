#include "life_server.h"

#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

#include <memory>
#include <thread>

namespace life_server {

life_server_t::life_server_t(int socket, std::shared_ptr<life_t> life) :
    socket_(socket), life_(life)
{
}

int life_server_t::bind_local_port(int port) {
    int listenfd;
    struct sockaddr_in servaddr;
    listenfd = ::socket(AF_INET, SOCK_STREAM, 0);

    int on = 1;
    setsockopt(listenfd, SOL_SOCKET,
            SO_REUSEADDR,
            (const char *) &on, sizeof(on));

    bzero(&servaddr,sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(port);
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 1024);
    return listenfd;

}

int life_server_t::accept_client() {
    return accept(socket_, nullptr, 0);
}

life_server_t life_server_t::create_new(int port) {
    int socket = bind_local_port(port);
    return life_server_t(socket, std::shared_ptr<life_t>(new life_t()));
}

void life_server_t::run() {
    for(;;) {
        int client_socket = accept_client();
        std::thread(std::ref(*life_), client_socket).detach();
    }
}

life_server_t::~life_server_t() {
    close(socket_);
}

}
