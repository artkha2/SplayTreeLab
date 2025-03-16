#include <iostream>
#include <string>

using namespace std;

// KeyValuePair class to store key-value pairs
class KeyValuePair {
    string key;
    string value;
public:

    KeyValuePair(const string& k, const string& v) : key(k), value(v) {}

    string get_key() {
        return key;
    }

    string get_value() {
        return value;
    }

    void set_value(const string& v) {
        value = v;
    }

    void set_key(const string& k) {
        key = k;
    }

    bool operator<(const KeyValuePair& other) const {
        return key < other.key;
    }

    bool operator>(const KeyValuePair& other) const {
        return key > other.key;
    }

    bool operator==(const KeyValuePair& other) const {
        return key == other.key;
    }
};


// Splay Tree implementation
class SplayTree {
    // Nested Node class
    class Node {
    public:
        KeyValuePair data;
        Node* left;
        Node* right;
    
        Node(const string& key, const string& value) : data(key, value), left(nullptr), right(nullptr) {}
        ~Node() {
            delete left;
            delete right;
        }
    };

    Node* root;

    // Right rotation
    Node* right_rotate(Node* y) {
        Node* x  = y->left;
        Node* T2 = x->right;

        x->right = y;
        y->left = T2;

        return x; // new root
    }

    // Left rotation
    Node* left_rotate(Node* x) {
        Node* y = x->right;
        Node* T2 = y->left;

        y->left = x;
        x->right = T2;

        return y; // new root
    }

    // Splay operation. Takes root of subtree and the key to splay as arguments, returns new root of the subtree
    // If key is present, brings it to root. If not, bring the last accessed item to the root.
    Node* splay(Node* root, string key) {
        // Base case: root is null or key is at the root
        if (root == nullptr || root->data.get_key() == key)
            return root;
        
        // Key is in left subtree
        if (root->data.get_key() > key) {
            
            if (root->left == nullptr) 
                return root; // Key not in tree, return root
            
            // Zig-zig (left left)
            if (root->left->data.get_key() > key) {
                root->left->left = splay(root->left->left, key);
                root = right_rotate(root);
            }
            // Zig-zag (left right)
            else if (root->left->data.get_key() < key) {
                root->left->right = splay(root->left->right, key);
                if (root->left->right != nullptr)
                    root->left = left_rotate(root->left);
            }
            return (root->left == nullptr) ? root : right_rotate(root);
        }
        // Key is in the right subtree
        else {
            if (root->right == nullptr)
                return root; // Key is not in the tree
            
            // Zag-zig (right left)
            if (root->right->data.get_key() > key) {
                root->right->left = splay(root->right->left, key);
                if (root->right->left != nullptr)
                    root->right = right_rotate(root->right);
            }

            // Zag-zag (right right) 
            else if (root->right->data.get_key() < key) {
                root->right->right = splay(root->right->right, key);
                root = left_rotate(root);
            }
            return (root->right == nullptr) ? root : left_rotate(root);
        }
    }

public:
    SplayTree() : root(nullptr) {}

    ~SplayTree() {
        delete root;
    }

    Node* get_root(){
        return root;
    }

    // Insert, return newly inserted node
    Node* insert(const string& key, const string& value) {
        if (!root) {
            // if empty tree, insert root
            root = new Node(key, value);
            return root;
        }
        root = splay(root, key);  // search for key, splay and return it if it already exists
        // otherwise perform rotations so that the last accessed leaf node becomes the new root
        // In other words, splay the node with the closest value to key

        if (root->data.get_key() == key) {
            root->data.set_value(value);  // if key already exists, update its value
            return root;
        }

        Node* new_node = new Node(key, value);
        if (key < root->data.get_key()) {  // Key is in the left subtree
            new_node->right = root;
            new_node->left = root->left;
            root->left = nullptr;
        }
        else {  // Key is in the right subtree
            new_node->left = root;
            new_node->right = root->right;
            root->right = nullptr;
        }
        root = new_node;
        return root;
    }

    // Access a specific key
    string get(const string& key) {
        // Splay, return value if key found, empty string otherwise
        root = splay(root, key);
        return (root && root->data.get_key() == key) ? root->data.get_value() : "";
    }

    // Delete a key, return new root
    Node* delete_key(const string& key) {
        if (!root)
            return nullptr;
        root = splay(root, key);  // splay given key
        
        if (root->data.get_key() != key)
            return root;  // if root's key doesn't match, given key is not in the tree
        
        Node* temp;
        if (!root->left) {
            // if root has no left child, root's right child become new root
            temp = root;
            root = root->right;
        }
        else {
            temp = root;
            // key is in the root, so splaying that key starting at the root's left child
            // will result in a tree without right subtree
            root = splay(root->left, key);
            root->right = temp->right;
        }
        temp->left = nullptr;  // without this, dangling pointers break the tree
        temp->right = nullptr;
        delete temp;
        return root;
    }

    // print preorder traversal
    void pre_order(Node* root) {
        if (root) {
            cout << root->data.get_key() << "," << root->data.get_value() << "  ";
            pre_order(root->left);
            pre_order(root->right);
        }
    }
};

// TreeMap class utilizing the SplayTree
class TreeMap {
    SplayTree tree;

public:
    void insert(const string& key, const string& value) {
        tree.insert(key, value);
    }

    string get(const string& key) {
        return tree.get(key);
    }

    void delete_key(const string& key) {
        tree.delete_key(key);
    }

    void pre_order(){
        tree.pre_order(tree.get_root());
    }
    
};

int main() {
    TreeMap map;
    map.insert("keyOne", "valueOne");
    cout << "Tree after inserting keyOne: ";
    map.pre_order();
    cout << endl;

    map.insert("keyTwo", "valueTwo");
    cout << "Tree after inserting keyTwo: ";
    map.pre_order();
    cout << endl;

    map.insert("keyThree", "valueThree");
    cout << "Tree after inserting keyThree: ";
    map.pre_order();
    cout << endl;

    cout << "keyOne value: ";
    cout << map.get("keyOne") << endl;
    cout << "Tree after accessing keyOne: ";
    map.pre_order();
    cout << endl;

    cout << "keyThree value: ";
    cout << map.get("keyThree") << endl;
    cout << "Tree after accessing keyThree: ";
    map.pre_order();
    cout << endl;

    cout << "keyDoesNotExist value: ";
    cout << map.get("keyDoesNotExist") << endl;
    cout << "Tree after trying to access a non-existing key KeyDoesNotExit: ";
    map.pre_order();
    cout << endl;

    
    map.delete_key("keyOne");
    cout << "Tree after deleting keyOne: ";
    map.pre_order();
    cout << endl;

    cout << "keyOne value: ";
    cout << map.get("keyOne") << endl;
    cout << "Tree after trying to access keyOne: ";
    map.pre_order();
    cout << endl;

    map.delete_key("KeyDoesNotExist");
    cout << "Tree after trying to delete a non-existing key KeyDoesNotExit: ";
    map.pre_order();
    cout << endl;

    map.insert("keyTwo", "newValue");
    cout << "Tree after updating keyTwo: ";
    map.pre_order();
    cout << endl;

}



