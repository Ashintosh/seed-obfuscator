////////////////////////////////////////////////////////////////////////////
// seed-encryptor                                                         //
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

#include "seedstringtools.h"


// Private //

std::vector<std::string> seedstringtools::split_seed_by_whitespace(std::string pSeed)
{
    std::vector<std::string> seedWordList;
    std::istringstream stringstream(pSeed);
    std::string stringstream_result;

    // Add each word in seed phrase, separated by space, to vector string
    while (getline(stringstream, stringstream_result, ' ')) {
        seedWordList.push_back(stringstream_result);
    }

    return seedWordList;
}

std::string seedstringtools::vector_to_string(std::vector<std::string> pVctr) {
    std::string output = "";
    for (std::string &item : pVctr) {
        output.append(item);
    }

    return output;
}


// Public //

std::string seedstringtools::caesar_encrypt(std::string pSeed, std::string pPassphrase, int pOffsetMult, bool pReverse)
{
    std::string passphrase_sha256 = crypto::sha256_hash(pPassphrase);
    std::string offset_direc_determiner_sha256 = crypto::sha256_hash(passphrase_sha256);
    std::vector<std::string> split_seed_phrase = split_seed_by_whitespace(pSeed);

    std::vector<int> offset;
    std::vector<int> offset_direc_determiner;
    std::vector<std::string> ob_seed_words;

    for (char& c : passphrase_sha256)
        offset.push_back((int) c - '0');
    for (char& c : offset_direc_determiner_sha256)
        offset_direc_determiner.push_back((int) c - '0');

    for (int i = 0; i < split_seed_phrase.size(); i++) {
        int word_index = bip39::get_element_index(split_seed_phrase.at(i));
        int new_word_index;

        // Check if word exists in bip39 wordlist
        if (word_index < 0)  return "";

        // Decide offset shift direction with the determiner offset by calculating if value is odd or even
        int offset_direc_left = (int)(offset_direc_determiner.at(i) & 1);

        // Get new bip39 word index using offset value and shift direction
        if (offset_direc_left && pReverse ||
           !offset_direc_left && !pReverse)
        {
            new_word_index = word_index + offset.at(i) * pOffsetMult;
        }
        else  new_word_index = word_index - offset.at(i) * pOffsetMult;

        // Check if new index is out of bounds in the bip39 wordlist and correct the value if necessary
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

    return vector_to_string(ob_seed_words);
}

std::string seedstringtools::aes_encrypt(std::string pSeed, std::string pPassphrase, bool pReverse)
{
    std::vector<std::string> split_seed_phrase = split_seed_by_whitespace(pSeed);
    std::vector<int> word_indexes;
    std::string plaintext_conv = "";

    for (std::string &word : split_seed_phrase) {
        int index = bip39::get_element_index(word);
        std::ostringstream ss;
        ss << std::hex << index;
        plaintext_conv.append(ss.str() + ".");
    }

    std::string encrypted_str = crypto::aes_pbkdf2_encrypt(plaintext_conv, pPassphrase);
    std::string encrypted_str_conv = "";

    for (int i = 0; i < encrypted_str.size(); i++) {

        if ((i % 5) == 0 && i != 0) {
             encrypted_str_conv.push_back(encrypted_str.at(i));
             encrypted_str_conv.push_back(' ');
        } else  encrypted_str_conv.push_back(encrypted_str.at(i));
    }

    return encrypted_str_conv;
}
