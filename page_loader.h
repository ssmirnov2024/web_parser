#pragma once
#include <string>
#include <errno.h>
#include <filesystem>
#include <curl/curl.h>

class PageLoader {
public:
    PageLoader(std::string url);
    ~PageLoader();

    PageLoader(PageLoader &other) = delete;
    void operator=(const PageLoader&) = delete;

    std::string get_request(std::string url) const;
    void get_save_file(std::string save_folder, std::string url) const;
    std::string get_main_url() const;

private:
    CURL* mCurl = nullptr;
    std::string mRootUrl;
};
