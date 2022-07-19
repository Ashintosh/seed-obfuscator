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

#ifndef SEEDSTRINGTOOLS_H
#define SEEDSTRINGTOOLS_H

#include <iostream>
#include <sstream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <vector>

#include "bip39.h"
#include "crypto/crypto.h"


class seedstringtools
{
private:
    static std::vector<std::string> split_seed_by_whitespace(std::string pSeed);
    static std::string vector_to_string(std::vector<std::string> pVctr);

public:
    static std::string caesar_encrypt(std::string pSeed, std::string pPassphrase, int pOffsetMult, bool pReverse);
    static std::string aes_encrypt(std::string pSeed, std::string pPassphrase, bool pReverse);
};

#endif // SEEDSTRINGTOOLS_H
