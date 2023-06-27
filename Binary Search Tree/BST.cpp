#include <iostream>

using namespace std;

class Node
{
    public: 
		int Data;
		Node* parent;
    	Node* left;
    	Node* right;
    		
    public: Node(int data)
    {
    	Data = data;
    	parent = NULL;
    	left = NULL;
    	right = NULL;
	}
	
	public: Node()
    {
    	Data = NULL;
    	parent = NULL;
    	left = NULL;
    	right = NULL;
	}	
};

class BST
{
	private: Node* root ;
	
	public:
		BST()
	    {
	    	root = new Node();
	    }
	    
	    ~BST()
	    {
		}
	    
	    Node* getTree()
	    {
	    	return root;
		}
	    
	    bool isEmpty()
	    {
	    	return root ==NULL;
		}
		
		void inOrderTraversal(Node* T)
		{
			if (T != NULL)
			{
				inOrderTraversal(T->left);
				cout << T->Data << endl;
				inOrderTraversal(T->right);
			}
		}

		void preOrderTraversal(Node* T)
		{
			if (T != NULL)
			{
				cout << T->Data << endl;
				preOrderTraversal(T->left);
				preOrderTraversal(T->right);
			}
		}

		void postOrderTraversal(Node* T)
		{
			if (T != NULL)
			{
				postOrderTraversal(T->left);
				postOrderTraversal(T->right);
				cout << T->Data << endl;
			}
		}
						
		Node* findNode(int x)
		{
			Node* p = root;
			
			while (p->left != NULL || p->right != NULL)
			{
				if (x == p->Data)
				{
					return p;
				}
				else if (x < p->Data )
				{
					if (p->left == NULL)
						break;
					p = p->left;
				}
				else if (x > p->Data )
				{
					if (p->right == NULL)
						break;
					p = p->right;
				}
			}
			return p;
		}
		
		Node* insertNode(int x)
		{
			if ( root->Data == NULL)
			{
				root = new Node(x);
				return root;
			}
			
			Node* N = new Node(x);
			Node* p = findNode(x);
			
			if (p->Data == N->Data)
			{
				return N;
			}
			else if (p->Data < N->Data)
			{
				N->right = p->right;
				p->right = N;
				N->parent = p;
			}
			else if (p->Data > N->Data)
			{
				N->left = p->left;
				p->left = N;
				N->parent = p;
			}
			return N;
		}

		int NumberofNodes(Node* T)
		{
			int count = 0;
			if (T != NULL)
			{
				count = 1;
				count += NumberofNodes(T->left);
				count += NumberofNodes(T->right);
			}
			return count;
		}
		
		int Height(Node* T)
		{
			int left = 0, right = 0;
			if (T != NULL)
			{
				right = left = 1;
				left += Height(T->left);
				right += Height(T->right);
			}
			
			if (left > right)
				return left;
			else
				return right;
		}
		
		void LeafNodes(Node* T)
		{
			if (T != NULL)
			{
				LeafNodes(T->left);
				if (T->left == NULL && T->right == NULL)
					cout << T->Data<< endl;
					
				LeafNodes(T->right);
			}
		}
        
        bool isBST(Node* T)
		{
		    if (T == NULL)
		        return true ;
		    
		    if (T->left != NULL && T->left->Data > T->Data)
		        return false ;
		    if (T->right != NULL && T->right->Data < T->Data)
		        return false;
		    
		    if (isBST(T->left) && isBST(T->right))
		        return true;
		    return false;
		}


        Node* treeMinimum(Node* x)
		{
			while(x->left != NULL)
				x = x->left;
			return x;
		}

		Node* treeMaximum(Node* x)
		{
			while(x->right != NULL)
				x = x->right;
			return x;
		}

		Node* Successor(Node* x)
		{
			if (x->right != NULL)
				return treeMinimum(x->right);
			Node* y = x->parent;
			while(y != NULL && x == y->right)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}

		Node* Predrcessor(Node* x)
		{
			if (x->left != NULL)
				return treeMaximum(x->left);
			Node* y = x->parent;
			while(y != NULL && x == y->left)
			{
				x = y;
				y = y->parent;
			}
			return y;
		}
        

		void Transplant(Node* u, Node* v)
		{
			if(u->parent == NULL)
				root = v;
			else if(u == u->parent->left)
				u->parent->left = v;
			else
				u->parent->right = v;
			if(v != NULL)
				v->parent = u->parent;
		}
		
		void Delete(Node* z)
		{
			if (z->left == NULL)
				Transplant(z, z->right);
			else if(z->right == NULL)
				Transplant(z, z->left);
			else 
			{
				Node* y = treeMinimum(z->right);
				if(y->parent != z)
				{
					Transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				Transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
			}
		}
		
		Node* Search(Node* x, int k)
		{
			if (x == NULL || k == x->Data)
				return x;
			if (k < x->Data)
				return Search(x->left, k);
			else
				return Search(x->right, k);
		}
	};


int main()
{
    cout << "Hamza" << endl;
    
    BST tree;
    tree.insertNode(5);
    tree.insertNode(7);
    tree.insertNode(3);
	tree.insertNode(8);
	tree.insertNode(4);
	tree.insertNode(2);
	tree.insertNode(1);
	tree.insertNode(0);
	
	    
    tree.inOrderTraversal(tree.getTree());
    
    
    cout << "count " << tree.NumberofNodes(tree.getTree()) << endl;
    cout << "height " << tree.Height(tree.getTree()) << endl;
    cout << "Is BST " << tree.isBST(tree.getTree()) << endl;
	
	Node* y = tree.Search(tree.getTree(), 5);
	
	Node* z = tree.Successor(y);
	cout << "suc" << z->Data << endl;
	cout << ".." << (y->Data ) <<endl;
	tree.Delete(y);
	
	tree.inOrderTraversal(tree.getTree());
    
    
    return 0;
}
