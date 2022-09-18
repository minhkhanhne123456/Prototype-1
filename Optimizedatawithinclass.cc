#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
#include <cstdint>
using namespace std;

static int number_of_lines;
//void loadData();
const int SIZE = 1000;
template <size_t N>
//Split string and add to array
void splitString(string (&arr)[N], string str)
{
    int n = 0;
    istringstream iss(str);
    for (auto it = istream_iterator<string>(iss); it != istream_iterator<string>() && n < N; ++it, ++n)
        arr[n] = *it;
}

namespace control{
struct canconfigure1 {
    uint32_t canid;
    uint16_t canlength; 
    string name_variables; 
    uint16_t startbit;    
    uint16_t length;      
    double scale;          
    double offset;
    bool isBigendian;
}canconfigure[SIZE];
};



int main()
    {
     ifstream in("CAN_config1.txt");
    string line1;
    
    while (getline (in, line1))
    {
        
        string splitdata[8];
        string split = "" + line1;
        splitString(splitdata,split);
        //Explicit type conversion
        unsigned int canidconvert = stoi(splitdata[0]);
        unsigned int canlengthconvert = stoi(splitdata[1]);
        unsigned int startbitconvert = stoi(splitdata[3]);
        unsigned int lengthconvert = stoi(splitdata[4]);
        double scaleconvert = stod(splitdata[5]);
        double offsetconvert = stod(splitdata[6]);
        bool endian = false;
        /*cout << canidconvert << " " << canlengthconvert << " " << splitdata[2] << " " << startbitconvert << " " << lengthconvert << " " <<
        offsetconvert << " " << splitdata[7] << endl;
         canlengthconvert;
        */

        control::canconfigure[number_of_lines].canid = canidconvert;
        control::canconfigure[number_of_lines].canlength = canlengthconvert;
        control::canconfigure[number_of_lines].name_variables = splitdata[2];
        control::canconfigure[number_of_lines].startbit = startbitconvert;
        control::canconfigure[number_of_lines].length = lengthconvert;
        control::canconfigure[number_of_lines].scale = scaleconvert;
        control::canconfigure[number_of_lines].offset = offsetconvert;
        control::canconfigure[number_of_lines].isBigendian = endian;

        cout << control::canconfigure [number_of_lines].canid << " ";
        cout << control::canconfigure [number_of_lines].canlength << " ";
        cout << control::canconfigure [number_of_lines].name_variables << " ";
        cout << control::canconfigure [number_of_lines].startbit << " ";
        cout << control::canconfigure [number_of_lines].length << " ";
        cout << control::canconfigure [number_of_lines].scale << " ";
        cout << control::canconfigure [number_of_lines].offset << " ";
        cout << control::canconfigure [number_of_lines].isBigendian << endl;
        
        number_of_lines++;
        //double doubledata[2];
        // array vs linkedlist , enum vs struct vs union
        //intdata[0] = stoi(splitdata[0]);
        //intdata[1] = stoi(splitdata[1]);
        //intdata[2] = stoi(splitdata[3]);
        //intdata[3] = stoi(splitdata[4]);
        //doubledata[0] = stod(splitdata[5]);
        //doubledata[1] = stod(splitdata[6]);
        //Check split data 
        //cout << intdata[0] << " " << intdata[1] << " " << splitdata[2] << " " << intdata[2] << " " << intdata[3] << " " << doubledata[0] << " " <<
        //doubledata[1] << " "  << endl;
        /*cout << intdata[0]; 
        cout << intdata[1]; 
        cout << splitdata[2];
        cout << intdata[2]; 
        cout << intdata[3];
        cout << doubledata[0];
        cout << doubledata[1];
        */
        //cout << doubledata[0];
        //cout << doubledata[1]; 
        // " " << canLength << " " << splitdata[2] << " " << splitdata[3] << " " << splitdata[4] << " " << splitdata[5] << " " << splitdata[6] << " " << splitdata[7] << " " << endl;
        // Create a structure variable and assign values to it using namespace
       


        /*
        Write data to structs without using namespace
        canconfigure1[number_of_lines] = splitdata[0];
        canconfigure1[number_of_lines].canlength = splitdata[1];
        canconfigure1[number_of_lines].startbit = splitdata[2];
        canconfigure1[number_of_lines].length = splitdata[3];
        canconfigure1[number_of_lines].name_variables = splitdata[4];
        canconfigure1[number_of_lines].scale = splitdata[5];
        canconfigure1[number_of_lines].offset =  splitdata[6];
        canconfigure1[number_of_lines].endian =  splitdata[7];

        /*
        //Check data in structs without using namespace
        cout << canconfigure1[number_of_lines].canid << " " << canconfigure1[number_of_lines].canlength << " " << canconfigure1[number_of_lines].startbit  <<
        canconfigure1[number_of_lines].length << " " << canconfigure1[number_of_lines].name_variables << " " << canconfigure1[number_of_lines].scale << " " <<
        canconfigure1[number_of_lines].offset << " " << canconfigure1[number_of_lines].endian << endl;
        number_of_lines++;
        */
    }
    return 0;
    }
    

/*
void loadData()
{   
    ifstream in("CAN_config1.txt");
    string line1;
    
    while (getline (in, line1))
    {
        
        string splitdata[8];
        string split = "" + line1;
        splitString(splitdata,split);
        //Explicit type conversion
        unsigned int canidconvert = stoi(splitdata[0]);
        unsigned int canlengthconvert = stoi(splitdata[1]);
        unsigned int startbitconvert = stoi(splitdata[3]);
        unsigned int lengthconvert = stoi(splitdata[4]);
        double scaleconvert = stod(splitdata[5]);
        double offsetconvert = stod(splitdata[6]);
        bool endian = false;
        /*cout << canidconvert << " " << canlengthconvert << " " << splitdata[2] << " " << startbitconvert << " " << lengthconvert << " " <<
        offsetconvert << " " << splitdata[7] << endl;
         canlengthconvert;
        
        control::canconfigure[number_of_lines].canid = canidconvert;
        control::canconfigure[number_of_lines].canlength = canlengthconvert;
        control::canconfigure[number_of_lines].name_variables = splitdata[2];
        control::canconfigure[number_of_lines].startbit = startbitconvert;
        control::canconfigure[number_of_lines].length = lengthconvert;
        control::canconfigure[number_of_lines].scale = scaleconvert;
        control::canconfigure[number_of_lines].offset = offsetconvert;
        control::canconfigure[number_of_lines].isBigendian = endian;

        cout << control::canconfigure [number_of_lines].canid << " ";
        cout << control::canconfigure [number_of_lines].canlength << " ";
        cout << control::canconfigure [number_of_lines].name_variables << " ";
        cout << control::canconfigure [number_of_lines].startbit << " ";
        cout << control::canconfigure [number_of_lines].length << " ";
        cout << control::canconfigure [number_of_lines].scale << " ";
        cout << control::canconfigure [number_of_lines].offset << " ";
        cout << control::canconfigure [number_of_lines].isBigendian << endl;
        
        number_of_lines++;
        
        //double doubledata[2];
        // array vs linkedlist , enum vs struct vs union
        //intdata[0] = stoi(splitdata[0]);
        //intdata[1] = stoi(splitdata[1]);
        //intdata[2] = stoi(splitdata[3]);
        //intdata[3] = stoi(splitdata[4]);
        //doubledata[0] = stod(splitdata[5]);
        //doubledata[1] = stod(splitdata[6]);
        //Check split data 
        //cout << intdata[0] << " " << intdata[1] << " " << splitdata[2] << " " << intdata[2] << " " << intdata[3] << " " << doubledata[0] << " " <<
        //doubledata[1] << " "  << endl;
        /*cout << intdata[0]; 
        cout << intdata[1]; 
        cout << splitdata[2];
        cout << intdata[2]; 
        cout << intdata[3];
        cout << doubledata[0];
        cout << doubledata[1];
        */
        //cout << doubledata[0];
        //cout << doubledata[1]; 
        // " " << canLength << " " << splitdata[2] << " " << splitdata[3] << " " << splitdata[4] << " " << splitdata[5] << " " << splitdata[6] << " " << splitdata[7] << " " << endl;
        // Create a structure variable and assign values to it using namespace
       


        /*
        Write data to structs without using namespace
        canconfigure1[number_of_lines] = splitdata[0];
        canconfigure1[number_of_lines].canlength = splitdata[1];
        canconfigure1[number_of_lines].startbit = splitdata[2];
        canconfigure1[number_of_lines].length = splitdata[3];
        canconfigure1[number_of_lines].name_variables = splitdata[4];
        canconfigure1[number_of_lines].scale = splitdata[5];
        canconfigure1[number_of_lines].offset =  splitdata[6];
        canconfigure1[number_of_lines].endian =  splitdata[7];

        /*
        //Check data in structs without using namespace
        cout << canconfigure1[number_of_lines].canid << " " << canconfigure1[number_of_lines].canlength << " " << canconfigure1[number_of_lines].startbit  <<
        canconfigure1[number_of_lines].length << " " << canconfigure1[number_of_lines].name_variables << " " << canconfigure1[number_of_lines].scale << " " <<
        canconfigure1[number_of_lines].offset << " " << canconfigure1[number_of_lines].endian << endl;
        number_of_lines++;
        */
    