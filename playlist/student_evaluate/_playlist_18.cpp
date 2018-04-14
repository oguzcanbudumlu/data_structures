/*UNDO V2*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Playlist.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Playlist pl1 = Playlist(); 
    pl1.load("list50.txt");
    pl1.print();
    pl1.deleteEntry("Title798");
    pl1.print();
    pl1.deleteEntry("Title177");
    pl1.print();
    pl1.deleteEntry("Title612");
	pl1.printHistory();
    pl1.print();
    pl1.undo();
    pl1.print();
    pl1.undo();
    pl1.print();
    pl1.undo();
    pl1.print();	
    pl1.undo();
    pl1.print();	
	pl1.printHistory();
    return 0;
}
