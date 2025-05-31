#pragma once

#include <string>
#include <vector>
#include <openssl/evp.h> // For EVP API
#include <iomanip>      // For std::setw and std::setfill
#include <sstream>      // For std::ostringstream
#include <stdexcept>    // For std::runtime_error

inline std::string CalculateHash_SHA512(const std::string& text) {
    EVP_MD_CTX* mdctx = NULL;
    const EVP_MD* md = NULL;
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hash_len = 0;
    std::string error_msg;

    try {
        md = EVP_sha512();
        if (md == NULL) {
            throw std::runtime_error("EVP_sha512() failed to return md");
        }

        mdctx = EVP_MD_CTX_new();
        if (mdctx == NULL) {
            throw std::runtime_error("EVP_MD_CTX_new() failed");
        }

        if (1 != EVP_DigestInit_ex(mdctx, md, NULL)) {
            throw std::runtime_error("EVP_DigestInit_ex() failed");
        }

        if (1 != EVP_DigestUpdate(mdctx, text.c_str(), text.length())) {
            throw std::runtime_error("EVP_DigestUpdate() failed");
        }

        if (1 != EVP_DigestFinal_ex(mdctx, hash, &hash_len)) {
            throw std::runtime_error("EVP_DigestFinal_ex() failed");
        }

        EVP_MD_CTX_free(mdctx); // Clean up context

        std::ostringstream oss;
        for (unsigned int i = 0; i < hash_len; ++i) {
            oss << std::hex << std::setw(2) << std::setfill('0') << static_cast<int>(hash[i]);
        }
        return oss.str();

    } catch (const std::exception& e) {
        if (mdctx) {
            EVP_MD_CTX_free(mdctx);
        }
        // Re-throw or handle more gracefully, e.g., log and return empty string or specific error code
        throw; // Re-throwing the caught exception
    }
}