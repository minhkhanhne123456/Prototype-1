#include<iostream>
#include<algorithm>
#include <string>
#include <fstream> 

using namespace std;

void deletespecialcharacters(string txtfile){
   ifstream myfile(txtfile);
   string line;
   if (myfile.is_open()){
      ofstream newfile("CAN_config1.txt");
      while(getline(myfile, line)){ //while succesful read
       replace(line.begin(), line.end(), '@', ' ');
       replace(line.begin(), line.end(), '|', ' ');
       replace(line.begin(), line.end(), '(', ' ');
       replace(line.begin(), line.end(), ')', ' ');
       replace(line.begin(), line.end(), '[', ' ');
       replace(line.begin(), line.end(), ']', ' ');
       replace(line.begin(), line.end(), '-', ' ');
       replace(line.begin(), line.end(), '+', ' ');
       replace(line.begin(), line.end(), ',', ' ');
       newfile << line << endl;
   }
   myfile.close();
}
   else{
        cout << "Unable to open file ";
    }
}


int main(){
   string txtfile = "CAN_config.txt";
   deletespecialcharacters(txtfile);
   return 0;
}