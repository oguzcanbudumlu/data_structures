#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "Playlist.hpp"
#include "Entry.hpp"

using namespace std;


Playlist::Playlist()
{
    srand(15);
}

int Playlist::getRandomNumber(int i, int n) const
{
    int range=n-i;
    int random = rand() % range + i;
    return random;
}

void Playlist::print()
{
    cout << "[PLAYLIST SIZE=" << entries.getSize() <<"]";
    entries.print();
}
void Playlist::printHistory()
{
    cout<<"[HISTORY]";
    history.print();
}

/* TO-DO: method implementations below */

void Playlist::load(string fileName)
{
  // Entry* guide = entries.getTail();
  // entries.insertNode(guide, );
  int i = 0;
  int counter = 0;
  string title;
  string genre;
  string year;
  string garbage;
  ifstream file(fileName.c_str());
  while(file.get()!= EOF)
  {
      getline(file,garbage, '\n');
      counter++;
  }
  ifstream n_file(fileName.c_str());
  if (n_file.is_open())
  {
      while ( i< counter )
      {
          getline(n_file, title, ';');
          getline(n_file, genre, ';');
          getline(n_file, year);
          Entry* temp = new Entry(title, genre, year);
          callInsert(temp -> getTitle(), temp -> getGenre(), temp -> getYear());
          delete temp;
          i++;
      }
      file.close();
  }


}

void Playlist::callInsert(string title, string genre, string year)
{
    Entry temp(title, genre, year);
    insertEntry(temp);
}

void Playlist::insertEntry(const Entry &e)
{
  if(doesFind(e))
  {
    return;
  }
  else
  {
    Node<Entry>* guide = entries.getTail();
    entries.insertNode(guide, e);
    HistoryRecord record(INSERT, e);
    history.push(record);
  }
}

bool Playlist::doesFind(const Entry &e)
{
  Node<Entry>* guide = entries.getHead();
  while(guide)
  {
    if(guide -> getData() == e)
    {
      return true;
    }
    guide = guide -> getNext();
  }
  return false;
}

Node<Entry>* Playlist::findFromTitle(const std::string &_title)
{
  Node<Entry>* guide = entries.getHead();
  while(guide)
  {
    if(guide -> getData().getTitle() == _title)
    {
      return guide;
    }
    guide = guide -> getNext();
  }
  return NULL;
}

void Playlist::deleteEntry(const std::string &_title)
{
    Node<Entry>* guide = findFromTitle(_title);
    if(guide)
    {
      Node<Entry>* prev = entries.findPrev(guide -> getData());
      if(prev == NULL)
      {
        entries.setHead(guide -> getNext());
      }
      else
      {
        if(guide -> getNext() == NULL)
        {
          entries.setTail(prev);
        }
        prev -> setNext(guide -> getNext());
      }
      HistoryRecord record(DELETE, guide -> getData());
      history.push(record);
      delete guide;
    }

    // Node<Entry>* guide = findFromTitle(_title);
    // if(guide)
    // {
    //   Node<Entry>* prev = entries.findPrev(guide -> getData());
    //   entries.deleteNode(prev)
    // //   if(prev == NULL)
    // //   {
    // //     entries.setHead(guide -> getNext());
    // //   }
    // //   else
    // //   {
    // //     if(guide -> getNext() == NULL)
    // //     {
    // //       entries.setTail(prev);
    // //     }
    // //     prev -> setNext(guide -> getNext());
    // //   }
    //   HistoryRecord record(DELETE, guide -> getData());
    //   history.push(record);
    //   delete guide;
    // }


}
//
void Playlist::moveLeft(const std::string &title)
{
  Node<Entry>* guide = findFromTitle(title);
  if(guide -> getData().getTitle() == entries.getHead() -> getData().getTitle())
  {
    return;
  }
  else
  {
    Node<Entry>* prev = entries.findPrev(guide -> getData());
    Node<Entry>* prevofprev = entries.findPrev(prev-> getData());
    if(prevofprev == NULL)
    {
      Node<Entry>* newNode = new Node<Entry>(guide -> getData());
      newNode -> setNext(prev);
      entries.setHead(newNode);
      prev -> setNext(guide -> getNext());
      delete guide;
    }
    else
    {
      prev -> setNext(guide -> getNext());
      guide -> setNext(prev);
      prevofprev -> setNext(guide);
    }
  }
}
//
void Playlist::moveRight(const std::string &title)
{
  Node<Entry>* guide = findFromTitle(title);
  if(guide -> getData().getTitle() == entries.getTail() -> getData().getTitle())
  {
    return;
  }
  else
  {
    Node<Entry>* latter = guide -> getNext();
    if(guide == entries.getHead())
    {
        Node<Entry>* newNode = new Node<Entry>(latter -> getData());
        newNode -> setNext(guide);
        entries.setHead(newNode);
        guide -> setNext(latter -> getNext());
        delete latter;
        latter = 0;
    }
    else
    {
      Node<Entry>* prev = entries.findPrev(guide -> getData());
      guide -> setNext(latter -> getNext());
      latter -> setNext(guide);
      prev -> setNext(latter);
    }
  }
}

void Playlist::reverse()
{
    Node<Entry>* prev = NULL;
    Node<Entry>* current = entries.getHead();
    Node<Entry>* next;
    HistoryRecord record(REVERSE);
    history.push(record);
    while(current  != NULL)
    {
        next = current -> getNext();
        if(!prev)
        {
            entries.setTail(current);
        }
        current -> setNext(prev);
        prev = current;
        current = next;
    }
    entries.setHead(prev);



  // Node<Entry>* temp = entries.getHead();
  // Node<Entry>* cleaner = temp;
  // MyStack<Entry> reverse;
  // while(temp)
  // {
  //   reverse.push(temp -> getData());
  //   temp = temp -> getNext();
  //   delete cleaner;
  //   cleaner = temp;
  // }
  // // temp =
  // while(!reverse.isEmpty())
  // {
  //   if(entries.getHead() == NULL)
  //   {
  //       entries.insertNode(NULL, reverse.Top() -> getData());
  //   }
  //   else
  //   {
  //       cout << "buradayım\n";
  //       entries.insertNode(entries.getTail(), reverse.Top() -> getData());
  //   }
  //   // temp = entries.getTail();
  //   reverse.pop();
  // }

}
//


void Playlist::sort()
{
  Node<Entry>* ref = entries.getHead();
  Node<Entry>* min = ref;
  while(ref)
  {
      Node<Entry>* mobile = ref -> getNext();
      while(mobile)
      {
          if(mobile -> getData().getTitle() < min -> getData().getTitle())
          {
              min = mobile;
          }

          mobile = mobile -> getNext();

      }
      if(ref != min)
      {
          Node<Entry>* holder = ref;
          Node<Entry>* holder2 = min;
          ref = ref -> getNext();
          min = ref;
          swap(holder, holder2);
      }
      else
      {
          ref = ref -> getNext();
          min = ref;
      }
  }
}




Node<Entry>* Playlist::getPointer() const
{
    return entries.getHead();
}

void Playlist::insertByIndex(int index, Entry &e)
{
    if(index == 0)
    {
        entries.insertNode(NULL, e);
        return;
    }
    index -=1;
    Node<Entry>* p = entries.getHead();
    for(int i = 0; i < index ; i++)
    {
        p = p -> getNext();
    }
    entries.insertNode(p, e);
}

void Playlist::merge(const Playlist & pl)
{
    int index = 0;
    Node<Entry>* q = pl.getPointer();
    while(q)
    {
        Node<Entry>* p = entries.getHead();
        while(p)
        {
            if(q -> getData().getTitle() > p -> getData().getTitle())
            {
                index++;
                p = p -> getNext();
            }
            else
            {
                break;
            }
        }
        Entry temp(q -> getData().getTitle(), q -> getData().getGenre(), q -> getData().getYear());
        insertByIndex(index, temp);
        q = q -> getNext();
        index = 0;
    }

    // Node<Entry>* new_head;
    // Node<Entry>* p = entries.getHead();
    // Node<Entry>* q = pl.getPointer();
    //
    // // cout << "q'dan sonraki: "<< q -> getNext() -> getData().getTitle();
    // Node<Entry>* sorting;
    // if(p == NULL) return;
    // if(q == NULL) return;
    // if(p && q)
    // {
    //     if(p -> getData().getTitle() < q -> getData().getTitle())
    //     {
    //         sorting = p;
    //         p = sorting -> getNext();
    //     }
    //     else
    //     {
    //         sorting = q;
    //         q = sorting -> getNext();
    //     }
    // }
    //
    //
    // new_head = sorting;
    //
    // while(p && q)
    // {
    //     if(p -> getData().getTitle() < q -> getData().getTitle())
    //     {
    //         sorting -> setNext(p);
    //         sorting = p;
    //         p = sorting -> getNext();
    //     }
    //     else
    //     {
    //         sorting -> setNext(q);
    //         sorting = q;
    //         q = sorting -> getNext();
    //     }
    // }
    // if(p == NULL)
    // {
    //     sorting -> setNext(q);
    // }
    // if(q == NULL)
    // {
    //     sorting -> setNext(p);
    // }


}





void Playlist::swap(Node<Entry>* ref, Node<Entry>* min)
{
    Node<Entry>* initTail = this->entries.getTail();
    if(min == initTail){
        initTail = ref;
    }
    // ya initTaili swaplerse ne yapacan


    this->entries.insertNode(NULL,Entry());
    this->entries.insertNode(this->entries.getTail(),Entry());
    this->entries.insertNode(ref, Entry());

    Node<Entry>* prev1 = this->entries.findPrev(ref -> getData());
    Node<Entry>* prev2 = this->entries.findPrev(min -> getData());
    Node<Entry>* temp;

    temp = ref -> getNext();
    ref -> setNext(min -> getNext());
    min -> setNext(temp);

    temp = prev1 -> getNext();
    prev1 -> setNext(prev2 -> getNext());
    prev2 -> setNext(temp);

    this->entries.deleteNode(NULL);
    this->entries.deleteNode(initTail);
    this->entries.deleteNode(min);


    // if(ref == NULL) cout << "ref== NULL";
    // if(min == NULL) cout << "min==NULL";
    // if(ref -> getNext() == min)
    // {
    //     Node<Entry>* temp = new Node<Entry>(min -> getData());
    //     Node<Entry>* prev1 = entries.findPrev(ref -> getData());
    //     temp -> setNext(ref);
    //     prev1 -> setNext(temp);
    //     ref -> setNext(min -> getNext());
    //     delete min;
    //     min = 0;
    // }
    // else
    // {
    //     Node<Entry>* temp = new Node<Entry>(min -> getData());
    //     Node<Entry>* temp2 = new Node<Entry>(ref-> getData());
    //     Node<Entry>* prev1 = entries.findPrev(ref -> getData());
    //     Node<Entry>* prev2 = entries.findPrev(min -> getData());
    //     temp -> setNext(ref -> getNext());
    //     if(prev1 != NULL)
    //     {
    //         prev1 -> setNext(temp);
    //     }
    //     delete ref;
    //     cout << min -> getNext() << endl;
    //     temp2 -> setNext(min -> getNext());
    //     if(prev2 != NULL) cout <<"asdasd";
    //     prev2 -> setNext(temp2);
    //     delete min;
    //     // // prev2 -> setNext(ref);
    //     // // ref -> setNext(min -> getNext());
    //     // // // cout << min -> getData().getTitle();
    //     // // // cout << prev2 -> getData();
    //     // // delete min;
    //     // //
    //     // // min = 0;
    //     // // cout << "buradayım\n";
    //
    // }
    //
    // // if(ref == entries.getHead())
    // // {
    // //   if(ref -> getNext() !=  min)
    // //   {
    // //   //   Node<Entry>* temp = new Node<Entry>(min -> getData());
    // //   //   Node<Entry>* prev = entries.findPrev(min -> getData());
    // //   //   Node<Entry>* after = min -> getNext();
    // //   //   temp -> setNext(ref -> getNext());
    // //   //   entries.setHead(temp);
    // //   //   if(after)
    // //   //   ref -> setNext(after);
    // //   //
    // //   //   prev -> setNext(ref);
    // //   //   cout << "buradayım\n";
    // //   //   delete min;
    // //   //   min = 0;
    // //   Node<Entry>* after1 = ref -> getNext();
    // //   Node<Entry>* prev = entries.findPrev(min -> getData());
    // //
    // //
    // //   Node<Entry>* after2 = min -> getNext();
    // //
    // //   ref -> setNext(after2);
    // //   if(prev)
    // //   prev -> setNext(ref);
    // //   min -> setNext(after1);
    // //   entries.setHead(min);
    // //   if(ref -> getNext() == NULL)
    // //   {
    // //       entries.setTail(ref);
    // //   }
    // //
    // //
    // //   }
    // //   else
    // //   {
    // //     Node<Entry>* temp = new Node<Entry>(min -> getData());
    // //     temp -> setNext(ref);
    // //     entries.setHead(temp);
    // //     ref -> setNext(min -> getNext());
    // //     delete min;
    // //   }
    // // }
    // // else
    // // {
    // //   if(min == entries.getTail())
    // //   {
    // //     entries.setTail(ref);
    // //   }
    // //   if(ref -> getNext() != min)
    // //   {
    // //     Node<Entry>* prev1 = entries.findPrev(ref -> getData());
    // //     Node<Entry>* prev2 = entries.findPrev(min -> getData());
    // //     Node<Entry>* after1 = ref -> getNext();
    // //     prev1 -> setNext(min);
    // //     prev2 -> setNext(prev2);
    // //     ref -> setNext(min -> getNext());
    // //     min -> setNext(after1);
    // //     prev2 -> setNext(ref);
    // //   }
    // //   else
    // //   {
    // //     Node<Entry>* prev1 = entries.findPrev(ref -> getData());
    // //     Node<Entry>* prev2 = entries.findPrev(min -> getData());
    // //     prev1 -> setNext(min);
    // //     prev2 -> setNext(prev2);
    // //     ref -> setNext(min -> getNext());
    // //     min -> setNext(ref);
    // //   }
    // // }
    // //   // Node<Entry>* prevOfRef = entries.findPrev(ref);
    // //   // Node<Entry>* prevOfMin = entries.findPrev(min);
    // //   // prevOfRef -> setNext(min);
    // //   // prevOfMin -> setNext(prevOfMin);
    // //   // Ref ->




}

// int Playlist::getRandomNumber(int i, int n) const
// {
//     int range=n-i;
//     int random = rand() % range + i;
//     return random;
// }

Node<Entry>* Playlist::findFromIndex(int index)
{
    Node<Entry>* p = entries.getHead();
    for(int i = 0; i < index; i++)
    {
        p = p -> getNext();
    }
    return p;
}

void Playlist::shuffle()
{
    int n = entries.getSize();
    for(int i = 0 ; i < n ; i++)
    {
        int j = getRandomNumber(i, n);
        if(i != j)
        {
            swap(findFromIndex(i), findFromIndex(j));
        }
    }
}

void Playlist::undo()
{
    if(history.Top() -> getData().getOperation() == INSERT)
    {
        deleteEntry(history.Top() -> getData().getEntry().getTitle());
        cout << "buradayım\n";
    }
    else if(history.Top() -> getData().getOperation() == DELETE)
    {
        insertEntry(history.Top() -> getData().getEntry());
    }
    else if(history.Top() -> getData().getOperation() == REVERSE)
    {
        reverse();
    }
    history.pop();
}
