# seed-encryptor

We know the safest way to store your crypto wallet seed phrases is on physical materials such as paper or metal, but how do we protect our phrases from physical attacks such as theft? 

This tool makes it easier to encrypt your seed phrases with your own passphrase so you can safely store them physically. This tools has two available encryption methods: Custom Caeser Cipher style encryption, AES-256-CBC encryption.

*NOTICE: Any wallet seed that has not been created using the BIP-39 wordlist will not be supported by this tool.*

## Encryption Types
- BIP-39 "Caesar Cipher" style encryption
- AES-256-CBC encryption with easy-to-read formatting

## To Add
- Cross-wordlist obfuscation

## Dependencies
- Qt6: [Website](https://www.qt.io/) - [Source](https://github.com/qt/qtbase) - [License](https://doc.qt.io/qt-6/lgpl.html)
- Crypto++: [Website](https://cryptopp.com/) - [Source](https://github.com/weidai11/cryptopp) - [License](https://github.com/weidai11/cryptopp/blob/master/License.txt)
