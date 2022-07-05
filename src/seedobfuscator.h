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

#ifndef SEEDOBFUSCATOR_H
#define SEEDOBFUSCATOR_H

#include <iostream>


class seedobfuscator
{
public:
    static const int VER_MAJOR = 0;
    static const int VER_MINOR = 1;
    static const int VER_REV = 0;
    static const int VER_BUILD = 1;

    static std::string get_version_str();
};

#endif // SEEDOBFUSCATOR_H
