//Name: Aniya Ross
//Date: 4/19/2024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie {
  struct Trie *children[26];
  int isWord;
  
};
// Initializes a trie structure
  struct Trie *createTrie() {
    //declare and initialize trie structure
    struct Trie *pTrie = (struct Trie*)malloc(sizeof(struct Trie));
    if (pTrie == NULL) {
        // Handle memory allocation failure
        printf("Memory allocation failed\n");
        exit(1);
    }
    pTrie->isWord = 0;

    //initialize the children of the trie
    for (int i = 0; i < 26; i++) {
      pTrie->children[i] = NULL;
    }

    //return the initialized trie
    return pTrie;
  }

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word) {
    int len = strlen(word);
    struct Trie *curr = pTrie;

    for (int i = 0; i < len; i++) {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) {
            curr->children[index] = createTrie();
        }
        curr = curr->children[index];
    }
    // Increment the count for occurrences of the word
    curr->isWord++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word) {
    //declare and initialize variable for traversing through trie and tracking the number of times the given word occurs
    int len = strlen(word);
    int numOccurances = 0;
    struct Trie *curr = pTrie;

    for(int i = 0; i < len; i++){
        int index = word[i] - 'a';
        if(curr->children[index] == NULL)
            return 0;
    
        curr = curr->children[index];
    }

    return curr->isWord;
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie) {
    //deallocate trie from inside out
    for(int i = 0; i < 26; i++){
        if (pTrie->children[i] != NULL){
        deallocateTrie(pTrie->children[i]);
        }
    }
    
    free(pTrie);
    return NULL;
}

  
  // this function will return number of words in the dictionary,
  // and read all the words in the dictionary to the structure words
  int readDictionary(char *filename, char **pInWords) {
    //attempt to open given file and double check if doing so was successful
    FILE *ifp = fopen(filename, "r");
    if(ifp == NULL){
      printf("cannot open file");
      exit(1);
    }

    //declare and initialize variables
    int numWords = 0;
    int i=0;
    char word[100];

    //read the number of words in the file and store each subsequent word in array
    while(fscanf(ifp, "%s", word) != EOF){
      numWords++;
      pInWords[i] = (char *)malloc(sizeof(char) * strlen(word));
      strcpy(pInWords[i], word);
      i++;
    }
    //return the number of words in the file
    return numWords;
  }

  int main(void) {
    char *inWords[256];

    // read the number of the words in the dictionary
    int numWords = readDictionary("dictionary.txt", inWords);
    for (int i = 0; i < numWords; ++i) {
      printf("%s\n", inWords[i]);
    }

    struct Trie *pTrie = createTrie();
    for (int i = 0; i < numWords; i++) {
      insert(pTrie, inWords[i]);
    }
    // parse lineby line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) {
      printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
    }
    pTrie = deallocateTrie(pTrie);
    if (pTrie != NULL)
      printf("There is an error in this program\n");
    return 0;
  }