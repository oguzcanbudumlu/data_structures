/*Sort  500*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Playlist.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Playlist pl1 = Playlist(); 
    pl1.load("list500.txt");
    pl1.print();
    pl1.sort();
    pl1.print();
    
    return 0;
}
