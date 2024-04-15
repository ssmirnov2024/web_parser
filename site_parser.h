#pragma once
#include <string>
#include <string_view>
#include <unordered_map>

class PageLoader;

// Interface for a different web site parsers
class SiteParser {
    public:
        SiteParser() {
        };
        virtual ~SiteParser() {};

        virtual void parse(std::string url) = 0;
};

// Parses a web site using libxml library
class SiteParserLibxml: public SiteParser {
public:
    SiteParserLibxml(std::string main_url, std::string saveFolder);

    SiteParserLibxml(SiteParserLibxml &other) = delete;
    void operator=(const SiteParserLibxml&) = delete;

    virtual ~SiteParserLibxml() {};

    // Starts parsing of web site structure and saves html pages and html elements to a local folder
    virtual void parse(std::string url);

    // Returns folder to save web site content in
    std::string get_save_folder() const {
        return mSaveFolder;
    }
    // Returns root url
    std::string get_root() const;

private:
    // Depth-first recursive parsing algorithm
    void parse_recursive(std::string url, std::string path, std::unordered_map<std::string, bool>& pages);
    // Parses a web page for html elements
    void get_html_elements(xmlXPathContextPtr context, std::string elementName, std::string subElementName);
    // Saves a web page to a local folder
    void save_page(std::string path, std::string_view web_page);
private:
    std::string mSaveFolder;
    std::unique_ptr<PageLoader> mPageLoader;
};

// Takes base class SiteParser as parameter and calls its parse() method in parse_web_site()
class WebParser {
public:
    WebParser() = delete;
    WebParser(SiteParser& siteParser): mSiteParser(siteParser) {};

    void parse_web_site(std::string url) {
        mSiteParser.parse(url);
    }

private:
    SiteParser& mSiteParser;
};