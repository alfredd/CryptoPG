cmake_minimum_required(VERSION 3.16)
project(CryptoPG)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH /home/alfredd/.local/)

include_directories(/home/alfredd/.local/include)
link_directories(/home/alfredd/.local/lib)


add_executable(CryptoPG main.cpp)

target_link_libraries(CryptoPG cryptopp)

add_subdirectory(tests)
