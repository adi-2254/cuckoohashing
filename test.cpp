#include <iostream>
#include <string>
#include <cassert>
#include "CuckooHashTable.h" // Ensure your header file is named this

void run_tests() {
    std::cout << "--- Starting Cuckoo Hash Table Tests ---\n\n";

    // Initialize with a small capacity to force rehashing early
    CuckooHashTable<int, std::string> map(8);

    // Test 1: Basic Insertions and Lookups
    std::cout << "[Test 1] Insertions & Lookups... ";
    map.insert(1, "Node A");
    map.insert(2, "Node B");
    map.insert(3, "Node C");
    
    assert(map.contains(1) == true);
    assert(map.contains(2) == true);
    assert(map.contains(3) == true);
    assert(map.contains(4) == false); // Should not exist
    std::cout << "Passed!\n";

    // Test 2: Updates to Existing Keys
    std::cout << "[Test 2] Updating Existing Keys... ";
    map.insert(2, "Node B_Updated");
    // Size should remain unchanged
    assert(map.size() == 3); 
    std::cout << "Passed!\n";

    // Test 3: Removals
    std::cout << "[Test 3] Removals... ";
    assert(map.remove(2) == true);
    assert(map.contains(2) == false);
    assert(map.remove(99) == false); // Attempting to remove non-existent key
    assert(map.size() == 2);
    std::cout << "Passed!\n";

    // Test 4: Forcing a Rehash (Capacity Expansion & Cycle Breaking)
    std::cout << "[Test 4] High Load & Automatic Rehashing... ";
    for (int i = 10; i < 30; ++i) {
        map.insert(i, "Data_" + std::to_string(i));
    }
    
    // Verify all inserted elements survived the rehash(es)
    for (int i = 10; i < 30; ++i) {
        assert(map.contains(i) == true);
    }
    assert(map.contains(1) == true); // Original elements should still be there
    assert(map.size() == 22);        // 2 original + 20 new
    std::cout << "Passed!\n\n";

    std::cout << "--- All Tests Completed Successfully! ---\n";
}

int main() {
    run_tests();
    return 0;
}
