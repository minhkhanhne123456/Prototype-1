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
    double scale;          
    double offset;
    bool endian;
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
        cout << splitdata[0] << endl;
        cout << splitdata[1] << endl;
        cout << splitdata[2] << endl;
        cout << splitdata[3] << endl;
        cout << splitdata[4] << endl;
        cout << splitdata[5] << endl;
        cout << splitdata[6] << endl;
        cout << splitdata[7] << endl;
        
    for (int i = 0 ; i < number_of_lines; i++)
    {
        /*if (!in)
        {                                               
            cerr << "File can't be opened! " << endl;
            system("PAUSE");
        }
        */

        /*
        canconfigure1[i].canid = splitdata[0];
        canconfigure1[i].canlength = splitdata[1];
        canconfigure1[i].startbit = splitdata[2]
        canconfigure1[i].length =
        canconfigure1[i].name_variables = 
        canconfigure1[i].scale = 
        canconfigure1[i].offset =  
        canconfigure1[i].endian =  
        */
       
      
        /*
        in >> canconfigure1[i].canid >> canconfigure1[i].canlength >> canconfigure1[i].name_variables >> canconfigure1[i].startbit >> canconfigure1[i].length  >> canconfigure1[i].endian >> canconfigure1[i].scale >>canconfigure1[i].offset;
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
