#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chart.h"
#include "expenses.h"

void showBarChart() {
    if (count == 0) {
        printf("\nNo expenses to show in bar chart.\n");
        return;
    }
    char categories[MAX_EXPENSES][MAX_CATEGORY];
    float catTotals[MAX_EXPENSES] = {0};
    int catCount = 0;
    float maxAmount = 0;
    for (int i = 0; i < count; i++) {
        int idx = findCategoryIndex(categories, catCount, expenses[i].category);
        if (idx == -1) {
            strcpy(categories[catCount], expenses[i].category);
            catTotals[catCount] = expenses[i].amount;
            if (catTotals[catCount] > maxAmount) maxAmount = catTotals[catCount];
            catCount++;
        } else {
            catTotals[idx] += expenses[i].amount;
            if (catTotals[idx] > maxAmount) maxAmount = catTotals[idx];
        }
    }
    printf("\n===== Category Bar Chart =====\n");
    for (int i = 0; i < catCount; i++) {
        printf("%-10s | ", categories[i]);
        int barLength = (int)(catTotals[i] / maxAmount * 40);
        for (int j = 0; j < barLength; j++) {
            putchar('#');
        }
        printf(" $%.2f\n", catTotals[i]);
    }
}
