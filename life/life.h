#pragma once

#include <memory>
#include <vector>

namespace life_server {

class life_t {
        const size_t table_size = 20;
        const char dead = '.';
        const char live = '*';

        std::shared_ptr<std::vector<char>> for_client;
        std::shared_ptr<std::vector<char>> processing;   

        void make_start_field();
        void create_new_field();
    public:
        life_t();
        void operator()();
        void operator()(int client_socket);
};

}
