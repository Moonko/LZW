//
//  lzw.h
//  LZW
//
//  Created by Андрей Рычков on 18.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef LZW_lzw_h
#define LZW_lzw_h

#include <fstream>
#include <string>
#include <iostream>
#include <ctime>
#include <map>
#include <list>
#include <vector>
#include <iterator>
#include <ext/hash_map>
#include "lzwBit.h"

using namespace __gnu_cxx;

typedef twelveBits lzwBits;

namespace lzw
{
    void compress(const char* in, const char* out)
    {
        ibitfstream inFile(in);
        if (!inFile)
        {
            throw "Can not open input file";
        }
        obitfstream outFile(out);
        if (!outFile)
        {
            throw "Can not open output file";
        }
        std::cout << "Compressing..." << std::endl;
        long tic = time(NULL);
        std::string tmp;
        hash_map<std::string, unsigned short> table;
        for (unsigned short c = 0; c < 256; ++c)
        {
            table[tmp+(char)c] = c;
        }
        unsigned short number = 255;
        char c;
        lzwBits t;
        while (inFile.peek() != EOF)
        {
            inFile.get(c);
            if (table.find(tmp+c) != table.end())
            {
                tmp += c;
            }
            else
            {
                outFile << t.setValue(table[tmp]);
                if (number < 4095)
                {
                    table[tmp+c] = ++number;
                }
                tmp = c;
            }
        }
        outFile << t.setValue(table[tmp]);
        std::cout << "Compression succeded by " << time(NULL) - tic << " seconds" << std::endl;
        outFile.close();
        inFile.close();
    }
// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    void decompress(const char* in, const char* out)
    {
        ibitfstream inFile(in);
        if (!inFile)
        {
            throw "Can not open input file";
        }
        obitfstream outFile(out);
        if (!outFile)
        {
            throw "Can not open output file";
        }
        std::cout << "Decompressing..." << std::endl;
        long tic = time(NULL);
        std::string tmp;
        hash_map<unsigned short, std::string> table;
        for (unsigned short i = 0; i < 256; ++i)
        {
            table[i] = tmp+(char)i;
        }
        lzwBits oCode;
        lzwBits nCode;
        inFile >> oCode;
        unsigned short num = 255;
        char c = table[oCode.number][0];
        outFile << c;
        while (inFile.peek() != EOF)
        {
            inFile >> nCode;
            if (table.find(nCode.number) != table.end())
            {
                tmp = table[nCode.number];
            }
            else
            {
                tmp = table[oCode.number];
                tmp += c;
            }
            outFile << tmp;
            c = tmp[0];
            if (num < 4095)
            {
                table[++num] = table[oCode.number] + c;
            }
            oCode = nCode;
        }
        
        outFile.close();
        inFile.close();
        std::cout << "Decompression succeded by " << time(NULL) - tic << " seconds" << std::endl;
    }
}

#endif
