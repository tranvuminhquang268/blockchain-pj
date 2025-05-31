#include <iostream>
#include "blockchain.h"
#include "hash.h"
#include <string>
#include <sstream> 

using namespace std;

void print_help() {
    cout << "\nAvailable commands:\n";
    cout << "  add <data>       - Add a new block with the given data\n";
    cout << "  show <index>     - Show block at the given index (0 for genesis)\n";
    cout << "  latest           - Show the latest block\n";
    cout << "  length           - Show the current chain length\n";
    cout << "  print            - Print all blocks in the chain\n";
    cout << "  help             - Show this help message\n";
    cout << "  exit             - Exit the program\n";
    cout << "  mine <number>    - Automatically mine a specified number of blocks with auto-generated data\n";
    cout << "--------------------------------------------------\n";
}

void print_block_details(const Block& block, int index) {
    cout << "\n--- Block " << index << " ---\n";
    cout << "Data: " << block.get_data() << endl;
    cout << "Hash: " << block.get_hash() << endl;
    cout << "Previous Hash: " << block.get_prev_hash() << endl;
    cout << "-------------------\n";
}

int main() {
    const int difficulty = 4; // Độ khó của việc khai thác block
    cout << "Initializing Blockchain...\n";
    BlockChain blockChain = BlockChain();
    cout << "Blockchain Initialized.\n";
    print_help();

    string line;
    string command;
    string argument;

    while (true) {
        cout << "\nEnter command: ";
        getline(cin, line);
        stringstream ss(line);
        ss >> command; // Đọc lệnh đầu tiên
        
        // Đọc phần còn lại của dòng làm đối số (nếu có)
        argument = ""; 
        string temp_arg;
        if (ss >> temp_arg) {
            argument = temp_arg;
            while(ss >> temp_arg) {
                argument += " " + temp_arg;
            }
        }

        if (command == "add") {
            if (argument.empty()) {
                cout << "Error: 'add' command requires data. Usage: add <your data here>\n";
                continue;
            }
            Block newBlock = Block(
                blockChain.get_latest_block().get_hash(),
                argument,
                CalculateHash_SHA512(argument + blockChain.get_latest_block().get_hash()) 
            );
            blockChain.add_block(newBlock);
            cout << "Block added successfully.\n";
            print_block_details(blockChain.get_latest_block(), blockChain.chain_length() - 1);
        } 
        else if (command == "show") {
            if (argument.empty()) {
                cout << "Error: 'show' command requires an index. Usage: show <index>\n";
                continue;
            }
            int index = stoi(argument);
            if (index >= 0 && index < blockChain.chain_length()) {
                print_block_details(blockChain.get_block(index), index);
            } else {
                cout << "Error: Index out of bounds.\n";
            }
        } 
        else if (command == "latest") { 
            if (blockChain.chain_length() > 0) {
                print_block_details(blockChain.get_latest_block(), blockChain.chain_length() - 1);
            } else {
                cout << "Blockchain is empty.\n";
            }
        } 
        else if (command == "length") {
            cout << "Current chain length: " << blockChain.chain_length() << endl;
        } 
        else if (command == "print") {
            if (blockChain.chain_length() == 0) {
                cout << "Blockchain is empty.\n";
            } else {
                for (int i = 0; i < blockChain.chain_length(); ++i) {
                    print_block_details(blockChain.get_block(i), i);
                }
            }
        } 
        else if (command == "help") {
            print_help();
        } 
        else if (command == "exit") {
            cout << "Exiting program.\n";
            break;
        } 
        else if (command == "mine") {
    if (argument.empty()) {
        cout << "Error: 'mine' command requires a number. Usage: mine <number_of_blocks>\n";
        continue;
    }
    int numBlocks = stoi(argument);
    for (int i = 0; i < numBlocks; ++i) {
        string data = "Auto block " + to_string(blockChain.chain_length());  // Tự sinh dữ liệu

        Block newBlock(blockChain.get_latest_block().get_hash(), data);
        cout << "Mining block " << blockChain.chain_length() << "...\n";
        newBlock.mineBlock(difficulty);
        blockChain.add_block(newBlock);
        cout << "-> Block " << blockChain.chain_length() - 1 << " mined.\n";
    }
    cout << numBlocks << " block(s) mined successfully.\n";
}

        else {
            cout << "Unknown command. Type 'help' for available commands.\n";
        }
    }
    return 0;
}
