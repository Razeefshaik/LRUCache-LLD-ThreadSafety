#include<bits/stdc++.h>
using namespace std;

template <typename K, typename V>

struct Node{
  
  K key;
  V val;
  Node* next;
  Node* prev;
  Node(K key, V val){
    this->key=key;
    this->val=val;
    next=nullptr;
    prev=nullptr;
  }

  Node(){
    
    next=nullptr;
    prev=nullptr;
  }
};

template <typename K, typename V>
class DoublyLinkedList{
    Node<K,V>* head;
    Node<K,V>* tail;
    
 public:
    DoublyLinkedList(){
          head= new Node<K,V>();
          tail= new Node<K,V>();

          head->next=tail;
          tail->prev=head;
    }

    ~DoublyLinkedList(){
        delete head;
        delete tail;
    }

    void addNode(Node<K, V>* node) {
        node->next = head->next;
        node->prev = head;

        head->next->prev = node;
        head->next = node;
    }

    void addNode(K k, V v){
        Node<K,V>* node= new Node<K,V>(k,v);
        
        node->next= head->next;
        head->next->prev=node;
        head->next=node;
        node->prev=head;
    }

    void remove(Node<K,V>* node){
        Node<K,V>* l=node->prev;
        Node<K,V>* r= node->next;
        l->next=r;
        r->prev=l;
    }

    void moveFront(Node<K,V>* node){
        remove(node);
        node->next=head->next;
        head->next->prev=node;
        head->next= node;
        node->prev=head;
    }

    Node<K,V>* removeLast(){
        if(tail->prev==head) return nullptr;
        Node<K,V>* node= tail->prev;
        remove(node);
        return node;
    }
};
