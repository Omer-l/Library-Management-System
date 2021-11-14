#ifndef BST_hpp
#define BST_hpp

struct Node
{
    std::string key;
    Book value;
    Node* left;
    Node* right;
    
    Node(std::string key, Book value)
    {
        this->key = key;
        this->value = value;
        left = right = nullptr;
    }
};

class BST {
private:
    Node* root;
    
    Book& get(Node* root, std::string key)
    {
        // root's key is key, then return it
        if (key == root->key)
        {
            return root->value;
        } else if (key < root->key)
        { //if root is less than it, check if the next one is !root AKA nullptr.
            
            //if there is no root left, put new element there.
            if (!root->left)
            {
                root->left = new Node(key, Book());
                return root->left->value;
            }
            //if there is another left branch
            return get(root->left, key);
        } else
        { //ELSE, key is more than root's key.
            
            //if there is no root right, put searched node there.
            if (!root->right)
            {
                root->right = new Node(key, Book());
                return root->right->value;
            }
            //if there is a right node, perform function with right node and same searched key.
            return get(root->right, key);
        }
    }
    
    //GETS the min
    Node* min(Node* node)
    {
        //if there is no more left node..
        if (!node->left)
            //return the current node.
            return node;
        else
            return min(node->left);
    }
    
    //DELETES the min, and returns the result.
    Node* remove_min(Node* node)
    {
        if (!node->left)
        {
            Node* temp = node->right;
            delete node;
            return temp;
        }
        node->left = remove_min(node->left);
        return node;
    }
    
    Node* remove (Node* node, std::string key)
    {
        //do nothing
        if (!node)
            return nullptr;
        
        if (key < node->key)
        {// if key smaller than current node key, search for removal from left
            node->left = remove(node->left, key);
        } else if (key > node->key)
        {// if key larger than current node key: search for removal from right
            node->right = remove(node->right, key);
        } else
        {// Node to delete has only left child?
            if (!node->right)
            { // replace with left
                Node* temp = node->left;
                delete node;
                //return left child.
                return temp;
            }
            //Node to delete has only right child?
            if (!node->left)
            { // 1 link, replace with right
                Node* temp = node->right;
                delete node;
                return temp;
            }
            
            //If node to delete has two children
            // 2 links: swap node with min from the right
            Node* temp = node;
            
            // copy min(temp->right) as it will be removed below(using remove_min function later), node itself becomes the furthest left of right child
            node = new Node(*min(temp->right));
            
            //connect new node to it's left and right childs
            node->right = remove_min(temp->right);
            //left stays the same as we don't touch the left children.
            node->left = temp->left;
            //we don't need temp anymore
            delete temp;
        }
        return node;
    }
    
    void display_A_Z(Node* node)
    {
        if (node != nullptr)
        {
            // display A - Z
            display_A_Z(node->left);
            node->value.toString();
            display_A_Z(node->right);
        }
    }
    
    void display_Z_A(Node* node)
    {
        if (node != nullptr)
        {
            // display Z - A
            display_Z_A(node->right);
            node->value.toString();
            display_Z_A(node->left);
        }
    }
    
    void partialSearch(Node* node, std::string userInput, std::string firstLetterCap)
    {
        int count = 0;
        
        if (node != nullptr)
        {
            // search in order
            partialSearch(node->left, userInput, firstLetterCap);
            if(node->key.find(userInput) != std::string::npos
               || node->key.find(firstLetterCap) != std::string::npos)
            {
                node->value.toString();
                count++;
            }
            
            partialSearch(node->right, userInput, firstLetterCap);
        }
    }
    
public:
    
    BST()
    {
        root = nullptr;
    }
    
    Book& operator[](std::string key)
    {
        //Create a temporary node
        if (!root)
        {
            root = new Node(key, Book());
            return root->value;
        }
        return get(root, key);
    }
    
    void display_A_Z() {
        display_A_Z(root);
        std::cout << "\n";
    }
    
    void display_Z_A() {
        display_Z_A(root);
        std::cout << "\n";
    }
    
    void partialSearch(std::string userInput)
    {
        //make first letter capital
        std::stringstream firstLetterCap;
        firstLetterCap << (char)toupper(userInput[0]) << userInput.substr(1);
        
        partialSearch(root, userInput, firstLetterCap.str());
    }
    
    void remove(std::string key)
    {
        root = remove(root, key);
    }
    
};

#endif
