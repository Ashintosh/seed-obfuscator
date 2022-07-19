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


// Public //

std::string crypto::sha256_hash(std::string pPlainText)
{
    CryptoPP::SHA256 sha;
    CryptoPP::byte digest[CryptoPP::SHA256::DIGESTSIZE];

    sha.CalculateDigest(digest, (const CryptoPP::byte*)pPlainText.c_str(), pPlainText.length());

    CryptoPP::HexEncoder encoder;
    std::string output;

    encoder.Attach(new CryptoPP::StringSink(output));
    encoder.Put(digest, sizeof(digest));
    encoder.MessageEnd();

    std::transform(output.begin(), output.end(), output.begin(), tolower);

    return output;
}

CryptoPP::SecByteBlock crypto::pbkdf2_salt_hash(std::string pPlainText, CryptoPP::SecByteBlock pSalt)
{
    CryptoPP::PKCS5_PBKDF2_HMAC<CryptoPP::SHA256> pbkdf;
    CryptoPP::SecByteBlock output(CryptoPP::AES::DEFAULT_KEYLENGTH);

    CryptoPP::byte text_bytes[pPlainText.size()];
    std::memcpy(text_bytes, pPlainText.data(), pPlainText.size());

    size_t plaintext_length = strlen((const char*)text_bytes);
    size_t salt_length = pSalt.size();

    pbkdf.DeriveKey(output, output.size(), 0, text_bytes, plaintext_length, pSalt, salt_length, 1024, 0.0f);

    return output;
}

std::string crypto::aes_pbkdf2_encrypt(std::string pPlainText, std::string pKey)
{
    CryptoPP::AutoSeededRandomPool prng;
    CryptoPP::SecByteBlock iv (CryptoPP::AES::BLOCKSIZE);
    CryptoPP::SecByteBlock salt (CryptoPP::AES::DEFAULT_KEYLENGTH / 2);
    CryptoPP::SecByteBlock key (CryptoPP::AES::DEFAULT_KEYLENGTH);

    prng.GenerateBlock(salt, salt.size());
    prng.GenerateBlock(iv, iv.size());
    key = pbkdf2_salt_hash(pKey, salt);

    std::string cipher, output;

    try {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Encryption e;
        e.SetKeyWithIV(key, key.size(), iv);

        CryptoPP::StringSource stringsource (pPlainText, true,
            new CryptoPP::StreamTransformationFilter(e,
                new CryptoPP::StringSink(cipher)
            )
        );
    } catch (const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        return "";
    }

    CryptoPP::HexEncoder encoder(new CryptoPP::FileSink(std::cout));
    std::string cipher_str, iv_str, salt_str;

    encoder.Detach(new CryptoPP::StringSink(salt_str));
    encoder.Put(salt, salt.size());
    encoder.MessageEnd();

    encoder.Detach(new CryptoPP::StringSink(iv_str));
    encoder.Put(iv, iv.size());
    encoder.MessageEnd();

    encoder.Detach(new CryptoPP::StringSink(cipher_str));
    encoder.Put((const CryptoPP::byte*)&cipher[0], cipher.size());
    encoder.MessageEnd();

    output = iv_str + cipher_str + salt_str;

    return output;
}

std::string crypto::aes_pbkdf2_decrypt(std::string pCipherText, std::string pKey)
{
    std::string iv_str = pCipherText.substr(0, 32);
    std::string salt_str = pCipherText.substr(pCipherText.size() - 16, pCipherText.size());
    std::string cipher_str = pCipherText.substr(iv_str.size(), pCipherText.size() - (iv_str.size() + salt_str.size()));

    std::string iv, cipher, salt, output;
    CryptoPP::HexDecoder decoder;

    decoder.Attach(new CryptoPP::StringSink(iv));
    decoder.Put((CryptoPP::byte*)iv_str.data(), iv_str.size());
    decoder.MessageEnd();

    decoder.Attach(new CryptoPP::StringSink(salt));
    decoder.Put((CryptoPP::byte*)salt_str.data(), salt_str.size());
    decoder.MessageEnd();

    decoder.Attach(new CryptoPP::StringSink(cipher));
    decoder.Put((CryptoPP::byte*)cipher_str.data(), cipher_str.size());
    decoder.MessageEnd();

    try {
        CryptoPP::CBC_Mode<CryptoPP::AES>::Decryption decryptor;
        CryptoPP::SecByteBlock saltBlk((const CryptoPP::byte*) salt.data(), salt.size());
        CryptoPP::SecByteBlock key = pbkdf2_salt_hash(pKey, saltBlk);
        decryptor.SetKeyWithIV(key.data(), key.size(), (CryptoPP::byte*)iv.data(), CryptoPP::AES::BLOCKSIZE);

        CryptoPP::StringSource s(cipher, true,
            new CryptoPP::StreamTransformationFilter(decryptor,
                new CryptoPP::StringSink(output)
            )
        );
    } catch (const CryptoPP::Exception& e) {
        std::cerr << e.what() << std::endl;
        return "";
    }

    return output;
}
