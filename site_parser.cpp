#include <iostream>
#include <fstream>
#include <unordered_map>
#include "libxml/HTMLparser.h"
#include "libxml/xpath.h"
#include "site_parser.h"
#include "page_loader.h"

using namespace std;

void SiteParserLibxml::parse(string url)
{
    auto save_folder = get_save_folder();
    if(!filesystem::exists(save_folder)) {
        filesystem::create_directory(save_folder);
    }
    unordered_map<string, bool> pages{};
    parse_recursive(url, "", pages);  
}

void SiteParserLibxml::save_page(std::string path, std::string_view web_page)
{
    if(!filesystem::exists(path)) {
        ofstream out_page(path);
        out_page << web_page;
    }
}

void SiteParserLibxml::parse_recursive(string url, string path, unordered_map<string, bool>& pages)
{
    string sub_path = path + url;
    pages[sub_path] = true;
    if(url == mPageLoader.get_main_url()) {
        url = "index.html";
    }
    auto index = url.rfind("/");
    string sub_dir{};
    if(index != string::npos) {
        sub_dir = path + url.substr(0, index + 1);
        url = url.substr(index + 1, url.length());
    }
    if(sub_dir == "") {
        sub_dir = path;
    }
    auto full_url = mPageLoader.get_main_url() + "/" + sub_dir + url;
    auto web_page = mPageLoader.get_request(full_url);

    string output_folder = mSaveFolder + "/" + sub_dir;
    if(!filesystem::exists(output_folder)){
        filesystem::create_directories(output_folder);
    }
    save_page(output_folder + url, web_page);

    htmlDocPtr doc = htmlReadMemory(web_page.c_str(), web_page.length(), nullptr, nullptr, HTML_PARSE_NOERROR);
    xmlXPathContextPtr context = xmlXPathNewContext(doc);

    xmlXPathObjectPtr pagination_html_elements = xmlXPathEvalExpression((xmlChar *)"//a", context);
    for (int Ix = 0; Ix < pagination_html_elements->nodesetval->nodeNr; ++Ix) {
        xmlNodePtr pagination_html_element = pagination_html_elements->nodesetval->nodeTab[Ix];

        xmlXPathSetContextNode(pagination_html_element, context);
        string page_link = string(reinterpret_cast<char *>(xmlGetProp(pagination_html_element, (xmlChar*) "href")));
        if(page_link.find("../") == 0){
            continue;
        }
        if(pages.find(sub_dir + page_link) != pages.end()) {
            if(pages[sub_path] == false) {
                parse_recursive(page_link, sub_dir, pages);
            } 
        } else {
            parse_recursive(page_link, sub_dir, pages);
        }
    }
    
    get_html_elements(context, "//link", "href");
    get_html_elements(context, "//img", "src");
    get_html_elements(context, "//script", "src");
}

void SiteParserLibxml::get_html_elements(xmlXPathContextPtr context, string elementName, string subElementName)
{
    xmlXPathObjectPtr html_elements = xmlXPathEvalExpression((xmlChar *)elementName.c_str(), context);
    for (int i = 0; i < html_elements->nodesetval->nodeNr; ++i) {
        xmlNodePtr html_element = html_elements->nodesetval->nodeTab[i];
        
        xmlXPathSetContextNode(html_element, context);
        auto props = xmlGetProp(html_element, (xmlChar*)subElementName.c_str());
        if(props) {
            string link = string(reinterpret_cast<char*>(props));
            int prefix_index = link.find("http");
            if(prefix_index != 0 || prefix_index == string::npos) {
                auto pos = link.rfind("../");
                if(pos != string::npos){
                    link = link.substr(pos + 3, link.length());
                }
                mPageLoader.get_save_file(mSaveFolder, link);
            }
        } 
    }
}

