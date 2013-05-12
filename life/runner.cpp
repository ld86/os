#include "runner.h"

#include "life_server.h"
#include "life.h"

#include <cstdlib>
#include <cstdio>

#include <string>

namespace life_server {

bool runner_t::is_right_arguments(int argc, char** argv) {
    if (argc != 2) {
        return false;
    }

    if (atoi(argv[1]) == 0) {
        return false;
    }

    return true;
}

int runner_t::show_usage(char* filename) {
    std::fprintf(stderr, "Usage: %s <port>\n", filename);
    return 1;
}

int runner_t::run(int argc, char** argv) {
    if (!is_right_arguments(argc, argv)) {
        return show_usage(argv[0]);
    }

    int port = atoi(argv[1]);
    life_server_t server = life_server_t::create_new(port);
    server.run();
}

} // namespace life
