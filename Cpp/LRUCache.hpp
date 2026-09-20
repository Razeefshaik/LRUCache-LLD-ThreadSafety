#include<bits/stdc++.h>
#include <mutex>

#include "DoublyLinkedList.hpp"
using namespace std;

template <typename K, typename V>
class LRUCache{
    private:
     int capacity;
     DoublyLinkedList<K,V> list;
     unordered_map<K, Node<K,V>*> mpp;
     mutex mtx;

    public:
    LRUCache(int cap){
        this->capacity=cap;
        mpp.clear();
    }
    ~LRUCache() {
       
        for (auto& pair : mpp) {
            delete pair.second;
        }
    }

    optional<V> get(const K &k){
        lock_guard<mutex> lock(mtx); 

        auto it= mpp.find(k);
        if(it==mpp.end()){
            return nullopt;
        }
        V v= it->second->val;
        list.moveFront(it->second);
        return v;

    }

    void put(const K& k, const V& v){
        lock_guard<mutex> lock(mtx);

        auto it= mpp.find(k);
        if(it!=mpp.end()){
            Node<K,V>* node= it->second;
            node->val= v;
            list.moveFront(node);
        }else{
            if(mpp.size()>=capacity){
                Node<K,V>* node= list.removeLast();
                if(node!=NULL){
                    mpp.erase(node->key);
                    delete node;
                }
            }

            Node<K,V>* node=new Node<K,V>(k,v);
            list.addNode(node);
            mpp[k]=node; 
        }
    }
};
