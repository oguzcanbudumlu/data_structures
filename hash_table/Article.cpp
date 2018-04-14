#include "Article.h"

/*#############################
#               NOTE!         #
#    Please don't forget to   #
#     check PDF. Fuctions     #
#    may have more detailed   #
#     tasks which are not     #
#       mentioned here.       #
#############################*/

Article::Article( int table_size,int h1_param, int h2_param )
{
    this->h1_param = h1_param;
    this->h2_param = h2_param;
    this->table_size=table_size;
    this->n = 0;
    this->table = new std::pair<std::string, int>[table_size];
    for (int i = 0; i < table_size; i++) {
        table[i].first = EMPTY_KEY;
        table[i].second = EMPTY_INDEX;
    }    /*#############################
    #            TO-DO            #
    # Write a default constructor #
    #   for the Article Class     #
    #############################*/
}

Article::~Article()
{
    delete[] this->table;

    /*#############################
    #             TO-DO           #
    #  Write a deconstructor for  #
    #     the Article Class       #
    #############################*/
}

int Article::get( std::string key, int nth, std::vector<int> &path ) const
{
    /*#############################################
    #                    TO-DO                    #
    #      Your get function should return        #
    # the original index (index in the text file) #
    #    of the nth 'key' in the hash table.      #
    #    If there is no such a key, return -1     #
    #    If there is, return the original index   #
    #     In both cases, you need to push each    #
    #          visited index while probing        #
    #           that you calculated until         #
    #      finding the key, to the path vector.   #
    #############################################*/



    int index;
    int anotherIndex;
    int counter=0;
    bool isItFirst = true;
    for(int i = 0; i < this->table_size; i++)
    {
        index = hash_function(key, i);

        if(this->table[index].first == key)
        {
            counter++;
        }


        if(i!=0)
        {
            path.push_back(index);

        }
        if(counter==nth)
        {
            return this->table[index].second;
        }

        if(this->table[index].first == EMPTY_KEY &&this->table[index].second == EMPTY_INDEX)
        {
            return -1;
        }
        isItFirst=false;

    }
    return -1;

}

int Article::insert( std::string key, int original_index )
{
    /*#########################################
    #                 TO-DO                   #
    #      Insert the given key, with the     #
    # original index value (at the text file) #
    #           to the hash table.            #
    #  Return the total number of probes you  #
    #      encountered while inserting.       #
    #########################################*/


    if(MAX_LOAD_FACTOR < getLoadFactor())
    {
        expand_table();
    }
    int index;
    int cep;
    for(int i = 0; i < this->table_size; i++)
    {
        index = hash_function(key, i);
        if (this->table[index].first == EMPTY_KEY)
        {
            this->table[index].first = key;
            this->table[index].second = original_index;

            this->n++;
            return i;
        }
        if(this->table[index].first != key)
        {
            continue;
        }
        else
        {
            if(original_index < this->table[index].second)
            {
                cep = this->table[index].second;
                this->table[index].second = original_index;
                original_index = cep;

            }
            continue;
        }
    }


return 0;

}


int Article::remove( std::string key, int nth )
{
    /*#########################################
    #                  TO-DO                  #
    #      Remove the nth key at the hash     #
    #                  table.                 #
    #  Return the total number of probes you  #
    #      encountered while inserting.       #
    #   If there is no such a key, return -1  #
    #     If there, put a mark to the table   #
    #########################################*/

    int index;
    int counter = 0;

    for(int i = 0; i < this->table_size; i++)
    {
        index = hash_function(key, i);
        if(this->table[index].first == key)
        {
            counter++;
        }
        if(counter==nth)
        {
            this->table[index].first = EMPTY_KEY;
            this->table[index].second = MARKED_INDEX;
            this->n--;
            return i;
        }

    }
    return -1;
}

double Article::getLoadFactor() const
{
    return (this->n)*1.0 / (this->table_size);

    /*#########################################
    #                TO-DO                    #
    #      Return the load factor of the      #
    #                table                    #
    #########################################*/
    return 0;
}

void Article::getAllWordsFromFile( std::string filepath )
{
    std::ifstream inFile;
    inFile.open(filepath.c_str());
    std::string item;
    int i = 1;
    if(inFile.is_open())
    {
        while(inFile>>item)
        {
//            inFile >> item;
            insert(item, i);
            i++;
        }
    }
    inFile.close();

    /*#########################################
    #                  TO-DO                  #
    #       Parse the words from the file     #
    #      word by word and insert them to    #
    #                hash table.              #
    #   For your own inputs, you can use the  #
    #  'inputify.py' script to fix them to    #
    #            the correct format.          #
    #########################################*/
}


void Article::expand_table()
{
    /*#########################################
    #                  TO-DO                  #
    #   Implement the expand table function   #
    #   in order to increase the table size   #
    #   to the very first prime number after  #
    #      the value of (2*table size).       #
    #         Re-hash all the data.           #
    #       Update h2_param accordingly.      #
    #########################################*/
    int old_size =this->table_size;
    int new_size = nextPrimeAfter(2*table_size);
    this->table_size = new_size;
    this->h2_param = firstPrimeBefore(this->table_size);
    this->n = 0;
    std::pair<std::string, int>* old_table = this->table;

    std::pair<std::string, int>* new_table;
    new_table = new std::pair<std::string, int>[this->table_size];
    this->table = new_table;
    for(int i = 0; i < new_size; i++)
    {
        this->table[i].first = EMPTY_KEY;
        this->table[i].second = EMPTY_INDEX;
    }
    for(int i = 0; i < old_size ;i++)
    {
        if(old_table[i].first != EMPTY_KEY)
        {
            insert(old_table[i].first, old_table[i].second);
        }
    }
    delete[] old_table;

}

int Article::hash_function( std::string& key, int i ) const
{
    /*#########################################
    #                TO-DO                    #
    #       Implement the main hashing        #
    #    function. Firstly, convert key to    #
    #    integer as stated in the homework    #
    #      text. Then implement the double    #
    #            hashing function.            #
    #      use convertStrToInt function to    #
    #      convert key to a integer for       #
    #         using it on h1 and h2           #
    #               reminder:                 #
    #            you should return            #
    #    ( h1(keyToInt) + i*h2(keyToınt) )    #
    #            modulo table_size            #
    #########################################*/
    int convertedKey = convertStrToInt(key);
    int h1_ = h1(convertedKey);
    int h2_ = h2(convertedKey);
    int result = (h1_ + i*h2_) % this->table_size;
    if(result < 0)
    {
        result += table_size;
    }
    return result;
}

int Article::h1( int key ) const
{
    /*###############################
    #              TO-DO            #
    #      First Hash function      #
    # Don't forget to use h1_param. #
    ###############################*/
    int pop_count = countSetBits(key); //number of 1's in key
    int result = pop_count * this->h1_param;
    return result;
}

int Article::h2( int key ) const
{
    /*###############################
    #              TO-DO            #
    #     Second Hash function      #
    # Don't forget to use h2_param. #
    ###############################*/
    int modulo = key % this->h2_param;
    return this->h2_param - modulo;
}

int Article::countSetBits(int n)
const
{
    int count = 0;
    while(n)
    {
        count += n & 1;
        n>>=1;
    }
    return count;
}
