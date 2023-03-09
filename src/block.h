#ifndef SRC_ALY_BLOCK_H
#define SRC_ALY_BLOCK_H

#include <iostream>
#include <vector>
#include <ctime>
#include <sstream>
#include <nlohmann/json.hpp>
#include "sha256.h"
#include "db/database.h"
#include "helper.h"
#include "transaction.h"
#include "merkle_tree.h"

#define TARGET_ZEROES 2

using json = nlohmann::json;

class CBlock 
{
public:
    CBlock(std::string prev_hash, std::vector<std::string> transactions) {
        this->timestamp = helper::h_UseTime();
        this->transactions = transactions;
        this->prev_hash = prev_hash;
        this->hash = CalcSha256(); 
        this->merkle = CMerkleTree(transactions).GetMerkleRoot();
        this->size = sizeof(*this);
        this->nonce = 0;
    }

    std::string CalcSha256() {
        CSHA256 sha;
        std::string block_data = ToJSON();
        return sha.sha256(block_data);
    }
    
    std::string ToJSON() {
        json j;
        j["timestamp"] = timestamp;
        j["transactions"] = transactions;
        j["prev_hash"] = prev_hash;
        j["hash"] = hash;
        j["merkle_root"] = merkle;
        j["size"] = size;
        j["nonce"] = nonce;
        return j.dump(4);
    }

    void RunPoW(CDatabase db) {
        while (true) {
            if (hash.substr(0, TARGET_ZEROES) == std::string("0", TARGET_ZEROES)) {
                std::cout << "block mined: " << hash << "\n";
                db.PutBlock(hash, ToJSON());
                break;
            } else {
                hash = CalcSha256();
                std::cout << hash << "\t\t\t" << "nonce = " << nonce << "\n";
                nonce++;
            }
        }
    }

    time_t GetTimestamp() {
        return timestamp;
    }

    std::vector<std::string> GetTxns() {
        return transactions;
    }

    std::string GetPrevHash() {
        return prev_hash;
    }

    std::string GetHash() {
        return hash;
    }

    std::string GetMerkle() {
        return merkle;
    }

    uint64_t GetNonce() {
        return nonce;
    }

private:
    time_t timestamp;
    std::vector<std::string> transactions;
    std::string prev_hash;
    std::string hash;
    std::string merkle;
    uint16_t size;
    uint64_t nonce;
};

#endif