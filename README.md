# seed-obfuscator

### Development Status: **Working on new features**

We know the safest way to store your crypto wallet seed phrases is on physical materials such as paper or metal, but how do we protect our phrases from physical attacks such as theft? 

This tool makes it easier to obfuscate your seed phrases with your own passphrase. It uses a hashed version of your passphrase to shift each word in your seed phrase to another that is a part of the BIP-39 wordlist.

*NOTICE: Any wallet seed that has not been created using the BIP-39 wordlist will not be supported by this tool.*

## Obfuscation Types
- BIP-39 "Caesar Cipher" style obfuscation

# Dependencies
- Qt5: [Website](https://www.qt.io/) - [Source](https://github.com/qt/qt5) - [License](https://doc.qt.io/qt-5/lgpl.html)
- libcurl: [Website](https://curl.se/libcurl/) - [Source](https://github.com/curl/curl) - [License](https://raw.githubusercontent.com/curl/curl/master/COPYING)

# Credits
- src/sha256/: [Jérémy LAMBERT (SystemGlitch)](https://github.com/System-Glitch) - [Source](https://github.com/System-Glitch/SHA256) - [License](https://raw.githubusercontent.com/Ashintosh/seed-obfuscator/main/src/sha256/LICENSE)

## To Add
- Cross-wordlist obfuscation
- Random letter obfuscation
