#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1024
int valid_money_count = 0, valid_product_count = 0;
int max_index = 0, max_cost = 0, current_index = -1;

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

void check_max_cost(int cost, int number) {
    if (cost / number > max_cost) {
        max_cost = cost / number;
        max_index = current_index;
    }
}

int main() {
    char line[MAX_LINE_LENGTH];
    printf("Enter the data: \n");
    while (fgets(line, MAX_LINE_LENGTH, stdin)) {
        int dd, mm, yyyy, number, cost;
        char seller[100] = {0}, buyer[100] = {0}, productID[100] = {0};
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = 0;
        if (strcmp(line, "$") == 0)
            break;
        sscanf(line, "%d-%d-%d %s %s %s %d %d", &dd, &mm, &yyyy, seller, buyer, productID, &number, &cost);
        current_index++;
        bool result = validate_cost(cost);
        bool result2 = validate_number(number);
        if (result && result2)
            check_max_cost(cost, number);
    }

    printf("%d\n", valid_money_count);
    printf("%d\n", valid_product_count);
    printf("%d\n", max_index);
    return 0;
}
