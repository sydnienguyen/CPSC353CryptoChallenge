#include <string.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <vector>
#include "functions.h"
using namespace std;

int count1 = 0;
int stringsFoundCount = 0;
float charRatio = 0.79;
double charCount = 0.0;
string likelyChars1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
string likelyChars2 = "abcdefghijklmnopqrstuvwxyz";
string unlikelyChars = "!@#$%^&*(){}[]`~|/.,<>?;:+";

int main()
{
  string initialHex1 = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
  string binaryString1 = "";

  int mod = initialHex1.length() % 8;
  if (mod == 0) {mod = 8;}

  initialHex1.insert(0, "000000000", 0, 8 - mod);

  cout << "Hex String1: \n" << initialHex1 << endl << endl;

  for (int i = 0; i < initialHex1.length()/8; i++)
  {
    binaryString1.append(HexToDecimal(initialHex1.substr(i*8,8)));
  }

  binaryString1 = binaryString1.erase(0,4*(8-mod));

  cout << "Binary String1: \n" << binaryString1 << endl << endl;


  for (int i = 32; i < 128; i++)
  {
    char b = i;
    string c(1, b);
    string tempAscii = AsciiToBinary(c);
    string binaryXOR = "";
    string asciiString = "";
    string tempAsciiString = "";

    for (int j = 0; j < binaryString1.length(); j++)
    {
      int mod2 = j % 8;
      if((binaryString1[j] == '1' and tempAscii[mod2] == '1') or (binaryString1[j] == '0' and tempAscii[mod2] == '0'))
      {
        binaryXOR.append("0");
      }
      else
      {
        binaryXOR.append("1");
      }
    }
    for (int k = 0; k < binaryXOR.length()/8; k++)
    {
      string tempXOR = binaryXOR.substr(k*8,8);
      tempAsciiString = toascii_frombinary(tempXOR.c_str());
      asciiString.append(tempAsciiString);
    }
    count1++;
    charCount = 0;

    for (int i = 0; i < asciiString.length(); i++)
    {
      for (int j = 0; j < likelyChars1.length(); j++)
      {
        if (asciiString[i] == likelyChars1[j] or asciiString[i] == likelyChars2[j])
        {
          charCount++;
        }
        if (asciiString[i] == unlikelyChars[j])
        {
          charCount--;
        }
      }
    }
    if (charCount / asciiString.length() > charRatio)
    {
      cout << ("\ntest #: ") << count1 << endl;
      cout << ("Key value in Binary: ") << tempAscii << endl;
      cout << asciiString << endl;
      cout << ("Ratio: ") << charCount / asciiString.size() << endl;
      stringsFoundCount++;
    }
  }
    cout << ("\nTotal Tests Run: ") << count1 << endl;
    cout << ("Successful Strings Found: ") << stringsFoundCount << endl;
}