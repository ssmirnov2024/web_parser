#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

#include "cl_parser.h"
#include "page_loader.h"
#include "site_parser.h"

using namespace std;

void progress()
{
    string progress_str{"="};
    int count = 0;
    while(true) {
        cout << progress_str << endl;;
        this_thread::sleep_for(4000ms);
        progress_str += "=";
    }
}

int main(int argc, char *argv[])
{   
    std::string main_url("https://books.toscrape.com");
    std::string save_folder("website");
    cl_parser::parse_command_line(argc, argv, main_url, save_folder);

    PageLoader pageLoader(main_url);
    SiteParserLibxml siteParser(pageLoader, save_folder);

    thread progressThread(progress);
    progressThread.detach();

    siteParser.parse(main_url);
    return 0;
}