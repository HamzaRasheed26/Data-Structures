#include <iostream>

using namespace std;

class Node
{
    public: 
		int Data;
		string color;
		Node* parent;
    	Node* left;
    	Node* right;
    		
    public: Node(int data, string c)
    {
    	Data = data;
    	color = c;
    	parent = NULL;
    	left = NULL;
    	right = NULL;
	}
	
	public: Node(int data)
    {
    	Data = data;
    	color = "";
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

class RedBlackTree
{
	private: Node* root ;
	
	public:
		RedBlackTree()
	    {
	    	root = NULL;
	    }
	    
	    ~RedBlackTree()
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
			Node* y = z;
			Node* x;
			string yColor = y->color;
			if (z->left == NULL)
			{
				x = z->right;
				Transplant(z, z->right);
			}
			else if(z->right == NULL)
			{
				x = z->left;
				Transplant(z, z->left);
			}
			else 
			{
				y = treeMinimum(z->right);
				yColor = y->color;
				x = y->right;
				if(y->parent == z)
					x->parent = y;
				else
				{
					Transplant(y, y->right);
					y->right = z->right;
					y->right->parent = y;
				}
				Transplant(z, y);
				y->left = z->left;
				y->left->parent = y;
				y->color = z->color;
			}
			if( yColor == "black")
				DeleteFixUp(x);
		}
		
		void DeleteFixUp(Node* x)
		{
			while(x != root && x->color == "black")
			{
				if(x == x->parent->left)
				{
					Node* w = x->parent->right;
					if (w->color == "red")
					{
						w->color = "black";
						x->parent->color = "red";
						LeftRotate(x->parent);
						w = x->parent->right;
					}
					if( w->left->color == "black" && w->right->color == "black")
					{
						w->color = "red";
						x = x->parent;
					}
					else 
					{
						if (w->right->color == "black")
						{
							w->left->color = "black";
							w->color = "red";
							RightRotate(w);
							w = x->parent->right;
						}
						w->color = x->parent->color;
						x->parent->color = "black";
						w->right->color = "black";
						LeftRotate(x->parent);
						x = root;
					}
				}
				else 
				{
					Node* w = x->parent->left;
					if (w->color == "red")
					{
						w->color = "black";
						x->parent->color = "red";
						RightRotate(x->parent);
						w = x->parent->left;
					}
					if( w->right->color == "black" && w->left->color == "black")
					{
						w->color = "red";
						x = x->parent;
					}
					else 
					{
						if (w->left->color == "black")
						{
							w->right->color = "black";
							w->color = "red";
							LeftRotate(w);
							w = x->parent->left;
						}
						w->color = x->parent->color;
						x->parent->color = "black";
						w->left->color = "black";
						RightRotate(x->parent);
						x = root;
					}
				}
				x->color = "black";
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
		
		void LeftRotate(Node* x)
		{
			Node* y = x->right;
			x->right = y->left;
			if (y->left != NULL)
				y->left->parent = x;
			y->parent = x->parent;
			
			if (x->parent == NULL)
				root = y;
			else if (x == x->parent->left)
				x->parent->left= y;
			else 
				x->parent->right = y;
			y->left = x;
			x->parent = y;
		}

		void RightRotate(Node* x)
		{
			Node* y = x->left;
			x->left = y->right;
			if (y->right != NULL)
				y->right->parent = x;
			y->parent = x->parent;
			
			if (x->parent == NULL)
				root = y;
			else if (x == x->parent->right)
				x->parent->right= y;
			else 
				x->parent->left = y;
			y->right = x;
			x->parent = y;
		}
		
		void insert(int k)
		{
			Node* z = new Node(k);
			Node* y = NULL;
			Node* x = root;
			while (x != NULL)
			{
				y = x;
				if (z->Data < x->Data)
					x = x->left;
				else
					x = x->right;
			}
			z->parent = y;
			if (y == NULL)
				root = z;
			else if (z->Data < y->Data)
				y->left = z;
			else 
				y->right = z;
			z->left = NULL;
			z->right = NULL;
			z->color = "red";
			InsertFixUp( z);
		}
		
		
		void InsertFixUp(Node* z)
		{
			while (z->parent != NULL && z->parent->color == "red")
			{
				
				if (z->parent == z->parent->parent->left)
				{
					Node* y = z->parent->parent->right;
					if(y != NULL &&  y->color == "red")
					{
						z->parent->color = "black";
						y->color = "black";
						z->parent->parent->color = "red";
						z = z->parent->parent;
					}
					else 
					{
						if (z == z->parent->right)
						{
							z = z->parent;
							LeftRotate(z);
						}
						z->parent->color = "black";
						z->parent->parent->color = "red";
						RightRotate(z->parent->parent);
					}
				}
				else
				{
					Node* y = z->parent->parent->left;
					if(y != NULL && y->color == "red")
					{
						z->parent->color = "black";
						y->color = "black";
						z->parent->parent->color = "red";
						z = z->parent->parent;
					}
					else 
					{
						if (z == z->parent->left)
						{
							z = z->parent;
							RightRotate(z);
						}
						z->parent->color = "black";
						z->parent->parent->color = "red";
						LeftRotate(z->parent->parent);
					}
				}
			}
			root->color = "black";
		}
		
	};


int main()
{
    cout << "Hamza" << endl;
    
    RedBlackTree tree;
    tree.insert(5);
    tree.insert(7);
    tree.insert(3);
	tree.insert(8);
	tree.insert(4);
	tree.insert(2);
	tree.insert(1);
	tree.insert(0);
	    
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
