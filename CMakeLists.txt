cmake_minimum_required(VERSION 3.16)
project(CryptoPG)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_PREFIX_PATH /home/alfredd/.local/)
include_directories(/home/alfredd/.local/include)
link_directories(/home/alfredd/.local/lib)

include(FindProtobuf)
find_package(Protobuf REQUIRED)
find_package(gRPC REQUIRED)


#NOT RECOMMENDED. Currently done just to checkout gRPC code generation.
execute_process(
        COMMAND bash -c "${CMAKE_PREFIX_PATH}/bin/protoc -I=${CMAKE_CURRENT_SOURCE_DIR} --grpc_out=. --plugin=protoc-gen-grpc=${CMAKE_PREFIX_PATH}/bin/grpc_cpp_plugin ${CMAKE_CURRENT_SOURCE_DIR}/cryptopg.proto"
        COMMAND bash -c "${CMAKE_PREFIX_PATH}/bin/protoc -I=${CMAKE_CURRENT_SOURCE_DIR} --cpp_out=. ${CMAKE_CURRENT_SOURCE_DIR}/cryptopg.proto"
)

include_directories("${CMAKE_CURRENT_BINARY_DIR}")

add_executable(CryptoPG main.cpp)

target_link_libraries(CryptoPG cryptopp)




add_executable(cserver cryptopg_server.cpp cryptopg.grpc.pb.cc cryptopg.pb.cc KeyManager.cpp)
target_link_libraries(cserver gRPC::grpc++)

add_subdirectory(tests)


#[[
include_directories(${PROTOBUF_INCLUDE_DIR})
include_directories(${GRPC_INCLUDE_DIR})
PROTOBUF_GENERATE_CPP(PROTO_SRC PROTO_HEADER cryptopg.proto)
#GRPC_GENERATE_CPP(GRPC_SRC GRPC_HEADER cryptopg.proto)
add_library(proto ${PROTO_HEADER} ${PROTO_SRC} ${GRPC_SRC} ${GRPC_HEADER})
]]
#target_link_libraries(CryptoPG proto)
