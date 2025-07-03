#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file.h"
#include "expenses.h"


void saveToFile() {
    FILE *fp = fopen("expenses.txt", "w");
    if (!fp) {
        printf("\nError opening file!\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s,%s,%.2f,%s\n", expenses[i].date, expenses[i].category,
                expenses[i].amount, expenses[i].note);
    }
    fclose(fp);
    printf("\nExpenses saved to 'expenses.txt'\n");
}

void loadFromFile() {
    FILE *fp = fopen("expenses.txt", "r");
    if (!fp) return;

    while (fscanf(fp, "%10[^,],%29[^,],%f,%99[^\n]\n",
                  expenses[count].date,
                  expenses[count].category,
                  &expenses[count].amount,
                  expenses[count].note) == 4) {
        count++;
    }
    fclose(fp);
}
