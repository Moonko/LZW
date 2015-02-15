//
//  main.cpp
//  LZW
//
//  Created by Андрей Рычков on 18.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#include <iostream>
#include "lzw.h"
#include <ctime>

using namespace std;

int main()
{
    try
    {
        int exit = 2013;
        while (exit != 0)
        {
            cout << endl;
            cout << "  - - - - - - - - - - - - - - - -" << endl;
            cout << "|        LZW compressor           |" << endl;
            cout << "  - - - - - - - - - - - - - - - -" << endl;
            cout << "| 1. Compress file                |" << endl;
            cout << "| 2. Decompress file              |" << endl;
            cout << "| 3. Compress and decompress file |" << endl;
            cout << "| 0. Exit                         |" << endl;
            cout << "  - - - - - - - - - - - - - - - -" << endl;
            cout << "Choose action: ";
            cin >> exit;
            cout << endl;
            switch (exit)
            {
                case 1:
                {
                    char inFile[32];
                    cout << "Enter input file's name: ";
                    cin >> inFile;
                    cout << endl;
                    char outFile[32];
                    cout << "Enter compressed file's name: ";
                    cin >> outFile;
                    cout << endl;
                    lzw::compress(inFile, outFile);
                    break;
                }
                case 2:
                {
                    char inFile[32];
                    cout << "Enter input file's name: ";
                    cin >> inFile;
                    cout << endl;
                    char outFile[32];
                    cout << "Enter decompressed file's name: ";
                    cin >> outFile;
                    cout << endl;
                    lzw::decompress(inFile, outFile);
                    break;
                }
                case 3:
                {
                    char inFile[32];
                    cout << "Enter input file's name: ";
                    cin >> inFile;
                    cout << endl;
                    char outFile[32];
                    cout << "Enter compressed file's name: ";
                    cin >> outFile;
                    cout << endl;
                    char deFile[32];
                    cout << "Enter decompressed file's name: ";
                    cin >> deFile;
                    cout << endl;
                    lzw::compress(inFile, outFile);
                    lzw::decompress(outFile, deFile);
                    break;
                }
                default:
                {
                    exit = 0;
                    break;
                }
            }
        }
    }
    catch(const char* error)
    {
        cout << error;
    }
    return 0;
}