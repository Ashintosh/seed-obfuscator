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

#ifndef CRYPTO_H
#define CRYPTO_H

#include <iostream>
#include <cryptopp/aes.h>
#include <cryptopp/sha.h>
#include <cryptopp/hex.h>
#include <cryptopp/pwdbased.h>
#include <cryptopp/rijndael.h>
#include <cryptopp/cryptlib.h>
#include <cryptopp/osrng.h>
#include <cryptopp/files.h>
#include <cryptopp/modes.h>

class crypto
{
public:
    static std::string sha256_hash(std::string pPlainText);
    static CryptoPP::SecByteBlock pbkdf2_salt_hash(std::string pPlainText, CryptoPP::SecByteBlock pSalt);
    static std::string aes_pbkdf2_encrypt(std::string pPlainText, std::string pKey);
    static std::string aes_pbkdf2_decrypt(std::string pCipherText, std::string pKey);
};

#endif // CRYPTO_H
