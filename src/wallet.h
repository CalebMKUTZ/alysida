#ifndef SRC_ALY_WALLET_H
#define SRC_ALY_WALLET_H

#include <iostream>
#include <nlohmann/json.hpp>
#include <glog/logging.h>
#include <rang.hpp>
#include <string>
#include "transaction.h"
#include "private_key.h"
#include "sha256.h"

using json = nlohmann::json;
using namespace rang;

class CWallet {
public:
    CWallet(std::string name) {
        this->name = name;
        this->public_key = private_key.GetPublicKey();
        this->address = GenWalletAddress();
        this->balance = 100; // TODO!: this is for testing purposes. Change this in PROD.
    }

    std::string GenWalletAddress() {
        CSHA256 sha;
        std::string wallet_data = ToJSON();
        return sha.sha256(wallet_data);
    }

    std::string GetWalletAddress() {
        return address;
    }

    void Send(std::string sender_address, std::string recipient_address, uint32_t amount) {
        if (amount > balance) {
            std::cout << fg::red << "insufficient funds." << fg::reset << "\n";
            exit(1);
        }
        CTransaction tx(sender_address, recipient_address, amount);
        tx.Sign(private_key);
        std::cout << fg::green << "transaction sent                  " << tx.CalcTxId() << fg::reset << "\n";
    }

    std::string ToJSON() {
        json j;
        j["name"] = name;
        j["public_key"] = public_key;
        j["address"] = address;
        j["balance"] = balance;
        return j.dump(4);
    }

private:
    CPrivateKey private_key;
    std::string public_key;
    std::string name;
    std::string address;
    uint32_t balance;
};

#endif