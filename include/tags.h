#ifndef TAGS_H
#define TAGS_H
#define MAX_CATEGORY 30
int findCategoryIndex(char categories[][MAX_CATEGORY], int catCount, char *target);
void saveTags();
void loadTags();
void deleteTag();
void setupTags();
#endif // TAGS_H
