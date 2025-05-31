#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include <openssl/sha.h>

using namespace std;

class Block {
public:
    Block() {}

    // ✅ Constructor 2 tham số
    Block(string prevHash, string data) {
        _prevBlockHash = prevHash;
        _data = data;
        _nonce = 0;
        _hash = calculateHash();
    }

    // ✅ Constructor 3 tham số (để tương thích code cũ)
    Block(string prevHash, string data, string hash) {
        _prevBlockHash = prevHash;
        _data = data;
        _hash = hash;
        _nonce = 0;
    }

    string calculateHash() const {
        stringstream ss;
        ss << _prevBlockHash << _data << _nonce;
        string input = ss.str();

        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256(reinterpret_cast<const unsigned char*>(input.c_str()), input.size(), hash);

        stringstream output;
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            output << hex << setw(2) << setfill('0') << (int)hash[i];
        }
        return output.str();
    }

    void mineBlock(int difficulty) {
        string target(difficulty, '0');
        while (_hash.substr(0, difficulty) != target) {
            _nonce++;
            _hash = calculateHash();
        }
    }

    // GETTER & SETTER
    void set_hash(string hash) { _hash = hash; }
    void set_prev_hash(string prevHash) { _prevBlockHash = prevHash; }
    void set_data(string data) { _data = data; }

    string get_hash() const { return _hash; }
    string get_prev_hash() const { return _prevBlockHash; }
    string get_data() const { return _data; }
    int get_nonce() const { return _nonce; }
    int get_index() const { return _index; }

    // ✅ Đổi tên hàm này để không xung đột với std::to_string
    string rawString() const {
        return _prevBlockHash + _data + _hash + std::to_string(_nonce);
    }

private:
    string _prevBlockHash;
    string _hash;
    string _data;
    int _nonce = 0;
    int _index = 0;
};
