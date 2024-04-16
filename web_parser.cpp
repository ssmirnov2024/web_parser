#include <iostream>
#include <fstream>
#include <string>
#include <thread>
#include <atomic>
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"

#include "cl_parser.h"
#include "page_loader.h"
#include "site_parser.h"

using namespace std;

void progress(atomic_bool& stop_thread)
{
    string progress_str{"="};
    int count = 0;
    while(!stop_thread) {
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

    SiteParserLibxml siteParser(main_url, save_folder);

    atomic_bool stop_thread{false};
    thread progressThread(progress, ref(stop_thread));

    WebParser webParser(siteParser);
    webParser.parse_web_site(main_url);
    stop_thread = true;
    progressThread.join();
    return 0;
}