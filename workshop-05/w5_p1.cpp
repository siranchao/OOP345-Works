#include <iostream>
#include <string>
#include <iomanip>

#include "CentralUnit.h"
#include "Job.h"
#include "Processor.h"

void printLine() {
    std::cout << std::setfill('-') << std::setw(45) << "-" << std::setfill(' ') << "\n";
}

void printHeader(std::string label) {
    size_t padLeft = (45 - label.length()) / 2;

    printLine();
    std::cout << std::setw(padLeft) << " " << label << std::endl;
    printLine();
}

int main(int argc, char** argv) {
    std::cout << "Command Line:\n";
    printLine();
    for (int i = 0; i < argc; i++)
        std::cout << std::setw(3) << i + 1 << ": " << argv[i] << '\n';
    printLine();
    std::cout << "\n";

    printHeader("CPU SETUP");

    try {
        sdds::CentralUnit<sdds::Processor> fake_host("fake", "invalid file");
    } catch (std::invalid_argument& e) {
        std::cout << "**EXPECTED EXCEPTION: " << e.what() << std::endl;
    }
    
    sdds::CentralUnit<sdds::Processor>* cpu = new sdds::CentralUnit<sdds::Processor>("Processing", argv[1]);

    try {
        sdds::CentralUnit<sdds::Processor> test_host = *cpu;
    } catch (...) {
        std::cout << "**EXPECTED EXCEPTION: Central Unit cannot be copy-assigned." << std::endl;
    }

    if (std::is_copy_assignable<sdds::CentralUnit<sdds::Processor>>::value) {
        std::cout << "**EXCEPTION: Central Unit should not support copy operations.\n"
                  << std::endl;
    }

    if (!std::is_move_constructible<sdds::CentralUnit<sdds::Processor>>::value || !std::is_move_assignable<sdds::CentralUnit<sdds::Processor>>::value) {
        std::cout << "**EXCEPTION: Central Unit should support move operations.\n"
                  << std::endl;
    }

    std::cout << "CPU has " << cpu->get_available_units() << " available units and has " << (cpu->has_jobs() ? "some pending" : "no") << " jobs on setup." << std::endl;

    printLine();

    printHeader("ADD JOBS");

    *cpu += "Add two numbers";
    *cpu += "Join two strings";
    *cpu += "Subtract n numbers";
    *cpu += "Add a file";

    std::cout << "Successfully added 4 jobs to the queue." << std::endl;
    try {
        *cpu += "Divide 2 integers";
    } catch (...) {
        std::cout << "**EXPECTED EXCEPTION: Job queue is full." << std::endl;
    }

    printLine();

    printHeader("RUN CPU");

    std::cout << "CPU run #1" << std::endl;
    cpu->run();

    std::cout << "CPU now has " << cpu->get_available_units() << " available units and has " << (cpu->has_jobs() ? "some pending" : "no") << " jobs after run #1." << std::endl;
    std::cout << "Queuing `Divide 2 integers` job" << std::endl;
    *cpu += "Divide 2 integers";
    std::cout << std::endl;

    for (auto i = 0; cpu->has_jobs(); i++) {
        std::cout << "CPU run # " << i + 2 << std::endl;
        cpu->run();
        std::cout << "CPU now has " << cpu->get_available_units() << " available units and has " << (cpu->has_jobs() ? "some pending" : "no") << " jobs after run #" << i + 2 << "." << std::endl;
        std::cout << std::endl;
    }

    printLine();

    delete cpu;
}