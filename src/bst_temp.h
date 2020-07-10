#pragma once
#include "../algo.h"

// WARNING : Including this file more than one compilation unit will cause a compile time error
//           this repo is not well coded to organize sources intentionally (only include in main.cpp).


struct BST {
	int data = 0;
	bool data_new = true;
	BST* left = nullptr;
	BST* right = nullptr;
	BST() {}
	BST(int _data) { data = _data; }

	void insert(int p_data) {
		BST* tree = this;
		while (tree) {
			if (tree->data <= p_data) {
				if (tree->right) tree = tree->right;
				else {
					tree->right = new BST(p_data);
					break;
				}
			} else {
				if (tree->left) tree = tree->left;
				else {
					tree->left = new BST(p_data);
					break;
				}
			}
		}
	}
};

void print_tree(BST* bst, std::string indentation = "", bool last_leaf = false) {
	printf("%s |__ ", indentation.c_str());

	if (last_leaf) indentation += "     ";
	else indentation += " |   ";

	if (bst) {
		if (bst->data_new) {
			cprint(std::to_string(bst->data).append("\n").c_str(), Color::D_YELLOW);
			bst->data_new = false;
		} else {
			printf("%i\n", bst->data);
		}
		print_tree(bst->left, indentation, false);
		print_tree(bst->right, indentation, true);
	} else {
		printf("NULL\n");
	}
}

/* TEST CASE:
	BST root;
	root.data = 12;
	for (int i = 0; i < 10; i++) {
		system("cls");
		set_cursor_pos(0, 0);
		root.insert(rand()%10+7);
		print_tree(&root);
		char c = getchar();

	}
*/