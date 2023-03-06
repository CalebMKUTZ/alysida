#ifndef SRC_ALY_MERKLE_TREE_H
#define SRC_ALY_MERKLE_TREE_H

#include <iostream>
#include <openssl/sha.h>

class CMerkleTree 
{
public:
    CMerkleTree(std::vector<std::string> txns) {
        this->txns = txns;
    }
    
    std::string GetMerkleRoot() {
    if (txns.empty()) {
        return "";
    }
    
    std::vector<std::string> hashes;
        for (const auto& txn : txns) {
            unsigned char hash[SHA256_DIGEST_LENGTH];
            SHA256(reinterpret_cast<const unsigned char*>(txn.data()), txn.size(), hash);
            hashes.emplace_back(reinterpret_cast<const char*>(hash), SHA256_DIGEST_LENGTH);
        }

        while (hashes.size() > 1) {
            if (hashes.size() % 2 == 1) {
                hashes.emplace_back(hashes.back());
            }
            
            std::vector<std::string> new_hashes;
            for (auto it = hashes.begin(); it != hashes.end(); it += 2) {
                unsigned char hash[SHA256_DIGEST_LENGTH];
                SHA256_CTX ctx;
                SHA256_Init(&ctx);
                SHA256_Update(&ctx, reinterpret_cast<const unsigned char*>(it->data()), it->size());
                SHA256_Update(&ctx, reinterpret_cast<const unsigned char*>((it+1)->data()), (it+1)->size());
                SHA256_Final(hash, &ctx);
                new_hashes.emplace_back(reinterpret_cast<const char*>(hash), SHA256_DIGEST_LENGTH);
            }
            hashes = std::move(new_hashes);
        }
        
        std::ostringstream s;
        s << std::hex << std::setfill('0');
        for (const auto& byte : hashes[0]) {
            s << std::setw(2) << static_cast<unsigned int>(static_cast<unsigned char>(byte));
        }

        return s.str();
    }

private:
    std::vector<std::string> txns;
};

#endif