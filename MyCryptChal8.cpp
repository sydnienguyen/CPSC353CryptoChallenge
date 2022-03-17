/*Detect AES in ECB mode
In this file are a bunch of hex-encoded ciphertexts.

One of them has been encrypted with ECB.

Detect it.

Remember that the problem with ECB is that it is stateless and deterministic; the same 16 byte plaintext block will always produce the same 16 byte ciphertext.
*/
#include <iostream>
#include <vector>
#include <fstream>
using namespace std;

int main(){
    string line;
    ifstream myfile ("data8.txt");
    vector<string> wholeVect; 
    vector<string> block;
    int count[400];
    int tempcount;
    int big = 0;
    int placement = 0;

    //opening file and adding each line into vector
    if (myfile.is_open())
    {
      while ( getline (myfile,line) )
      {
        wholeVect.push_back(line);
      }
      myfile.close();
    }

    // iterate through vector from file 
    for (int s = 0; s < wholeVect.size(); s++)
    {
      // count[s] counts how many block similarities there are  
      count[s] = 0;
      line = wholeVect[s];
      // breaks the line into 16 byte blocks of 32 hex chars 
      for (int i = 0; i < line.length() / 32; i++)
      {
        block.push_back((line.substr(i*32,32)));
        // comparing each block to find similarities 
        for (int j = 0; j < block.size(); j++)
        {
          tempcount = 0;
          for (int k = j; k < block.size(); k++)
          {
            if (block[j] == block[k])
            {
                tempcount++;
            }
          }
          // count will increase if there are more similarities than the previous count 
          if (tempcount > count[s])
          {
            count[s] = tempcount;
          }
        }
      }
      // clearing block in order to take in new block for new line 
      block.clear();
    }

    // calculates biggest block similarities.  biggest = winner 
    big = count[0];
    for(int h = 0; h < wholeVect.size() - 1; h++) 
    {    
      // finds the biggest common block within the line 
      if (big < count[h+1])
      {
          big = count[h+1];
          placement = h+1;
      }
    }

    // print the results 
    cout << endl << "Number of similar blocks : " << big << endl;
    cout << "LINE # : " << placement << endl;
    cout << "DATA : " << wholeVect[placement] << endl << endl;
    return 0; 
}