c/* Napisati program koji omoguæava rad s binarnim stablom pretraživanja.
Treba omoguæiti unošenje novog elementa u stablo, ispis elemenata
(inorder, preorder, postorder i level order), brisanje i pronalaženje nekog elementa.*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef struct node node;
typedef struct node* position;

struct node {
	int val;
	position left;
	position right;
};

position createNode(int val);
position insert(position root, int val);

int Inorder(position root);
int Preorder(position root);
int Postorder(position root);

position searchNode(position root, int val);
position deleteNode(position root, int val);
position Min(position root);

int main() {

	int rootVal = 0;
	int choice;
	position root = NULL;
	printf("Vrijednost root-a:\n");
	scanf("%d", &rootVal);
	root = insert(root, rootVal);
	while (1) {
		printf("Odaberite sto zelite:\n 1- Unijeti novu vrijednost\n 2- Inorder ispis\n 3- Preorder ispis\n 4- Postorder ispis\n 5- Pretrazivanje elementa\n 6- Brisanje elementa iz stabla\n");
		scanf("%d", &choice);
		if (choice == 1) {
			int value = 0;
			printf("Unesite vrijednost:\n");
			scanf("%d", &value);
			root = insert(root, value);
		}
		else if (choice == 2) {
			printf("Inorder ispis:\n");
			root = Inorder(root);
		}
		else if (choice == 3) {
			printf("Preorder ispis:\n");
			root = Preorder(root);
		}
		else if (choice == 4) {
			printf("Postorder ispis:\n");
			root = Postorder(root);
		}
		else if (choice == 5) {
			int value = 0;
			printf("Koju vrijednost zelite pretraziti:\n");
			scanf("%d", &value);
			position result = NULL;
			result = searchNode(root, value);
			if (result != NULL)
				printf("\nPronaden je element %d.\n", value);
			else
				printf("Element %d nije pronaden.\n", value);

		}
		else if (choice == 6) {
			int val = 0;
			printf("Unesite element koji zelite obrisati:\n");
			scanf("%d", &val);
			deleteNode(root, val);
		}

		else {
			printf("Pogresan odabir.\n");
		}
	}

	return 0;
}
position createNode(int val) {
	position newnode = NULL;
	newnode = (position)malloc(sizeof(struct node));
	if (newnode == NULL) {
		printf("Greska pri alociranju memorije.\n");
		return NULL;
	}
	newnode->val = val;
	newnode->left = NULL;
	newnode->right = NULL;
	return newnode;

}
position insert(position root, int val) {

	if (root == NULL) {
		root = createNode(val);
	}
	else if (val < root->val) {
		root->left = insert(root->left, val);
	}
	else if (val > root->val) {
		root->right = insert(root->right, val);
	}
	return root;
}
int Inorder(position root) {
	if (root != NULL) {
		root->left = Inorder(root->left);
		printf("%d ", root->val);
		root->right = Inorder(root->right);
	}
	return 0;
}
int Preorder(position root) {
	if (root != NULL) {
		printf("%d ", root->val);
		root->left = Preorder(root->left);
		root->right = Preorder(root->right);
	}
	return 0;
}
int Postorder(position root) {
	if (root != NULL) {
		root->left = Postorder(root->left);
		root->right = Postorder(root->right);
		printf("%d ", root->val);
	}
	return 0;
}
position searchNode(position root, int val) {
	if (root == NULL) {
		return NULL;
	}
	else if (val < root->val) {
		return searchNode(root->left, val);
	}
	else if (val > root->val) {
		return searchNode(root->right, val);
	}
	else
		return root;

}

position deleteNode(position root, int val) {
	if (root == NULL) {
		return root;
	}
	else if (val < root->val) {
		root->left = deleteNode(root->left, val);
	}
	else if (val > root->val) {
		root->right = deleteNode(root->right, val);
	}
	else {
		if (root->left == NULL) {
			position temp = root->right;
			free(root);
			return temp;
		}
		else if (root->right == NULL) {
			position temp = root->left;
			free(root);
			return temp;
		}

		//dvoje djece
		position temp = Min(root->right);
		root->val = temp->val;
		root->right = deleteNode(root->right, temp->val);
	}
	return root;
}

position Min(position root) {
	if (root == NULL) {
		return NULL;
	}
	else {
		if (root->left == NULL) {
			return root;
		}
		else {
			return findMin(root->left);
		}
	}
}
