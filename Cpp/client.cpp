#include<bits/stdc++.h>
using namespace std;
#include "LRUCache.hpp"

int main() {
    cout << "=== LRU Cache Demo ===" << endl << endl;

    LRUCache<string, int> cache(3);

    cout << "1. Adding items to cache (capacity = 3)" << endl;
    cache.put("a", 1);
    cout << "   put('a', 1)" << endl; 
    cache.put("b", 2);
    cout << "   put('b', 2)" << endl;
    cache.put("c", 3);
    cout << "   put('c', 3)" << endl;
    cout << "   Cache state: {a=1, b=2, c=3}" << endl;

    cout << endl << "2. Accessing 'a' makes it most recently used" << endl;
    auto valueA = cache.get("a");
    cout << "   get('a') = " << (valueA.has_value() ? to_string(valueA.value()) : "nullopt") << endl;
    cout << "   Order now: b (LRU) -> c -> a (MRU)" << endl;

    cout << endl << "3. Adding 'd' should evict 'b' (the LRU item)" << endl;
    cache.put("d", 4);
    cout << "   put('d', 4)" << endl;
    auto valueB = cache.get("b");
    cout << "   get('b') = " << (valueB.has_value() ? to_string(valueB.value()) : "nullopt")
              << " (nullopt means evicted)" << endl;

    cout << endl << "4. Verifying other items still accessible" << endl;
    auto valC = cache.get("c");
    auto valA = cache.get("a");
    auto valD = cache.get("d");
    cout << "   get('c') = " << (valC.has_value() ? to_string(valC.value()) : "nullopt") << endl;
    cout << "   get('a') = " << (valA.has_value() ? to_string(valA.value()) : "nullopt") << endl;
    cout << "   get('d') = " << (valD.has_value() ? to_string(valD.value()) : "nullopt") << endl;

    cout << endl << "5. Updating existing key" << endl;
    cache.put("c", 30);
    cout << "   put('c', 30) - updates value and marks as MRU" << endl;
    auto updatedC = cache.get("c");
    cout << "   get('c') = " << (updatedC.has_value() ? to_string(updatedC.value()) : "nullopt") << endl;

    cout << endl << "6. Adding 'e' should evict 'a' (now the LRU)" << endl;
    cache.put("e", 5);
    cout << "   put('e', 5)" << endl;
    auto evictedA = cache.get("a");
    auto stillD = cache.get("d");
    cout << "   get('a') = " << (evictedA.has_value() ? to_string(evictedA.value()) : "nullopt")
              << " (nullopt means evicted)" << endl;
    cout << "   get('d') = " << (stillD.has_value() ? to_string(stillD.value()) : "nullopt") << endl;

    cout << endl << "=== Demo Complete ===" << endl;

    return 0;
}
