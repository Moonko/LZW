//
//  12bit.h
//  LZW
//
//  Created by Андрей Рычков on 24.04.13.
//  Copyright (c) 2013 Андрей Рычков. All rights reserved.
//

#ifndef LZW__12bit_h
#define LZW__12bit_h

#include <bitset>
#include <fstream>
#include "bitstream.h"

struct lzwLowBit
{
    unsigned short number;
    lzwLowBit setValue(unsigned short num = 0)
    {
        number = num;
        return *this;
    }
};

obitfstream& operator << (obitfstream& out, const lzwLowBit& x)
{
    unsigned short tmp = x.number;
    bool a;
    for (int i = 0; i < 12; ++i)
    {
        a = tmp % 2;
        out.putBit(a);
        tmp /= 2;
    }
    return out;
}
ibitfstream& operator >> (ibitfstream& in, lzwLowBit& x)
{
    std::bitset<12> bits;
    for (int i = 0; i < 12; ++i)
    {
        bits[i] = in.getBit();
    }
    x.number = bits.to_ulong();
    return in;
}


#endif
