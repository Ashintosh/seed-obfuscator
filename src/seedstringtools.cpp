////////////////////////////////////////////////////////////////////////////
// seed-obfuscator                                                        // 
// Copyright (C) 2022 Ashintosh                                           //
//                                                                        //
// This program is free software: you can redistribute it and/or modify   //
// it under the terms of the GNU General Public License as published by   //
// the Free Software Foundation, either version 3 of the License, or      //
// (at your option) any later version.                                    //
//                                                                        //
// This program is distributed in the hope that it will be useful,        //
// but WITHOUT ANY WARRANTY; without even the implied warranty of         //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          //
// GNU General Public License for more details.                           //
//                                                                        //
// You should have received a copy of the GNU General Public License      //
// along with this program.  If not, see <https://www.gnu.org/licenses/>. //
////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

#include "seedstringtools.h"
#include "bip39.h"
#include "sha256/sha256.h"


// Private //



std::vector<std::string> seedstringtools::split_seed_by_whitespace(std::string input)
{
    std::vector<std::string> seed_word_list;
    std::istringstream stringstream(input);
    std::string stringstream_res;

    // Add each word in seed phrase, separated by space, to vector string
    while (getline(stringstream, stringstream_res, ' ')) {
        seed_word_list.push_back(stringstream_res);
    }

    return seed_word_list;
}

std::string seedstringtools::vector_to_string(std::vector<std::string> input) {
    std::string output_string = "";
    for (std::string &item : input) {
        output_string.append(item);
    }

    return output_string;
}


// Public //

std::string seedstringtools::obfuscate_seed(std::string seed, std::string passphrase)
{
    std::string passphrase_sha256 = SHA256::to_sha256(passphrase);
    std::vector<std::string> split_seed_phrase = seedstringtools::split_seed_by_whitespace(seed);

    std::vector<int> offset;
    std::vector<std::string> ob_seed_words;

    for (char& c : passphrase_sha256) {
        offset.push_back((int) c - '0');
    }

    for (int i = 0; i < split_seed_phrase.size(); i++) {
        int word_index = bip39::get_element_index(split_seed_phrase.at(i));
        int new_word_index;

        // Decide the offset direction by the int value of offset / 3 and checking if the returned result is odd or even
        if ((int)(offset.at(i) / 3) & 1) {
            new_word_index = word_index - offset.at(i) * 20;
        } else {
            new_word_index = word_index + offset.at(i) * 20;
        }

        // Check if new index is out of bounds in the bip39 wordlist and corrects the value if necessary
        while (new_word_index < 0 || new_word_index > bip39::bip_39_wordlist.size()) {
            if (new_word_index < 0) {
                int difference = new_word_index * -1;
                new_word_index = bip39::bip_39_wordlist.size() - difference;
            } else if (new_word_index > bip39::bip_39_wordlist.size()) {
                int difference = new_word_index - bip39::bip_39_wordlist.size();
                new_word_index = difference;
            }
        }

        // Add shifted word to new seed phrase
        ob_seed_words.push_back(bip39::bip_39_wordlist.at(new_word_index) + ' ');
    }

    return seedstringtools::vector_to_string(ob_seed_words);
}
