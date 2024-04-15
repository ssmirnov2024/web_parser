#pragma once
#include <string>
#include <string_view>
#include <unordered_map>

class PageLoader;

class SiteParser {
    public:
        SiteParser(PageLoader& pageLoader) : mPageLoader(pageLoader) {};
        virtual void parse(std::string url) = 0;
    protected:
        PageLoader& mPageLoader;
};

class SiteParserLibxml: public SiteParser {
public:
    SiteParserLibxml(PageLoader& pageLoader, std::string saveFolder) : SiteParser(pageLoader) {
        mSaveFolder = saveFolder;
    }

    ~SiteParserLibxml() {};

    virtual void parse(std::string url);

    std::string get_save_folder() const {
        return mSaveFolder;
    }

private:
    void parse_recursive(std::string url, std::string path, std::unordered_map<std::string, bool>& pages);
    void get_html_elements(xmlXPathContextPtr context, std::string elementName, std::string subElementName);
    void save_page(std::string path, std::string_view web_page);
private:
    std::string mSaveFolder;
};