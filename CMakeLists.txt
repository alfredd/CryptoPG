cmake_minimum_required(VERSION 3.16)
project(CryptoPG)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenSSL REQUIRED)


add_executable(CryptoPG main.cpp)

target_link_libraries(CryptoPG OpenSSL::SSL)

add_subdirectory(tests)