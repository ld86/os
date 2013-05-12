#include "runner.h"

int main(int argc, char** argv) {
    using life_server::runner_t;

    runner_t runner;
    return runner.run(argc, argv);
}
