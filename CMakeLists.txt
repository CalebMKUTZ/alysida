cmake_minimum_required(VERSION 3.2)

include("cmake/HunterGate.cmake")

HunterGate(
    URL "https://github.com/cpp-pm/hunter/archive/v0.23.297.tar.gz"
    SHA1 "3319fe6a3b08090df7df98dee75134d68e2ef5a3"
)

project(aly)

hunter_add_package(OpenSSL)
find_package(OpenSSL REQUIRED)

hunter_add_package(nlohmann_json)
find_package(nlohmann_json CONFIG REQUIRED)

hunter_add_package(sqlite3)
find_package(sqlite3 CONFIG REQUIRED)

hunter_add_package(rocksdb)
find_package(RocksDB CONFIG REQUIRED)

hunter_add_package(asio)
find_package(asio CONFIG REQUIRED)

hunter_add_package(glog)
find_package(glog CONFIG REQUIRED)

hunter_add_package(rang)
find_package(rang CONFIG REQUIRED)

set(CMAKE_CXX_STANDARD 20)

add_executable(aly main.cpp src/block.h src/db/database.h src/helper.h src/merkle_tree.h src/sha256.h src/transaction.h src/wallet.h)

target_link_libraries(aly PUBLIC OpenSSL::SSL OpenSSL::Crypto)
target_link_libraries(aly PUBLIC sqlite3::sqlite3)
target_link_libraries(aly PUBLIC nlohmann_json::nlohmann_json)
target_link_libraries(aly PUBLIC RocksDB::rocksdb)
target_link_libraries(aly PUBLIC asio::asio_static)
target_link_libraries(aly PUBLIC glog::glog)
target_link_libraries(aly PUBLIC rang::rang)