#pragma once

#include <cstdint>
#include <stdlib.h>

uint64_t AppendNodeID(uint64_t id) {
    return id | (id << 60);
}

uint64_t Rand60()
{
    uint64_t nRandData = 0;
    for (int i = 0; i < 8; i++)
    {
        nRandData <<= 8;
        uint64_t nData = rand() % 256;
        nRandData |= nData;
    }
    nRandData &= 0x0FFFFFFFFFFFFFFF;
    return nRandData;
}

