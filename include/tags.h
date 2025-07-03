#ifndef TAGS_H
#define TAGS_H
int findCategoryIndex(char categories[][MAX_CATEGORY], int catCount, char *target);
void saveTags();
void loadTags();
void deleteTag();
void setupTags();
#endif // TAGS_H
