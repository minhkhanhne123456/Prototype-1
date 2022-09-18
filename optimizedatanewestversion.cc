#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <sstream>
#include <iterator>
using namespace std;


static int number_of_lines;

const int SIZE = 1000;
void loadData();
int numberoflines();

template <size_t N>
//Split string and add to array
void splitString(string (&arr)[N], string str)
{
    int n = 0;
    istringstream iss(str);
    for (auto it = istream_iterator<string>(iss); it != istream_iterator<string>() && n < N; ++it, ++n)
        arr[n] = *it;
}



struct Canconfigure1 {
    string canid;
    string canlength; 
    string name_variables; 
    string startbit;    
    string length;      
    string scale;          
    string offset;
    string endian;
}canconfigure1[SIZE];

int main()
    {
    numberoflines();
    loadData();
    return 0;
    }

void loadData()
{   
    ifstream in("CAN_config1.txt");
    string line1;
    while (getline (in, line1))
    {
        string splitdata[8];
        string split = "" + line1;
        splitString(splitdata,split);
        cout << splitdata[0] << splitdata[1] << splitdata[2] << splitdata[3] <<
        splitdata[4] << splitdata[5] << splitdata[6] << splitdata[7] << endl;

        //Su dung for nhung khong phai cach cu nen cho mot bien dem number of lines ben ngoai con ben trong chi cho lap 1 lan, bien i cong don len
        /*
        for (int i = 0; i < number_of_lines; i++){
        canconfigure1[i].canid = splitdata[0];
        canconfigure1[i].canlength = splitdata[1];
        canconfigure1[i].startbit = splitdata[2];
        canconfigure1[i].length = splitdata[3];
        canconfigure1[i].name_variables = splitdata[4];
        canconfigure1[i].scale = splitdata[5];
        canconfigure1[i].offset =  splitdata[6];
        canconfigure1[i].endian =  splitdata[7];
        cout << canconfigure1[i].canid << " ";
        cout << canconfigure1[i].canlength << " ";
        cout << canconfigure1[i].name_variables<<" ";
        cout << canconfigure1[i].startbit << " ";
        cout << canconfigure1[i].length << " " ;
        cout << canconfigure1[i].scale <<" ";
        cout << canconfigure1[i].offset <<" " ;
        cout << canconfigure1[i].endian << " " << endl;
        */
    }
    }


int numberoflines(){
    string line;
    ifstream myfile("CAN_config1.txt");
    if(myfile.is_open()){
        while(getline(myfile,line)){
            number_of_lines++;
        }
        myfile.close();
    }
    return number_of_lines;
}
