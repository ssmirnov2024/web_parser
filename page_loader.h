#pragma once
#include <string>
#include <errno.h>
#include <filesystem>
#include <curl/curl.h>

// Downloads and saves
class PageLoader {
public:
    PageLoader(std::string url);
    ~PageLoader();

    PageLoader(PageLoader &other) = delete;
    void operator=(const PageLoader&) = delete;

    // Downloads a web page as string
    std::string get_request(std::string url) const;
    // Downlowads and saves web files, such as images, CSS files, scripts.
    void get_save_file(std::string save_folder, std::string url) const;
    // Returns web site's root url
    std::string get_root_url() const;

private:
    CURL* mCurl = nullptr;
    std::string mRootUrl;
};
