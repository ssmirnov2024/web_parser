cmake_minimum_required(VERSION 3.5.0)
project(web_parser VERSION 0.1.0)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include>)

add_executable(${PROJECT_NAME} web_parser.cpp site_parser.cpp page_loader.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_17)

find_package(LibXml2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE LibXml2::LibXml2)

find_package(CURL REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE CURL::libcurl)
