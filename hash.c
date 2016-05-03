#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include <ctype.h>
#include <stdbool.h>

#define DICTIONARY_SIZE 200000
#define WORD_SIZE 20
#define HASH_TABLE_SIZE 1009
#define INPUT_LINE_SIZE 100

//Declaration of the node data type.
typedef struct Node {
    struct Node *next;
    char word[WORD_SIZE];
    int count;
} node;

//Function that takes in a file and reads it word by word. It uses characters in
//array a[] to determine the end of the word.
void read(FILE *book, char word[WORD_SIZE]){
    char c;
    if(fscanf(book,"%c",&c)!=EOF){
        char a[]=". ,;:*!?'()-\n\r";
        int i = 0;
        while(strchr(a,c) == NULL){
        	  word[i]=c;
        	  i++;
        	  if(fscanf(book,"%c",&c)==EOF){
                  break;
              }
        }
        word[i]='\0';
    }
}

//Function that loads all the words from the text file into an array of words.
//It returns the number of words loaded.
int fileInArray(char *fileName, char words[DICTIONARY_SIZE][WORD_SIZE]){
    FILE *book = fopen(fileName,"r");
    char word[WORD_SIZE];
    int i = 0;
    while (!feof(book)){
        if (strcmp(word, "") != 0){
            strcpy(words[i],word);
            read(book, word);
            i++;
        }else{
            read(book, word);
        }
    }
    fclose(book);
    return i;
}

//Searches through the list recursevly to find a node, increasing comparisons
//as it goes. If it finds the node it returns it otherwise it returns NULL.
node* find (char word[WORD_SIZE], node *list, int *comps){
    if (list==NULL){
        return NULL;
    }
    (*comps)++;
    if (strcmp(word, list->word)==0){
        return list;
    }
    return find(word, list->next, comps);
}

//Searches through the list for a word and if found it increasses the count,
//otherwise it creates a new node for the specific word.
node* add (char word[WORD_SIZE], node *list){
    int c = 0;
    node *found = find(word, list, &c);
    if(found){
        found->count++;
        return list;
    }else{
        node *new = malloc (sizeof(node));
        new->next = list;
        new->count = 1;
        strcpy (new->word, word);
        return new;
    }
}

//Creates a linked list from the array of words which is loaded in the main
//function.
node* linkedList(char words[DICTIONARY_SIZE][WORD_SIZE],int n){
    node *list = NULL;
    for(int i=0; i<n; i++){
        list = add(words[i],list);
    }
    return list;
}

//Prints the content of all the nodes from the list.
void printList (node *list){
    if (list != NULL){
        printf("%s\n",list->word);
        printList(list->next);
    }
}

//Hash function takes a word and creates a hash table index for it.
int hash(char word[WORD_SIZE]){
    int length = strlen(word);
    int sum = 0;
    for (int i=0; i<length; i++){
        sum = sum + word[i]*(i+1);
    }
    return sum%HASH_TABLE_SIZE;
}

//Creates a hash table from the array of words which is loaded in the main
//function.
void hashTable(char words[DICTIONARY_SIZE][WORD_SIZE], node **HashTable,int size, int n){
    memset(HashTable, 0, size);
    for(int i=0; i<n; i++){
        if (strcmp(words[i], "") != 0){
            int h = hash(words[i]);
            HashTable[h] = add(words[i],HashTable[h]);
        }
    }
}

//Checks how many empty indexes hash table has given a hash table and size.
int emptyHash(int n, node* HashTable[n]){
    int emptyHash = 0;
    for (int i=0;i<n;i++){
        if (HashTable[i]==NULL) {
            emptyHash++;
        }
    }
    return emptyHash;
}

//Calculates the length of the list given a list.
int listLength(node *list){
    int length = 0;
    node *currentNode = list;
    while (currentNode != NULL){
        length++;
        currentNode = currentNode->next;
    }
    return length;
}

//Calculates the maximum list length of all hash table indexes.
int maxHash(int n, node* HashTable[n]){
    int max = 0;
    for (int i=0;i<n;i++){
        int length = listLength(HashTable[i]);
        max = length > max ? length : max;
    }
    return max;
}

//Searches through the hash table to find the word given a word, hash table and
// number of comparisons.
node* findInHash(char *word, node **HashTable, int *comparisons){
    int i = hash(word);
    return find(word,HashTable[i],comparisons);
}

//This function takes in the file as an argument and comunicates the queries
//with the user.
int main(int argc, char *argv[argc]){
    //Reading the file into an array.
    char words[DICTIONARY_SIZE][WORD_SIZE];
    int totalWords = fileInArray(argv[1],words);
    //Measuring time required to load words from array into linked list.
    clock_t startList=clock();
    node *list=linkedList(words,totalWords);
    clock_t stopList=clock();
    double time_taken_list=(double)(stopList-startList)/CLOCKS_PER_SEC;
    //Declaring hash table and calculating time required to load in from array.
    node* HTable[HASH_TABLE_SIZE];
    int size = sizeof(HTable);
    clock_t startHash=clock();
    hashTable(words,HTable,size,totalWords);
    clock_t stopHash=clock();
    double time_taken_hash=(double)(stopHash-startHash)/CLOCKS_PER_SEC;
    //Printing the details about loading time and hash table details.
    int emptyIndexes = emptyHash(HASH_TABLE_SIZE,HTable);
    int maxIndex = maxHash(HASH_TABLE_SIZE,HTable);
    double hashUsage = (double)(HASH_TABLE_SIZE-emptyIndexes)/HASH_TABLE_SIZE*100;
    printf("\nReading into a list took %.2fs for %d words\n",time_taken_list,totalWords);
    printf("Reading into a table took %.2fs for %d words\n\n",time_taken_hash,totalWords);
    printf("Hash table details:\n");
    printf("Size in bites: %d.\n", size);
    printf("Total nuber of indexes: %d.\n", HASH_TABLE_SIZE);
    printf("Empty indexes: %d.\n", emptyIndexes);
    printf("Longest index: %d nodes.\n", maxIndex);
    printf("Percentage of hash table used: %.2f%c\n\n", hashUsage,37);
    //Prompting the user to search for the words and printing the number of
    //occurances and number of comparisons.
    bool newSearch = true;
    do{
        char line[INPUT_LINE_SIZE], word[INPUT_LINE_SIZE];
        int listComparisons = 0;
        int hashComparisons = 0;
        printf("Enter word for retreival:");
        fgets(line,INPUT_LINE_SIZE, stdin);
        sscanf(line,"%s",word);
        node *locationlist;
        locationlist=find(word,list,&listComparisons);
        findInHash(word,HTable,&hashComparisons);
        if (locationlist != NULL){
            printf("'%s' occurs %d times\n", word, locationlist->count);
            printf("Retreival from the list took %d comparisons.\n", listComparisons);
            printf("Retreival from the hash table took %d comparisons.\n\n", hashComparisons);
        }else{
            printf("Word not found.\n\n");
        }
        printf("Another query? [y/n] ");
        fgets(line, INPUT_LINE_SIZE, stdin);
        newSearch = line[0]=='y';
    }while(newSearch);
}
