#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

struct Trie {
    int count;
    struct Trie *children[ALPHABET_SIZE];
};

struct Trie *createNode() {
    struct Trie *newNode = (struct Trie *)malloc(sizeof(struct Trie));
    newNode->count = 0;
    for (int i = 0; i < ALPHABET_SIZE; i++)
        newNode->children[i] = NULL;
    return newNode;
}

void insert(struct Trie **ppTrie, char *word) {
    if (*ppTrie == NULL)
        *ppTrie = createNode();

    struct Trie *current = *ppTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            current->children[index] = createNode();
        current = current->children[index];
    }
    current->count++;
}

int numberOfOccurances(struct Trie *pTrie, char *word) {
    struct Trie *current = pTrie;
    for (int i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL)
            return 0;
        current = current->children[index];
    }
    return current->count;
}

struct Trie *deallocateTrie(struct Trie *pTrie) {
    if (pTrie == NULL)
        return NULL;

    for (int i = 0; i < ALPHABET_SIZE; i++)
        deallocateTrie(pTrie->children[i]);

    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = NULL;

    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++)
        insert(&trie, pWords[i]);

    for (int i = 0; i < 5; i++)
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));

    trie = deallocateTrie(trie);
    if (trie != NULL)
        printf("There is an error in this program\n");
    return 0;
}
