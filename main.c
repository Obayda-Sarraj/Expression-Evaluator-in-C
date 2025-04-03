///Obayda Sarraj
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define MAX_SIZE 100

typedef struct node* ptr ;
struct node {
    char expression[MAX_SIZE] ;
    ptr next ;
};
typedef struct node* LinkedList ;
typedef struct node* pos ;

typedef struct leaf* children ;
struct leaf {
    int expNumber ;
    char expChar ;
    children right ;
    children left ;
};
typedef struct leaf* BT ;

struct tree {
    struct tree* ptr ;
};
typedef struct tree* stackTree;

// Function prototypes
LinkedList creatNodeList();
BT creatNodeTreeForNum(int x);
BT creatNodeTreeForChar(char x);
stackTree creatNodeStack();
void insertLast(char Line[], LinkedList l);
int isExpression(char c);
int isOperator(char c);
int priority(char expChar);
bool isNumber(char inFix);
void filterExpression(char Arr[]);
void loadFile(LinkedList list);
void printList(LinkedList list);
void infixTOPostfix(char Arr[]);
BT fillTreeWithExpression(char expression[]);
void printTree(BT tree);
int evaluate(BT root);
void evaluateList(LinkedList list);
void printPostFixList(LinkedList list);
void UploadToFile(LinkedList list);

int main()
{
    LinkedList expressions = creatNodeList();
    //loadFile(expressions);
    //printList(expressions);
    /*char Arr[MAX_SIZE] = "(1+2)*3-(4*100)";
    infixTOPostfix(Arr);
    BT Tree = fillTreeWithExpression(Arr);
    printf("Expression in postfix : ");
    printTree(Tree);
    printf("  -->   Result = %d",evaluate(Tree));*/

    int numOfOperation = 0 ;
    // Menu driven interface for user operations
    do
    {
        printf("\nPlease select one of operations:\n");
        printf("1. Read equations\n");
        printf("2. Print equations\n");
        printf("3. Evaluate using Expression tree\n");
        printf("4. Print postfix expressions\n");
        printf("5. Save to output file (postfix and results)\n");
        printf("6. Exit\n\n");
        scanf(" %d", &numOfOperation);

        switch (numOfOperation)
        {
            case 1:
                loadFile(expressions);
                printf("The File has been loaded\n");
                break;

            case 2:
                printList(expressions);
                break;

            case 3:
                evaluateList(expressions);
                break;

            case 4:
                printPostFixList(expressions);
                break;

            case 5:
                UploadToFile(expressions);
                printf("\nData has been uploaded\n");
                break;

            case 6:
                printf("Exiting program. Goodbye!\n");
                break;

            default:
                printf("No such operation!  please try again.\n");
                break;
        }
    }while(numOfOperation != 6);
    return 0;
}

// Function to create an empty List
LinkedList creatNodeList()
{
    // Reserve a place in memory
    LinkedList list = (LinkedList)malloc(sizeof(struct node));
    if (list == NULL)
    {
        printf("Out of memory!\n");
        return NULL;
    }
    // Make the pointers to point on NULL
    list->next = NULL;
    return list;
}

// Function to create a node Tree and insert an integer to it
BT creatNodeTreeForNum(int x)
{
    BT Tree = (BT)malloc(sizeof(struct leaf));
    if(Tree == NULL)
    {
        printf("Out of memory!\n");
        return NULL ;
    }
    Tree->expNumber = x ;
    Tree->expChar = 'n' ;
    Tree->left = NULL;
    Tree->right = NULL;
    return  Tree ;
}

// Function to create a node Tree and insert a character to it
BT creatNodeTreeForChar(char x)
{
    BT Tree = (BT)malloc(sizeof(struct leaf));
    if(Tree == NULL)
    {
        printf("Out of memory!\n");
        return NULL ;
    }
    Tree->expNumber = 1211128 ;
    Tree->expChar = x ;
    Tree->left = NULL;
    Tree->right = NULL;
    return  Tree ;
}

// Function to create an empty stack points to tree
stackTree creatNodeStack()
{
    stackTree node = (stackTree)malloc(sizeof(struct tree));
    if(node == NULL)
    {
        printf("Out of memory!\n");
        return NULL ;
    }
    node->ptr = NULL;
    return  node ;
}

// Function to insert nodes at the end of the list
void insertLast(char Line[], LinkedList l)
{
    // Reserve a place in memory
    LinkedList newNode = (LinkedList)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Out of memory!");
        return;
    }

    strcpy(newNode->expression, Line);


    pos p = l;
    while (p->next != NULL) {
        p = p->next;
    }

    newNode->next = NULL;
    p->next = newNode;
}

// Function to check if character belongs to expression or not
int isExpression(char c)
{
    switch (c) {
        case '0' : return 1 ;
            break;
        case '1' : return 1 ;
            break;
        case '2' : return 1 ;
            break;
        case '3' : return 1 ;
            break;
        case '4' : return 1 ;
            break;
        case '5' : return 1 ;
            break;
        case '6' : return 1 ;
            break;
        case '7' : return 1 ;
            break;
        case '8' : return 1 ;
            break;
        case '9' : return 1 ;
            break;
        case '+' : return 1 ;
            break;
        case '-' : return 1 ;
            break;
        case '*' : return 1 ;
            break;
        case '/' : return 1 ;
            break;
        case '%' : return 1 ;
            break;
        case '(' : return 1 ;
            break;
        case ')' : return 1 ;
            break;
        default: return 0 ;
            break;
    }
}

// Function to check if character is number or not
int isOperator(char c)
{
    switch (c) {
        case '+' : return 1 ;
            break;
        case '-' : return 1 ;
            break;
        case '*' : return 1 ;
            break;
        case '/' : return 1 ;
            break;
        case '%' : return 1 ;
            break;
        case '(' : return 1 ;
            break;
        case ')' : return 1 ;
            break;
        default: return 0 ;
            break;
    }
}

// Function to clear the expression from spaces and spacial character
void filterExpression(char Line[])
{
    for(int i=0 ; i< strlen(Line) ; i++)
    {
        while(!isExpression(Line[i]))
        {
            for(int j=i ; j < strlen(Line) ; j++)
                Line[j] = Line[j+1];
        }
    }
}

// Function to load all data in file "input"
void loadFile(LinkedList list)
{
    FILE *read = fopen("input.txt","r");
    if(read == NULL) {
        printf("Error: input.txt file not found!\n");
        return 0;
    }

    char Line[100];
    while (fgets(Line, sizeof(Line), read) != NULL)
    {
        // Remove trailing newline if present
        if (Line[strlen(Line) - 1] == '\n') {
            Line[strlen(Line) - 1] = '\0';
        }
        filterExpression(Line);
        insertLast(Line,list);
    }
    fclose(read);
}

// Function to print the list
void printList(LinkedList list)
{
    pos p = list->next ;
    if(p == NULL) {
        printf("The File is Empty\n");
        return;
    }
    printf("\n");
    while(p != NULL)
    {
        printf("%s\n",p->expression);
        p = p->next ;
    }
}

// Function to compare between two character acoording to priority
int priority(char expChar)
{
    switch (expChar) {
        case '+' : return 0 ;
            break;
        case '-' : return 0 ;
            break;
        case '*' : return 1 ;
            break;
        case '/' : return 1 ;
            break;
        case '%' : return 1 ;
            break;
        default: return -1 ;
            break;
    }
}

// Function to check if character is number or not
bool isNumber(char inFix)
{
    return (inFix >= '0' && inFix <= '9');
}

// Function to convert infix expression to postfix
void infixTOPostfix(char inFix[])
{

    char operatorStack[100];
    int topOfOperatorStack= -1 ;
    char newExpression[100];
    int topOfNewExpression= -1 ;

    for(int i=0 ; i< strlen(inFix) ; i++)
    {
        //push to top of operatorStack with priority
        if(isOperator(inFix[i]))
        {
            if(i==0 || inFix[i] == '(')
            {
                operatorStack[++topOfOperatorStack] = inFix[i];
            }
            else if(inFix[i] == ')')
            {
                while(operatorStack[topOfOperatorStack] != '(')
                {
                    newExpression[++topOfNewExpression] = operatorStack[topOfOperatorStack--];
                    newExpression[++topOfNewExpression] = ' ';
                }
                // we shift on '('
                topOfOperatorStack-- ;
            }
            else if(priority(inFix[i]) >= priority(operatorStack[topOfOperatorStack]))
            {
                operatorStack[++topOfOperatorStack] = inFix[i];
            }
            else if(priority(inFix[i]) < priority(operatorStack[topOfOperatorStack]))
            {
                while(priority(inFix[i]) < priority(operatorStack[topOfOperatorStack]))
                {
                    newExpression[++topOfNewExpression] = operatorStack[topOfOperatorStack--];
                    newExpression[++topOfNewExpression] = ' ';
                    operatorStack[++topOfOperatorStack] = inFix[i];
                }
            }
        }
        //push to top of newExpression array
        else
        {
            while(isNumber(inFix[i])&&isNumber(inFix[i+1]))
            {
                newExpression[++topOfNewExpression] = inFix[i];
                i++ ;
            }
            newExpression[++topOfNewExpression] = inFix[i];
            newExpression[++topOfNewExpression] = ' ';
        }
    }
    // Pop remaining operators from stack to newExpression
    while(topOfOperatorStack != -1)
    {
        newExpression[++topOfNewExpression] = operatorStack[topOfOperatorStack--];
    }
    newExpression[++topOfNewExpression] = '\0' ;

    strcpy(inFix,newExpression);
}

// Function to fill tree with postsix expression
BT fillTreeWithExpression(char expression[])
{
    char postFix[MAX_SIZE];
    strcpy(postFix,expression);

    stackTree treeExpression[MAX_SIZE];
    int topOfTreeExpression = -1 ;

    for (int i=0 ; i < MAX_SIZE; i++)
    {
        treeExpression[i] = creatNodeStack();
    }



    int length = strlen(postFix);

    for (int i=0 ; i < length ; i++)
    {
        //push to top of operatorStack with priority
        if(isOperator(postFix[i]))
        {BT operator ;
            operator = creatNodeTreeForChar(postFix[i]);
            operator->right = treeExpression[topOfTreeExpression]->ptr ;
            treeExpression[topOfTreeExpression--]->ptr = NULL ;
            operator->left = treeExpression[topOfTreeExpression]->ptr ;
            treeExpression[topOfTreeExpression--]->ptr = NULL ;

            treeExpression[++topOfTreeExpression]->ptr = operator ;
        }
        //push to top of treeExpression array
        else if (postFix[i] != ' ') {
            int numOfDigit = 0;
            char subStr[50];
            while (postFix[i] != ' ' && i < length) {
                subStr[numOfDigit++] = postFix[i++];
            }
            subStr[numOfDigit] = '\0';
            treeExpression[++topOfTreeExpression]->ptr = creatNodeTreeForNum(atoi(subStr));
        }
    }
    return treeExpression[topOfTreeExpression]->ptr ;
}

// Function to print postfix expression from tree
void printTree(BT tree)
{
    if(tree != NULL) {
        printTree(tree->left); // Traverse left subtree
        printTree(tree->right); // Traverse right subtree
        if(tree->expChar == 'n')
            printf("%d ",tree->expNumber);
        else
            printf("%c ",tree->expChar);
    }
}

// Function to evaluate expression from tree
int evaluate(BT Tree)
{
    // Empty Tree
    if (Tree == NULL)
        return 0;

    // leaf node i.e, an integer
    if (Tree->left == NULL && Tree->right == NULL)
        return Tree->expNumber;

    // Evaluate left subtree
    int leftValue = evaluate(Tree->left);

    // Evaluate right subtree
    int rightValue = evaluate(Tree->right);

    // Check which operator to apply
    if (Tree->expChar=='+')
        return leftValue+rightValue;

    if (Tree->expChar=='-')
        return leftValue-rightValue;

    if (Tree->expChar=='*')
        return leftValue*rightValue;

    if(Tree->expChar == '%' && rightValue != 0)
        return leftValue%rightValue;

    if(Tree->expChar == '%' && rightValue == 0)
        return -9999999999;

    if(Tree->expChar == '/' && rightValue != 0)
        return leftValue/rightValue;
    else
        return -9999999999 ;
}

void evaluateList(LinkedList list)
{
    pos p = list->next ;
    while (p != NULL){

        printf("Expression in infix : %s", p->expression);
        infixTOPostfix(p->expression);
        BT Tree = fillTreeWithExpression(p->expression);
        printf("  -->   Result = %d\n",evaluate(Tree));
        p = p->next ;
    }
}

void printPostFixList(LinkedList list)
{
    pos p = list->next ;
    while (p != NULL)
    {
        infixTOPostfix(p->expression);
        BT Tree = fillTreeWithExpression(p->expression);
        printf("Expression in postfix :");
        printTree(Tree);
        printf("\n");
        p = p->next ;
    }
}

void UploadToFile(LinkedList list)
{
    FILE * write = fopen("output.txt" , "w");
    pos p = list->next ;
    while (p != NULL)
    {
        infixTOPostfix(p->expression);
        BT Tree = fillTreeWithExpression(p->expression);
        fprintf(write , "Expression in postfix : %s\n" , p->expression);
        fprintf(write , "  -->   Result = %d\n",evaluate(Tree));
        p = p->next ;
    }
    fclose(write);
}
