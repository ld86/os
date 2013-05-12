#include "life.h"

#include <unistd.h>
#include <cstdlib>
#include <cstdio>

#include <thread>
#include <vector>

namespace life_server {

life_t::life_t() {
    srand(time(nullptr));
    make_start_field();
    std::thread(std::ref(*this)).detach();
}

void life_t::make_start_field() {
    for_client.reset(new std::vector<char>(table_size * table_size));
    for (size_t i = 0; i < table_size * table_size; ++i) {
        (*for_client)[i] = (rand() % 2 == 0) ? dead : live;
    }
}

int toindex(int row, int col, int N) {
    if (row < 0) {
        row = row + N;
    } else if (row >= N) {
        row = row - N;
    }
    if (col < 0) {
        col = col + N;
    } else if (col >= N) {
        col = col - N;
    }
    return row * N + col;
}

void life_t::create_new_field() {
    processing.reset(new std::vector<char>(table_size * table_size));
    for (int i = 0; i < table_size; ++i) {
        for (int j = 0; j < table_size; ++j) {
            int alive_count = 0;
            for (int di = -1; di <= 1; ++di) {
                for (int dj = -1; dj <= 1; ++dj) {
                    if ((di != 0 || dj != 0) 
                        && (*for_client)[toindex(i + di, j + dj, table_size)] == live) 
                    {
                        ++alive_count;
                    }
                }
            }
            int current = i * table_size + j;
            if (alive_count == 3 || (alive_count == 2 && (*for_client)[current] == live)) {
                (*processing)[current] = live;
            } else {
                (*processing)[current] = dead;
            }
        }
    }     
}

void life_t::operator()() {
    for(;;) {
        create_new_field();
        for_client = processing;
        sleep(1);
    }
}

void life_t::operator()(int client_socket) {
    std::shared_ptr<std::vector<char>> local_ptr = for_client;
    write(client_socket, &((*for_client)[0]), table_size * table_size);
    close(client_socket);
};

}
