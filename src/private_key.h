#ifndef SRC_ALY_PRIVATE_KEY_H
#define SRC_ALY_PRIVATE_KEY_H

#include <openssl/evp.h>
#include <openssl/ecdsa.h>
#include <openssl/pem.h>

class CPrivateKey {
public:
    CPrivateKey() {
        key_ = EC_KEY_new_by_curve_name(NID_secp256k1);
        EC_KEY_generate_key(key_);
    }

    ~CPrivateKey() {
        EC_KEY_free(key_);
    }

    std::string Sign(const std::string& message) const {
        const unsigned char* msg = reinterpret_cast<const unsigned char*>(message.c_str());
        std::vector<unsigned char> signature(72);

        unsigned char digest[32];
        SHA256(msg, message.length(), digest);

        unsigned int signature_length = 0;
        if (ECDSA_sign(0, digest, sizeof(digest), signature.data(), &signature_length, key_) != 1) {
            throw std::runtime_error("Failed to sign message");
        }

        signature.resize(signature_length);

        std::stringstream ss;
        for (const auto& byte : signature) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }

        return ss.str();
    }

    std::string GetPublicKey() const {
        const EC_POINT* public_key_point = EC_KEY_get0_public_key(key_);
        if (public_key_point == nullptr) {
            throw std::runtime_error("Failed to get public key");
        }

        std::vector<unsigned char> public_key(65);
        int length = EC_POINT_point2oct(EC_KEY_get0_group(key_), public_key_point, POINT_CONVERSION_UNCOMPRESSED, public_key.data(), public_key.size(), nullptr);
        public_key.resize(length);

        std::stringstream ss;
        for (const auto& byte : public_key) {
            ss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(byte);
        }

        return ss.str();
    }

private:
    EC_KEY* key_;
};

#endif