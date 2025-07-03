#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "expenses.h"



int compareDates(const void *a, const void *b) {
    const Expense *expA = (const Expense *)a;
    const Expense *expB = (const Expense *)b;
    int dA, mA, yA, dB, mB, yB;
    sscanf(expA->date, "%2d-%2d-%4d", &dA, &mA, &yA);
    sscanf(expB->date, "%2d-%2d-%4d", &dB, &mB, &yB);
    if (yA != yB) return yA - yB;
    if (mA != mB) return mA - mB;
    return dA - dB;
}

int isValidDate(const char *date) {
    if (strlen(date) != 10) return 0;
    if (date[2] != '-' || date[5] != '-') return 0;
    int day, month, year;
    if (sscanf(date, "%2d-%2d-%4d", &day, &month, &year) != 3) return 0;
    if (month < 1 || month > 12) return 0;
    int daysInMonth[] = {31, 28, 31, 30, 31, 30,
                         31, 31, 30, 31, 30, 31};
    if (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0)) daysInMonth[1] = 29;
    if (day < 1 || day > daysInMonth[month - 1]) return 0;
    return 1;
}

void addExpense() {
    if (count >= MAX_EXPENSES) {
        printf("\nExpense list is full!\n");
        return;
    }
    if (tagCount == 0) {
        printf("No tags available. Please set up tags first.");
        return;
    }
    printf("\nEnter date (DD-MM-YYYY): ");
    scanf("%10s", expenses[count].date);
    getchar();
    if (!isValidDate(expenses[count].date)) {
        printf("Invalid date format or value.\n");
        return;
    }
    printf("Choose a tag:\n");
    for (int i = 0; i < tagCount; i++) {
        printf("%d. %s\n", i + 1, predefinedTags[i]);
    }
    int tagChoice;
    printf("Enter the number of the tag: ");
    scanf("%d", &tagChoice);
    getchar();
    if (tagChoice < 1 || tagChoice > tagCount) {
        printf("Invalid tag selection.\n");
        return;
    }
    strcpy(expenses[count].category, predefinedTags[tagChoice - 1]);
    printf("Enter amount: $");
    scanf("%f", &expenses[count].amount);
    getchar();
    printf("Enter note (optional): ");
    fgets(expenses[count].note, MAX_NOTE, stdin);
    expenses[count].note[strcspn(expenses[count].note, "\n")] = 0;
    count++;
    printf("Expense added successfully!\n");
}

void viewExpenses() {
    if (count == 0) {
        printf("\nNo expenses recorded yet.\n");
        return;
    }
    qsort(expenses, count, sizeof(Expense), compareDates);
    float total = 0;
    char categories[MAX_EXPENSES][MAX_CATEGORY];
    float catTotals[MAX_EXPENSES] = {0};
    int catCount = 0;
    printf("\n===== Expense List (Chronological) =====\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s | %s | $%.2f | %s\n", i + 1,
               expenses[i].date,
               expenses[i].category,
               expenses[i].amount,
               expenses[i].note);
        total += expenses[i].amount;
        int idx = findCategoryIndex(categories, catCount, expenses[i].category);
        if (idx == -1) {
            strcpy(categories[catCount], expenses[i].category);
            catTotals[catCount] = expenses[i].amount;
            catCount++;
        }
        else {
            catTotals[idx] += expenses[i].amount;
        }
    }
    printf("\n===== Category Totals =====\n");
    for (int i = 0; i < catCount; i++) {
        printf("%s: $%.2f\n", categories[i], catTotals[i]);
    }
    printf("-----------------------------\n");
    printf("Total spent: $%.2f\n", total);
}


void deleteExpense() {
    if (count == 0) {
        printf("\nNo expenses to delete.\n");
        return;
    }
    viewExpenses();
    printf("\nEnter the number of the expense to delete: ");
    int index;
    scanf("%d", &index);
    getchar();
    if (index < 1 || index > count) {
        printf("Invalid expense number.\n");
        return;
    }
    for (int i = index - 1; i < count - 1; i++) {
        expenses[i] = expenses[i + 1];
    }
    count--;
    printf("Expense deleted successfully.\n");
}
