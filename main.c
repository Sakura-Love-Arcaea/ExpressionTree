#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AND '^'
#define OR 'v'
#define Q1
//#define INFIX
struct TreeNode {
    char ele;
    struct TreeNode *left;
    struct TreeNode *right;
};
struct TreeNode *createTreeNode(char ele) {
    struct TreeNode * node = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    node->ele = ele;
    node->left = NULL;
    node->right = NULL;
    return node;
}

struct TreeNode *combind(char ele, struct TreeNode *left, struct TreeNode *right) {
    struct TreeNode * node = (struct TreeNode *) malloc(sizeof(struct TreeNode));
    node->ele = ele;
    node->left = left;
    node->right = right;
    return node;
}

void TreePrint(struct TreeNode *root) {
    if (root == NULL) {
        return;
    } else {
#ifdef Q2        
        printf("%c", root->ele);
        TreePrint(root->left);
        TreePrint(root->right);
#endif
#ifdef Q3        
        TreePrint(root->left);
        TreePrint(root->right);
        printf("%c", root->ele);
#endif

#ifdef INFIX
        if (root->left != NULL || root->right != NULL) {
            printf("%c", '(');
        }
        TreePrint(root->left);
        printf("%c", root->ele);
        TreePrint(root->right);
        if (root->left != NULL || root->right != NULL) {
            printf("%c", ')');
        }
#endif
    }
}


void printLevel(struct TreeNode *root) {
    if (root == NULL) {
        return;
    } else {
        if (root->left) printf("%c", root->left->ele);
        if (root->right) printf("%c", root->right->ele);
        printLevel(root->left);
        printLevel(root->right);
    }
    
}

void printLevelOrder(struct TreeNode *root) {
    if (root == NULL) {
        return;
    } else {
        printf("%c", root->ele);
        printLevel(root);
    }
    
}

int isOperator(char c) {
    if (c == AND || c == OR) {
        return 1;
    } else {
        return 0;
    }
}

char *infixToPostfix(char *expression) {
    //-a^b
    //a^-b
    //a^(-bVc)
    int top = -1;
    char stack[99] = {0};
    char *output = (char *) malloc(sizeof(char) * 999);
    int outputIndex = 0;
    
    for (int i = 0; i < strlen(expression); i++) {
        if ((expression[i] == '-' && i == 0) ||
            (expression[i] == '-' && isOperator(expression[i-1])) ||
            (expression[i] == '-' && expression[i-1] == '(')) {
            stack[++top] = '-';
        } else if (expression[i] == '(') {
            stack[++top] = '(';
        } else if (expression[i] == ')') {
            while (stack[top] != '(') {
                output[outputIndex++] = stack[top--];
            }
            top--;
            if (stack[top] == '-') {
                output[outputIndex++] = stack[top--];
            }
        } else if (isOperator(expression[i])) {//符號
            if (isOperator(stack[top])) {
                output[outputIndex++] = stack[top--];
            }
            stack[++top] = expression[i];
        } else {
            output[outputIndex++] = expression[i];
            if (stack[top] == '-') {
                output[outputIndex++] = stack[top--];
            }
            
        }
    }
    while (top != -1) {
        output[outputIndex++] = stack[top--];
    }
    return output;
}

struct TreeNode *expressionTree(char *infix) {
    char *input = infixToPostfix(infix);
        //stack
    int top = -1;
    struct TreeNode *stack[30] = {0};
    for (int i = 0; i < strlen(input); i++) {
//        printf("%c\n", input[i]);
        if (input[i] != AND && input[i] != OR && input[i] != '-') {
            stack[++top] = createTreeNode(input[i]);
        } else if (input[i] != '-'){
            struct TreeNode *right = stack[top--];
            struct TreeNode *left = stack[top--];
            stack[++top] = combind(input[i], left, right);
        } else {
            struct TreeNode *temp = stack[top];
            stack[top] = createTreeNode('-');
            stack[top]->right = temp;
    
        }
    }
    return stack[top--];
}


int main(int argc, const char * argv[]) {
    char infix[999];
    for (;;) {
        scanf("%998s", infix);
        if (infix[0] == '0') {
            printf("quit\n");
            return 0;
        }
        // printf("infix: %s\n", infix);
        // printf("postfix: %s\n", infixToPostfix(infix));
        // printf("TreeOutput: ");
#ifdef Q1
    printLevelOrder(expressionTree(infix));
#endif
#ifndef Q1
    TreePrint(expressionTree(infix));
#endif
        printf("\n");
        // printf("\n");
    }
    return 0;
}
