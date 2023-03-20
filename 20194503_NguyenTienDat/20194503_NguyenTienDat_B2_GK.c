#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX_LINE_LENGTH 1024
#define MAX_LENGTH 1024

extern char *strptime(const char *__restrict _s,
                      const char *__restrict _fmt, struct tm *_tp)
__THROW;

struct node {
    time_t timestamp;
    char seller[100];
    char buyer[100];
    char productID[100];
    int number;
    int cost;
    struct node *left, *right;
};

char input[MAX_LENGTH][MAX_LINE_LENGTH];

time_t convertTime(char *string) {
    struct tm *info = malloc(sizeof(struct tm));
    memset(info, 0, sizeof(struct tm));
    strptime(string, "%d-%m-%Y", info);
    return mktime(info);
}

struct node *newNode(char *timestamp, char *seller, char *buyer, char *productID, int number, int cost) {
    time_t time = convertTime(timestamp);
    struct node *temp = (struct node *) malloc(sizeof(struct node));
    temp->timestamp = time;
    sprintf(temp->seller, "%s", seller);
    sprintf(temp->buyer, "%s", buyer);
    sprintf(temp->productID, "%s", productID);
    temp->number = number;
    temp->cost = cost;
    temp->left = temp->right = NULL;
    return temp;
}

void inorder(struct node *root) {
    if (root != NULL) {
        inorder(root->left);
        printf("%s %s %s %d %d\n", root->seller, root->buyer, root->productID, root->number, root->cost);
        inorder(root->right);
    }
}

int totalNodes(struct node *root) {
    if (root == NULL)
        return 0;
    int l = totalNodes(root->left);
    int r = totalNodes(root->right);
    return 1 + l + r;
}

struct node *
insert(struct node *node, char *timestamp, char *seller, char *buyer, char *productID, int number, int cost) {
    if (node == NULL)
        return newNode(timestamp, seller, buyer, productID, number, cost);
    if (cost < node->cost)
        node->left = insert(node->left, timestamp, seller, buyer, productID, number, cost);
    else if (number < node->number)
        node->left = insert(node->left, timestamp, seller, buyer, productID, number, cost);
    else if (strcmp(productID, node->productID) < 0)
        node->left = insert(node->left, timestamp, seller, buyer, productID, number, cost);
    else if (difftime(convertTime(timestamp), node->timestamp) < 0)
        node->left = insert(node->left, timestamp, seller, buyer, productID, number, cost);
    else {
        char seller_buyer[200];
        sprintf(seller_buyer, "%s_%s", seller, buyer);
        char seller_buyer2[200];
        sprintf(seller_buyer2, "%s_%s", node->seller, node->buyer);
        int result = strcmp(seller_buyer, seller_buyer2);
        if (result < 0)
            node->left = insert(node->left, timestamp, seller, buyer, productID, number, cost);
        else if (result > 0)
            node->right = insert(node->right, timestamp, seller, buyer, productID, number, cost);
        else {
            node->number += number;
            node->cost += cost;
        }
    }
    return node;
}

int valid_money_count = 0, valid_product_count = 0;

bool validate_cost(int cost) {
    if (cost >= 1 && cost <= 2000000) {
        valid_money_count++;
        return true;
    }
    return false;
}

bool validate_number(int number) {
    if (number >= 1 && number < 100) {
        valid_product_count++;
        return true;
    }
    return false;
}

struct node *buildTree(int N) {
    struct node *root = NULL;
    int index = 0;
    while (index < N) {
        int dd, mm, yyyy, number, cost;
        char seller[100] = {0}, buyer[100] = {0}, productID[100] = {0};
        char timestamp[100] = {0};
        sscanf(input[index], "%d-%d-%d %s %s %s %d %d", &dd, &mm, &yyyy, seller, buyer, productID, &number, &cost);
        sprintf(timestamp, "%d-%d-%d", dd, mm, yyyy);
        if (validate_cost(cost) && validate_number(number))
            root = insert(root, timestamp, seller, buyer, productID, number, cost);
        index++;
    }

    printf("Total nodes: %d\n", totalNodes(root));
    return root;
}

int height(struct node *p) {
    if (p == NULL) return 0;
    int maxH = 0;
    int hl = height(p->left);
    if (maxH < hl) maxH = hl;
    int hr = height(p->right);
    if (maxH < hr) maxH = hr;
    return maxH + 1;
}

int main() {
    char line[MAX_LINE_LENGTH];
    int N = 0;
    int index = 0;
    printf("Enter the data: \n");
    while (fgets(line, MAX_LINE_LENGTH, stdin)) {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = 0;
        if (strcmp(line, "$") == 0)
            break;
        sprintf(input[index], "%s", line);
        index++;
    }
    printf("Input N: ");
    scanf("%d%*c", &N);
    struct node *root = buildTree(N);
    printf("Height of tree: %d\n", height(root));
    return 0;
}
