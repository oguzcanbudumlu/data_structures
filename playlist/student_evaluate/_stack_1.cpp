//test with integer type
#include <iostream>
#include <cstdlib>
#include "MyStack.hpp"

		
using namespace std;

int main(int argc, char* argv[]){
    MyStack<int>  a = MyStack<int>();
    a.print();
    for(int i=0;i<100;i++) a.push(i);
    a.print();
    return 0;
}	
