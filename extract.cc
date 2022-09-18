#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>

using namespace std;
int DecToHexDec(int dec, int);
char hexaDecNum[50];
string messageData[5];
string arrangeHex(int i);

template <size_t N>

//Split string and add to array
void splitString(string (&arr)[N], string str)
{
    int n = 0;
    istringstream iss(str);
    for (auto it = istream_iterator<string>(iss); it != istream_iterator<string>() && n < N; ++it, ++n)
        arr[n] = *it;
}

//Use to check start 
bool startswith(const string& str, const string& cmp)
{
  return str.compare(0, cmp.length(), cmp) == 0;
}

//Extract messages and signals from dbc file into dbcConfig.txt file 
void extractMessageSignal(string dbcFile){
    // Extract messages and signals from dbc file
    string line; 
    // Change input file whenever change dbc file
    ifstream myfile (dbcFile);
    if (myfile.is_open())
    {   
        //Clear content in CAN_config.txt
        string outputFile = "CAN_config.txt";
        ofstream ofs;
        ofs.open(outputFile, std::ofstream::out | std::ofstream::trunc);
        ofs.close();
        //Read line in dbcConfig
        while (getline (myfile, line))
        {   
            string signalData[8];
            if (startswith(line,"BO_")){
                string message = "" + line;
                splitString(messageData,message);
                ofstream dbcfile(outputFile, ios::app);
            }else if (startswith(line," SG_")) {
                string signal = "" + line;
                splitString(signalData,signal);
                ofstream dbcfile(outputFile, ios::app);
                int i;
                int decimalNum1 = stoi(messageData[1]);
                i = DecToHexDec(decimalNum1,0);
                cout << arrangeHex(i) <<endl;
                dbcfile <<"0x" << arrangeHex(i) << " " << messageData[3] << " "
                        << signalData[1] << " " << signalData[3] << " "
                        << signalData[4] << " "  << " \n";
            }
        }
        myfile.close();
    }
    else{
        cout << "Unable to open file " + dbcFile;
    }   
}


int main(){

    // // Change dbcFile name when have new dbc file
    string dbcFile = "can_newdb.dbc";
    extractMessageSignal(dbcFile);
    int i;
    return 0;
}

int DecToHexDec(int dec, int i){
    int rem;
    while(dec!=0)
    {
        rem = dec%16;
        if(rem<10)
            rem = rem+48;
        else
            rem = rem+55;
        hexaDecNum[i] = rem;
        i++;
        dec = dec/16;
    }
    return i;
}

string arrangeHex(int i){
    string temp ;
    for(i=i-1; i>=0; i--){
       
        temp += hexaDecNum[i];}
   
    return temp;
}
