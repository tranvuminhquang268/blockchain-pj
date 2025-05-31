#pragma once

#include "block.h" 
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class BlockChain{
public:
	BlockChain() {
        Block firstBlock("**********", "First Block Ever", "**********");
        _chain.push_back(firstBlock);
    }

	void add_block(Block block) {
        int nPrevIndex; 
        if (_chain.size() > 0) {
            nPrevIndex = chain_length() - 1;
        }
        else nPrevIndex = 0; 

		_previou_block = _chain.at(nPrevIndex);
        _chain.push_back(block);
        _current_block = _chain.at(chain_length() - 1); 
    }

	Block get_block(int index) const { 
        if (index >= 0 && index < chain_length()) {
            return _chain.at(index);
        } 
		else {
            return _chain.at(0); 
        }
    }

	Block get_latest_block() const { 
        return _chain.back();
    }

	int chain_length() const {
        return (int)_chain.size();
    }

private:
	vector<Block> _chain;
	Block _current_block; 
	Block _previou_block;
};
