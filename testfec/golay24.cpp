///////////////////////////////////////////////////////////////////////////////////
// Copyright (C) 2016 Edouard Griffiths, F4EXB.                                  //
//                                                                               //
// This program is free software; you can redistribute it and/or modify          //
// it under the terms of the GNU General Public License as published by          //
// the Free Software Foundation as version 3 of the License, or                  //
//                                                                               //
// This program is distributed in the hope that it will be useful,               //
// but WITHOUT ANY WARRANTY; without even the implied warranty of                //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the                  //
// GNU General Public License V3 for more details.                               //
//                                                                               //
// You should have received a copy of the GNU General Public License             //
// along with this program. If not, see <http://www.gnu.org/licenses/>.          //
///////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include "../fec.h"

void decode(DSDcc::Golay_24_12& Golay_24_12, unsigned char *codeword)
{
    for (int i = 0; i < 24; i++)
    {
        std::cout << (int) codeword[i] << " ";
    }

    std::cout << std::endl;

    if (Golay_24_12.decode(codeword))
    {
        for (int i = 0; i < 12; i++)
        {
            std::cout << (int) codeword[i] << " ";
        }

        std::cout << std::endl << "Decoding OK" << std::endl;
    }
    else
    {
        std::cout << "Decoding error" << std::endl;
    }
}

int main(int argc, char *argv[])
{
    unsigned char msg[12]  = {1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0};
    unsigned char er0[24] = {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    unsigned char codeword[24], xcodeword[24];

    DSDcc::Golay_24_12 golay_24_12;
    golay_24_12.encode(msg, codeword);

    std::cout << "No errors" << std::endl;
    decode(golay_24_12, codeword);

    std::cout << std::endl << "Error on one bit (4)" << std::endl;
    decode(golay_24_12, er0);

    std::cout << std::endl << "Flip one bit (4)" << std::endl;
    std::copy(codeword, codeword + 24, xcodeword);
    xcodeword[4] ^=  1;
    decode(golay_24_12, xcodeword);

    std::cout << std::endl << "Flip one bit (15) in parity" << std::endl;
    std::copy(codeword, codeword + 24, xcodeword);
    xcodeword[15] ^=  1;
    decode(golay_24_12, xcodeword);

    std::cout << std::endl << "Flip two bits (1,5)" << std::endl;
    std::copy(codeword, codeword + 24, xcodeword);
    xcodeword[1] ^= 1;
    xcodeword[5] ^= 1;
    decode(golay_24_12, xcodeword);

    std::cout << std::endl << "Flip two bits (1,15) - one in parity" << std::endl;
    std::copy(codeword, codeword + 24, xcodeword);
    xcodeword[1] ^= 1;
    xcodeword[15] ^= 1;
    decode(golay_24_12, xcodeword);

    std::cout << std::endl << "Flip three bits (1,5,9)" << std::endl;
    std::copy(codeword, codeword + 24, xcodeword);
    xcodeword[1] ^= 1;
    xcodeword[5] ^= 1;
    xcodeword[9] ^= 1;
    decode(golay_24_12, xcodeword);

    std::cout << std::endl << "Flip three bits (1,5,15) - 1 in parity" << std::endl;
    std::copy(codeword, codeword + 24, xcodeword);
    xcodeword[1] ^= 1;
    xcodeword[5] ^= 1;
    xcodeword[15] ^= 1;
    decode(golay_24_12, xcodeword);

    std::cout << std::endl << "Flip three bits (1,15,21) - 2 in parity" << std::endl;
    std::copy(codeword, codeword + 24, xcodeword);
    xcodeword[1] ^= 1;
    xcodeword[15] ^= 1;
    xcodeword[21] ^= 1;
    decode(golay_24_12, xcodeword);

    std::cout << std::endl << "Flip three bits (15,18,21) - all parity" << std::endl;
    std::copy(codeword, codeword + 24, xcodeword);
    xcodeword[15] ^= 1;
    xcodeword[18] ^= 1;
    xcodeword[21] ^= 1;
    decode(golay_24_12, xcodeword);

    return 0;
}



