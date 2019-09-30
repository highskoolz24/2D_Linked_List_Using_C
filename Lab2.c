#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXWORDLENGTH 20

struct node2d {
	struct node1d *first;
	char *name;
	struct node2d *down;
};
struct node1d {
	struct node1d *next;
	char *name;
};

struct node2d* head = NULL;

char    buf[BUFSIZE];         
int     bufptr = 0;          

int insert2d(char name[]);
int append2d(char name[]);
int appendAfter2d(char name[], char afterName[]);
int insert1d(char name[], char name2d[]);
int printAll();
int print1dList(char name2d[]);
int getword(char *word, int lim);



int main(int argc, char* argv[argc]) {
	char word[MAXWORDLENGTH];
	char* t;
	
	while (getword(word, MAXWORDLENGTH) != EOF) {
		if (strcmp(word, "insert2d") == 0) {
			getword(word, MAXWORDLENGTH);
			insert2d(word);
		}
		else if (strcmp(word, "append2d") == 0) {
			getword(word, MAXWORDLENGTH);
			append2d(word);
		}
		else if (strcmp(word, "appendAfter2d") == 0) {
			getword(word, MAXWORDLENGTH);
			t = (char *)malloc(20 * sizeof(char));
			strcpy(t, word);
			getword(word, MAXWORDLENGTH);
			appendAfter2d(t, word);
		}
		else if (strcmp(word, "insert1d") == 0) {
			getword(word, MAXWORDLENGTH);
			t = (char *)malloc(20 * sizeof(char));
			strcpy(t, word);
			getword(word, MAXWORDLENGTH);
			insert1d(t, word);
		}
		else if (strcmp(word, "printAll") == 0) {
			printAll();
		}
		else if (strcmp(word, "print1dList") == 0) {
			getword(word, MAXWORDLENGTH);
			print1dList(word);
		}
		else {
			printf("Wrong entry!\n");
		}	
	}
}

int insert2d(char name[]) {
	struct node2d* current, *t;
	char *name_me;
	if (head == NULL) {
		current = (struct node2d *) malloc(sizeof(struct node2d));
		name_me = (char *)malloc(20 * sizeof(char));
		strcpy(name_me, name);
		current->name = name_me;
		current->first = NULL;
		current->down = NULL;
		head = current;
//		tail = current;
	}
	else {
		current = (struct node2d *) malloc(sizeof(struct node2d));
		name_me = (char *)malloc(20 * sizeof(char));
		strcpy(name_me, name);
		current->name = name_me;
		current->first = NULL;
		t = (struct node2d *) malloc(sizeof(struct node2d));
		*t = *head;
		head = current;
		head->down = t;
	}
	return 0;
}
int append2d(char name[]) {
	struct node2d* current, *t;
	char *name_me;
	if (head == NULL) {
		current = (struct node2d *) malloc(sizeof(struct node2d));
		name_me = (char *)malloc(20 * sizeof(char));
		strcpy(name_me, name);
		current->name = name_me;
		current->first = NULL;
		current->down = NULL;
		head = current;
//		tail = current;
	}
	else {
		current = (struct node2d *) malloc(sizeof(struct node2d));
		name_me = (char *)malloc(20 * sizeof(char));
		strcpy(name_me, name);
		current->name = name_me;
		current->first = NULL;
		current->down = NULL;

		t = head;
		while (t->down != NULL)
			t = t->down;

		t->down = current;


		//t = (struct node2d *) malloc(sizeof(struct node2d));
		//*t = *tail;
		//t->down = current;
		//tail = current;
	}
	return 0;
}
int appendAfter2d(char name[], char afterName[]) {
	//finding a node with afterName
	struct node2d* current, *new_node, *t;
	char* name_me;
	current = head;
	int check = 0;
	while(strcmp(current->name, afterName)!=0){
		if (current->down == NULL) {
			check = 1;
			break;
		}
		current = current->down;
	}
	//if found -> append, if not -> error
	if (check == 0) {
		if (current->down == NULL) {
			new_node = (struct node2d *) malloc(sizeof(struct node2d));
			name_me = (char *)malloc(20 * sizeof(char));
			strcpy(name_me, name);
			new_node->name = name_me;
			new_node->first = NULL;
			new_node->down = NULL;
			current->down = new_node;
			//tail = new_node;
		}
		else {
			t = current->down;
			new_node = (struct node2d *) malloc(sizeof(struct node2d));
			name_me = (char *)malloc(20 * sizeof(char));
			strcpy(name_me, name);
			new_node->name = name_me;
			new_node->first = NULL;
			current->down = new_node;
			new_node->down = t;
		}
	}
	else {
		fprintf(stderr, "%s\n", "No 2Dnode with the name!");
		exit(1);
	}
	return 0;
}

int insert1d(char name[], char name2d[]) {
	//finding a node with name2d
	struct node2d* current;
	struct node1d* new_1d, *t;
	char* name_me;
	current = head;
	int check = 0;
	while (strcmp(current->name, name2d) != 0) {
		if (current->down == NULL) {
			check = 1;
			break;
		}
		current = current->down;
	}
	//if found ->update node1d
	if (check == 0) {
		new_1d = (struct node1d *) malloc(sizeof(struct node1d));
		name_me = (char *)malloc(20 * sizeof(char));
		strcpy(name_me,name);
		new_1d->name = name_me;
		if (current->first == NULL) {
			current->first = new_1d;
			new_1d->next = NULL;
		}
		else {
			t = current->first;
			current->first = new_1d;
			new_1d->next = t;
		}
	}
	else {
		fprintf(stderr, "%s\n", "No 2d node with the name!");
		exit(1);
	}
	return 0;
}

int printAll() {
	struct node2d* current;
	struct node1d* new_1d, *t;
	current = head;
	while (current != NULL) {
		printf("2d node name = %s\n", current->name);
		t = current->first;
		while (t != NULL) {
			printf("   1d node name = %s\n", t->name);
			t = t->next;
		}
		current = current->down;
	}
	return 0;
}

int print1dList(char name2d[]) {
	//finding a node with name2d
	struct node2d* current;
	struct node1d* new_1d, *t;
	current = head;
	int check = 0;
	while (strcmp(current->name, name2d) != 0) {
		if (current->down == NULL) {
			check = 1;
			break;
		}
		current = current->down;
	}
	if (check == 0) {
		if (current->first != NULL) {
			t = current->first;
			printf("2d node name = %s\n", name2d);
			while (t != NULL) {
				printf("   1d node name = %s\n", t->name);
				t = t->next;
			}
		}
		else {
			printf("No 1d nodes in this 2d node\n");
		}
	}
	else {
		fprintf(stderr, "%s\n", "No 2d node with the name!");
		exit(1);
	}
	return 0;
}

int getword(char *word, int lim) {
	int c, getch(void);
	void ungetch(int);
	char *w = word;
	while (isspace(c = getch()));
	if (c != EOF)
		*w++ = c;
	if (!isalpha(c)) {
		*w = '\0';
		return c;
	}
	for (; --lim > 0; w++)
		if (!isalnum(*w = getch())) {
			ungetch(*w);
			break;
		}
	*w = '\0';
	return word[0];
}


int getch(void){
	return (bufptr > 0) ? buf[--bufptr] : getchar();
}

void ungetch(int c){
	if (bufptr >= BUFSIZE)
		printf("ungetch: too many characters\n");
	else
		buf[bufptr++] = c;
	return;
}