#pragma once

namespace life_server {

class runner_t {
        bool is_right_arguments(int argc, char** argv);
        int show_usage(char* filename);

    public:
        int run(int argc, char** argv);
};

} // namespace life

