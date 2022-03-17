#include <string.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <vector>
#include "functions.h"
using namespace std;

int main()
{
    string initialString = ("Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal");
    string keyString = "ICE";
    string binaryString = "";
    string binaryXOR = "";
    string binaryKey = "";
    string hexXor = "";
    
    for (int i = 0; i < initialString.length(); i++)
    {
        binaryString.append(AsciiToBinary(initialString.substr(i*1,1)));
    }

    for (int i = 0; i < keyString.length(); i++)
    {
        binaryKey.append(AsciiToBinary(keyString.substr(i*1,1)));
    }
    
    for (int j = 0; j < binaryString.length(); j++)
    {
        int mod2 = j % binaryKey.length();
        if((binaryString[j] == '1' and binaryKey[mod2] == '1') or (binaryString[j] == '0' and binaryKey[mod2] == '0'))
        {
        binaryXOR.append("0");
        }
        else
        {
        binaryXOR.append("1");
        }
    }
    // cout << "Binary XOR: " << binaryXOR << endl;
    for (int i = 0; i < binaryXOR.length()/4; i++)
    {
        hexXor.append(BinaryToHex(binaryXOR.substr(i*4,4)));
    }
    cout << hexXor << endl;
}