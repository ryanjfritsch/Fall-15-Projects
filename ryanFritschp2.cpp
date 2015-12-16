//ryanFritschp2.cpp 
//09/09/2015
//Milestone #1
//1.0.1

/*
PROJECT DESCRIPTION
This project is designed to accept information about 'm' iPhone applications,
and store them in myAppStore using a binary search tree for struct tree.
Once applications are created using a struct, they are placed in the correct
spot on the binary search tree. They can then be searched for by name, category
name, and price. These iPhone applications are also stored in a hash table.
*/

#include "stdio.h"
#include <iostream>
#include <cstring>
#include <istream>
#include <math.h>
#include <fstream>
#include <omp.h>
#include <stdio.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <omp.h>

//ifstream Name; //define an input stream, need to include fstream.h

using namespace std;

#define CAT_NAME_LEN 25
#define APP_NAME_LEN 50
#define VERSION_LEN 10
#define UNIT_SIZE 3


struct app_info{
	char category[CAT_NAME_LEN]; // Name of category
	char app_name[APP_NAME_LEN]; // Name of the application
	char version[VERSION_LEN]; // Version number
	float size; // Size of the application
	char units[UNIT_SIZE]; // GB or MB
	float price; // Price in $ of the application
};


struct categories{
	char category[CAT_NAME_LEN]; // Name of category
	struct tree *root; // Pointer to root of search tree for this category
};


struct tree{ // A binary search tree
	app_info info; // Information about the application
	struct tree *parent;
	struct tree *left; // Pointer to the left subtree
	struct tree *right; // Pointer to the right subtree
} *root = NULL;



struct hash_table_entry{
	char app_name[APP_NAME_LEN]; // Name of the application
	struct tree *app_node; // Pointer to node in tree containing the application information
};

string com = "";
int n = 0;
int A = 0;

categories cats[100];

tree* getNewNode(app_info info){
	tree* newNode = (struct tree*)malloc(sizeof(struct tree));
	newNode->info = info;
	newNode->left = newNode->right = NULL;
	return newNode;
}

void freeT(tree* x){
	int freeApps = 0;
	if (x != NULL){
		freeT(x->left);

		if (x->info.price == 0.00){
			freeApps++;
			cout << x->info.app_name << endl;
		}

		freeT(x->right);
	}

	if (freeApps == 0){
		//cout << "No free applications found." << endl;
	}
}

int hashF(string in){
	int leng = in.length();
	int hashV = 0;

	for (int x = 0; x < leng; x++){
		hashV += (int)in[x];
	}

	return (hashV % A);
}

void priceT(tree* x, int low, int high){
	int freeApps = 0;
	if (x != NULL){
		priceT(x->left, low, high);

		if (x->info.price >= low && x->info.price <= high){
			freeApps++;
			cout << x->info.app_name << endl;
		}

		priceT(x->right, low, high);
	}

	if (freeApps == 0){
		cout << "No applications found for given range." << endl;
	}
}

void alphT(tree* x, string low, string high){
	int freeApps = 0;
	if (x != NULL){
		alphT(x->left, low, high);

		if ((x->info.app_name > low) && (x->info.app_name < high)){
			freeApps++;
			cout << x->info.app_name << endl;
		}

		alphT(x->right, low, high);
	}

	if (freeApps == 0){
		cout << "No applications found for given range." << endl;
	}
}

void traversal(tree* x){
	
	if (x != NULL){
	//cout << "Called Traversal" << endl;
		traversal(x->left);
		cout << x->info.app_name << endl;
		traversal(x->right);
	}
}


tree* getCat(char cat[]){
	for (int x = 0; x < A; x++){
		string catT = "";
		//cats[x]->category >> catT;
		if ((strcmp(cat, cats[x].category) == 0)){
			//cout << "Category Found!" << endl;
			return cats[x].root;
		}
	}

	return NULL;
}


void findCat(char cat[]){
	//cout << cat << endl;
	for (int x = 0; x < n; x++){
		string catT = "";
		//cats[x]->category >> catT;
		//cout << cats[x].category << endl;

		if ((strcmp(cat, cats[x].category) == 0)){
			//cout << "Category Found!" << endl;
			traversal(cats[x].root);
		}
	}
}

void Insert(tree* inroot){
	//cout << "Insert" << endl;

	for (int x = 0; x < A; x++){
		string catT = "";
		//cats[x]->category >> catT;
		if ((strcmp(inroot->info.category, cats[x].category) == 0)){
			if (cats[x].root == NULL){
				//cout << "This is the first node" << endl;
				cats[x].root = inroot;
			}
			else{
				struct tree *yptr = (struct tree *)malloc(sizeof(struct tree));
				struct tree *xptr = (struct tree *)malloc(sizeof(struct tree));

				yptr = NULL;
				xptr = cats[x].root;

				//cats[x].root->left = inroot;


				while (xptr != NULL){
					yptr = xptr;
					//cout << "XPTR: " << xptr->info.app_name << endl;
					//if(xptr->left != NULL) cout << "XPTRL: " << xptr->left->info.app_name << endl;
					//cout << "INR: " << inroot->info.app_name << endl;

					if (strcmp(inroot->info.app_name, xptr->info.app_name) > 0){
						if (xptr->right != NULL){ xptr = xptr->right; }
						else{ xptr->right = inroot; break; }
					}
					else{
						if (xptr->left != NULL){ xptr = xptr->left; }
						else{ xptr->left = inroot; break; }
					}

				}

			}
		}
		/*cout << cats[x].root->info.app_name << endl;

		if (cats[x].root->left->left != NULL){
		cout << cats[x].root->left->info.app_name << endl;
		}
		if (cats[x].root->right->l != NULL){
		cout << cats[x].root->right->info.app_name << endl;
		}*/

		//traversal(cats[x].root);

		break;
	}


}

bool TestForPrime(int val)
{
	int limit, factor = 2;

	limit = (long)(sqrtf((float)val) + 0.5f);
	while ((factor <= limit) && (val % factor))
		factor++;

	return(factor > limit);
}


void nodeDelete(){




}



int main()
{
	string N;
	getline(cin, N);
	//cin >> com;
	n = atoi(N.c_str());

	//cout << "M: " << n << endl;

	for (int i = 0; i < n; i++){
		string lineIn = "";
		getline(cin, lineIn);
		strcpy(cats[i].category, lineIn.c_str());
		//cout << "Cat " << cats[i].category << endl;
	}

	//int A = 0;
	string appN = "";
	//cin >> appN;
	getline(cin, appN);
	//cout << appN << endl;
	A = atoi(appN.c_str());

	int hashZ = A;

	while (!TestForPrime(hashZ)){
		hashZ++;
	}

	hash_table_entry* table = NULL;
	table = new hash_table_entry[hashZ];



	for (int y = 0; y < A; y++){
		struct app_info *ptr = (struct app_info *)malloc(sizeof(struct app_info));
		struct tree *ptr2 = (struct tree *)malloc(sizeof(struct tree));

		string N;
		getline(cin, N);
		strcpy(ptr->category, N.c_str());

		string B;
		getline(cin, B);
		strcpy(ptr->app_name, B.c_str());

		string C;
		getline(cin, C);
		strcpy(ptr->version, C.c_str());

		//cin >> ptr->category;
		//cin >> ptr->app_name;
		//cin >> ptr->version;

		int hashVal = hashF(ptr->app_name);

		float v = 0.0;
		string appV = "";
		getline(cin, appV);
		//cin >> appV;
		v = atof(appV.c_str());

		ptr->size = v;

		C = "";
		//cin >> ptr->units;
		getline(cin, C);
		strcpy(ptr->units, C.c_str());


		float p = 0.0;
		string appP = "";
		//cin >> appP;
		getline(cin, appP);
		p = atof(appP.c_str());

		ptr->price = p;

		ptr2 = getNewNode(*ptr);
		Insert(ptr2);


		*table[hashVal].app_name = *ptr->app_name;
		table[hashVal].app_node = ptr2;

	}

	int count = 0;

	int comms = 0;
	string E;
	getline(cin, E);
	comms = atoi(E.c_str());

	//cout << comms << endl;

	do{
		count++;
		string N;
		//getline(cin, N);
		//strcpy_s(com, N);

		cin >> N;

		//cout << "N: " << N << endl;

		if ((strcmp(N.c_str(), "find") == 0)){
			//cout << "FIND FIND FIND" << endl;

			string finder = "";
			cin >> finder;
			//getline(cin, finder);
			if ((strcmp(finder.c_str(), "app") == 0)){
				//cout << "APP APP" << endl;

				string appN = "";
				//cin >> appN;
				cin.ignore();
				getline(cin, appN);
				int keyV = hashF(appN);
				if (table[keyV].app_node != NULL){
					cout << table[keyV].app_node->info.app_name << endl;
					cout << "$" << table[keyV].app_node->info.price << endl;
					cout << table[keyV].app_node->info.category << endl;
					cout << table[keyV].app_node->info.size << table[keyV].app_node->info.units << endl;
					cout << table[keyV].app_node->info.version << endl;
				}
				else{
					cout << "Application not found." << endl;
				}
			}
			else if ((strcmp(finder.c_str(), "category") == 0)){
				char categoryIN[50];
				//cin >> categoryIN;
				string B = "";

				cin.ignore();
				getline(cin, B);
				strcpy(categoryIN, B.c_str());

				findCat(categoryIN);
			}
			else if ((strcmp(finder.c_str(), "price") == 0)){
				string free = "";
				cin >> free;
				for (int x = 0; x < n; x++){
					freeT(cats[x].root);
				}
			}
		}
		else if ((strcmp(N.c_str(), "range") == 0)){
			//cout << "RANGE" << endl;
			char categ[] = "";
			string sorter = "";
			int low = 0;
			int high = 0;

			cin >> categ;
			cin >> sorter;

			if ((strcmp(sorter.c_str(), "price") == 0)){
				//cout << "PRICE" << endl;
				cin >> com;
				low = atoi(com.c_str());
				cin >> com;
				high = atoi(com.c_str());
				priceT(getCat(categ), low, high);
			}
			else if ((strcmp(sorter.c_str(), "app") == 0)){
				//cout << "APP" << endl;
				string low = "";
				string high = "";
				cin >> low;
				cin >> high;
				alphT(getCat(categ), low, high);
			}

		}
		else if ((strcmp(N.c_str(), "delete") == 0)){
			char categoryIN[50];
			string appNa = "";
			cin >> categoryIN;
			string B = "";

			cin.ignore();
			getline(cin, B);
			//strcpy(appNa, B.c_str());
		}
		else{
			cout << "Command not recognized. Please try again." << endl;
		}

	} while (count <= comms);

	//while ((strcmp(N.c_str(), "Exit") != 0));

	return 0;
}

