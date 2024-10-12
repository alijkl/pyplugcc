
/*
  simple example taken from
  https://en.wikipedia.org/wiki/C_data_types#Structures
*/

struct birthday {
	char name[20];
	int day;
	int month;
	int year;
};

struct birthday John;

struct node {
	int val;
	struct node *next;
};

struct node Lnode;
