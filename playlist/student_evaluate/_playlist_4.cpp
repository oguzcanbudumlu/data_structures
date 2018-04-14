/*Delete V2*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Playlist.hpp"

using namespace std;

int main(int argc, char* argv[]){
     
    Playlist pl1 = Playlist(); 
    pl1.insertEntry(Entry("Rendez-Vous 2"));
    pl1.insertEntry(Entry("Equinoxe 4"));
    pl1.insertEntry(Entry("The Four Seasons","Classical"));
    pl1.insertEntry(Entry("Billy Jean","dance-pop","1983"));
    pl1.print();
    pl1.printHistory();
    pl1.deleteEntry("DELETE");
	
    pl1.print();
    pl1.printHistory();
    
    return 0;
}
