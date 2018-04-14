//find node :Get the node that stores the data item. 
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <sstream>
#include "LinkedList.hpp"

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()
		

class tmpClass{
    public:
        tmpClass(string val1 = "", int val2 = 0): s_val(val1), i_val(val2) {};
        friend ostream &operator<<(ostream &out, const tmpClass& r){
            out << "["<<r.s_val << ":" << r.i_val<<"]";
            return out;
        };
        bool operator==(const tmpClass & rhs) const{
	    return (this->s_val==rhs.s_val);
        };
        
    private:
        string s_val;
        int i_val;
};


using namespace std;

int main(int argc, char* argv[]){
    srand (39);
    LinkedList<tmpClass> list = LinkedList<tmpClass>();
    for (int i = 0; i < 10; ++i){
        list.insertNode(list.getTail(),tmpClass(SSTR(i), rand()%10));
    }
    list.print();
    
    Node<tmpClass>* node1= list.findNode(list.getHead()->getData());
    Node<tmpClass>* node2= list.findNode(list.getTail()->getData());
    
    cout<<node1->getData()<<endl;
    cout<<node2->getData()<<endl;
    
    return 0;
}
