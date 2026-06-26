#include "example/main.hpp"
#include "example/meta.hpp"

#include <getopt.h>
#include <stdexcept>

namespace example
{

namespace
{

void print_help(std::ostream & out)
{
    out << name() << " v" << version() << ", Copyright (c) 2026 Falk Werner" << std::endl;
    out << R"(CMake Template example application

Usage:
    app [-h|--help] [-v|--version]

Options:
    -h, --help      Show this help message and exit
    -v, --version   Show version information and exit
)";
}

} // namespace

enum class command
{
    help,
    version
};

struct context
{
    context(int argc, char* argv[])
    : exit_code(0)
    , cmd(command::help)
    {
        option long_opts[] = {
            {"help", no_argument, nullptr, 'h'},
            {"version", no_argument, nullptr, 'v'},
            {nullptr, 0, nullptr, 0}
        };

        opterr = 0;
        optind = 0;

        bool done = false;
        while (!done) {
            int const c = getopt_long(argc, argv, "hv", long_opts, nullptr);
            switch (c) {
                case -1:
                    done = true;
                    break;
                case 'h':
                    cmd = command::help;
                    done = true;
                    break;
                case 'v':
                    cmd = command::version;
                    done = true;
                    break;
                default:
                    throw std::runtime_error("invalid command line option");
                    break;                
            }
        }
    }

    int exit_code;
    command cmd;
};

int main(int argc, char* argv[], std::ostream & out, std::ostream & err) noexcept
{
    try {
        context ctx(argc, argv);

        switch (ctx.cmd) {
            case command::help:
                print_help(out);
                break;
            case command::version:
                out << version() << std::endl;
                break;
        }

        return ctx.exit_code;
    }
    catch (std::exception const & ex) {
        err << "error: " << ex.what() << std::endl;
        return EXIT_FAILURE;;
    }
    catch (...) {
        err << "fatal: unknown error" << std::endl;
        return EXIT_FAILURE;
    }
}

}