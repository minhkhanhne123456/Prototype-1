
#include <iostream>
using namespace std;

#define PERSON_NUM 5

typedef struct {   
    char name[20];
    char sex; 
    int age;
    double height; 
    double weight; 
} person_t;

main(){
    person_t p[PERSON_NUM] = {{"Bob",      'M', 19, 165.4, 72.5},
                              {"Alice",    'F', 19, 161.7, 44.2},
                              {"Tom",      'M', 20, 175.2, 66.3},
                              {"Stefany",  'F', 18, 159.3, 48.5},
                              {"Leonardo", 'M', 19, 172.8, 67.2}};
    
    //Truy cập vào thực thể trong mảng cấu trúc và gán thực thể vào một biến
    
    person_t p0 = p[0];
    //Truy cập vào thành viên của thực thể trên và gán vào một mảng chuỗi
    string name = p0.name;  // string name = p[0].name;
    cout << name ;
    return 0;
}