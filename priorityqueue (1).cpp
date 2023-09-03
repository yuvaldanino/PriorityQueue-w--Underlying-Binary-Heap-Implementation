#include <iostream> // this includes the C++ library that helps with the file input and output
#include "json.hpp" // this includes the JSON library which helps in the reaidng and parsing of data in the JSOn format

#include "priorityqueue.h" //  this contains the data of priorty queue structure which wilkl help the code used below

PriorityQueue::PriorityQueue(std::size_t max_size) : // the declearation of a constructor function for the class prioprtiyqueue
        nodes_(max_size + 1, KeyValuePair()), max_size_(max_size), size_(0) {} // nodes is  avectr thatstores the elements of the priortiy queue as a binary heap  it initializes the nodes vector with max size + 1

void PriorityQueue::insert(Key k) { // insert has a parameter of type key 
    insert(std::make_pair(k, std::make_pair(0, 0))); // new element is innserted as k
}

void PriorityQueue::insert(KeyValuePair kv) { // comment is below
    // push back the item into the vector items
    nodes_[++size_] = kv; // comment is below
    // make the vector items into a heap structure
    heapifyUp(size_); // funciton named heapifyUp in the priority queue class has a new varibale size_
}

KeyValuePair PriorityQueue::min() { // function named min returns the KeyValuePair object that is also in the main class
    return nodes_[1]; // this returns the nodes vector with a value of 1
}

KeyValuePair PriorityQueue::removeMin() { // removemin is retuned wththe object KeyValuePair as well in the main clasas
    if (size_ == 0) // if statemnt regardingthe value of size_ being 0. if truw, the following code bvelow runs
        throw std::underflow_error( // throw function when it is an underflow
                "Empty priority queue!"); // when the throw function is conmplete, the mesage is outputed saying that the priorty queue is emopty

    KeyValuePair root = nodes_[1]; // initializes key value pair object root. it is initialized withthe eleemt nodes which ahs athe value of 1

    nodes_[1] = nodes_[size_--]; // nodes which has a value of 1 is replaced withhe value of size_--
    nodes_.erase(nodes_.end()); // this statemnt removes the alst element of nodes with the erase funciton
    heapifyDown(1); // calls the heapifyDown function withthe argument of 1 to maintainthe heap proprty of priorty queuue since an element was removed above

    return root; // root is retruned
}

bool PriorityQueue::isEmpty() const { // isEmpty returns a boolean value to check the priprty queue is empty or nnot
    return size_ == 0; // if size is 0 then it returns true if not it retrns false
}

nlohmann::json PriorityQueue::JSON() const { // JSON for the priortu queue returns nlohmann :: json object  
    nlohmann::json result; // this creates a new json objectwhich is result
    for (size_t i = 1; i <= size_; i++) { // for loop that iterates size_t and i has to beless than or equal to it. if it is, i is incrememnnted by 1 after easch loop
        nlohmann::json node; // new JSON value node
        KeyValuePair kv = nodes_[i]; // retrieves the keyvaluepair objectwhich is indexed at i
        node["key"] = kv.first; // adds a new keyvalue to node object
        node["value"] = kv.second; // adds another nbew value to hre node objectwith the value 
        if (i != ROOT) { // if i f does not equal ROOT, the code below is run
            node["parent"] = std::to_string((i / 2)); //((i - 1) / 2 + 1); the new keyvalue is added to the node object witht he key parent
        }
        if (2 * i <= size_) { // checks if element has a left child
            node["leftChild"] = std::to_string(2 * i); // new key value is added tyo node with leftchild
        }
        if (2 * i + 1 <= size_) { // checkls if element has rightchild
            node["rightChild"] = std::to_string(2 * i + 1); // new key value is added to righthild 
        }
        result[std::to_string(i)] = node; // adds node object to the result object
    }
    result["metadata"]["max_size"] = max_size_; // adds a new keu value pair rtot he reult object with the key metadata
    result["metadata"]["size"] = size_; //same as above but with the current size instead of max size
    return result; // returns the result once the main has ended
}

void PriorityQueue::heapifyUp(size_t i) { // decleration of the function heapifyUP whichtakes argument i of type size _ t
    while (i > 1 && nodes_[i].first < nodes_[i/2].first) { // while loop that runs the index i is greater thn 1 and node at i is less than i/2
        std::swap(nodes_[i], nodes_[i/2]);// if while loop is true, then they are swapped using the std::swap()
        i = i/2; // index i is updated to 1/2
    }
}

void PriorityQueue::heapifyDown(size_t i) { // decleraton of ehapifyDown which takes arguemnt i of size_t
    while (2*i <= size_) { // while loop that runs while index i has 2*i child
        size_t j = 2*i; // sets j to the index of left child i
        if (j < size_ && nodes_[j+1].first < nodes_[j].first) { // checks the right child i exists and has a smaller key value than the left child  if it is true then heap is satisfied
            j++; // j is incremented
        }
        if (nodes_[i].first <= nodes_[j].first) { // checks if the keyvalue of the nodesi first is less than or eual to nodes j first.if satisfied it breaks
            break; // breaks 
        }
        std::swap(nodes_[i], nodes_[j]); // nodes are swapped if i is grater than j using the swap function 
        i = j; // i is updated to the swapped node
    }
}

void PriorityQueue::removeNode(size_t i) { // decleration of the remove node with argument i of size_t
    // swap root with end
    nodes_[i] = nodes_[size_--]; // swapping the root with ther end as shon above
    // delete old root
    nodes_.erase(nodes_.end()); // erasing the old root as shown above
    if (i > 1 && nodes_[i].first < nodes_[i/2].first) { // of statement whcich shows that i has to begreater than 1 and child is less han parent
        heapifyUp(i); // if above is true, this code is run
    } else { // else statemnt if the if statement does not work
        heapifyDown(i); // heapifyDown is run insetad
    }
}

Key PriorityQueue::getKey(size_t i) { //getKey is given the vae of size_t i witthe new key value
    return nodes_[i].first; // node is returned at the very end
}
