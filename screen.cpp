#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fstream>
using namespace std;

// C++ program to demonstrate
// accessing of data members

class Chatscreen
{
    // Access specifier
    public:

    // Data Members
    string geekname;
    string filename;
   // std::ifstream myfile(filename);
    Chatscreen(string user1,string user2, string user3){
    	cout <<"Chat room for " << user1 <<", " << user2 <<", "<<user3 <<"\n ";
    	filename = user1+user2+user3+".txt";
    	std::ofstream myfile(filename,ios::app);
    	myfile <<"\n" <<"Chat room for " << user1 <<", " << user2 <<", "<<user3 <<"\n ";

    }
    // Member Functions()
    void printname()
    {
       cout << "Geekname is: " << geekname;
    }
    void displayscreen(){
    	std::ifstream myfile(filename);
    	std::string line;
   		if (myfile.is_open())
    	{
        	while(!myfile.eof()){
        		getline(myfile,line);
        		std::cout << line << '\n';
        	}
        	myfile.close();
    	}
    	else
        std::cout << "Unable to open file.\n";
	}
};

int main() {

    // Declare an object of class geeks
    Chatscreen obj1("bp","abc","sharad");

    // accessing data member
    obj1.geekname = "Abhi";

    // accessing member function
    obj1.printname();
    obj1.displayscreen();
    return 0;
}
