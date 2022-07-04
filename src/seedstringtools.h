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

#ifndef SEEDSTRINGTOOLS_H
#define SEEDSTRINGTOOLS_H

#include <iostream>
#include <vector>

class seedstringtools
{
private:
    static std::vector<std::string> split_seed_by_whitespace(std::string);
    static std::string vector_to_string(std::vector<std::string>);

public:
    static std::string obfuscate_seed(std::string, std::string);
    static std::string deobfuscate_seed(std::string, std::string);
};

#endif // SEEDSTRINGTOOLS_H
