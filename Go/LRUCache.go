package main


import (
	"fmt"
	"sync"
)

type Node struct{
	key int
	val int
	next  *Node
	prev  *Node 
}


type DoublyLinkedList struct{
	head *Node
	tail *Node
}

func NewDoublyLinkedList() *DoublyLinkedList{

	
	head:= &Node{}
	tail:= &Node{}
	head.next=tail;
	tail.prev=head;
	return &DoublyLinkedList{
		head :head,
		tail : tail,
	}
}

func (list *DoublyLinkedList)AddNode(node *Node){
        node.next = list.head.next
		node.prev = list.head

		list.head.next.prev = node
		list.head.next = node
}

func (list *DoublyLinkedList) Remove(node *Node){
	node.prev.next = node.next
	node.next.prev = node.prev

	node.prev = nil
	node.next = nil
}

func (list *DoublyLinkedList) MoveToFront(node *Node){
	list.Remove(node)
	list.AddNode(node)
}

func (list *DoublyLinkedList) RemoveLast() *Node {
	if list.tail.prev == list.head {
		return nil
	}

	node := list.tail.prev
	list.Remove(node)

	return node
}


type LRUCache struct{
	capacity int
	mpp map[int]*Node
	list *DoublyLinkedList
	mutex sync.Mutex

}

func NewLRUCache(cap int) *LRUCache{

	return &LRUCache{
		capacity: cap,
		mpp: make(map[int]*Node),
		list: NewDoublyLinkedList(),
	}
}

func (lru *LRUCache) Get(key int)(int, bool){
	lru.mutex.Lock()
	defer lru.mutex.Unlock()

	node, exists := lru.mpp[key]
	if !exists {
		return 0, false
	}

	lru.list.MoveToFront(node)
	return node.val, true
}

func (lru *LRUCache) Put(key int, value int) {
	lru.mutex.Lock()
	defer lru.mutex.Unlock()

	if lru.capacity <= 0 {
		return
	}

	if node, exists := lru.mpp[key]; exists {
		node.val = value
		lru.list.MoveToFront(node)
		return
	}

	if len(lru.mpp) >= lru.capacity {
		lastNode := lru.list.RemoveLast()

		if lastNode != nil {
			delete(lru.mpp, lastNode.key)
		}
	}

	newNode := &Node{
		key:   key,
		val: value,
	}

	lru.list.AddNode(newNode)
	lru.mpp[key] = newNode
}

func main() {
	cache := NewLRUCache(3)

	cache.Put(1, 10)
	cache.Put(2, 20)
	cache.Put(3, 30)

	if value, found := cache.Get(1); found {
		fmt.Println("Key 1:", value)
	}

	cache.Put(4, 40) // Evicts key 2

	if _, found := cache.Get(2); !found {
		fmt.Println("Key 2 was evicted")
	}

	if value, found := cache.Get(4); found {
		fmt.Println("Key 4:", value)
	}
}

 