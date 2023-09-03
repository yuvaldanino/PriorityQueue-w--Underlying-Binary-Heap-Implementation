#ifndef _PRIORITYQUEUE_H_ // used ot check if the file priorityqueue is already defined
#define _PRIORITYQUEUE_H_ // defines the file to make sure it is not repeated

#include <vector> // this is incldued for the imnplementation of vectorsin the code
#include <utility> // provides different utilioty functions used inthe code for it to compile
#include "json.hpp" // includes the JSOn library 

typedef double                  Key; // creates the key for the data type double
typedef std::pair<int, int>     Value; // creates the alias Value for the data rte of two integers inthe code 
typedef std::pair<Key, Value>   KeyValuePair;  // KeyValue Pair is created for the data type of the key which is doubvle and the value which is two integers

class PriorityQueue { // defined the class priorityqueue
  public: // these are of the public form
    PriorityQueue(std::size_t max_nodes); // constructor functiomn that takes the maxnodes
    void insert(Key k); // inserts a newkey value paid with the default value of k
    void insert(KeyValuePair kv); // anotehr insert of a key value pair
    KeyValuePair min(); // this returns the minimum pair but does not erase it 
    KeyValuePair removeMin(); // this removes the minimumthat we found earlier
    bool isEmpty() const; // returns truew if it is empty
    size_t size() const; // retuns the number of elements
    nlohmann::json JSON() const; // retunrs the JSOn object 

  private: // this is a private class
    void heapifyUp(size_t i); // private functionm that takes index i and performs the heapifyUp operation on it 
    void heapifyDown(size_t i); // same as above but eprformas the heapifyDown operation on it 
    void removeNode(size_t i); // removes the node at the index from the priorityqueue
    Key getKey(size_t i); // returns the key of the node
    bool InBounds(size_t); // returns the boolean value fromthe index i to ssee if it is within the bounds
    bool LessThan(size_t, size_t); // indicated i and j and retunrs the boolean bvalue to see which has a smaller node

    std::vector<KeyValuePair>   nodes_; // vecotr is keyvalue pair representingth enodes in it 
    size_t                      max_size_; // maxsize is a value of sizet representingthe maximum size thatcan be stored
    size_t                      size_; // same as above but instead of max size it shows the number of nodes in there atthe moment

    const static size_t         ROOT = 1; // const which shows te value of ROOt which is 1
};  // class PriorityQueue

#endif  // _PRIORITYQUEUE_H_