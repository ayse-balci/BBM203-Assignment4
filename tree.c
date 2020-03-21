#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>



typedef struct {
    char *data;
    int countChild;
}node0;

typedef struct {
    char *data;
    int countChild;
    void *child1;
}node1;

typedef struct {
    char *data;
    int countChild;
    void *child1;
    void *child2;
}node2;

typedef  struct {
    char *data;
    int countChild;
    void *child1;
    void *child2;
    void *child3;
}node3;
 
int findLengthOfFile(char *file);   //Function for calculating length of file
int findLineCount(char *fileString, char *file, int size);  //Function for calculating count of file
char** allocateAndFillArray(char*stringArray, int lineCount, int size);  //Function for allocating memory 
node0* createNode0(char *value);  //function creates new node with 0 child by given char* value
node1* createNode1(char *value, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array);  //function creates new node with 1 child by given char* value
node2* createNode2(char *value, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array);   //function creates new node with 2 child by given char* value
node3* createNode3(char *value, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array);   //function creates new node with 3 child by given char* value
int randomNumber(int lower, int upper,int count);  //function returns integer number between lower count and upper count
void createCondition(node3* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array);  //if root <cond>, it calculate random number 0 or 1. if number is 0: Childs: <cond><set-op><cond>, if number is 1: Childs:<expr><rel-op><expr>
void call3ChildNodes(node3* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array);
void createExpressionNode3(node3* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array); //if expression node is 3, expr childs are <expr><op><expr>
void createExpressionNode2(node2* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array);  //if expression node is 2, expr childs are <pre-op>(<expr>
void createExpressionNode1(node1* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array);  //if expression node is 1, expr child is <var>
void print1(node3* root);  //function take node3 root from main function, print2 or print3, then if child's type node3, return yourself, if child's type node2 return print2, if child's type node1 return print1
void print2(node2* root);  //function take node3 root from print2 or print3, then if child's type node3, return print2, if child's type node2 return yourself, if child's type node1 return print1
void print3(node1* root);  //function send own child to print4
void print4(node0* root);  //function writes data
int findCountChildOfNode3(node3* root);  //function return node3 root'child type
int findCountChildOfNode2(node2* root);  //function return node2 root'child type
int findCountChildOfNode1(node1* root);  //function return node1 root'child type

int main(){
    char *op = "op";
    char *pre_op ="pre_op";
    char *rel_op = "rel_op";
    char *set_op = "set_op";
    char *var = "var";

    int op_size = findLengthOfFile(op);
    int pre_op_size = findLengthOfFile(pre_op);
    int rel_op_size = findLengthOfFile(rel_op);
    int set_op_size = findLengthOfFile(set_op);
    int var_size = findLengthOfFile(var);

    char opStringArray[op_size];
    char pre_opStringArray[pre_op_size];
    char rel_opStringArray[rel_op_size];
    char set_opStringArray[set_op_size];
    char varStringArray[var_size];

    int op_count = findLineCount(opStringArray, op, op_size);
    int pre_op_count = findLineCount(pre_opStringArray, pre_op, pre_op_size);
    int rel_op_count = findLineCount(rel_opStringArray, rel_op, rel_op_size);
    int set_op_count = findLineCount(set_opStringArray, set_op, set_op_size);
    int var_count = findLineCount(varStringArray, var, var_size);
    
    char **op_array = allocateAndFillArray(opStringArray, op_count, op_size);
    char **pre_op_array = allocateAndFillArray(pre_opStringArray, pre_op_count, pre_op_size);
    char **rel_op_array = allocateAndFillArray(rel_opStringArray, rel_op_count, rel_op_size);
    char **set_op_array = allocateAndFillArray(set_opStringArray, set_op_count, set_op_size);
    char **var_array = allocateAndFillArray(varStringArray, var_count, var_size);
   
    srand(time(0)); 
    node3* root = createNode3("cond", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    call3ChildNodes(root, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    printf("if");
    print1(root);
    printf("{}\n");
    return 0;
}

int findLengthOfFile(char *file){
    FILE *fp = fopen(file, "r");
    fseek(fp, 0L, SEEK_END);
    int sz = ftell(fp);
    return sz;
}

int findLineCount(char *fileString, char *file, int size){
    FILE *fp = fopen(file, "r");
    char ch;
    int line_count = 0, count = 0;
    while((ch=fgetc(fp)) != EOF){
        fileString[count] = ch;
        count++;
        if (ch == '\n' || ch == '\r'){
            line_count++;
        }
    }
    return line_count;
}

char** allocateAndFillArray(char *stringArray, int lineCount, int size){
    int i,j;
    char **matrixArray = (char**) malloc(lineCount *sizeof(char*));
    for (i = 0; i < lineCount; i++){
        matrixArray[i] = (char*) malloc(size* sizeof(char));
    }
    char *word;
	word = strtok (stringArray,"\n");
	for (j=0; j<lineCount;j++) {
		strcpy(matrixArray[j] , word);
        word = strtok (NULL, "\n");
       
	}
    return matrixArray;
}

void call3ChildNodes(node3* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array){
    int x;
    if (root != NULL){
        if (strcmp(root->data, "cond") == 0){
            createCondition(root, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        }
        else if(strcmp(root->data, "expr") == 0){
            x = randomNumber(0, 2, 1);
            printf("     %d ", x);
            if (x == 0){
                createExpressionNode3((node3*) root, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
            }
            else if(x == 1){
                createExpressionNode2((node2*) root, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
            }
            else if(x == 2){
                createExpressionNode1((node1*) root, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
            }
        }
    }
}

void createExpressionNode1(node1* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array){
    root -> child1 = createNode1("var", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
}

void createExpressionNode2(node2* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array){
    root -> child1 = createNode1("pre-op", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    int x = randomNumber(0, 2, 1);
    if (x == 0){
        root -> child2 = createNode3("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        createExpressionNode3(root -> child2, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
    else if(x == 1){
        root -> child2 = createNode2("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        createExpressionNode2(root -> child2, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
    else if(x == 2){
        root -> child2 = createNode1("var", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
}

void createExpressionNode3(node3* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array){
    int x = randomNumber(0, 2, 1);
    if (x == 0){
        root -> child1 = createNode3("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        createExpressionNode3(root -> child1, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
    else if(x == 1){
        root -> child1 = createNode2("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        createExpressionNode2(root -> child1, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
    else if(x == 2){
        root -> child1 = createNode1("var", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
    
    root -> child2 = createNode1("op", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);

    int y = randomNumber(0, 2, 1);
    if (y == 0){
        root -> child3 = createNode3("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        createExpressionNode3(root -> child3, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
    else if(y == 1){
        root -> child3 = createNode2("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        createExpressionNode2(root -> child3, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
    else if(y == 2){
        root -> child3 = createNode1("var", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
}

void createCondition(node3* root, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array){
    int x, y, z;
    x = randomNumber(0, 1, 1);
    if (x == 0){
        root -> child1 = createNode3("cond", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        call3ChildNodes(root->child1, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        root -> child2 = createNode1("set-op", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        root -> child3 = createNode3("cond", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        call3ChildNodes(root->child3, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
    }
    if (x == 1){
        y = randomNumber(0, 2, 1);
        if (y == 0){
            root -> child1 = createNode3("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
            createExpressionNode3(root -> child1, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        }
        else if(y == 1){
            root -> child1 = createNode2("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
            createExpressionNode2(root -> child1, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        }
        else if(y == 2){
            root -> child1 = createNode1("var", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        }
        
        root -> child2 = createNode1("rel-op", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        z = randomNumber(0, 2, 1);
        if (z == 0){
            root -> child3 = createNode3("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
            createExpressionNode3(root -> child3, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        }
        else if(z == 1){
            root -> child3 = createNode2("expr", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
            createExpressionNode2(root -> child3, op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        }
        else if(z == 2){
            root -> child3 = createNode1("var", op_count, op_array, pre_op_count, pre_op_array, rel_op_count, rel_op_array, set_op_count, set_op_array, var_count, var_array);
        }
        
    }
}


node0* createNode0(char *value){
    node0* newNode = malloc(sizeof(node0));
    newNode->data = value;
    //printf("%s ", newNode->data);
    newNode->countChild = 0;
    return newNode;
}

node1* createNode1(char *value, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array){
    node1* newNode = malloc(sizeof(node1));
    newNode->data = value;
    newNode->countChild = 1;
    if (strcmp(newNode->data, "op") == 0){
        newNode->child1 = createNode0(op_array[randomNumber(0, op_count - 1, 1)]);
    }
    else if (strcmp(newNode->data, "pre-op") == 0){
        newNode->child1 = createNode0(pre_op_array[randomNumber(0, pre_op_count - 1, 1)]);
    }
    else if (strcmp(newNode->data, "rel-op") == 0){
        newNode->child1 = createNode0(rel_op_array[randomNumber(0, rel_op_count - 1, 1)]);
    }
    else if (strcmp(newNode->data, "set-op") == 0){
        newNode->child1 = createNode0(set_op_array[randomNumber(0, set_op_count - 1, 1)]);
    }
    else if (strcmp(newNode->data, "var") == 0){
        newNode->child1 = createNode0(var_array[randomNumber(0, var_count - 1, 1)]);
    }
    return newNode;
}

node2* createNode2(char *value, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array){
    node2* newNode = malloc(sizeof(node2));
    newNode->data = value;
    newNode->countChild = 2;
    newNode->child1 = NULL;
    newNode->child2 = NULL;
   // printf("%s ", newNode->data);
    return newNode;
}

node3* createNode3(char *value, int op_count, char **op_array, int pre_op_count, char **pre_op_array, int rel_op_count, char **rel_op_array, int set_op_count, char **set_op_array, int var_count, char **var_array){
    node3* newNode = malloc(sizeof(node3));
    newNode->data = value;
    newNode->countChild = 3;
    newNode->child1 = NULL;
    newNode->child2 = NULL;
    newNode->child3 = NULL;
    //printf("%s ", newNode->data);
    return newNode;
}

int randomNumber(int lower, int upper,int count) { 
    int i, num; 
    for (i = 0; i < count; i++) { 
        num = (rand() % 
           (upper - lower + 1)) + lower; 
    } 
    return num;
} 

void print1(node3* root){
    if (root != NULL){
        printf("(");
        if (findCountChildOfNode3(root->child1) == 3){
            print1(root->child1);
        }
        else if (findCountChildOfNode2(root->child1) == 2){
            print2(root->child1);
        }
        else if (findCountChildOfNode1(root->child1) == 1){
            printf("(");
            print3(root->child1);
            printf(")");
        }
        if (findCountChildOfNode3(root->child2) == 3){
            print1(root->child2);
        }
        else if (findCountChildOfNode2(root->child2) == 2){
            print2(root->child2);
        }
        else if (findCountChildOfNode1(root->child2) == 1){
            print3(root->child2);
        }
        if (findCountChildOfNode3(root->child3) == 3){
            print1(root->child3);
        }
        else if (findCountChildOfNode2(root->child3) == 2){
            print2(root->child3);
        }
        else if (findCountChildOfNode1(root->child3) == 1){
            printf("(");
            print3(root->child3);
            printf(")");
        }
        printf(")");
    }
}

void print2(node2* root){
    if (root != NULL){
        if (findCountChildOfNode3(root->child1) == 3){
            print1(root->child1);
        }
        else if (findCountChildOfNode2(root->child1) == 2){
            print2(root->child1);
        }
        else if (findCountChildOfNode1(root->child1) == 1){
            print3(root->child1);
        }
        printf("(");
        if (findCountChildOfNode3(root->child2) == 3){
            print1(root->child2);
        }
        else if (findCountChildOfNode2(root->child2) == 2){
            print2(root->child2);
        }
        else if (findCountChildOfNode1(root->child2) == 1){
            print3(root->child2);
        }
        printf(")");
    }
}

void print3(node1* root){
    print4(root->child1);
}

void print4(node0* root){
    printf("%s", root->data);
}

int findCountChildOfNode3(node3* root){
    return root->countChild;
}

int findCountChildOfNode2(node2* root){
    return root->countChild;
}

int findCountChildOfNode1(node1* root){
    return root->countChild;
}

