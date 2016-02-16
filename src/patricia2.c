#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>


struct node
{
	char info;
	int bitindex;
	struct node* lc;
	struct node* rc;
};

typedef struct node nd;


void traverse(nd* T, char a);
int findbit(char d, char a);
int shift;

nd* root;

int main()
{
	char a;
	char choice;	
	nd* start;
	int flag;
	nd* T;

	start = '\0';
	
	printf("Enter the character: \n");
	scanf("%c", &a);
	
	if(!start){
		start = (nd*)malloc(sizeof(nd));
		start->info = a;	
		start->bitindex = findbit('\0', a);        // null has got all 0s in all the 7 bits
		start->lc = '\0';			   
		start->rc = start;
		//printf("Info at root: %c\n", start->rc->info);		
		printf("bitindex of the node %c is %d\n", a, start->bitindex);		
	}
	
	printf("Enter another node? answer in y/n ");
	scanf(" %c", &choice);			// the leading whitespace in scanf tells the function to skip any whitespace
	
	fflush(stdin);
	
	T = start;
	root = start;

	while(choice != 'n'){
		printf("Enter the character: \n");
		scanf(" %c", &a);
		shift = 6 - T->bitindex;
	 	traverse(T, a);
		printf("Enter another node? answer in y/n ");
		scanf(" %c", &choice);
	}		
	free(start);
	exit(EXIT_SUCCESS);
}


int findbit(char d, char a)
{
	int b;
	int c;

	a = a ^ d; 
        for(b = 6; b >= 0; a = a << 1){
                if(0100 & a){
                        //printf("1");
			return(b);
		}
                else{ ;
                        //printf("0");
		}
                b--;
        }
	return 0;
}

void traverse(nd* T, char a)
{
	int d, x, d1;
	nd* closest_node;
	nd* current;
	int flag;
	nd* new_node = (nd*) malloc(sizeof(nd));
  	new_node->info = a;
	new_node->rc = new_node->lc = '\0';										
	d = a << shift;                              			// skip the pointer to the bit_index of the current node
	if(0100 & d){							//if the new node has 1 in current node's bit_index postion go to right
		if(T->rc->bitindex >= T->bitindex){  			// search finds an uplink
			closest_node = T->rc;
			new_node->bitindex = findbit(closest_node->info, a);
			printf("bitindex of new node: %d\n", new_node->bitindex); 
			//if(new_node->bitindex < closest_node->bitindex){
			if(new_node->bitindex < T->bitindex){		// we check whether new_node should be a child of current node
				T->rc = new_node;
				x = a << (6 - new_node->bitindex);
				if(0100 & x){				// right link to itself, left link to closest node
					printf("the info at closest_node: %c\n", closest_node->info);
					new_node->rc = new_node;
					new_node->lc = closest_node;
				}
				else{					// left link to itself, right link to closest node
					printf("the info at closest_node: %c\n", closest_node->info);
					new_node->lc = new_node;
					new_node->rc = closest_node;
				} 
			}
			else{						// the new node can't be a child of the current node,find right place
				shift = 6 - (T->bitindex);
				d = a << shift;
				T = root;
				while(T->bitindex > new_node->bitindex){// finds the proper parent of new node
					if(0100 & d){			// new node to be inserted as right child
						flag = 1;
						if(T->rc->bitindex < new_node->bitindex)	
							break;
						else
							;
					}
					else{				// new node to be inserted as left child
						flag = 0;
						if(T->lc->bitindex < new_node->bitindex)
							break;
						else
							;
					}
				}
				if(flag){				// inserting the previous child as right child of new node

					if(0100 & (T->rc->info << (6 - new_node->bitindex))){
						new_node->rc = T->rc;
						if(0100 & (a << (6 - new_node->bitindex)))
							new_node->lc = closest_node;
						else
							new_node->lc = new_node;
					}

					else{				// inserting the previous child as left child of new node
						new_node->lc = T->rc;
						if(0100 & (a << (6 - new_node->bitindex)))
							new_node->rc = new_node;
						else
							new_node->rc = closest_node;
					}
				}
					
			}	
		}
		else{							// normal link to a child node, so we call the routine recursively
			
			free(new_node);
			new_node = '\0';
			shift = 6 - (T->rc->bitindex);
                        traverse(T->rc, a);
		}
	}
	else{							// if the new node has 0 in its current node's bit_index position go to left
		if(T->lc == '\0'){                      	// search hits null
                        new_node->bitindex = findbit('\0', a);
			new_node->lc = '\0';
			new_node->rc = new_node;
			printf("bitindex of new node: %d\n", new_node->bitindex);
                        if(new_node->bitindex < T->bitindex){
                                T->lc = new_node;
                                new_node->lc = '\0';
                                new_node->rc = new_node;
				printf("the info at closest node: %c\n", T->info);
                        }
                        else{					// new node can't be a child node of present node
				shift = 6 - (T->bitindex);
				d = a << shift;
				T = root;
				while(T->bitindex > new_node->bitindex){// finds the proper parent of new node
					if(0100 & d){			// new node to be inserted as right child
						flag = 1;
						if(T->rc->bitindex < new_node->bitindex)	
							break;
						else
							;
					}
					else{				// new node to be inserted as left child
						flag = 0;
						if(T->lc->bitindex < new_node->bitindex)
							break;
						else
							;
					}
				}
				if(flag){				// inserting the previous child as right child of new node

					if(0100 & (T->rc->info << (6 - new_node->bitindex))){
						new_node->rc = T->rc;
					}

					else{				// inserting the previous child as left child of new node
						new_node->lc = T->rc;
					}
				}
                        }
                }
		else if(T->lc->bitindex >= T->bitindex){  		// search finds an uplink
                        closest_node = T->lc;
                        new_node->bitindex = findbit(closest_node->info, a);
			printf("bitindex of new node: %d\n", new_node->bitindex);
                        if(new_node->bitindex < T->bitindex){		// we check whether new_node should be a child of current node
				T->lc = new_node;
                                x = a << (6 - new_node->bitindex);
                                if(0100 & x){				// right link to itself, left link to closest node
                                        new_node->rc = new_node;
                                        new_node->lc = closest_node;
					printf("the info at closest_node: %c\n", closest_node->info);
                                }
                                else{					// left link to itself, right link to closest node
                                        new_node->lc = new_node;
                                        new_node->rc = closest_node;
					printf("the info at closest_node: %c\n", closest_node->info);	
                                }
                        }
                        else{						// when the new node cannot be a child of the current node
				shift = 6 - (T->bitindex);
				d = a << shift;
				T = root;
				while(T->bitindex > new_node->bitindex){// finds the proper parent of new node
					if(0100 & d){			// new node to be inserted as right child
						flag = 1;
						if(T->rc->bitindex < new_node->bitindex)	
							break;
						else
							;
					}
					else{				// new node to be inserted as left child
						flag = 0;
						if(T->lc->bitindex < new_node->bitindex)
							break;
						else
							;
					}
				}
				if(flag){				// inserting the previous child as right child to new node

					if(0100 & (T->rc->info << (6 - new_node->bitindex))){
						new_node->rc = T->rc;
						if(0100 & (a << (6 - new_node->bitindex)))
							new_node->lc = closest_node;
						else
							new_node->lc = new_node;
					}

					else{				// inserting the previous child as the left child to new node
						new_node->lc = T->rc;
						if(0100 & (a << (6 - new_node->bitindex)))
							new_node->rc = new_node;
						else
							new_node->rc = closest_node;
					}
				}
                        }
                }
		else{                                           // normal link to a child node
                        free(new_node);
			new_node = '\0';
			shift = 6 - (T->lc->bitindex);
                        traverse(T->lc, a);
                }
	}
}



