# web_parser

Simple web site parser. It parses a website and saves all web pages, images, css files and scripts to a local folder.
In order to view the parsed werb site open index.html in <folder_to_save_in> folder. By default folder_to_save_in = website,
which will be located in the main project folder after the parsing.

Usage:
./web_parser [-l<url>] [-f<folder_to_save_in>]
where
url - url to a web site to parse
folder_to_save_in - local folder to save web content in
e.g.
./web_parser -lhttps://books.toscrape.com -fwebsite

Build instructions
Prerequsites:
  Installed CMake, Clang, libcurl, libxml

  1. % sudo apt update
  2. % sudo apt-get -y install cmake
  3. % sudo apt install clang
  4. % git clone https://github.com/Microsoft/vcpkg.git
  5. % cd vcpkg
  6. % ./bootstrap-vcpkg.sh
  7. % ./vcpkg integrate install
  8. % vcpkg install curl
  9. % vcpkg install libxml2

  // Building
  1. % mkdir build
  2. % cmake --build ./build

  TO-DO:
  1. Add tests (GoogleTest)
  2. Parse web pages in parallel
  3. Better progress handling
  4. Better error handling (exceptions)

Design:
    helpers
    1. namespace cl_parser, which contains utilites to parse command line.
    Main classes
    2. PageLoader
    PageLoader uses libcurl library to download html pages as a string from the web in order to parse it for
    images, scripts, links, css files and save them locally.
    3. SiteParserLibxml
    SiteParserLibxml contains a method parse(), which starts a recursive Depth-First search on a web site structure using libxml
    library.
    4. WebParser
    WebParser parses a web site using a submitted subclass of base SiteParser class. In this case SiteParserLibxml



