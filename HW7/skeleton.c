/*
MAAHIR VOHRA
CS288-007 PROF DALE
HOMEWORK 7
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 4
#define NxN (N*N)
#define TRUE 1
#define FALSE 0

struct node {
	int tiles[N][N];
	int f, g, h;
	short zero_row, zero_column;	/* location (row and colum) of blank tile 0 */
	struct node *next;
	struct node *parent;			/* used to trace back the solution */
};

int goal_rows[NxN];
int goal_columns[NxN];
struct node *start,*goal;
struct node *open = NULL, *closed = NULL;
struct node *succ_nodes[4];

void print_a_node(struct node *pnode) {
	int i,j;
	for (i=0;i<N;i++) {
		for (j=0;j<N;j++) 
			printf("%2d ", pnode->tiles[i][j]);
		printf("\n");
	}
	printf("\n");
}

struct node *initialize(char **argv){
	int i,j,k,index, tile;
	struct node *pnode;

	pnode=(struct node *) malloc(sizeof(struct node));
	index = 1;
	for (j=0;j<N;j++)
		for (k=0;k<N;k++) {
			tile=atoi(argv[index++]);
			pnode->tiles[j][k]=tile;
			if(tile==0) {
				pnode->zero_row=j;
				pnode->zero_column=k;
			}
		}
	pnode->f=0;
	pnode->g=0;
	pnode->h=0;
	pnode->next=NULL;
	pnode->parent=NULL;
	start=pnode;
	printf("initial state\n");
	print_a_node(start);

	pnode=(struct node *) malloc(sizeof(struct node));
	goal_rows[0]=3;
	goal_columns[0]=3;

	for(index=1; index<NxN; index++){
		j=(index-1)/N;
		k=(index-1)%N;
		goal_rows[index]=j;
		goal_columns[index]=k;
		pnode->tiles[j][k]=index;
	}
	pnode->tiles[N-1][N-1]=0;	      /* empty tile=0 */
	pnode->f=0;
	pnode->g=0;
	pnode->h=0;
	pnode->next=NULL;
	goal=pnode; 
	printf("goal state\n");
	print_a_node(goal);

	return start;
}

/* merge the remaining nodes pointed by succ_nodes[] into open list. 
 * Insert nodes based on their f values --- keep f values sorted. */
void merge_to_open() { 
	for (int i = 0; i < 4; i++) {
		if (succ_nodes[i] == NULL) continue; //took me forever to realize this was missing
	
		struct node *curr = open;
		struct node *prev = NULL;

		while (curr != NULL && curr->f <= succ_nodes[i]->f) {
			prev = curr;
			curr = curr->next;
		}
		
		if (prev == NULL) { //insert at begenning of list
			succ_nodes[i]->next = open;
			open = succ_nodes[i];
		}
		else {
			succ_nodes[i]->next = curr;
			prev->next = succ_nodes[i];
		}
	}
}

/*swap two tiles in a node*/
void swap(int row1,int column1,int row2,int column2, struct node * pnode){
	int temp;
	temp = pnode->tiles[row1][column1];
	pnode->tiles[row1][column1] = pnode->tiles[row2][column2];
	pnode->tiles[row2][column2] = temp;
	//simple swap logic just complex syntax
}

/*update the f,g,h function values for a node */
void update_fgh(int i) {
	struct node *pnode = succ_nodes[i];
	if (pnode == NULL) return;

	if(pnode->parent) {
		pnode->g = pnode->parent->g + 1;
	}
	else {
		pnode->g = 0;
	}

	//calculating heurstic h
	pnode->h = 0;
	for(int i = 0; i < N; i++) {
		for(int j = 0; j < N; j++) {
			int tile = pnode->tiles[i][j];
			if(tile != 0) {
				pnode->h += abs(i - goal_rows[tile]) + abs(j - goal_columns[tile]);
			}
		}
	}
	pnode->f = pnode->g + pnode->h; //f = g + h
}

/* 0 goes down by a row */
void move_down(struct node * pnode){
	swap(pnode->zero_row, pnode->zero_column, pnode->zero_row+1, pnode->zero_column, pnode);
	pnode->zero_row++; //this updates the blank tiles row pos
}

/* 0 goes right by a column */
void move_right(struct node * pnode){
	swap(pnode->zero_row, pnode->zero_column, pnode->zero_row, pnode->zero_column+1, pnode);
	pnode->zero_column++; //column pos
}

/* 0 goes up by a row */
void move_up(struct node * pnode){
	swap(pnode->zero_row, pnode->zero_column, pnode->zero_row-1, pnode->zero_column, pnode);
	pnode->zero_row--;
}

/* 0 goes left by a column */
void move_left(struct node * pnode){
	swap(pnode->zero_row, pnode->zero_column, pnode->zero_row, pnode->zero_column-1, pnode);
	pnode->zero_column--;
}

/* expand a node, get its children nodes, and organize the children nodes using
 * array succ_nodes.
 */
void expand(struct node *selected) {
	int row = selected->zero_row;
	int col = selected->zero_column;

	for (int i = 0; i < 4; i++) {
		succ_nodes[i] = NULL;
	}

	//down
	if (row < N - 1) {
		struct node *pnode = (struct node *) malloc(sizeof(struct node));
		memcpy(pnode, selected, sizeof(struct node));
		pnode->parent = selected;
		move_down(pnode);
		succ_nodes[1] = pnode;
	}

	//right
	if (col < N - 1) {
		struct node *pnode = (struct node *) malloc(sizeof(struct node));
		memcpy(pnode, selected, sizeof(struct node));
		pnode->parent = selected;
		move_right(pnode);
		succ_nodes[3] = pnode;
	}

	//up
	if (row > 0) {
		struct node *pnode = (struct node *) malloc(sizeof(struct node));
		memcpy(pnode, selected, sizeof(struct node));
		pnode->parent = selected;
		move_up(pnode);
		succ_nodes[0] = pnode;
	}

	//left
	if (col > 0) {
		struct node *pnode = (struct node *) malloc(sizeof(struct node));
		memcpy(pnode, selected, sizeof(struct node));
		pnode->parent = selected;
		move_left(pnode);
		succ_nodes[2] = pnode;
	}
}

int nodes_same(struct node *a,struct node *b) {
	int flg=FALSE;
	if (memcmp(a->tiles, b->tiles, sizeof(int)*NxN) == 0)
		flg=TRUE;
	return flg;
}

/* Filtering. Some states in the nodes pointed by succ_nodes may already be included in 
 * either open or closed list. There is no need to check these states. Release the 
 * corresponding nodes and set the corresponding pointers in succ_nodes to NULL. This is 
 * important to reduce execution time.
 * This function checks the (i)th node pointed by succ_nodes array. You must call this
 * function in a loop to check all the nodes in succ_nodes. Free the successor node and 
 * set the corresponding pointer to NULL in succ_node[] if a matching node is found in 
 * the list.
 */ 
void filter(int i, struct node *pnode_list){ 
	struct node *pnode = succ_nodes[i];

	if (pnode == NULL) return;

	struct node *curr = pnode_list;
	while (curr != NULL) {
		if (nodes_same(pnode, curr)) {
			//free node and set pointer to null
			free(pnode);
			succ_nodes[i] = NULL;
			return;
		}
		curr = curr->next;
	}
}

int main(int argc,char **argv) {
	int iter,cnt;
	struct node *copen, *cp, *solution_path;
	int ret, i, pathlen=0, index[N-1];

	solution_path=NULL;
	start=initialize(argv);	/* init initial and goal states */
	open=start; 

	iter=0; 
	while (open!=NULL) {	/* Termination cond with a solution is tested in expand. */
		copen=open;
		open=open->next;  /* get the first node from open to expand */
		
		/* DEBUG: print the node (layout) in *copen 
		 * Fix segmentation faults first. If the program cannot produce correct results,
		 * select an initial layout close to the goal layout, and debug the program with it.
		 * gdb is recommended. You may also print data on the screen. But this is not as
		 * convenient as using gdb.
		 * */

		if(nodes_same(copen,goal)){ /* goal is found */
			do{ /* trace back and add the nodes on the path to a list */
				copen->next=solution_path;
				solution_path=copen;
				copen=copen->parent;
				pathlen++;
			} while(copen!=NULL);
			
			printf("Path (length=%d):\n", pathlen); 
			copen=solution_path;
			while (copen != NULL) { /* print out the nodes on the list */
				print_a_node(copen);
				copen=copen->next;
			} 
			break;
		}
		expand(copen);       /* Find new successors */

		/* DEBUG: print the layouts/nodes organized by succ_nodes[] */

		for(i=0;i<4;i++){
			filter(i,open);
			filter(i,closed);
			update_fgh(i);
		}

		/* DEBUG: print the layouts/modes remaining in succ_nodes[] */

		merge_to_open(); /* New open list */

		/* DEBUG: print the layouts/nodes on the open list */

		copen->next=closed;
		closed=copen;		/* New closed */
		/* print out something so that you know your 
		 * program is still making progress 
		 */
		iter++;
		if(iter %1000 == 0)
			printf("iter %d\n", iter);
	}
	return 0;
} /* end of main */