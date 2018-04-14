/*Load*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Playlist.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Playlist pl1 = Playlist(); 
    pl1.load("list.txt");
    pl1.print();
    pl1.printHistory();
    return 0;
}
