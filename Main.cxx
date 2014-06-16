#include <iostream>
#include <fstream>

using namespace std;

#include "NESHeader.hpp"

int main(int argc, char **argv)
{
    /* 数据来源于Battle_Kid_-_Fortress_of_Peril.nes
    起始偏移: 00000000, 尾部偏移: 0000000F, 长度: 00000010 */
    unsigned char rawData[16] = {
        0x4E, 0x45, 0x53, 0x1A, 0x10, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00
    };
    NESHeader header(rawData);
    cout<<header.to_string()<<endl;
}
