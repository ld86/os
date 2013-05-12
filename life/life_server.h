#pragma once 

#include "life.h"

#include <memory>

namespace life_server {

class life_server_t {
        std::shared_ptr<life_t> life_;
        int socket_;

        life_server_t(int socket, std::shared_ptr<life_t> life);
        static int bind_local_port(int port);
        int accept_client();
    public:
        static life_server_t create_new(int port);
        void run();
        ~life_server_t();
};

}
