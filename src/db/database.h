#ifndef SRC_ALY_DATABASE_H
#define SRC_ALY_DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <rocksdb/db.h>

class CDatabase
{
public:
    CDatabase() {
        this->options.create_if_missing = true;
        this->status = rocksdb::DB::Open(options, "/tmp/db", &db);
        if (!status.ok()) {
            std::cerr << status.ToString() << "\n";
        }
    }

    std::string GetBlockByHash(std::string hash) {
        std::string value;
        this->status = db->Get(rocksdb::ReadOptions(), hash, &value);
        return value;
    }

    void PutBlock(std::string hash, std::string json) {
        this->status = db->Put(rocksdb::WriteOptions(), hash, json);
        if (this->status.ok()) {
            std::cout << "'Put' block success" << "\n";
        }
    }

    void DeleteBlockByHash(std::string hash) {
        this->status = db->Delete(rocksdb::WriteOptions(), hash);
        if (this->status.ok()) {
            std::cout << "'Delete' block success" << "\n";
        }
    }

private:
    rocksdb::DB *db;
    rocksdb::Options options;
    rocksdb::Status status;
};

#endif