/*Merge V2*/
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Playlist.hpp"

using namespace std;

int main(int argc, char* argv[]){
    Playlist pl1 = Playlist(); 
    Playlist pl2 = Playlist(); 
    pl1.load("list100.txt");
    pl2.load("list150.txt");
    pl1.sort();
    pl2.sort();
    pl1.print();
    pl2.print();
    pl1.merge(pl2);
    pl1.print();
    pl2.print();
    return 0;
}
