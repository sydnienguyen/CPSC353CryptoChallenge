#include <iostream>
#include <string.h>
#include <vector>
#include <algorithm>
#include "functions.h"
using namespace std;

vector<string> ExpandKey(const vector<string> &key,int num);
string XORHexStrings(string first, string second);

int main()
{

    vector<string> Initial_key_vector;
    vector<string> Round1_key_vector;
    vector<string> Round2_key_vector;
    vector<string> Round3_key_vector;
    vector<string> Round4_key_vector;
    vector<string> Round5_key_vector;
    vector<string> Round6_key_vector;
    vector<string> Round7_key_vector;
    vector<string> Round8_key_vector;
    vector<string> Round9_key_vector;
    vector<string> Round10_key_vector;

    string key_hex = "5468617473206D79204B756E67204675";
//    string key_hex = "59454C4C4F57205355424D4152494E45";

    for (int i = 0; i < key_hex.length()/8; i++)
    {
        Initial_key_vector.push_back(key_hex.substr(i*8,8));
    }

    Round1_key_vector = ExpandKey(Initial_key_vector,0);

    for(int i = 0; i < Round1_key_vector.size(); i++)
    {
        cout << Round1_key_vector[i] << "\t";
    }

    cout << endl;

    Round2_key_vector = ExpandKey(Round1_key_vector,1);

    for(int i = 0; i < Round2_key_vector.size(); i++)
    {
        cout << Round2_key_vector[i] << "\t";
    }

    cout << endl;

    Round3_key_vector = ExpandKey(Round2_key_vector,2);

    for(int i = 0; i < Round3_key_vector.size(); i++)
    {
        cout << Round3_key_vector[i] << "\t";
    }

    cout << endl;

    Round4_key_vector = ExpandKey(Round3_key_vector,3);

    for(int i = 0; i < Round4_key_vector.size(); i++)
    {
        cout << Round4_key_vector[i] << "\t";
    }

    cout << endl;

    Round5_key_vector = ExpandKey(Round4_key_vector,4);

    for(int i = 0; i < Round5_key_vector.size(); i++)
    {
        cout << Round5_key_vector[i] << "\t";
    }

    cout << endl;

    Round6_key_vector = ExpandKey(Round5_key_vector,5);

    for(int i = 0; i < Round6_key_vector.size(); i++)
    {
        cout << Round6_key_vector[i] << "\t";
    }

    cout << endl;

    Round7_key_vector = ExpandKey(Round6_key_vector,6);

    for(int i = 0; i < Round7_key_vector.size(); i++)
    {
        cout << Round7_key_vector[i] << "\t";
    }

    cout << endl;

    Round8_key_vector = ExpandKey(Round7_key_vector,7);

    for(int i = 0; i < Round8_key_vector.size(); i++)
    {
        cout << Round8_key_vector[i] << "\t";
    }

    cout << endl;

    Round9_key_vector = ExpandKey(Round8_key_vector,8);

    for(int i = 0; i < Round9_key_vector.size(); i++)
    {
        cout << Round9_key_vector[i] << "\t";
    }

    cout << endl;

    Round10_key_vector = ExpandKey(Round9_key_vector,9);

    for(int i = 0; i < Round10_key_vector.size(); i++)
    {
        cout << Round10_key_vector[i] << "\t";
    }

    cout << endl;   
}
