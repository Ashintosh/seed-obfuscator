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

#include "crypto.h"

std::string crypto::to_sha256(std::string input)
{
    CryptoPP::SHA256 hash;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

    hash.CalculateDigest(digest, (const CryptoPP::byte*)input.c_str(), input.length());

    CryptoPP::HexEncoder encoder;
    std::string output;

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    std::transform(output.begin(), output.end(), output.begin(), tolower);

    return output;
}
