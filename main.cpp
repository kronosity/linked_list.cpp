#include <iostream>
using namespace std;

enum {aIsSmaller, aIsLarger, aIsSame};

class Data {
    public:
        Data(int newVal) : value(newVal) {}
        ~Data(){}
        int compare(const Data&);
        void show() {cout << value << "\n"; } 
    private:    
        int value;
};

int Data::compare(const Data& otherData) {
    if (value < otherData.value) return aIsSmaller;
    if (value > otherData.value) return aIsLarger;
    else return aIsSame;
}

class Node;
class HeadNode;
class TailNode;
class InternalNode;

//ADT of nodes in list
class Node {
    public:
        Node(){}
        virtual ~Node(){}
        virtual Node* insert(Data* data) = 0;
        virtual void show() = 0;
    private:
};

class InternalNode : public Node {
    public:
        InternalNode(Data* data, Node* next);
        virtual ~InternalNode() {delete next; delete data; }
        virtual Node* insert(Data* data);
        virtual void show() { 
            (*data).show(); (*next).show(); 
        }
    
    private:
        Data* data;
        Node* next;
  
};

//constructor 
 InternalNode::InternalNode(Data* newData, Node* newNext):data(newData), next(newNext) {}
    
//this will store new object in the list, the Node will work out where it goes
Node* InternalNode::insert(Data* otherData) {
    int result = (*data).compare(*otherData); // comparing size
    switch (result) {
        case aIsSame: // drops
        case aIsLarger: //new data comes first
            {
                InternalNode* dataNode = new InternalNode(otherData, this);
                return dataNode;
            }
        
        case aIsSmaller: 
            next = (*next).insert(otherData);
            return this;
}
        return this; //  return for compiler.
}

    class TailNode: public Node {
        public: 
            TailNode() {}
            virtual ~TailNode(){}
            virtual Node* insert (Data* data);
            virtual void show() {}
        private:    
    };
    
Node* TailNode::insert(Data* data) {
    InternalNode* dataNode = new InternalNode(data, this);
    return dataNode;
}    

class HeadNode : public Node {
    public:
        HeadNode();
        virtual ~HeadNode(){ delete next; }
        virtual Node* insert(Data* data);
        virtual void show() {(*next).show();}
    private: 
    Node* next;
};

//starts the node in the list
HeadNode::HeadNode() {
    next = new TailNode;
}
//wack this straight in first.
Node* HeadNode::insert(Data* data) {
    next = (*next).insert(data);
    return this;
}

class LinkedList {
    public:
        LinkedList();
        ~LinkedList() {delete head;}
        void insert(Data* data);
        void showAll() { (*head).show(); }
    private:
        HeadNode* head;
};

LinkedList::LinkedList() {
    head = new HeadNode;
}

void LinkedList::insert(Data* pData) {
    (*head).insert(pData);
}


int main()
{   
    Data* pData;
    int val;
    LinkedList LL;
    
    while(true) {
        cout << "What value (0 to stop)? ";
        cin >> val;
        if (!val)
        break;
        pData = new Data(val);
        LL.insert(pData);
    }
    
    LL.showAll();
    return 0;
}
