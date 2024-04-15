# web_parser

Simple web site parser. It parses a website and saves all web pages, images, css files and scripts to a local folder.

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
  1. Parse web pages in parallel
