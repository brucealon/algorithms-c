
#ifndef INPUT_H
#define INPUT_H

int read_all_ints(char *filename, int **integers, int *length);
void read_words(char *filename, int (*callback)(char *word, int wordlen, void *extra), void *extra);
int safe_filename(char *dest, char *source, int length);

#endif
