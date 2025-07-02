#include "tags.h"
#include <stdio.h>
#include <string.h>
void saveTags() {
    FILE *tags = fopen("tags.txt", "w");
    if (tags == NULL){
        printf("Error: Could not open tags file.\n");
        return;
    }
    for (int i = 0; i < tagCount; i++) {
        fprintf(tags, "%s\n", predefinedTags[i]);
    }
    if (fclose(tags)==0){
        printf("Tags saved successfully.\n");
    } else{
        printf("Tags could not be saved.\n");
    }
}

void loadTags() {
    FILE *tags = fopen("tags.txt", "r");
    if (tags == NULL){
        printf("Error: Could not open tags file.\n");
        return;
    }
    while (fgets(predefinedTags[tagCount], MAX_CATEGORY, tags)) {
        predefinedTags[tagCount][strcspn(predefinedTags[tagCount], "\n")] = 0; // should change to fscanf
        tagCount++;
        if (tagCount >= MAX_TAGS) break;
    }
    fclose(tags);
}

void deleteTag() {
    if (tagCount == 0) {
        printf("\nNo tags to delete.\n");
        return;
    }

    printf("\nExisting Tags:\n");
    for (int i = 0; i < tagCount; i++) {
        printf("%d. %s\n", i + 1, predefinedTags[i]);
    }

    printf("Enter the number of the tag to delete: ");
    int delIndex;
    scanf("%d", &delIndex);
    getchar();

    if (delIndex < 1 || delIndex > tagCount) {
        printf("Invalid tag number.\n");
        return;
    }

    for (int i = delIndex - 1; i < tagCount - 1; i++) {
        strcpy(predefinedTags[i], predefinedTags[i + 1]); // move everything backwards after deleting a tag
    }
    tagCount--; // reduce tagcount by 1
    saveTags();
    printf("Tag deleted successfully.\n");
}

void setupTags() {
    int subChoice;
    do {
        printf("\nTag Management:\n");
        printf("1. Add New Tags\n");
        printf("2. Delete a Tag\n");
        printf("3. Back to Main Menu\n");
        printf("Choose an option: ");
        scanf("%d", &subChoice);
        getchar();

        if (subChoice == 1) {
            while (tagCount < MAX_TAGS) {
                char input[MAX_CATEGORY];
                printf("Tag %d: ", tagCount + 1);
                fgets(input, MAX_CATEGORY, stdin);
                input[strcspn(input, "\n")] = 0;
                if (strcmp(input, "done") == 0) break;
                if (findCategoryIndex(predefinedTags, tagCount, input) != -1) {
                    printf("Tag '%s' already exists. Skipping.\n", input);
                    continue;
                }
                strcpy(predefinedTags[tagCount], input);
                tagCount++;
            }
            saveTags();
            printf("Tags setup complete!\n");
        } else if (subChoice == 2) {
            deleteTag();
        } else if (subChoice != 3) {
            printf("Invalid choice. Try again.\n");
        }
    } while (subChoice != 3);
}
