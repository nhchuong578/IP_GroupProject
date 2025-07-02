#ifndef TAGS_H
#define TAGS_H
#define MAX_CATEGORY 30
#define MAX_TAGS 20
extern char predefinedTags[MAX_TAGS][MAX_CATEGORY];
extern int tagCount;

int findCategoryIndex(char categories[][MAX_CATEGORY], int catCount, char *target);

void saveTags();
void loadTags();
void deleteTag();
void setupTags();
#endif // TAGS_H
