//
//  bitstream.h
//  LZW
//
//  Created by Андрей Рычков on 25.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef LZW_bitstream_h
#define LZW_bitstream_h

typedef unsigned char uchar;

class ibitfstream: public std::ifstream
{
    uchar buffer;
    uchar bitcount;
public:
    ibitfstream():bitcount(0),buffer(0){}
    ibitfstream(const char *fname): std::ifstream(fname,ios_base::binary),bitcount(0){}
    int getBit()
    {
        if (bitcount==8) bitcount = 0;
        if (bitcount==0) buffer = get();
        int i;
        i = buffer & (1<<(7-bitcount)) ? 1:0;
        ++bitcount;
        return i;
    }
    bool eof()
    {
        if (bitcount<8 && bitcount>0)
            return false;
        // return isftream::eof();
        if (peek()!=EOF)
            return false;
        return true;
    }
};

class obitfstream: public std::ofstream
{
    uchar bitcount;
    uchar buffer;
public:
    obitfstream():bitcount(0),buffer(0){}
    obitfstream(const char *fname): std::ofstream(fname, ios_base::binary),bitcount(0){}
    void putBit(bool x)
    {
        buffer |= ( (static_cast<uchar>(x)) << (7-bitcount));
        
        ++bitcount;
        
        if (bitcount==8) bitcount = 0;
        if (bitcount==0) { put(buffer); buffer = 0;}
    }
    void close()
    {
        if (bitcount>0)
            put(buffer);
        buffer=0;
        bitcount=0;
        std::ofstream::close();
    }
};


#endif
