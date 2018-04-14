/*Move Right V2*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Playlist.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Playlist pl1 = Playlist(); 
    pl1.insertEntry(Entry("T1"));
    pl1.insertEntry(Entry("T2"));
    pl1.insertEntry(Entry("T3"));
    pl1.insertEntry(Entry("T4"));
    pl1.print();


	
    pl1.moveRight("T1");
    pl1.print();
    
	
    pl1.moveRight("T1");
    pl1.print();
    
    pl1.printHistory();  

    return 0;
}
