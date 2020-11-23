#include <iostream>
#include <string>

using namespace std;

class AVLtree
{
	struct Node {
		double info{};
		Node* left = nullptr;
		Node* right = nullptr;
		Node* parent = nullptr;
		int height;
		Node() {}
		Node(double value) : Node()
		{
			info = value;
		}
		Node(double value, Node* ref) : Node(value)
		{
			parent = ref;
		}
		Node(double value, Node* ref, int height_value) : Node(value, ref)
		{
			height = height_value;
		}
	};

	double sum = 0;
	int amount = 0;
	Node* root;

public:
	AVLtree() : root(nullptr) {}

	Node* getRoot() { return root; }
	int getHeight(Node* tmp) { return ((tmp == nullptr) ? -1 : tmp->height); }
	int checkDifference(Node* tmp) { return (getHeight(tmp->right) - getHeight(tmp->left)); }
	double max(double a, double b) { return (a > b ? a : b); }

	void updateBalance(Node* tmp)
	{
		double left = -1, right = -1;
		if (tmp->left) { left = tmp->left->height; }
		if (tmp->right) { right = tmp->right->height; }
		tmp->height = 1 + max(left, right);
	}

	void LeftRotate(Node* x) {
		Node* nw_node = new Node();
		if (x->right->left) { nw_node->right = x->right->left; }
		nw_node->left = x->left;
		nw_node->info = x->info;
		x->info = x->right->info;

		x->left = nw_node;
		if (nw_node->left) { nw_node->left->parent = nw_node; }
		if (nw_node->right) { nw_node->right->parent = nw_node; }
		nw_node->parent = x;

		if (x->right->right) { x->right = x->right->right; }
		else { x->right = nullptr; }

		if (x->right) { x->right->parent = x; }

		updateBalance(x->left);
		if (x->right) { updateBalance(x->right); }
		updateBalance(x);
	}

	void RightRotate(Node* x) {
		Node* nw_node = new Node();
		if (x->left->right) { nw_node->left = x->left->right; }
		nw_node->right = x->right;
		nw_node->info = x->info;
		x->info = x->left->info;

		x->right = nw_node;
		if (nw_node->left) { nw_node->left->parent = nw_node; }
		if (nw_node->right) { nw_node->right->parent = nw_node; }
		nw_node->parent = x;

		if (x->left->left) { x->left = x->left->left; }
		else { x->left = nullptr; }

		if (x->left) { x->left->parent = x; }

		updateBalance(x->right);
		if (x->left) { updateBalance(x->left); }
		updateBalance(x);
	}

	void TreeFix(Node* tmp) {
		if (checkDifference(tmp) == 2) {
			if (checkDifference(tmp->right) < 0) { RightRotate(tmp->right); }
			LeftRotate(tmp);
			updateBalance(tmp);
		}
		else if (checkDifference(tmp) == -2) {
			if (checkDifference(tmp->left) > 0) { LeftRotate(tmp->left); }
			RightRotate(tmp);
			updateBalance(tmp);
		}
	}

	void rebalance(Node* tmp)
	{
		if (tmp == root) { TreeFix(root); }
		else {
			while (tmp != nullptr) {
				updateBalance(tmp);
				tmp = tmp->parent;
				if (tmp) { TreeFix(tmp); }
			}
		}
	}

	void insertNode(double value)
	{
		++amount;
		sum += value;
		if (root == nullptr)
			root = new Node(value, nullptr, 0);
		else
		{
			Node* linker = getRoot();
			Node* tmp = new Node();
			while (linker != nullptr)
			{
				if (linker->info > value)
				{
					if (linker->left == nullptr) { linker->left = tmp; tmp->height = 0; tmp->parent = linker; tmp->info = value; break; }
					else { linker = linker->left; }
				}
				else
				{
					if (linker->right == nullptr) { linker->right = tmp; tmp->height = 0; tmp->parent = linker; tmp->info = value; break; }
					else { linker = linker->right; }
				}
			}
			rebalance(tmp);
		}
	}

	void symmetricTraversal(Node* tmp) {
		if (tmp == nullptr) { return; }
		symmetricTraversal(tmp->left);
		cout << " -- " << tmp->info;
		symmetricTraversal(tmp->right);
	}

	double leavesSum = 0;
	double getSum(Node* tmp)
	{
		if (tmp != nullptr)
		{
			getSum(tmp->left);
			getSum(tmp->right);
			if (tmp->left == nullptr && tmp->right == nullptr)
				leavesSum += tmp->info;
			return leavesSum;
		}
		return 0;
	}

	double getAverage()
	{
		if (amount == 0) {
			return 0;
		}
		else
		return sum / amount;
	}
};

enum Code {
	Insert = 1,
	Traversal,
	Sum,
	Average,
	Exit
};

int main()
{
	AVLtree tree;
	double element;
	//int sum;
	//string a = "";
	//string c;
	//bool flag = 0;
	//int ss;
	//int b6 = 0;
	int code;

	while (true)
	{
		cout << "Choose action: \n 1) Insert element \n 2) Symmetric traversal \n 3) The sum of all the values of the leaves of the tree \n 4) Get the arithmetic mean of all nodes \n 5) Exit \n";
		cin >> code;
		switch (code)
		{
		case(Insert):
			cout << "Enter element: \n";
			cin >> element;
			tree.insertNode(element);
			break;
		case(Traversal):
			cout << "Symmetric Traversal:\n";
			tree.symmetricTraversal(tree.getRoot());
			cout << "\n";
		case(Sum):
			cout << "Sum of leaves:\n";
			cout << tree.getSum(tree.getRoot()) << "\n";
			break;
		case(Average):
			cout << "Average:\n";
			cout << tree.getAverage() << "\n";
			break;
		case(Exit):
			cout << "Stop program\n";
			return 0;
		default:
			cout << "Invalid code, try again\n";
			break;
		}
	}


	//while (true) {
	//	while (a != "1" && a != "2" && a != "3" && a != "4" && a != "5" && a != "6") {
	//		if (flag != 0) {
	//			cout << "Wrong value \n";
	//		}
	//		cout << "Choose action: \n 1) Insert element \n 2) Symmetric traversal \n 3) The sum of all the values of the leaves of the tree \n 4) Get the arithmetic mean of all nodes \n 5) Exit \n";
	//		cin >> a;
	//		++flag;
	//	}
	//	int b = stoi(a);
	//	flag = 0;
	//	a = "";
	//	switch (b) {
	//	case 1:
	//		cout << "Enter element: \n";
	//		cin >> choose;
	//		tree.insertNode(choose);
	//		break;
	//	case 2:
	//		cout << "Symmetric Traversal:\n";
	//		tree.symmetricTraversal(tree.getRoot());
	//		cout << "\n";
	//		break;
	//	case 3:
	//		cout << "Sum of leaves:\n";
	//		cout << tree.getSum(tree.getRoot()) << "\n";
	//		break;
	//	case 4:
	//		cout << "Average:\n";
	//		cout << tree.getAverage() << "\n";
	//		break;
	//	case 5:
	//		cout << "Exit..\n";
	//		return 0;
	//	default: 
	//		cout << "Invalid value entered \n";
	//	}
	//}
}