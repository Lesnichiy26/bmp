#include <iostream>
#include "lib/sandpile.h"

struct Arguments {
    std::string tsv_directory_;
    std::string out_directory_;
    uint64_t iterations_;
    uint64_t frequency_;

    Arguments(std::string& tsv_directory, std::string& out_directory, uint64_t iterations, uint64_t frequency) :
            tsv_directory_(tsv_directory),
            out_directory_(out_directory),
            iterations_(iterations),
            frequency_(frequency)
    {}
};


int main(int argc, char *argv[]) {
    std::string settings = ""; // write your default directory for tests here
    std::string directory = ""; // write your default directory here
    uint64_t iter = 100000;
    uint64_t freq = 100000;

    for (int i = 1; i < argc; i++) { // simple parser for arguments
        std::string command = argv[i];
        if ("-i" == command || "--input" == command) {
            settings = argv[i + 1];
            i++;
        } else if ("-o" == command || "--output" == command) {
            directory = argv[i + 1];
            i++;
        } else if ("-m" == command || "--max-iter" == command) {
            iter = std::stoi(argv[i + 1]);
            i++;
        } else if ("-f" == command || "--freq" == command) {
            freq = std::stoi(argv[i + 1]);
            i++;
        }
    }

    Arguments start(settings, directory, iter, freq);

    Sandpile s(start.tsv_directory_, start.iterations_, start.frequency_);
    s.CreateField();
    s.Work(start.out_directory_);
    std::cout << "ready" << '\n';

    return EXIT_SUCCESS;
}