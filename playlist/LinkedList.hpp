#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include <iostream>
#include "Node.hpp"

using namespace std;

/*....DO NOT EDIT BELOW....*/
template<class T>
class LinkedList {
private:
/*First node of the linked-list*/
    Node<T> *head;
/*Last node of the linked-list*/
    Node<T> *tail;
/*size of the linked-list*/
    size_t size;
public:

    LinkedList();

    LinkedList(const LinkedList<T> &ll);

    LinkedList<T> &operator=(const LinkedList<T> &ll);

    ~LinkedList();

/* Return head of the linked-list*/
    Node<T> *getHead() const;

/* Set head of the linked-list*/
    void setHead(Node<T> *n);

/* Return tail of the linked-list*/
    Node<T> *getTail() const;

/* Set tail of the linked-list*/
    void setTail(Node<T> *n);

/* Get the previous node of the node that contains the data item.
 * If the head node contains the data item, this method returns NULL.*/
    Node<T> *findPrev(const T &data) const;

/* Get the node that stores the data item.
 * If data is not found in the list, this function returns NULL.*/
    Node<T> *findNode(const T &data) const;

/* Insert a new node to store the data item.
 * The new node should be placed after the “prev” node.
 * If prev is NULL then insert new node to the head.*/
    void insertNode(Node<T> *prev, const T &data);

/* This method is used to delete the node that is next to “prevNode”.
 * PS:prevNode is not the node to be deleted. */
    void deleteNode(Node<T> *prevNode);

/* This method is used to clear the contents of the list.*/
    void clear();

/* This method returns true if the list empty, otherwise returns false.*/
    bool isEmpty() const;

/* This method returns the current size of the list. */
    size_t getSize() const;

/*Prints the list. This method was already implemented. Do not modify.*/
    void print() const;
};

template<class T>
void LinkedList<T>::print() const {
    const Node<T> *node = head;
    while (node) {
        std::cout << node->getData();
        node = node->getNext();
    }
    cout << std::endl;
}

/*....DO NOT EDIT ABOVE....*/

/* TO-DO: method implementations below */

template<class T>
LinkedList<T>::LinkedList() : head(NULL), tail(NULL), size(0) {

}

template<class T>
LinkedList<T>::LinkedList(const LinkedList<T> &ll) {
    head = NULL;
    tail = NULL;
    size = 0;
    *this = ll;
}

template<class T>
LinkedList<T> &LinkedList<T>::operator=(const LinkedList<T> &ll) {

    if (this != &ll) {
        clear();

        //  setHead(0);
        //  setTail(0);

        const Node<T> *r = ll.getHead();
        while (r) {
            insertNode(getTail(), r->getData());
            r = r->getNext();
        }
    }
    return *this;
}

template<class T>
LinkedList<T>::~LinkedList() {
    // cout << "destructor\n";
    clear();
    setTail(NULL);
    setHead(NULL);
    //  clear();

}


template<class T>
Node<T> *LinkedList<T>::getHead() const {
    return head;
}

template<class T>
void LinkedList<T>::setHead(Node<T> *n) {
    head = n;
}

template<class T>
Node<T> *LinkedList<T>::getTail() const {
    return tail;
}

template<class T>
void LinkedList<T>::setTail(Node<T> *n) {
    tail = n;
}

template<class T>
Node<T> *LinkedList<T>::findPrev(const T &data) const {
    Node<T> *guide = getHead();
    if (guide->getData() == data) {
        return NULL;
    }
    while (guide->getNext()) {
        if (guide->getNext()->getData() == data) {
            return guide;
        }
        guide = guide->getNext();
    }
    return NULL;
}

template<class T>
Node<T> *LinkedList<T>::findNode(const T &data) const {
    Node<T> *guide = getHead();
    while (guide) {
        if (guide->getData() == data) {
            return guide;
        }
        guide = guide->getNext();
    }
    return NULL;
}

template<class T>
void LinkedList<T>::insertNode(Node<T> *prev, const T &data) {
    Node<T> *newNode = new Node<T>(data);
    if (prev != NULL) {
        newNode->setNext(prev->getNext());
        if (prev->getNext() == NULL) {
            setTail(newNode);
            newNode->setNext(NULL);
        }
        prev->setNext(newNode);
    } else {
        if (isEmpty()) {
            setTail(newNode);
            newNode->setNext(NULL);
        }

        newNode->setNext(getHead()); // sen burada bildiğin circular link list yapmış olmadın mı şimdi ??
        setHead(newNode);
    }
    this->size++;
}

template<class T>
void LinkedList<T>::deleteNode(Node<T> *prevNode) {

    if (prevNode){
        Node<T> *target = prevNode->getNext();
        if (target) { // target null değilse
            prevNode->setNext(target->getNext()); // silinecekten sonrakini prevNode nextine yazdım
            delete target;
            this->size--;
        }
        if(prevNode->getNext() == NULL) // son durumda prevNode un nexti nullsa prevnode tail olmuştur
            this->setTail(prevNode);
    } else {
        Node<T> *target = this->getHead();
        if (target) { // target null değilse
            this->setHead(target->getNext()); // silinecekten sonrakini prevNode nextine yazdım
            if(target->getNext() == NULL)
                this->setTail(NULL);
            delete target;
            this->size--;
        }
    }


    // cout << "buradayım\n";
    // if(getSize()==0)
    // {
    //         return;
    // }
    // else if(getSize()== 1)
    // {
    //         if(prevNode == NULL)
    //         {
    //                 delete head;
    //
    //                 setHead(NULL);
    //         }
    //         else
    //         {
    //                 return;
    //         }
    // }
    // else
    // {
    //         if(prevNode == NULL)
    //         {
    //                 Node<T>* temp = head->getNext();
    //                 delete head;
    //                 setHead(temp);
    //         }
    //         else
    //         {
    //                 if(prevNode->getNext() != NULL)
    //                 {
    //                         Node<T>* temp = prevNode->getNext();
    //                         prevNode->setNext(temp->getNext()); // NULL da olabilir
    //                         if(prevNode->getNext() == NULL)
    //                         {
    //                                 setTail(prevNode);
    //                         }
    //                         delete temp;
    //
    //                 }
    //                 else
    //                 {
    //                         return;
    //                 }
    //
    //         }
    // }
    //
    // if(!prevNode)
    // {
    //   if(getSize() == 1)
    //   {
    //     Node<T>* temp = getHead();
    //     delete temp;
    //     setHead(NULL);
    //   }
    //   else
    //   {
    //     Node<T>* temp = head;
    //     Node<T>* temp2 = head -> getNext();
    //     delete temp;
    //     setHead(temp2);
    //   }
    //
    // }
    // else
    // {
    //   if(prevNode -> getNext())
    //   {
    //     Node<T>* temp = prevNode -> getNext();
    //     if(temp -> getNext())
    //     {
    //       prevNode -> setNext(temp -> getNext());
    //       delete temp;
    //     }
    //     else
    //     {
    //       delete temp;
    //       setTail(prevNode);
    //     }
    //   }
    // }
//
    // if(prevNode)
    // {
    //   Node<T>* temp = prevNode -> getNext();
    //   if(getTail()==temp)
    //   {
    //     setTail(prevNode);
    //   }
    //   if(temp)
    //   prevNode -> setNext(temp -> getNext());
    //
    //   delete temp;
    // }
//
//   if(prevNode == NULL)
//   {
//     if(getHead())
//     {
//       if(getHead() -> getNext())
//       {
//         Node<T>* temp = getHead();
//         setHead(getHead() -> getNext());
//         delete temp;
//      }
//     else
//     {
//       setHead(NULL);
//       setTail(NULL);
//     }
//   }
// }
//   else
//   {
//     if(prevNode -> getNext() != NULL)
//     {
//       Node<T>* temp = prevNode -> getNext();
//       if(temp -> getNext() == NULL)
//       {
//         delete temp;
//         setTail(prevNode);
//       }
//       else
//       {
//         prevNode -> setNext(temp -> getNext());
//         delete temp;
//       }
//     }
//     else
//     {
//       return;
//     }
// }
//
//
    //
    // if(prevNode -> getNext())
    // {
    //   Node<T>* temp = prevNode -> getNext();
    //   prevNode -> setNext(temp -> getNext());
    //   delete temp;
    // }
    // else
    // {
    //
    // }
//
    // if(prevNode)
    // {
    //   Node<T>* temp = prevNode -> getNext();
    //   if(prevNode -> getNext())
    //   {
    //     if(prevNode -> getNext() -> getNext())
    //     {
    //       setTail(prevNode);
    //       Node<T>* temp = prevNode -> getNext();
    //       delete temp;
    //       prevNode -> setNext(NULL);
    //     }
    //     else
    //     {
    //       Node<T>* temp = prevNode -> getNext();
    //       prevNode -> setNext(temp -> getNext());
    //       delete temp;
    //     }
    //   }
    //   // if(getTail()==temp)
    //   // {
    //   //   setTail(prevNode);
    //   // }
    //
    //
    //   //
    //   // prevNode -> setNext(temp -> getNext());
    //   // delete temp;
    // }
    // else
    // {
    //   if(head!= NULL)
    //   {
    //     Node<T>* temp = getHead();
    //     setHead(head -> getNext());
    //     delete temp;
    //   }
    // }

}

template<class T>
void LinkedList<T>::clear() {
    // // Node<T> *target = this->head, *temp = NULL;
    // //   while (target) {
    // //     temp = target->getNext();
    // //     delete target;
    // //     target = temp;
    // //     /* code */
    // //   }
    //
    //   // while(!isEmpty())
    //   // {
    //   //   if(head -> getNext() == NULL)
    //   //   {
    //   //     break;
    //   //   }
    //   //   deleteNode(head);
    //   // }
    //   //  delete head;
    //   //  setTail(NULL);
    //   //  setHead(NULL);
    //
    //   // while(!isEmpty())
    //   // {
    //   //   deleteNode(head);
    //   // }
    //   // deleteNode(NULL);
    //   while(!isEmpty())
    //   {
    //     deleteNode(head);
    //   }
    if (this->head) {
        while (this->head->getNext()) {
            deleteNode(head);
        }
        delete head;
        this->size--;
        setTail(NULL);
        setHead(NULL);
    }
}

template<class T>
bool LinkedList<T>::isEmpty() const {
    return (head == NULL);
}

template<class T>
size_t LinkedList<T>::getSize() const {
    size_t i = 0;
    Node<T> *ptr = getHead();
    while (ptr) {
        i++;
        ptr = ptr->getNext();
    }

    return i;
    // return size;
}

/* end of your implementations*/

#endif
