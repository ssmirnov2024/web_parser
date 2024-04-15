# web_parser

Simple web site parser. It parses a website and saves all web pages, images, css files and scripts to a local folder.

Usage:
./web_parser [-l <url>] [-f <folder_to_save_in>]
where
url - url to a web site to parse
folder_to_save_in - local folder to save web content in
e.g.
./web_parser -l https://books.toscrape.com -f website

Build instructions
Prerequsites:
  Installed CMake, Clang, libcurl, libxml

  % sudo apt update
  % sudo apt-get -y install cmake
  % sudo apt install clang

  % git clone https://github.com/Microsoft/vcpkg.git
  % cd vcpkg
  % ./bootstrap-vcpkg.sh
  % ./vcpkg integrate install
  % vcpkg install curl
  % vcpkg install libxml2

  // Building
  % mkdir build
  % cmake --build ./build

  TO-DO:
  1. Show progress
  2. Parse web pages in parallel
