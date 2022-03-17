#include <vector>
#include <string>
#include <algorithm>

int getbit(unsigned x, unsigned n) { return (x >> n) & 1; }

char* tobinary(unsigned long x, int bits) 
{ 
    static char buf[BUFSIZ];
    memset(buf, 0, sizeof(char));

    char* p = buf;
    for (int i = bits - 1; i >= 0; --i)
    { 
        *p++ = (getbit(x, i) == 1 ? '1' : '0');
        // if (i % 8 == 0) { *p++ = ' ';  }
    }
    if (*(p - 1) == ' ') { --p; }
    *p = '\0';
    return buf;
}

char* tobinary_4(unsigned long x) { return tobinary(x, 32); }
char* tobinary_8( unsigned long x) { return tobinary(x, 8); }

char tobase64(char c) { 
  if (c < 26) { return c + 65; 
  } else if (c < 52) { return c + 71; 
  } else if (c < 62) { return c - 4; 
  } else if (c == 62) { return 43; 
  } else { return 47; }
}

char toascii_frombinary(const char* s) {
  int n = strlen(s);
  const char* p = s + n - 1;
  char c = 0;
  unsigned power = 1;
  while (*p != '\0' && p >= s) { 
    if (*p != '0' && *p != '1') { throw new std::invalid_argument("invalid binary number"); }
    if (*p-- == '1') { 
      c += power;
    }
    power <<= 1;
  }
  return c;
}

// e.g., D --> 1101
std::string HexToBinary(std::string Hex) 
{      
    unsigned long x = strtoll(Hex.c_str(), NULL, 16);
    return std::string(tobinary_4(x));
}

std::string BinaryToBase64(std::string Binary) {
  static char buf[16];
  memset(buf, 0, sizeof(buf));
  char c = toascii_frombinary(Binary.c_str());
  char cbase64 = tobase64(c);
  snprintf(buf, sizeof(buf), "%c", cbase64);
  return std::string(buf);
}

std::string HexToDecimal(std::string Hex) 
{      
    auto x = strtol(Hex.c_str(), NULL, 16);
    return std::string(tobinary_4(x));
}

std::string BinaryToHex(std::string Binary) {    // e.g., 1101 --> D
  static char buf[16];
  unsigned c = toascii_frombinary(Binary.c_str());
  snprintf(buf, sizeof(buf), "%x", c);
  return std::string(buf);
}

std::string AsciiToBinary(std::string Ascii) {   // e.g., 'A' --> 01000001
  char c = Ascii.c_str()[0];
  const char* s = tobinary_8(c);
  return std::string(s);
}

std::string Base64toBinary(std::string base64)
{
  std::string binaryString = "";
  for (int i = 0; i < base64.length(); i++)
  {
    char chr = base64[i];
    if (chr >= 'A' && chr <= 'Z') binaryString.append(tobinary((chr - 'A'),6));
    else if (chr >= 'a' && chr <= 'z') binaryString.append(tobinary((chr - 'a' + ('Z' - 'A') + 1),6));
    else if (chr >= '0' && chr <= '9') binaryString.append(tobinary((chr - '0' + ('Z' - 'A') + ('z' - 'a') + 2),6));
    else if (chr == '+') binaryString.append(tobinary(62,6));
    else if (chr == '/') binaryString.append(tobinary(63,6)); 
    else
      throw std::runtime_error("Input is not valid base64-encoded data."); 
  } 
  return binaryString;
}

int hammingDistanceforStrings(std::string encoded1, std::string encoded2)
{
  std::cout << ("String 1: \n") << encoded1 << std::endl;
  std::cout << ("String 2: \n") << encoded2 << std::endl;

  std::string binaryString1 = "";
  std::string binaryString2 = "";
  std::string binaryXOR = "";
  int distance = 0;

  for (int i = 0; i < encoded1.length(); i++)
  {
    binaryString1.append(AsciiToBinary(encoded1.substr(i*1,1)));
  }
  
  for (int i = 0; i < encoded2.length(); i++)
  {
    binaryString2.append(AsciiToBinary(encoded2.substr(i*1,1)));
  }

  std::cout << ("Binary String 1: \n") << binaryString1 << std::endl;    
  std::cout << ("Binary String 2: \n") << binaryString2 << std::endl;    
  

  for (int i = 0; i < binaryString1.length(); i++)
  {
    if((binaryString1[i] == '1' and binaryString2[i] == '1') or (binaryString1[i] == '0' and binaryString2[i] == '0'))
    {
      binaryXOR.append("0");
    }
    else
    {
      binaryXOR.append("1");
    }
  }

  std::cout << ("Binary XOR: \n") << binaryXOR << std::endl;

  for (int i = 0; i < binaryXOR.length(); i++)
  {
    if (binaryXOR[i] == '1')
    {
      distance++;
    }
  }
  return distance;
}

int hammingDistanceforBinary(std::string encoded1, std::string encoded2)
{
  // std::cout << ("Binary String 1: \n") << encoded1 << std::endl;
  // std::cout << ("Binary String 2: \n") << encoded2 << std::endl;

  std::string binaryXOR = "";
  int distance = 0;

  for (int i = 0; i < encoded1.length(); i++)
  {
    if(encoded1[i] != encoded2[i])
    {
      distance++;
    }
  }
  return distance;
}

// used for encrypting and expanding key only
std::vector<std::vector<int>> s_box = {
                                      {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76},
                                      {0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0},
                                      {0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15},
                                      {0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75},
                                      {0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84},
                                      {0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf},
                                      {0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8},
                                      {0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2},
                                      {0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73},
                                      {0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb},
                                      {0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79},
                                      {0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08},
                                      {0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a},
                                      {0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e},
                                      {0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf},
                                      {0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16},
};
// used for expanding key only 
std::vector<std::vector<int>> RCON_vec = {
                                            {0x01,0x00,0x00,0x00},
                                            {0x02,0x00,0x00,0x00},
                                            {0x04,0x00,0x00,0x00},
                                            {0x08,0x00,0x00,0x00},
                                            {0x10,0x00,0x00,0x00},
                                            {0x20,0x00,0x00,0x00},
                                            {0x40,0x00,0x00,0x00},
                                            {0x80,0x00,0x00,0x00},
                                            {0x1B,0x00,0x00,0x00},
                                            {0x36,0x00,0x00,0x00}
};

// used for decrypting only
std::vector<std::vector<int>> s_boxINVERSE = {
                                      {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb},
                                      {0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb},
                                      {0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e},
                                      {0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25},
                                      {0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92},
                                      {0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84},
                                      {0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06},
                                      {0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b},
                                      {0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73},
                                      {0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e},
                                      {0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b},
                                      {0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4},
                                      {0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f},
                                      {0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef},
                                      {0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61},
                                      {0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d}
};
// only for excrypting for mixed columns 
std::vector<std::vector<int>> mul2 = {
                                      {0x00, 0x02, 0x04, 0x06, 0x08, 0x0a, 0x0c, 0x0e, 0x10, 0x12, 0x14, 0x16, 0x18, 0x1a, 0x1c, 0x1e},
                                      {0x20, 0x22, 0x24, 0x26, 0x28, 0x2a, 0x2c, 0x2e, 0x30, 0x32, 0x34, 0x36, 0x38, 0x3a, 0x3c, 0x3e},
                                      {0x40, 0x42, 0x44, 0x46, 0x48, 0x4a, 0x4c, 0x4e, 0x50, 0x52, 0x54, 0x56, 0x58, 0x5a, 0x5c, 0x5e},
                                      {0x60, 0x62, 0x64, 0x66, 0x68, 0x6a, 0x6c, 0x6e, 0x70, 0x72, 0x74, 0x76, 0x78, 0x7a, 0x7c, 0x7e},
                                      {0x80, 0x82, 0x84, 0x86, 0x88, 0x8a, 0x8c, 0x8e, 0x90, 0x92, 0x94, 0x96, 0x98, 0x9a, 0x9c, 0x9e},
                                      {0xa0, 0xa2, 0xa4, 0xa6, 0xa8, 0xaa, 0xac, 0xae, 0xb0, 0xb2, 0xb4, 0xb6, 0xb8, 0xba, 0xbc, 0xbe},
                                      {0xc0, 0xc2, 0xc4, 0xc6, 0xc8, 0xca, 0xcc, 0xce, 0xd0, 0xd2, 0xd4, 0xd6, 0xd8, 0xda, 0xdc, 0xde},
                                      {0xe0, 0xe2, 0xe4, 0xe6, 0xe8, 0xea, 0xec, 0xee, 0xf0, 0xf2, 0xf4, 0xf6, 0xf8, 0xfa, 0xfc, 0xfe},
                                      {0x1b, 0x19, 0x1f, 0x1d, 0x13, 0x11, 0x17, 0x15, 0x0b, 0x09, 0x0f, 0x0d, 0x03, 0x01, 0x07, 0x05},
                                      {0x3b, 0x39, 0x3f, 0x3d, 0x33, 0x31, 0x37, 0x35, 0x2b, 0x29, 0x2f, 0x2d, 0x23, 0x21, 0x27, 0x25},
                                      {0x5b, 0x59, 0x5f, 0x5d, 0x53, 0x51, 0x57, 0x55, 0x4b, 0x49, 0x4f, 0x4d, 0x43, 0x41, 0x47, 0x45},
                                      {0x7b, 0x79, 0x7f, 0x7d, 0x73, 0x71, 0x77, 0x75, 0x6b, 0x69, 0x6f, 0x6d, 0x63, 0x61, 0x67, 0x65},
                                      {0x9b, 0x99, 0x9f, 0x9d, 0x93, 0x91, 0x97, 0x95, 0x8b, 0x89, 0x8f, 0x8d, 0x83, 0x81, 0x87, 0x85},
                                      {0xbb, 0xb9, 0xbf, 0xbd, 0xb3, 0xb1, 0xb7, 0xb5, 0xab, 0xa9, 0xaf, 0xad, 0xa3, 0xa1, 0xa7, 0xa5},
                                      {0xdb, 0xd9, 0xdf, 0xdd, 0xd3, 0xd1, 0xd7, 0xd5, 0xcb, 0xc9, 0xcf, 0xcd, 0xc3, 0xc1, 0xc7, 0xc5},
                                      {0xfb, 0xf9, 0xff, 0xfd, 0xf3, 0xf1, 0xf7, 0xf5, 0xeb, 0xe9, 0xef, 0xed, 0xe3, 0xe1, 0xe7, 0xe5}
};

std::vector<std::vector<int>> mul3 = {
                                      {0x00, 0x03, 0x06, 0x05, 0x0c, 0x0f, 0x0a, 0x09, 0x18, 0x1b, 0x1e, 0x1d, 0x14, 0x17, 0x12, 0x11},
                                      {0x30, 0x33, 0x36, 0x35, 0x3c, 0x3f, 0x3a, 0x39, 0x28, 0x2b, 0x2e, 0x2d, 0x24, 0x27, 0x22, 0x21},
                                      {0x60, 0x63, 0x66, 0x65, 0x6c, 0x6f, 0x6a, 0x69, 0x78, 0x7b, 0x7e, 0x7d, 0x74, 0x77, 0x72, 0x71},
                                      {0x50, 0x53, 0x56, 0x55, 0x5c, 0x5f, 0x5a, 0x59, 0x48, 0x4b, 0x4e, 0x4d, 0x44, 0x47, 0x42, 0x41},
                                      {0xc0, 0xc3, 0xc6, 0xc5, 0xcc, 0xcf, 0xca, 0xc9, 0xd8, 0xdb, 0xde, 0xdd, 0xd4, 0xd7, 0xd2, 0xd1},
                                      {0xf0, 0xf3, 0xf6, 0xf5, 0xfc, 0xff, 0xfa, 0xf9, 0xe8, 0xeb, 0xee, 0xed, 0xe4, 0xe7, 0xe2, 0xe1},
                                      {0xa0, 0xa3, 0xa6, 0xa5, 0xac, 0xaf, 0xaa, 0xa9, 0xb8, 0xbb, 0xbe, 0xbd, 0xb4, 0xb7, 0xb2, 0xb1},
                                      {0x90, 0x93, 0x96, 0x95, 0x9c, 0x9f, 0x9a, 0x99, 0x88, 0x8b, 0x8e, 0x8d, 0x84, 0x87, 0x82, 0x81},
                                      {0x9b, 0x98, 0x9d, 0x9e, 0x97, 0x94, 0x91, 0x92, 0x83, 0x80, 0x85, 0x86, 0x8f, 0x8c, 0x89, 0x8a},
                                      {0xab, 0xa8, 0xad, 0xae, 0xa7, 0xa4, 0xa1, 0xa2, 0xb3, 0xb0, 0xb5, 0xb6, 0xbf, 0xbc, 0xb9, 0xba},
                                      {0xfb, 0xf8, 0xfd, 0xfe, 0xf7, 0xf4, 0xf1, 0xf2, 0xe3, 0xe0, 0xe5, 0xe6, 0xef, 0xec, 0xe9, 0xea},
                                      {0xcb, 0xc8, 0xcd, 0xce, 0xc7, 0xc4, 0xc1, 0xc2, 0xd3, 0xd0, 0xd5, 0xd6, 0xdf, 0xdc, 0xd9, 0xda},
                                      {0x5b, 0x58, 0x5d, 0x5e, 0x57, 0x54, 0x51, 0x52, 0x43, 0x40, 0x45, 0x46, 0x4f, 0x4c, 0x49, 0x4a},
                                      {0x6b, 0x68, 0x6d, 0x6e, 0x67, 0x64, 0x61, 0x62, 0x73, 0x70, 0x75, 0x76, 0x7f, 0x7c, 0x79, 0x7a},
                                      {0x3b, 0x38, 0x3d, 0x3e, 0x37, 0x34, 0x31, 0x32, 0x23, 0x20, 0x25, 0x26, 0x2f, 0x2c, 0x29, 0x2a},
                                      {0x0b, 0x08, 0x0d, 0x0e, 0x07, 0x04, 0x01, 0x02, 0x13, 0x10, 0x15, 0x16, 0x1f, 0x1c, 0x19, 0x1a}
};

// only for decrypting for column inverse matrix 
std::vector<std::vector<int>> mul9 = {
                                      {0x00, 0x09, 0x12, 0x1b, 0x24, 0x2d, 0x36, 0x3f, 0x48, 0x41, 0x5a, 0x53, 0x6c, 0x65, 0x7e, 0x77},
                                      {0x90, 0x99, 0x82, 0x8b, 0xb4, 0xbd, 0xa6, 0xaf, 0xd8, 0xd1, 0xca, 0xc3, 0xfc, 0xf5, 0xee, 0xe7},
                                      {0x3b, 0x32, 0x29, 0x20, 0x1f, 0x16, 0x0d, 0x04, 0x73, 0x7a, 0x61, 0x68, 0x57, 0x5e, 0x45, 0x4c},
                                      {0xab, 0xa2, 0xb9, 0xb0, 0x8f, 0x86, 0x9d, 0x94, 0xe3, 0xea, 0xf1, 0xf8, 0xc7, 0xce, 0xd5, 0xdc},
                                      {0x76, 0x7f, 0x64, 0x6d, 0x52, 0x5b, 0x40, 0x49, 0x3e, 0x37, 0x2c, 0x25, 0x1a, 0x13, 0x08, 0x01},
                                      {0xe6, 0xef, 0xf4, 0xfd, 0xc2, 0xcb, 0xd0, 0xd9, 0xae, 0xa7, 0xbc, 0xb5, 0x8a, 0x83, 0x98, 0x91},
                                      {0x4d, 0x44, 0x5f, 0x56, 0x69, 0x60, 0x7b, 0x72, 0x05, 0x0c, 0x17, 0x1e, 0x21, 0x28, 0x33, 0x3a},
                                      {0xdd, 0xd4, 0xcf, 0xc6, 0xf9, 0xf0, 0xeb, 0xe2, 0x95, 0x9c, 0x87, 0x8e, 0xb1, 0xb8, 0xa3, 0xaa},
                                      {0xec, 0xe5, 0xfe, 0xf7, 0xc8, 0xc1, 0xda, 0xd3, 0xa4, 0xad, 0xb6, 0xbf, 0x80, 0x89, 0x92, 0x9b},
                                      {0x7c, 0x75, 0x6e, 0x67, 0x58, 0x51, 0x4a, 0x43, 0x34, 0x3d, 0x26, 0x2f, 0x10, 0x19, 0x02, 0x0b},
                                      {0xd7, 0xde, 0xc5, 0xcc, 0xf3, 0xfa, 0xe1, 0xe8, 0x9f, 0x96, 0x8d, 0x84, 0xbb, 0xb2, 0xa9, 0xa0},
                                      {0x47, 0x4e, 0x55, 0x5c, 0x63, 0x6a, 0x71, 0x78, 0x0f, 0x06, 0x1d, 0x14, 0x2b, 0x22, 0x39, 0x30},
                                      {0x9a, 0x93, 0x88, 0x81, 0xbe, 0xb7, 0xac, 0xa5, 0xd2, 0xdb, 0xc0, 0xc9, 0xf6, 0xff, 0xe4, 0xed},
                                      {0x0a, 0x03, 0x18, 0x11, 0x2e, 0x27, 0x3c, 0x35, 0x42, 0x4b, 0x50, 0x59, 0x66, 0x6f, 0x74, 0x7d},
                                      {0xa1, 0xa8, 0xb3, 0xba, 0x85, 0x8c, 0x97, 0x9e, 0xe9, 0xe0, 0xfb, 0xf2, 0xcd, 0xc4, 0xdf, 0xd6},
                                      {0x31, 0x38, 0x23, 0x2a, 0x15, 0x1c, 0x07, 0x0e, 0x79, 0x70, 0x6b, 0x62, 0x5d, 0x54, 0x4f, 0x46}
};

std::vector<std::vector<int>> mul11 = {
                                      {0x00, 0x0b, 0x16, 0x1d, 0x2c, 0x27, 0x3a, 0x31, 0x58, 0x53, 0x4e, 0x45, 0x74, 0x7f, 0x62, 0x69},
                                      {0xb0, 0xbb, 0xa6, 0xad, 0x9c, 0x97, 0x8a, 0x81, 0xe8, 0xe3, 0xfe, 0xf5, 0xc4, 0xcf, 0xd2, 0xd9},
                                      {0x7b, 0x70, 0x6d, 0x66, 0x57, 0x5c, 0x41, 0x4a, 0x23, 0x28, 0x35, 0x3e, 0x0f, 0x04, 0x19, 0x12},
                                      {0xcb, 0xc0, 0xdd, 0xd6, 0xe7, 0xec, 0xf1, 0xfa, 0x93, 0x98, 0x85, 0x8e, 0xbf, 0xb4, 0xa9, 0xa2},
                                      {0xf6, 0xfd, 0xe0, 0xeb, 0xda, 0xd1, 0xcc, 0xc7, 0xae, 0xa5, 0xb8, 0xb3, 0x82, 0x89, 0x94, 0x9f},
                                      {0x46, 0x4d, 0x50, 0x5b, 0x6a, 0x61, 0x7c, 0x77, 0x1e, 0x15, 0x08, 0x03, 0x32, 0x39, 0x24, 0x2f},
                                      {0x8d, 0x86, 0x9b, 0x90, 0xa1, 0xaa, 0xb7, 0xbc, 0xd5, 0xde, 0xc3, 0xc8, 0xf9, 0xf2, 0xef, 0xe4},
                                      {0x3d, 0x36, 0x2b, 0x20, 0x11, 0x1a, 0x07, 0x0c, 0x65, 0x6e, 0x73, 0x78, 0x49, 0x42, 0x5f, 0x54},
                                      {0xf7, 0xfc, 0xe1, 0xea, 0xdb, 0xd0, 0xcd, 0xc6, 0xaf, 0xa4, 0xb9, 0xb2, 0x83, 0x88, 0x95, 0x9e},
                                      {0x47, 0x4c, 0x51, 0x5a, 0x6b, 0x60, 0x7d, 0x76, 0x1f, 0x14, 0x09, 0x02, 0x33, 0x38, 0x25, 0x2e},
                                      {0x8c, 0x87, 0x9a, 0x91, 0xa0, 0xab, 0xb6, 0xbd, 0xd4, 0xdf, 0xc2, 0xc9, 0xf8, 0xf3, 0xee, 0xe5},
                                      {0x3c, 0x37, 0x2a, 0x21, 0x10, 0x1b, 0x06, 0x0d, 0x64, 0x6f, 0x72, 0x79, 0x48, 0x43, 0x5e, 0x55},
                                      {0x01, 0x0a, 0x17, 0x1c, 0x2d, 0x26, 0x3b, 0x30, 0x59, 0x52, 0x4f, 0x44, 0x75, 0x7e, 0x63, 0x68},
                                      {0xb1, 0xba, 0xa7, 0xac, 0x9d, 0x96, 0x8b, 0x80, 0xe9, 0xe2, 0xff, 0xf4, 0xc5, 0xce, 0xd3, 0xd8},
                                      {0x7a, 0x71, 0x6c, 0x67, 0x56, 0x5d, 0x40, 0x4b, 0x22, 0x29, 0x34, 0x3f, 0x0e, 0x05, 0x18, 0x13},
                                      {0xca, 0xc1, 0xdc, 0xd7, 0xe6, 0xed, 0xf0, 0xfb, 0x92, 0x99, 0x84, 0x8f, 0xbe, 0xb5, 0xa8, 0xa3}
};

std::vector<std::vector<int>> mul13 = {
                                      {0x00, 0x0d, 0x1a, 0x17, 0x34, 0x39, 0x2e, 0x23, 0x68, 0x65, 0x72, 0x7f, 0x5c, 0x51, 0x46, 0x4b},
                                      {0xd0, 0xdd, 0xca, 0xc7, 0xe4, 0xe9, 0xfe, 0xf3, 0xb8, 0xb5, 0xa2, 0xaf, 0x8c, 0x81, 0x96, 0x9b},
                                      {0xbb, 0xb6, 0xa1, 0xac, 0x8f, 0x82, 0x95, 0x98, 0xd3, 0xde, 0xc9, 0xc4, 0xe7, 0xea, 0xfd, 0xf0},
                                      {0x6b, 0x66, 0x71, 0x7c, 0x5f, 0x52, 0x45, 0x48, 0x03, 0x0e, 0x19, 0x14, 0x37, 0x3a, 0x2d, 0x20},
                                      {0x6d, 0x60, 0x77, 0x7a, 0x59, 0x54, 0x43, 0x4e, 0x05, 0x08, 0x1f, 0x12, 0x31, 0x3c, 0x2b, 0x26},
                                      {0xbd, 0xb0, 0xa7, 0xaa, 0x89, 0x84, 0x93, 0x9e, 0xd5, 0xd8, 0xcf, 0xc2, 0xe1, 0xec, 0xfb, 0xf6},
                                      {0xd6, 0xdb, 0xcc, 0xc1, 0xe2, 0xef, 0xf8, 0xf5, 0xbe, 0xb3, 0xa4, 0xa9, 0x8a, 0x87, 0x90, 0x9d},
                                      {0x06, 0x0b, 0x1c, 0x11, 0x32, 0x3f, 0x28, 0x25, 0x6e, 0x63, 0x74, 0x79, 0x5a, 0x57, 0x40, 0x4d},
                                      {0xda, 0xd7, 0xc0, 0xcd, 0xee, 0xe3, 0xf4, 0xf9, 0xb2, 0xbf, 0xa8, 0xa5, 0x86, 0x8b, 0x9c, 0x91},
                                      {0x0a, 0x07, 0x10, 0x1d, 0x3e, 0x33, 0x24, 0x29, 0x62, 0x6f, 0x78, 0x75, 0x56, 0x5b, 0x4c, 0x41},
                                      {0x61, 0x6c, 0x7b, 0x76, 0x55, 0x58, 0x4f, 0x42, 0x09, 0x04, 0x13, 0x1e, 0x3d, 0x30, 0x27, 0x2a},
                                      {0xb1, 0xbc, 0xab, 0xa6, 0x85, 0x88, 0x9f, 0x92, 0xd9, 0xd4, 0xc3, 0xce, 0xed, 0xe0, 0xf7, 0xfa},
                                      {0xb7, 0xba, 0xad, 0xa0, 0x83, 0x8e, 0x99, 0x94, 0xdf, 0xd2, 0xc5, 0xc8, 0xeb, 0xe6, 0xf1, 0xfc},
                                      {0x67, 0x6a, 0x7d, 0x70, 0x53, 0x5e, 0x49, 0x44, 0x0f, 0x02, 0x15, 0x18, 0x3b, 0x36, 0x21, 0x2c},
                                      {0x0c, 0x01, 0x16, 0x1b, 0x38, 0x35, 0x22, 0x2f, 0x64, 0x69, 0x7e, 0x73, 0x50, 0x5d, 0x4a, 0x47},
                                      {0xdc, 0xd1, 0xc6, 0xcb, 0xe8, 0xe5, 0xf2, 0xff, 0xb4, 0xb9, 0xae, 0xa3, 0x80, 0x8d, 0x9a, 0x97}
};

std::vector<std::vector<int>> mul14 = {
                                      {0x00, 0x0e, 0x1c, 0x12, 0x38, 0x36, 0x24, 0x2a, 0x70, 0x7e, 0x6c, 0x62, 0x48, 0x46, 0x54, 0x5a},
                                      {0xe0, 0xee, 0xfc, 0xf2, 0xd8, 0xd6, 0xc4, 0xca, 0x90, 0x9e, 0x8c, 0x82, 0xa8, 0xa6, 0xb4, 0xba},
                                      {0xdb, 0xd5, 0xc7, 0xc9, 0xe3, 0xed, 0xff, 0xf1, 0xab, 0xa5, 0xb7, 0xb9, 0x93, 0x9d, 0x8f, 0x81},
                                      {0x3b, 0x35, 0x27, 0x29, 0x03, 0x0d, 0x1f, 0x11, 0x4b, 0x45, 0x57, 0x59, 0x73, 0x7d, 0x6f, 0x61},
                                      {0xad, 0xa3, 0xb1, 0xbf, 0x95, 0x9b, 0x89, 0x87, 0xdd, 0xd3, 0xc1, 0xcf, 0xe5, 0xeb, 0xf9, 0xf7},
                                      {0x4d, 0x43, 0x51, 0x5f, 0x75, 0x7b, 0x69, 0x67, 0x3d, 0x33, 0x21, 0x2f, 0x05, 0x0b, 0x19, 0x17},
                                      {0x76, 0x78, 0x6a, 0x64, 0x4e, 0x40, 0x52, 0x5c, 0x06, 0x08, 0x1a, 0x14, 0x3e, 0x30, 0x22, 0x2c},
                                      {0x96, 0x98, 0x8a, 0x84, 0xae, 0xa0, 0xb2, 0xbc, 0xe6, 0xe8, 0xfa, 0xf4, 0xde, 0xd0, 0xc2, 0xcc},
                                      {0x41, 0x4f, 0x5d, 0x53, 0x79, 0x77, 0x65, 0x6b, 0x31, 0x3f, 0x2d, 0x23, 0x09, 0x07, 0x15, 0x1b},
                                      {0xa1, 0xaf, 0xbd, 0xb3, 0x99, 0x97, 0x85, 0x8b, 0xd1, 0xdf, 0xcd, 0xc3, 0xe9, 0xe7, 0xf5, 0xfb},
                                      {0x9a, 0x94, 0x86, 0x88, 0xa2, 0xac, 0xbe, 0xb0, 0xea, 0xe4, 0xf6, 0xf8, 0xd2, 0xdc, 0xce, 0xc0},
                                      {0x7a, 0x74, 0x66, 0x68, 0x42, 0x4c, 0x5e, 0x50, 0x0a, 0x04, 0x16, 0x18, 0x32, 0x3c, 0x2e, 0x20},
                                      {0xec, 0xe2, 0xf0, 0xfe, 0xd4, 0xda, 0xc8, 0xc6, 0x9c, 0x92, 0x80, 0x8e, 0xa4, 0xaa, 0xb8, 0xb6},
                                      {0x0c, 0x02, 0x10, 0x1e, 0x34, 0x3a, 0x28, 0x26, 0x7c, 0x72, 0x60, 0x6e, 0x44, 0x4a, 0x58, 0x56},
                                      {0x37, 0x39, 0x2b, 0x25, 0x0f, 0x01, 0x13, 0x1d, 0x47, 0x49, 0x5b, 0x55, 0x7f, 0x71, 0x63, 0x6d},
                                      {0xd7, 0xd9, 0xcb, 0xc5, 0xef, 0xe1, 0xf3, 0xfd, 0xa7, 0xa9, 0xbb, 0xb5, 0x9f, 0x91, 0x83, 0x8d}
};

void ExpandKey(std::string initialKey, int array[4][44])
{
  std::vector<int> key_vec = {};
  int expandedKey[4][44];
  int w0[4];
  int w1[4];
  int w2[4];
  int w3[4];
  int w4[4];
  int w5[4];
  int w6[4];
  int w7[4];
  int rotw3[4];
  int g_w3[4];
  int division;
  int remainder;
  int iter = 0;
  int tempXor1;
  int tempXor2;

  //converts hex string to vector<int>
  for (int i = 0; i < initialKey.length()/2; i++)
  {
      std::string temp = initialKey.substr(i*2,2);
      long n = strtol(temp.c_str(),NULL, 16);
      key_vec.push_back(n);
  }

  //adds intial key into the expanded key vector
  int temp_counter = 0;
  for (int i = 0; i < 4; i++)
  {
      for (int j = 0; j < 4; j++)
      {
          expandedKey[j][i] = key_vec[temp_counter];
          temp_counter++;
      }
  }
  
  //expanding key for loop/function
  for (int i = 0; i < 40 /*expandedkey column size*/; i+=4)
  {
      //filling Word 0 with the first i*4 bytes
      for (int j = 0; j < 4; j++)
      {
          w0[j] = expandedKey[j][i];
      }
      
      //filling Word 1 with the second i*4 bytes
      for (int j = 0; j < 4; j++)
      {
          w1[j] = expandedKey[j][i+1];
      }
      
      //filling Word 2 with the third i*4 bytes
      for (int j = 0; j < 4; j++)
      {
          w2[j] = expandedKey[j][i+2];
      }
      
      //filling Word 3 with the fourth i*4 bytes
      for (int j = 0; j < 4; j++)
      {
          w3[j] = expandedKey[j][i+3];
      }

      //rotates w3 into rotw3
      for (int j = 0; j < 4; j++)
      {
          if (j == 3)
          {
              rotw3[j] = w3[j-3];
          }
          else
              rotw3[j] = w3[j+1];
      }

      //calculates subbyte
      for (int j = 0; j < 4; j++)
      {
          division = rotw3[j] / 16;
          remainder = rotw3[j] % 16;
          g_w3[j] = s_box[division][remainder];
      }

      //XOR with Round Constant
      int tempXOR1 = g_w3[0];
      int tempXOR2 = RCON_vec[iter][0];
      g_w3[0] = tempXOR1 ^ tempXOR2; 
      iter++;
      
      //generates the next 4 subkeys (1 full keyround)
      for (int j = 0; j < 4; j++)
      {
          tempXOR1 = w0[j];
          tempXOR2 = g_w3[j];
          w4[j] = tempXOR1 ^ tempXOR2;

          tempXOR1 = w4[j];
          tempXOR2 = w1[j];
          w5[j] = tempXOR1 ^ tempXOR2;

          tempXOR1 = w5[j];
          tempXOR2 = w2[j];
          w6[j] = tempXOR1 ^ tempXOR2;

          tempXOR1 = w6[j];
          tempXOR2 = w3[j];
          w7[j] = tempXOR1 ^ tempXOR2;
      }
      
      //adds the newly generated keys into the new words in the expandedKey vector
      for (int j = 0; j < 4; j++)
      {
          for (int k = 0; k < 4; k++)
          {
              expandedKey[k][i+4] = w4[k];
              expandedKey[k][i+5] = w5[k];
              expandedKey[k][i+6] = w6[k];
              expandedKey[k][i+7] = w7[k];
          }
      }
  
  }

  //sends full expanded key back to where function was called
  for (int i = 0; i < 44; i++)
  {
      for (int j = 0; j < 4; j++)
      {
        array[j][i] = expandedKey[j][i];
      }
  }

  // outputs full expanded key
  // int tempCounter2 = 0;
  // int roundCounter = 0;
  // for (int i = 0; i < 44; i++)
  // {
  //   if (tempCounter2 % 16 == 0)
  //   {
  //     std::cout << "Round " << std::dec << roundCounter << ":\n";
  //     roundCounter++;
  //   }
  //   for (int j = 0; j < 4; j++)
  //   {
  //     std::cout << std::hex << expandedKey[j][i] << "\t";
  //     tempCounter2++;
  //   }
  //   std::cout << std::endl;
  // }
}

// function to print array 
void print4x4Array(int array[4][4])
{
  for (int j = 0; j < 4; j++)
  {
    for (int k = 0; k < 4; k++)
    {
      std::cout << std::hex << array[k][j] << "\t";
    }
    std::cout << std::endl;
  }
}

// function to copy array 
void copy4x4Array(int src[4][4], int dest[4][4])
{
  for (int j = 0; j < 4; j++)
  {
    for (int k = 0; k < 4; k++)
    {
      dest[j][k] = src[j][k];
    }
  }
}

// use this function to check that it is correct 
void EncryptAES128Bit(std::string plainText, int expandedKeyArray[4][44], int encryptedArray[4][4])
{
  // encrypting a 128bit block of text
  std::vector<int> temp_Vec;
  std::vector<int> tempXorVec;
  int text_Array[4][4];
  int Temp_Array[4][4];
  int tmp[4][4];
  int division1;
  int remainder1;
  int tempXor1;
  int tempXor2;

  // converts hex string to vector<int>
  for (int i = 0; i < plainText.length() / 2; i++)
  {
    std::string temp = plainText.substr(i * 2, 2);
    long n = strtol(temp.c_str(), NULL, 16);
    temp_Vec.push_back(n);
  }

  // adds initial text into the state array
  int temp_counter = 0;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      text_Array[j][i] = temp_Vec[temp_counter];
      temp_counter++;
    }
  }

  // std::cout << "Original State Array: " << std::endl;
  // print4x4Array(text_Array);

  // Repeating for each of the 10 Rounds
  for (int i = 0; i < 10; i++)
  {
    // printing Key Round
    // std::cout << "Key Round: " << std::dec << i << std::endl;
    // for (int j = 0; j < 4; j++)
    // {
    //   for (int k = 0; k < 4; k++)
    //   {
    //     std::cout << std::hex << expandedKeyArray[k][i * 4 + j] << "\t";
    //   }
    //   std::cout << std::endl;
    // }

    // XOR State Array with Round Key
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        tempXor1 = text_Array[k][j];
        tempXor2 = expandedKeyArray[k][i * 4 + j];
        text_Array[k][j] = tempXor1 ^ tempXor2;
      }
    }

    // std::cout << "State Array XOR w/ Round Key: " << std::endl;
    // print4x4Array(text_Array);

    // performing SubByte switch - SBOX
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        division1 = text_Array[k][j] / 16;
        remainder1 = text_Array[k][j] % 16;
        text_Array[k][j] = s_box[division1][remainder1];
      }
    }

    // std::cout << "State Array SubByte Switch: " << std::endl;
    // print4x4Array(text_Array);

    // Shift Row Operation- Permutation 
    for (int j = 1; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        if (j == 1)
        {
          if (k == 3)
          {
            Temp_Array[j][k] = text_Array[j][k - 3];
          }
          else
            Temp_Array[j][k] = text_Array[j][k + j];
        }
        if (j == 2)
        {
          if (k == 2 || k == 3)
          {
            Temp_Array[j][k] = text_Array[j][k - 2];
          }
          else
            Temp_Array[j][k] = text_Array[j][k + j];
        }
        if (j == 3)
        {
          if (k == 1 || k == 2 || k == 3)
          {
            Temp_Array[j][k] = text_Array[j][k - 1];
          }
          else
            Temp_Array[j][k] = text_Array[j][k + j];
        }
      }
    }

    // copy4x4Array(Temp_Array, text_Array);
    for (int j = 1; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        text_Array[j][k] = Temp_Array[j][k];
      }
    }

    // std::cout << "State Array Shift Row Op: " << std::endl;
    // print4x4Array(text_Array);

    // Mix Column Step
    if (i != 9)
    {
      int fixedMatrix[4][4] = {
          {2, 3, 1, 1},
          {1, 2, 3, 1},
          {1, 1, 2, 3},
          {3, 1, 1, 2}};

      tmp[0][0] = mul2[text_Array[0][0] / 16][text_Array[0][0] % 16] ^ mul3[text_Array[1][0] / 16][text_Array[1][0] % 16] ^ text_Array[2][0] ^ text_Array[3][0];
      tmp[1][0] = text_Array[0][0] ^ mul2[text_Array[1][0] / 16][text_Array[1][0] % 16] ^ mul3[text_Array[2][0] / 16][text_Array[2][0] % 16] ^ text_Array[3][0];
      tmp[2][0] = text_Array[0][0] ^ text_Array[1][0] ^ mul2[text_Array[2][0] / 16][text_Array[2][0] % 16] ^ mul3[text_Array[3][0] / 16][text_Array[3][0] % 16];
      tmp[3][0] = mul3[text_Array[0][0] / 16][text_Array[0][0] % 16] ^ text_Array[1][0] ^ text_Array[2][0] ^ mul2[text_Array[3][0] / 16][text_Array[3][0] % 16];

      tmp[0][1] = mul2[text_Array[0][1] / 16][text_Array[0][1] % 16] ^ mul3[text_Array[1][1] / 16][text_Array[1][1] % 16] ^ text_Array[2][1] ^ text_Array[3][1];
      tmp[1][1] = text_Array[0][1] ^ mul2[text_Array[1][1] / 16][text_Array[1][1] % 16] ^ mul3[text_Array[2][1] / 16][text_Array[2][1] % 16] ^ text_Array[3][1];
      tmp[2][1] = text_Array[0][1] ^ text_Array[1][1] ^ mul2[text_Array[2][1] / 16][text_Array[2][1] % 16] ^ mul3[text_Array[3][1] / 16][text_Array[3][1] % 16];
      tmp[3][1] = mul3[text_Array[0][1] / 16][text_Array[0][1] % 16] ^ text_Array[1][1] ^ text_Array[2][1] ^ mul2[text_Array[3][1] / 16][text_Array[3][1] % 16];

      tmp[0][2] = mul2[text_Array[0][2] / 16][text_Array[0][2] % 16] ^ mul3[text_Array[1][2] / 16][text_Array[1][2] % 16] ^ text_Array[2][2] ^ text_Array[3][2];
      tmp[1][2] = text_Array[0][2] ^ mul2[text_Array[1][2] / 16][text_Array[1][2] % 16] ^ mul3[text_Array[2][2] / 16][text_Array[2][2] % 16] ^ text_Array[3][2];
      tmp[2][2] = text_Array[0][2] ^ text_Array[1][2] ^ mul2[text_Array[2][2] / 16][text_Array[2][2] % 16] ^ mul3[text_Array[3][2] / 16][text_Array[3][2] % 16];
      tmp[3][2] = mul3[text_Array[0][2] / 16][text_Array[0][2] % 16] ^ text_Array[1][2] ^ text_Array[2][2] ^ mul2[text_Array[3][2] / 16][text_Array[3][2] % 16];

      tmp[0][3] = mul2[text_Array[0][3] / 16][text_Array[0][3] % 16] ^ mul3[text_Array[1][3] / 16][text_Array[1][3] % 16] ^ text_Array[2][3] ^ text_Array[3][3];
      tmp[1][3] = text_Array[0][3] ^ mul2[text_Array[1][3] / 16][text_Array[1][3] % 16] ^ mul3[text_Array[2][3] / 16][text_Array[2][3] % 16] ^ text_Array[3][3];
      tmp[2][3] = text_Array[0][3] ^ text_Array[1][3] ^ mul2[text_Array[2][3] / 16][text_Array[2][3] % 16] ^ mul3[text_Array[3][3] / 16][text_Array[3][3] % 16];
      tmp[3][3] = mul3[text_Array[0][3] / 16][text_Array[0][3] % 16] ^ text_Array[1][3] ^ text_Array[2][3] ^ mul2[text_Array[3][3] / 16][text_Array[3][3] % 16];

      copy4x4Array(tmp, text_Array);

      // std::cout << ("State Array Mixed Columns: \n");
      // print4x4Array(text_Array);
    }
    else if (i == 9)
    {
      for (int j = 0; j < 4; j++)
      {
        for (int k = 0; k < 4; k++)
        {
          tempXor1 = text_Array[k][j];
          tempXor2 = expandedKeyArray[k][40 + j];
          text_Array[k][j] = tempXor1 ^ tempXor2;
        }
      }
      // std::cout << "Final Encrypted Text\n";
      // print4x4Array(text_Array);
    }

    //sends encrypted text array back to function call
    copy4x4Array(text_Array, encryptedArray);

  }
}

void DecryptAES128Bit(std::string encryptedText, int expandedKeyArray[4][44], int decryptedArray[4][4])
{
  std::vector<int> temp_Vec;
  std::vector<int> tempXorVec;
  int text_Array[4][4];
  int Temp_Array[4][4];
  int tmp[4][4];
  int tempXor1;
  int tempXor2;
  int division1;
  int remainder1;

  // converts hex string to vector<int>
  for (int i = 0; i < encryptedText.length() / 2; i++)
  {
    std::string temp = encryptedText.substr(i * 2, 2);
    long n = strtol(temp.c_str(), NULL, 16);
    temp_Vec.push_back(n);
  }

  // adds initial text into the state array
  int temp_counter = 0;
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      text_Array[j][i] = temp_Vec[temp_counter];
      temp_counter++;
    }
  }

  // std::cout << "Original State Array: " << std::endl;
  // print4x4Array(text_Array);

  // descending from 10 to 0 bc we're going backwards for decrypting 
  for (int i = 10; i > 0; i--)
  {
    // doing this step first bc at the end of the 10th step, we do not have to do column matrix 
    // only doing xor for 10th step but actually its the 1st step for decrypting 
    if (i == 10)
    {
      // printing Key Round
      // std::cout << "Key Round: " << std::dec << i << std::endl;
      // for (int j = 0; j < 4; j++)
      // {
      //   for (int k = 0; k < 4; k++)
      //   {
      //     // std::cout << std::hex << expandedKeyArray[k][i * 4 + j] << "\t";
      //   }
      //   // std::cout << std::endl;
      // }

      //XOR with Round Key
      for (int j = 0; j < 4; j++)
      {
        for (int k = 0; k < 4; k++)
        {
          tempXor1 = text_Array[k][j];
          tempXor2 = expandedKeyArray[k][i * 4 + j];
          text_Array[k][j] = tempXor1 ^ tempXor2;
        }
      }
      // std::cout << "State Array XOR w/ Round Key: " << std::endl;
      // print4x4Array(text_Array);
    }

    // Shift Row Operation - permutation 
    for (int j = 1; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        if (j == 1)
        {
          if (k == 3)
          {
            Temp_Array[j][k - 3] = text_Array[j][k];
          }
          else
          {
            Temp_Array[j][k + j] = text_Array[j][k];
          }
        }
        if (j == 2)
        {
          if (k == 2 || k == 3)
          {
            Temp_Array[j][k - 2] = text_Array[j][k];
          }
          else
          {
            Temp_Array[j][k + j] = text_Array[j][k];
          }
        }
        if (j == 3)
        {
          if (k == 1 || k == 2 || k == 3)
          {
            Temp_Array[j][k - 1] = text_Array[j][k];
          }
          else
          {
            Temp_Array[j][k + j] = text_Array[j][k];
          }
        }
      }
    }

    // keeping temp so it doesnt get messed up 
    for (int j = 1; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        text_Array[j][k] = Temp_Array[j][k];
      }
    }

    // std::cout << "State Array Shift Row Op: " << std::endl;
    // print4x4Array(text_Array);

    // performing SubByte switch - s box 
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        division1 = text_Array[k][j] / 16;
        remainder1 = text_Array[k][j] % 16;
        text_Array[k][j] = s_boxINVERSE[division1][remainder1];
      }
    }

    // std::cout << "State Array SubByte Switch: " << std::endl;
    // print4x4Array(text_Array);

    // printing Key Round
    // std::cout << "Key Round: " << std::dec << i - 1 << std::endl;
    // for (int j = 0; j < 4; j++)
    // {
    //   for (int k = 0; k < 4; k++)
    //   {
    //     // std::cout << std::hex << expandedKeyArray[k][(i - 1) * 4 + j] << "\t";
    //   }
    //   // std::cout << std::endl;
    // }

    //XOR with Round Key
    for (int j = 0; j < 4; j++)
    {
      for (int k = 0; k < 4; k++)
      {
        tempXor1 = text_Array[k][j];
        tempXor2 = expandedKeyArray[k][(i - 1) * 4 + j];
        text_Array[k][j] = tempXor1 ^ tempXor2;
      }
    }

    if (i == 1)
    {
      // std::cout << "Final Decrypted Array: " << std::endl;
      // sends encrypted text array back to function call
      copy4x4Array(text_Array, decryptedArray);
    }
    else
    {
      // std::cout << "State Array XOR w/ Round Key: " << std::endl;
    }
    
    // print4x4Array(text_Array);

    if (i != 1)
    {
      // Mix Column Step
      int fixedMatrix[4][4] = {
          {14, 11, 13, 9},
          {9, 14, 11, 13},
          {13, 9, 14, 11},
          {11, 13, 9, 14}};

      tmp[0][0] = mul14[text_Array[0][0] / 16][text_Array[0][0] % 16] ^ mul11[text_Array[1][0] / 16][text_Array[1][0] % 16] ^ mul13[text_Array[2][0] / 16][text_Array[2][0] % 16] ^ mul9[text_Array[3][0] / 16][text_Array[3][0] % 16];
      tmp[1][0] = mul9[text_Array[0][0] / 16][text_Array[0][0] % 16] ^ mul14[text_Array[1][0] / 16][text_Array[1][0] % 16] ^ mul11[text_Array[2][0] / 16][text_Array[2][0] % 16] ^ mul13[text_Array[3][0] / 16][text_Array[3][0] % 16];
      tmp[2][0] = mul13[text_Array[0][0] / 16][text_Array[0][0] % 16] ^ mul9[text_Array[1][0] / 16][text_Array[1][0] % 16] ^ mul14[text_Array[2][0] / 16][text_Array[2][0] % 16] ^ mul11[text_Array[3][0] / 16][text_Array[3][0] % 16];
      tmp[3][0] = mul11[text_Array[0][0] / 16][text_Array[0][0] % 16] ^ mul13[text_Array[1][0] / 16][text_Array[1][0] % 16] ^ mul9[text_Array[2][0] / 16][text_Array[2][0] % 16] ^ mul14[text_Array[3][0] / 16][text_Array[3][0] % 16];

      tmp[0][1] = mul14[text_Array[0][1] / 16][text_Array[0][1] % 16] ^ mul11[text_Array[1][1] / 16][text_Array[1][1] % 16] ^ mul13[text_Array[2][1] / 16][text_Array[2][1] % 16] ^ mul9[text_Array[3][1] / 16][text_Array[3][1] % 16];
      tmp[1][1] = mul9[text_Array[0][1] / 16][text_Array[0][1] % 16] ^ mul14[text_Array[1][1] / 16][text_Array[1][1] % 16] ^ mul11[text_Array[2][1] / 16][text_Array[2][1] % 16] ^ mul13[text_Array[3][1] / 16][text_Array[3][1] % 16];
      tmp[2][1] = mul13[text_Array[0][1] / 16][text_Array[0][1] % 16] ^ mul9[text_Array[1][1] / 16][text_Array[1][1] % 16] ^ mul14[text_Array[2][1] / 16][text_Array[2][1] % 16] ^ mul11[text_Array[3][1] / 16][text_Array[3][1] % 16];
      tmp[3][1] = mul11[text_Array[0][1] / 16][text_Array[0][1] % 16] ^ mul13[text_Array[1][1] / 16][text_Array[1][1] % 16] ^ mul9[text_Array[2][1] / 16][text_Array[2][1] % 16] ^ mul14[text_Array[3][1] / 16][text_Array[3][1] % 16];

      tmp[0][2] = mul14[text_Array[0][2] / 16][text_Array[0][2] % 16] ^ mul11[text_Array[1][2] / 16][text_Array[1][2] % 16] ^ mul13[text_Array[2][2] / 16][text_Array[2][2] % 16] ^ mul9[text_Array[3][2] / 16][text_Array[3][2] % 16];
      tmp[1][2] = mul9[text_Array[0][2] / 16][text_Array[0][2] % 16] ^ mul14[text_Array[1][2] / 16][text_Array[1][2] % 16] ^ mul11[text_Array[2][2] / 16][text_Array[2][2] % 16] ^ mul13[text_Array[3][2] / 16][text_Array[3][2] % 16];
      tmp[2][2] = mul13[text_Array[0][2] / 16][text_Array[0][2] % 16] ^ mul9[text_Array[1][2] / 16][text_Array[1][2] % 16] ^ mul14[text_Array[2][2] / 16][text_Array[2][2] % 16] ^ mul11[text_Array[3][2] / 16][text_Array[3][2] % 16];
      tmp[3][2] = mul11[text_Array[0][2] / 16][text_Array[0][2] % 16] ^ mul13[text_Array[1][2] / 16][text_Array[1][2] % 16] ^ mul9[text_Array[2][2] / 16][text_Array[2][2] % 16] ^ mul14[text_Array[3][2] / 16][text_Array[3][2] % 16];

      tmp[0][3] = mul14[text_Array[0][3] / 16][text_Array[0][3] % 16] ^ mul11[text_Array[1][3] / 16][text_Array[1][3] % 16] ^ mul13[text_Array[2][3] / 16][text_Array[2][3] % 16] ^ mul9[text_Array[3][3] / 16][text_Array[3][3] % 16];
      tmp[1][3] = mul9[text_Array[0][3] / 16][text_Array[0][3] % 16] ^ mul14[text_Array[1][3] / 16][text_Array[1][3] % 16] ^ mul11[text_Array[2][3] / 16][text_Array[2][3] % 16] ^ mul13[text_Array[3][3] / 16][text_Array[3][3] % 16];
      tmp[2][3] = mul13[text_Array[0][3] / 16][text_Array[0][3] % 16] ^ mul9[text_Array[1][3] / 16][text_Array[1][3] % 16] ^ mul14[text_Array[2][3] / 16][text_Array[2][3] % 16] ^ mul11[text_Array[3][3] / 16][text_Array[3][3] % 16];
      tmp[3][3] = mul11[text_Array[0][3] / 16][text_Array[0][3] % 16] ^ mul13[text_Array[1][3] / 16][text_Array[1][3] % 16] ^ mul9[text_Array[2][3] / 16][text_Array[2][3] % 16] ^ mul14[text_Array[3][3] / 16][text_Array[3][3] % 16];

      copy4x4Array(tmp, text_Array);

      // std::cout << ("State Array Mixed Columns: \n");
      // print4x4Array(text_Array);
    }
  }
}

std::string hexArraytoAscii(int hexArray[4][4])
{
  std::string asciiString = "";
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      char b = hexArray[j][i];
      std::string c(1, b);
      asciiString.append(c);
    }
  }
  // std::cout << "Hex Array Converted to ASCII: " << std::endl;
  // std::cout << asciiString << std::endl;

  return asciiString;
}
