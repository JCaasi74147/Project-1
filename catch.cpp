#define CATCH_CONFIG_MAIN  
#include "catch.hpp"
#include "StudentAVLTree.h"  

TEST_CASE("Incorrect Commands", "[StudentAVLTree]") {
    StudentAVLTree tree;
    unsigned int initialSize = tree.getSize();

    // Test 5 incorrect commands
    tree.insert("A11y@", "45679999");  // Invalid name with special char
    REQUIRE(tree.getSize() == initialSize);

    tree.insert("Ally", "456");  // Invalid ID (too short)
    REQUIRE(tree.getSize() == initialSize);
    
    tree.insert("Ally", "123456789");  // Invalid ID (too long)
    REQUIRE(tree.getSize() == initialSize);

    tree.insert("Ally", "45679999");  // Valid insert
    tree.insert("Ally", "45679999");  // Duplicate ID
    REQUIRE(tree.getSize() == initialSize + 1);

    tree.remove(0);  // Invalid remove
    REQUIRE(tree.getSize() == initialSize + 1);
}

TEST_CASE("Edge Cases", "[StudentAVLTree]") {
    StudentAVLTree tree;
    unsigned int initialSize = tree.getSize();

    // 3 edge cases
    tree.remove("12345678");  
    REQUIRE(tree.getSize() == initialSize);

    tree.insert("hi", "99999991");
    initialSize = tree.getSize();
    tree.removeNthInorder(2);
    REQUIRE(tree.getSize() == initialSize);

    tree.insert("hi", "99999991");
    REQUIRE(tree.getSize() == initialSize);

    tree.insert("whatsup", "00012944")

}

TEST_CASE("Test Rotations", "[StudentAVLTree]") {
    StudentAVLTree tree;
    tree.insert("A", "10000000");
    tree.insert("B", "20000000");
    tree.insert("C", "30000000");
    tree.insert("D", "25000000");
    tree.insert("E", "50000000");
    tree.insert("F", "10000000");
    REQUIRE(tree.isTreeBalanced() == true);  
}

TEST_CASE("Deletion Cases", "[StudentAVLTree]") {
    StudentAVLTree tree;
    tree.insert("Root", "10000010");
    tree.insert("LeftChild", "10000005");
    tree.insert("RightChild", "10000020");
    tree.insert("LeafA", "10000002");
    tree.insert("LeafB", "10000008");

    int initialSize = tree.getSize();

    // Node with no children
    tree.remove("10000002");  
    REQUIRE(tree.getSize() == initialSize - 1);

    initialSize = tree.getSize();

    // Node with one child 
    tree.remove("10000005");  
    REQUIRE(tree.getSize() == initialSize - 1);

    // Insert another node to keep the root with two children
    tree.insert("NewLeftChild", "10000004");
    initialSize = tree.getSize();

    // Node with two 
    tree.remove("10000010"); 
    REQUIRE(tree.getSize() == initialSize - 1);
}

TEST_CASE("Bulk Insert and Delete", "[StudentAVLTree]") {
    StudentAVLTree tree;
    for(int i = 1; i <= 100; ++i) {
        tree.insert("Student", std::to_string(10000000 + i));
    }
    REQUIRE(tree.getSize() == 100);

    // Removing random 10 nodes
    for(int i = 10; i <= 19; ++i) {
        tree.remove(std::to_string(10000000 + i));
    }
    REQUIRE(tree.getSize() == 90);

    std::vector<std::string> inorder = tree.inorderTraversal(tree.head);

    REQUIRE(inorder.size() == 90);
}