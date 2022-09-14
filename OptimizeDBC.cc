#include <iostream>
#include <string>
#include "CanUtils.h"
#include <fstream>
using namespace std;


static int number_of_lines;
ifstream in("CAN_config1.txt");
const int SIZE = 1000;
void debugPrint();
void loadData();
int numberoflines();

class test {
    public: 
    static utils::canConfigure mCanConfigSpeedData;
    static utils::canConfigure mCanConfigMCUDCVoltage;
    static utils::canConfigure mCanConfigSideStand;
    static utils::canConfigure mCanConfigBrake;
    static utils::canConfigure mCanConfigSpeedMode;
    static utils::canConfigure mCanConfigTotalOdometerMileage;
    static utils::canConfigure mCanConfigThrottlePercentage;
    static utils::canConfigure mCanConfigBrakeFault;
    static utils::canConfigure mCanConfigPositionSensorFault;
    static utils::canConfigure mCanConfigDriveMode;
    static utils::canConfigure mCanConfigSOCDisplay;

};

std::string createJson(std::string const& one, std::string const& two,
                  std::string const& three, std::string const& four)
{
    boost::property_tree::ptree pt;
    std::stringstream ss;

    pt.put("one", one);
    pt.put("two", two);
    pt.put("three", three);
    pt.put("four", four);

    write_json(ss, pt);

    return ss.str();
}

struct Canconfigure1 {
    string canid;
    string canlength; 
    string name_variables; 
    string startbit;    
    string length;      
    double scale;          
    double offset;
    string endian;
}canconfigure1[SIZE];

int main()
    {
    numberoflines();
    loadData();
    // debugPrint();
    // cout << canconfigure[0].canid << " ";
    // cout << canconfigure[0].name_variables << " " ; 
    // cout << canconfigure[0].canlength << " "; 
    // cout << canconfigure[0].startbit << " ";
    // cout << canconfigure[0].length << " " ;
    // cout << canconfigure[0].scale << " ";
    // cout << canconfigure[0].offset << " " ;
    // cout << canconfigure[0].endian << " ";
    // cout << "The number of lines is: " << number_of_lines << endl;

    return 0;
    }

void debugPrint()
{
    for (int i = 0; i < number_of_lines; i++) 
    {
        cout << canconfigure1[i].canid << " ";
        cout << canconfigure1[i].canlength << " ";
        cout << canconfigure1[i].name_variables<<" ";
        cout << canconfigure1[i].startbit << " ";
        cout << canconfigure1[i].length << " " ;
        cout << canconfigure1[i].scale <<" ";
        cout << canconfigure1[i].offset <<" " ;
        cout << canconfigure1[i].endian << " " << endl;
    }
}


void loadData()
{   
    for (int i = 0; i < number_of_lines; i++)
    {
        int temp;
        if (!in)
        {                                               
            cerr << "File can't be opened! " << endl;
            system("PAUSE");
        }
        in >> canconfigure1[i].canid >> canconfigure1[i].canlength >> canconfigure1[i].name_variables >> canconfigure1[i].startbit >> canconfigure1[i].length  >> canconfigure1[i].endian >> canconfigure1[i].scale >>canconfigure1[i].offset;
        cout << canconfigure1[i].canid << endl;
        
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
