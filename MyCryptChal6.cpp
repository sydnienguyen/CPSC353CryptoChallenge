#include <string.h>
#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cmath>
#include <vector>
// #include <algorithm>
// #include <iterator>

#include "functions.h"

using namespace std;

int main(){
    string encoded1 = "";
    string encoded2 = "";
    // orginal input string 
    string initialString = "HUIfTQsPAh9PE048GmllH0kcDk4TAQsHThsBFkU2AB4BSWQgVB0dQzNTTmVSBgBHVBwNRU0HBAxTEjwMHghJGgkRTxRMIRpHKwAFHUdZEQQJAGQmB1MANxYGDBoXQR0BUlQwXwAgEwoFR08SSAhFTmU+Fgk4RQYFCBpGB08fWXh+amI2DB0PQQ1IBlUaGwAdQnQEHgFJGgkRAlJ6f0kASDoAGhNJGk9FSA8dDVMEOgFSGQELQRMGAEwxX1NiFQYHCQdUCxdBFBZJeTM1CxsBBQ9GB08dTnhOSCdSBAcMRVhICEEATyBUCHQLHRlJAgAOFlwAUjBpZR9JAgJUAAELB04CEFMBJhAVTQIHAh9PG054MGk2UgoBCVQGBwlTTgIQUwg7EAYFSQ8PEE87ADpfRyscSWQzT1QCEFMaTwUWEXQMBk0PAg4DQ1JMPU4ALwtJDQhOFw0VVB1PDhxFXigLTRkBEgcKVVN4Tk9iBgELR1MdDAAAFwoFHww6Ql5NLgFBIg4cSTRWQWI1Bk9HKn47CE8BGwFTQjcEBx4MThUcDgYHKxpUKhdJGQZZVCFFVwcDBVMHMUV4LAcKQR0JUlk3TwAmHQdJEwATARNFTg5JFwQ5C15NHQYEGk94dzBDADsdHE4UVBUaDE5JTwgHRTkAUmc6AUETCgYAN1xGYlUKDxJTEUgsAA0ABwcXOwlSGQELQQcbE0c9GioWGgwcAgcHSAtPTgsAABY9C1VNCAINGxgXRHgwaWUfSQcJABkRRU8ZAUkDDTUWF01jOgkRTxVJKlZJJwFJHQYADUgRSAsWSR8KIgBSAAxOABoLUlQwW1RiGxpOCEtUYiROCk8gUwY1C1IJCAACEU8QRSxORTBSHQYGTlQJC1lOBAAXRTpCUh0FDxhUZXhzLFtHJ1JbTkoNVDEAQU4bARZFOwsXTRAPRlQYE042WwAuGxoaAk5UHAoAZCYdVBZ0ChQLSQMYVAcXQTwaUy1SBQsTAAAAAAAMCggHRSQJExRJGgkGAAdHMBoqER1JJ0dDFQZFRhsBAlMMIEUHHUkPDxBPH0EzXwArBkkdCFUaDEVHAQANU29lSEBAWk44G09fDXhxTi0RAk4ITlQbCk0LTx4cCjBFeCsGHEETAB1EeFZVIRlFTi4AGAEORU4CEFMXPBwfCBpOAAAdHUMxVVUxUmM9ElARGgZBAg4PAQQzDB4EGhoIFwoKUDFbTCsWBg0OTwEbRSonSARTBDpFFwsPCwIATxNOPBpUKhMdTh5PAUgGQQBPCxYRdG87TQoPD1QbE0s9GkFiFAUXR0cdGgkADwENUwg1DhdNAQsTVBgXVHYaKkg7TgNHTB0DAAA9DgQACjpFX0BJPQAZHB1OeE5PYjYMAg5MFQBFKjoHDAEAcxZSAwZOBREBC0k2HQxiKwYbR0MVBkVUHBZJBwp0DRMDDk5rNhoGACFVVWUeBU4MRREYRVQcFgAdQnQRHU0OCxVUAgsAK05ZLhdJZChWERpFQQALSRwTMRdeTRkcABcbG0M9Gk0jGQwdR1ARGgNFDRtJeSchEVIDBhpBHQlSWTdPBzAXSQ9HTBsJA0UcQUl5bw0KB0oFAkETCgYANlVXKhcbC0sAGgdFUAIOChZJdAsdTR0HDBFDUk43GkcrAAUdRyonBwpOTkJEUyo8RR8USSkOEENSSDdXRSAdDRdLAA0HEAAeHQYRBDYJC00MDxVUZSFQOV1IJwYdB0dXHRwNAA9PGgMKOwtTTSoBDBFPHU54W04mUhoPHgAdHEQAZGU/OjV6RSQMBwcNGA5SaTtfADsXGUJHWREYSQAnSARTBjsIGwNOTgkVHRYANFNLJ1IIThVIHQYKAGQmBwcKLAwRDB0HDxNPAU94Q083UhoaBkcTDRcAAgYCFkU1RQUEBwFBfjwdAChPTikBSR0TTwRIEVIXBgcURTULFk0OBxMYTwFUN0oAIQAQBwkHVGIzQQAGBR8EdCwRCEkHElQcF0w0U05lUggAAwANBxAAHgoGAwkxRRMfDE4DARYbTn8aKmUxCBsURVQfDVlOGwEWRTIXFwwCHUEVHRcAMlVDKRsHSUdMHQMAAC0dCAkcdCIeGAxOazkABEk2HQAjHA1OAFIbBxNJAEhJBxctDBwKSRoOVBwbTj8aQS4dBwlHKjUECQAaBxscEDMNUhkBC0ETBxdULFUAJQAGARFJGk9FVAYGGlMNMRcXTRoBDxNPeG43TQA7HRxJFUVUCQhBFAoNUwctRQYFDE43PT9SUDdJUydcSWRtcwANFVAHAU5TFjtFGgwbCkEYBhlFeFsABRcbAwZOVCYEWgdPYyARNRcGAQwKQRYWUlQwXwAgExoLFAAcARFUBwFOUwImCgcDDU5rIAcXUj0dU2IcBk4TUh0YFUkASEkcC3QIGwMMQkE9SB8AMk9TNlIOCxNUHQZCAAoAHh1FXjYCDBsFABkOBkk7FgALVQROD0EaDwxOSU8dGgI8EVIBAAUEVA5SRjlUQTYbCk5teRsdRVQcDhkDADBFHwhJAQ8XClJBNl4AC1IdBghVEwARABoHCAdFXjwdGEkDCBMHBgAwW1YnUgAaRyonB0VTGgoZUwE7EhxNCAAFVAMXTjwaTSdSEAESUlQNBFJOZU5LXHQMHE0EF0EABh9FeRp5LQdFTkAZREgMU04CEFMcMQQAQ0lkay0ABwcqXwA1FwgFAk4dBkIACA4aB0l0PD1MSQ8PEE87ADtbTmIGDAILAB0cRSo3ABwBRTYKFhROHUETCgZUMVQHYhoGGksABwdJAB0ASTpFNwQcTRoDBBgDUkksGioRHUkKCE5THEVCC08EEgF0BBwJSQoOGkgGADpfADETDU5tBzcJEFMLTx0bAHQJCx8ADRJUDRdMN1RHYgYGTi5jMURFeQEaSRAEOkURDAUCQRkKUmQ5XgBIKwYbQFIRSBVJGgwBGgtzRRNNDwcVWE8BT3hJVCcCSQwGQx9IBE4KTwwdASEXF01jIgQATwZIPRpXKwYKBkdEGwsRTxxDSToGMUlSCQZOFRwKUkQ5VEMnUh0BR0MBGgAAZDwGUwY7CBdNHB5BFwMdUz0aQSwWSQoITlMcRUILTxoCEDUXF01jNw4BTwVBNlRBYhAIGhNMEUgIRU5CRFMkOhwGBAQLTVQOHFkvUkUwF0lkbXkbHUVUBgAcFA0gRQYFCBpBPU8FQSsaVycTAkJHYhsRSQAXABxUFzFFFggICkEDHR1OPxoqER1JDQhNEUgKTkJPDAUAJhwQAg0XQRUBFgArU04lUh0GDlNUGwpOCU9jeTY1HFJARE4xGA4LACxSQTZSDxsJSw1ICFUdBgpTNjUcXk0OAUEDBxtUPRpCLQtFTgBPVB8NSRoKSREKLUUVAklkERgOCwAsUkE2Ug8bCUsNSAhVHQYKUyI7RQUFABoEVA0dWXQaRy1SHgYOVBFIB08XQ0kUCnRvPgwQTgUbGBwAOVREYhAGAQBJEUgETgpPGR8ELUUGBQgaQRIaHEshGk03AQANR1QdBAkAFwAcUwE9AFxNY2QxGA4LACxSQTZSDxsJSw1ICFUdBgpTJjsIF00GAE1ULB1NPRpPLF5JAgJUVAUAAAYKCAFFXjUeDBBOFRwOBgA+T04pC0kDElMdC0VXBgYdFkU2CgtNEAEUVBwTWXhTVG5SGg8eAB0cRSo+AwgKRSANExlJCBQaBAsANU9TKxFJL0dMHRwRTAtPBRwQMAAATQcBFlRlIkw5QwA2GggaR0YBBg5ZTgIcAAw3SVIaAQcVEU8QTyEaYy0fDE4ITlhIJk8DCkkcC3hFMQIEC0EbAVIqCFZBO1IdBgZUVA4QTgUWSR4QJwwRTWM=";
    //empty string so we can put the input string that's converted to binary 
    string initialBinaryString = "";
    vector<string> initialBinaryVec;
    int keysize = 0;
    int count = 0;
    int stringsFoundCount = 0;


    // ??? 
    float charRatio = 0.59;
    string likelyChars1 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    string likelyChars2 = "abcdefghijklmnopqrstuvwxyz";
    string unlikelyChars = ":@#$%^&*(){}[]`~|/.,<>?;+'";
    vector<double> tempRatios;

    //converts 64 string to binary string
    for (int i = 0; i < initialString.length()/8; i++)
    {
        initialBinaryString.append(Base64toBinary(initialString.substr(i*8,8)));
    }
    //stores binary string to binary vec. each element in the vector is 1 byte(8bits)
    for (int i = 0; i < initialBinaryString.length()/8; i++)
    {
        initialBinaryVec.push_back(initialBinaryString.substr(i*8,8));
    }
    

    while(true)
    {
        double charCount = 0.0;
        double likelyChars1Count = 0.0;
        double likelyChars2Count = 0.0;
        double unlikelyChars1Count = 0.0;
        string finalString;
        string binaryKey = "";
        string binaryString = "";
        string binaryXOR = "";
        string ASCIIXor = "";
        vector<string> transposeVec;

        // gets vector size of binary of input 
        int n=initialBinaryVec.size();

        // asking user for key size
        cout<< "what's the keysize??? ";
        cin>>keysize;
        //clearing out the vector to make sure there aren't past values in it 
        transposeVec.clear();

        //create the vector of keysize element and transpose the bytes of the vector from initialBinaryVec
        for(int i=0;i<n;i++)
        {
            string temp;
            temp.append(initialBinaryVec[i]);
            if (transposeVec.size()<keysize)
            {
                transposeVec.push_back(temp);
            }
            else 
            {
                string temp2;
                temp2= transposeVec[i%keysize]+initialBinaryVec[i];
                transposeVec[i%keysize]=temp2;
            }
        }
        //iterating through keysize
        for (int i = 0; i < keysize; i++)
        {
            //string holds block i 
            string tempTransposeString = transposeVec[i];
            //iterating through ascii chars
            for (int j = 32; j < 128; j++)
            {
                char b = j; //gives ascii of j
                string c(1, b); //converts char to string
                string tempAscii = AsciiToBinary(c); //converts ascii to binary 
                string binaryXOR = ""; 
                string asciiString = "";
                string tempAsciiString = "";
                //xor function loop
                for (int k = 0; k < tempTransposeString.length(); k++)
                {
                    if(tempTransposeString[k] != tempAscii[k%8])
                    {
                        binaryXOR.append("1");
                    }
                    else
                    {
                        binaryXOR.append("0");
                    }
                }
                // convert binaryxor to ascii string
                for (int k = 0; k < binaryXOR.length()/8; k++)
                {

                    string tempXOR = binaryXOR.substr(k*8,8);
                    tempAsciiString = toascii_frombinary(tempXOR.c_str());
                    asciiString.append(tempAsciiString);
                }    
            
                charCount = 0;
                likelyChars1Count = 0;
                likelyChars2Count = 0;
                unlikelyChars1Count = 0;
                // calculating character count
                for (int i = 0; i < asciiString.length(); i++)
                {
                    for (int j = 0; j < likelyChars1.length(); j++)
                    {
                        if (asciiString[i] == likelyChars1[j])
                        {
                            likelyChars1Count++;
                        }
                        if (asciiString[i] == likelyChars2[j])
                        {
                            likelyChars2Count++;
                        }
                        if (asciiString[i] == unlikelyChars[j])
                        {
                            unlikelyChars1Count++;
                        }
                    }
                }
                charCount = likelyChars1Count*0.8 + likelyChars2Count - unlikelyChars1Count;

                double tempRatioCalc = charCount / asciiString.length();
                //stores all ratios in the vector 
                tempRatios.push_back(tempRatioCalc);
            }
                //picks largest element and index 
                double largest_element = tempRatios[0];
                int largest_index = 0;
                for(int p = 1; p < tempRatios.size(); p++)  //start iterating from the second element
                {
                    if(tempRatios[p] > largest_element)
                    {
                    largest_element = tempRatios[p];
                    largest_index = p;
                    }
                }
                int temp_int = largest_index + 32;
                char temp_char = temp_int;
                string temp_string(1, temp_char);
                cout << ("Block ") << i << (" key: ") << temp_string << endl;
                finalString.append(temp_string);
                tempRatios.clear();
        }
        cout << ("The Key is: ") << finalString << endl;
    
        //turns initial string (base64) to binary 
        for (int i = 0; i < initialString.length()/8; i++)
        {
            binaryString.append(Base64toBinary(initialString.substr(i*8,8)));
        }
        //turns ascii to binary 
        for (int i = 0; i < finalString.length(); i++)
        {
            binaryKey.append(AsciiToBinary(finalString.substr(i*1,1)));
        }
        
        // xor initial string (binary) and keyString (binary)
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
    
        for (int i = 0; i < binaryXOR.length()/8; i++)
        {
            ASCIIXor = binaryXOR.substr(i*8,8);

            cout << (toascii_frombinary(ASCIIXor.c_str()));
        }
        cout << endl;
    }
    return 0;
}