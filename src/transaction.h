#ifndef SRC_ALY_TRANSACTION_H
#define SRC_ALY_TRANSACTION_H

#include <iostream>
#include <openssl/sha.h>
#include <nlohmann/json.hpp>
#include <sstream>
#include "helper.h"
#include "private_key.h"
#include "sha256.h"

using json = nlohmann::json;

struct CTxInput {
    std::string txid;
    size_t output_index;
    std::string signature;
};

struct CTxOutput {
    uint32_t value;
    std::string public_key;
};

class CTransaction
{
public:
    CTransaction(std::string sender_address, std::string recipient_address, uint32_t amount) {
        this->txid = CalcTxId();
        this->sender_address = sender_address;
        this->recipient_address = recipient_address;
        this->amount = amount;
        this->timestamp = helper::h_UseTime();

        CPrivateKey private_key;

        CTxInput input;
        input.txid = txid;
        input.output_index = vin.size();
        input.signature = signature;
        vin.push_back(input);

        CTxOutput output;
        output.public_key = private_key.GetPublicKey();
        output.value = amount;
        vout.push_back(output);
    }

    std::string CalcTxId() {
        CSHA256 sha;
        std::string tx_data = ToJSON();
        return sha.sha256(tx_data);
    }

    void Sign(CPrivateKey private_key) {
        std::string tx_data = ToJSON();
        signature = private_key.Sign(tx_data);
    }

    std::string ToJSON() {
        json j1;

        j1["txid"] = txid;
        j1["sender"] = sender_address;
        j1["recipient"] = recipient_address;
        j1["amount"] = amount;
        j1["timestamp"] = timestamp;
        
        json input_array = json::array();

        if (!vin.empty()) {
            for (const auto &in : vin) {
                json j = {
                    {"txid", in.txid},
                    {"out_index", in.output_index},
                    {"signature", in.signature},
                };
                input_array.push_back(j);
            }
        }

        json output_array = json::array();
        if (!vout.empty()) {
            for (const auto &out : vout) {
                json j = {
                    {"value", out.value},
                    {"public_key", out.public_key},
                };
                output_array.push_back(j);
            }
        }

        j1["inputs"] = input_array;
        j1["outputs"] = output_array;
        j1["signature"] = signature;
        return j1.dump(4);
    }

private:
    std::string txid;
    std::string sender_address;
    std::string recipient_address;
    uint32_t amount;
    std::vector<CTxInput> vin;
    std::vector<CTxOutput> vout;
    time_t timestamp;
    std::string signature;
};

#endif