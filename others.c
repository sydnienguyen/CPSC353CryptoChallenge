
// std::string decToHexa(int n)
// {
//   // char array to store hexadecimal number
//   char hexaDeciNum[100];

//   // counter for hexadecimal number array
//   int i = 0;
//   while (n != 0) {
//     // temporary variable to store remainder
//     int temp = 0;

//     // storing remainder in temp variable.
//     temp = n % 16;

//     // check if temp < 10
//     if (temp < 10) {
//         hexaDeciNum[i] = temp + 48;
//         i++;
//     }
//     else {
//         hexaDeciNum[i] = temp + 55;
//         i++;
//     }

//     n = n / 16;
//   }

//   std::string tempString;
//     for (int j = i - 1; j >= 0; j--)
//     {

//       tempString.push_back((hexaDeciNum[j]));
//     }
//   return tempString;
// }

// std::string XORHexStrings(std::string first, std::string second)
// {
//     std::vector<std::string> tempHexVec1;
//     std::vector<std::string> tempHexVec2;
//     std::vector<int> tempDecVec1;
//     std::vector<int> tempDecVec2;
//     std::string newexpandkey;

//     for (int i = 0; i < second.length()/2; i++)
//     {
//         tempHexVec1.push_back(second.substr(i*2,2));
//         tempHexVec2.push_back(first.substr(i*2,2));
//     }
    
//     for (int i = 0; i < tempHexVec1.size(); i++)
//     {
//         long m = strtol(tempHexVec1[i].c_str(), NULL, 16);
//         tempDecVec1.push_back(m);
//         long n = strtol(tempHexVec2[i].c_str(), NULL, 16);
//         tempDecVec2.push_back(n);
//     }

//     // for (int i = 0; i < tempDecVec1.size(); i++)
//     // {
//     //   std::cout << tempDecVec1[i] << std::endl;
//     // }
    

//     for (int i = 0; i < tempDecVec1.size(); i++)
//     {
//         int tempXOR = tempDecVec1[i] ^ tempDecVec2[i];
//         // std::cout << tempXOR << std::endl;
//         if(tempXOR < 16)
//         {
//           newexpandkey.append("0");
//         }
//         if(tempXOR == 0)
//         {
//           newexpandkey.append("0");
//         }
      
//         newexpandkey.append(decToHexa(tempXOR));
//     }

//     return newexpandkey;
// }

// std::vector<std::string> ExpandKey(const std::vector<std::string> &key, int num)
// {
//     std::vector<std::string> expanded_key_vector;
//     std::vector<int> hextoIntVec;
//     std::vector<int> hextoIntVec2;
//     std::vector<std::string> byteSub;
//     std::vector<std::string> Round1Key;
//     std::string g_w3;
//     std::string w4;
//     std::string w5;
//     std::string w6;
//     std::string w7;

//     for (int i = 0; i < key.size(); i++)
//     {
//         expanded_key_vector.push_back(key[i]);
//     }
    
//     std::string new_w3 = expanded_key_vector[3];
//     rotate(new_w3.begin(), new_w3.begin() + 2, new_w3.end());


//     for(int i = 0; i < new_w3.length(); i++)
//     {
//         long n = strtol(new_w3.substr(i,1).c_str(), NULL, 16);
//         hextoIntVec.push_back(n);
//     }

//     for (int i = 0; i < hextoIntVec.size(); i+=2)
//     {
//         // byteSub.push_back(s_box[hextoIntVec[i]][hextoIntVec[i+1]]);
//     }
    
//     new_w3 = "";

//     for(int i = 0; i < byteSub.size(); i++)
//     {
//         new_w3.append(byteSub[i]);
//     }

//     for(int i = 0; i < new_w3.length(); i+=2)
//     {
//         long n = strtol(new_w3.substr(i,2).c_str(), NULL, 16);
//         hextoIntVec2.push_back(n);
//     }
        
//     //HAVE TO CHANGE RCON[I] DEPENDING ON THE ITERATION

//     for(int i = 0; i < hextoIntVec2.size(); i++)
//     {
//       // std::string temp = RCON_vec[num][i];
//       // long n = strtol(temp.substr(0,2).c_str(), NULL, 16);
//       // int c = hextoIntVec2[i] ^ n;
//       // g_w3.append(decToHexa(c));
//     }


//     w4 = XORHexStrings(g_w3, expanded_key_vector[0]); // change to g_w3
//     Round1Key.push_back(w4);
//     w5 = XORHexStrings(w4, expanded_key_vector[1]);
//     Round1Key.push_back(w5);
//     w6 = XORHexStrings(w5, expanded_key_vector[2]);
//     Round1Key.push_back(w6);
//     w7 = XORHexStrings(w6, expanded_key_vector[3]);
//     Round1Key.push_back(w7);

//     return Round1Key;
// }