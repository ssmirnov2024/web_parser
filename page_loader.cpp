#include "page_loader.h"


using namespace std;

PageLoader::PageLoader(string url): mRootUrl(url) {
        mCurl = curl_easy_init();
    }

PageLoader::~PageLoader() {
    if(mCurl) {
        curl_easy_cleanup(mCurl);
    }
}

std::string PageLoader::get_request(std::string url) const
{
    std::string result;
    
    if(mCurl) {
        curl_easy_setopt(mCurl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, +[](void* contents, size_t size, size_t nmemb, void *userp){
                ((std::string*)userp)->append((char*)contents, size* nmemb);
                return size * nmemb;
        });
        curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, &result);
        curl_easy_perform(mCurl);
    } 

    return result;
}

void PageLoader::get_save_file(std::string save_folder, std::string url) const
{
    FILE *fp;
    std::string full_url = mRootUrl + "/" + url;
    std::string out_file_name = save_folder + "/" + url;
    auto pos = out_file_name.rfind("/");
    std::string output_folder = out_file_name.substr(0, pos);
    if(mCurl) {
        if(!std::filesystem::exists(output_folder)){
            std::filesystem::create_directories(output_folder);
        }
        if(!std::filesystem::exists(out_file_name)) {
            fp = fopen(out_file_name.c_str(), "wb");
            curl_easy_setopt(mCurl, CURLOPT_URL, full_url.c_str());
            curl_easy_setopt(mCurl, CURLOPT_WRITEFUNCTION, +[](void *contents, size_t size, size_t nmemb, void *stream){
                size_t bytes = fwrite(contents, size, nmemb, static_cast<FILE*>(stream));
                return bytes;
            });
            curl_easy_setopt(mCurl, CURLOPT_WRITEDATA, fp);
            curl_easy_perform(mCurl);
            fclose(fp);
        }
    }
}

std::string PageLoader::get_main_url() const
{
    return mRootUrl;
}