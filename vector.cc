#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Thing
{
   int number;
   string name;

   void input();
};


void Thing::input()
{
   cout << "Enter a number: ";   cin >> number;   cin.ignore( 1000, '\n' );
   cout << "Enter a name: ";     getline( cin, name );
}


int main()
{
   int N;
   cout << "How many things do you want? ";   cin >> N;
   vector<Thing> things( N );

   for ( int i = 0; i < N; i++ ) things[i].input();

  
}
