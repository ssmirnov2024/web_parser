#pragma once
#include <string>
#include <iostream>
#include <algorithm>

namespace cl_parser
{

    // Prints a usage to a console
    void print_usage(void)
    {
        std::cout << "Usage:\n";
        std::cout << "web_parser [-l<url>] [-f<folder_to_save_in>]\n";
    }

    // Reads a command line parameter's value
    bool get_option(std::string cline, std::string opt, std::string& value)
    {
        auto ind = cline.find(opt);
        if(ind != 0) {
            return false;
        }
        value = cline.substr(ind + 2, cline.length());
        return true;
    }
    // Parses a command line arguments
    void parse_command_line(int argc, char * argv[], std::string& website, std::string& output_folder)
    {
        if(argc > 3) {
            print_usage();
            std::cin.get();
            exit(0);
        } else {
            int count = 1;
            while (count < argc) {
                if(!get_option(std::string(argv[count]), "-l", website) &&
                !get_option(std::string(argv[count]), "-f", output_folder)) {
                    std::cout << "Invalid command line arguments!\n";
                    print_usage();
                }
                count++;
            }  
        }
    }

}