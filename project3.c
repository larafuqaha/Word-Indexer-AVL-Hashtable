/*
Name: Lara Foqaha 
ID: 1220071
Section: 5
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// implementation of AVL tree struct
struct node;
typedef struct node* Tnode;
struct node
{
    char word[50];
    Tnode left;
    Tnode right;
    int height;
    int frequency;
};
Tnode AVL_T; //global AVL tree

// implementation of hash table struct
struct hashCell;
struct hashCell
{
    char word[50];
    int frequency;
    int state; // 0 for Empty, 1 for Occupied, and 2 for Deleted
};
typedef struct hashCell* HashTable;
HashTable table; //global hash table
int tableSize =0; // # of elements in the hash table are 0 at first
int tableCapacity;

void menu ();
int max (int x, int y);
int getHeight(Tnode T);
Tnode singleRotateLeft (Tnode T);
Tnode singleRotateRight (Tnode T);
Tnode leftRightDoubleRotate (Tnode T);
Tnode rightLeftDoubleRotate(Tnode T);
Tnode insert (Tnode T, char addedWord[]);
Tnode loadFile ();
void printInorder (Tnode T);
Tnode find (char word[], Tnode T);
Tnode findMin (Tnode T);
Tnode delete (char delWord[], Tnode T);
int hashString (char word[], int tableSize);
int numberOfNodes(Tnode T);
int calcTableCapacity();
int nextPrime(int x);
int isPrime(int x);
void printHashTable(HashTable table);
HashTable createHashTable ();
int primeNumberLess();
int doubleHash(int hashValue, int i);
void insertHashTableFromAVL (char Word[], int Frequency);
void inorderTraverse (Tnode T);
int findInHashTable(char Word[]);
void insertHashTableFromUser (char Word[]);
void rehash ();
void insertForRehashing (char Word[], int Frequency, HashTable newTable, int newTableCapacity);
void deleteFromHashTable (char word[]);
int getMaxFrequency();
int numberOfUniqueWords();

int main()
{   
    int option, isLoaded=0, isCreatedAVL = 0, iscreatedHash = 0;
    do 
    {
        menu();
        scanf("%d",&option);
        switch (option)
        {
        case 1: 
            AVL_T = loadFile();
            isLoaded = 1;
            break;

        case 2:
            if(isLoaded == 1)
            {
                printf("Creating the AVL tree.\n\n");
                printf("AVL tree has been created.\n\n");
                isCreatedAVL = 1;
            }
            else 
                printf("Please load the file first.\n\n");
            break;

        case 3: 
            if(isLoaded == 1)
            {
                if(isCreatedAVL == 1)
                {
                printf("Enter a word to insert to the AVL tree.\n\n");
                char addedWord[50];
                scanf("%s", addedWord);
                strlwr(addedWord);
                if (find(addedWord, AVL_T) != NULL)
                {
                    AVL_T = insert(AVL_T, addedWord);
                    printf("\nWord '%s' already exists, so its frequency has been incremented.\n\n", addedWord);
                }    
                else 
                {
                    AVL_T = insert(AVL_T,addedWord);
                    printf("Word '%s' has been inserted.\n\n", addedWord);
                }  
                }
                else 
                    printf("Please create the AVL tree first.\n\n");
            }
            if (isLoaded == 0) 
                printf("Please load the file first.\n\n");
            break;

        case 4:
            if (isLoaded == 1)
            {
                if(isCreatedAVL == 1)
                {
                printf("Enter a word to delete from AVL tree.\n\n");
                char word[50];
                scanf("%s",word);
                AVL_T = delete(word, AVL_T);
                }
                else 
                    printf("Please create the AVL tree first.\n\n");
            }
            else 
                printf("Please load the file first.\n\n");
            break;

        case 5:
            if (isLoaded == 1)
            {
                if(isCreatedAVL == 1)
                {
                printInorder(AVL_T);
                printf("\n\n");
                }
                else 
                    printf("Please create the AVL tree first.\n\n");
            }
            else 
                printf("Please load the file first.\n\n");
            break;

        case 6:
            if(isLoaded == 1)
            {
                if(isCreatedAVL == 1)
                {
                printf("\nCreating the Hash Table...\n\n");
                tableCapacity = calcTableCapacity();
                //printf("********************************************capacity: %d\n",tableCapacity);
                table = createHashTable();
                inorderTraverse(AVL_T); //traversing through the AVL tree and inserting each node to the hash table
                printf("Hash Table is created.\n\n");
                printHashTable(table);
                iscreatedHash = 1;
                }
                else 
                    printf("Please create the AVL tree first.\n\n");
            }
            else 
                printf("Please load the file first.\n\n");
            break;

        case 7:
            if (isLoaded == 1)
            {
                if(iscreatedHash == 1)
                {
                printf("Enter a word to insert to the hash table.\n\n");
                char insertedWord[50];
                scanf("%s",insertedWord);
                strlwr(insertedWord);
                insertHashTableFromUser(insertedWord);
                printHashTable(table);
                }
                else 
                    printf("Please create the hash table first.\n\n");
            }
            else 
                printf("Please load the file first.\n\n");
            break;

        case 8:
            if (isLoaded == 1)
            {
                if(iscreatedHash == 1)
                {
                printf("Enter a word to delete from the hash table.\n");
                char delWord[50];
                scanf("%s",delWord);
                strlwr(delWord);
                deleteFromHashTable(delWord);
                printHashTable(table);
                }
                else 
                    printf("Please create the hash table first.\n\n");
            }
            else 
                printf("please load the file first.\n\n");
            break;

        case 9:
            if (isLoaded == 1)
            {
                if(iscreatedHash == 1)
                {
                printf("Enter a word to search for in the hash table.\n\n");
                char Word[50];
                scanf("%s",Word);
                strlwr(Word);
                int index = findInHashTable(Word);
                if(index == -1)
                    printf("Word '%s' does not exist in the hash table.\n\n",Word);
                else
                    printf("Word '%s' is found with frequency: %d\n\n",Word, table[index].frequency);
                }

                else 
                    printf("Please create the hash table first.\n\n");
            }
            else 
                printf("Please load the file first.\n\n");
            
            break;

        case 10:
            if (isLoaded == 1)
            {
            if (iscreatedHash == 1)
            {
            //getting the most frequent word(s)
            int maxFrequency = getMaxFrequency();
            printf("\nMost frequent word(s):\n");
            for(int i = 0; i<tableCapacity; i++)
                if (table[i].frequency == maxFrequency)
                    printf("'%s' ",table[i].word);
            printf("\n\n");

            // getting the total number of unique words and printing them
            printf("Number of unique words in the hash table: %d\n",numberOfUniqueWords());
            printf("Unique words are: ");
            for(int i=0; i<tableCapacity; i++)
                if(table[i].frequency == 1)
                    printf("'%s' ", table[i].word);
            printf("\n\n");

            //getting the words repeated more than a specific number
            printf("Enter a number to get words repeated more than a specific threshold.\n");
            int num;
            scanf("%d", &num);
            if(num > getMaxFrequency())
                printf("No words in the hash table with a frequency higher than %d.\n\n", num);
            else
            {
                printf("Words with a higher frequency than %d are: ", num);
                for(int i = 0; i<tableCapacity; i++)
                    if(table[i].frequency > num)
                    printf("'%s' ",table[i].word);
                printf("\n\n");
            }
            }
            else 
                printf("Please create the hash table first.\n\n");
            }
            else
                printf("Please load the file first.\n\n");
            
            break;

        default:
            printf("No such option, try again!\n\n");
            break;
        }
    } while (option != 11);
    return 0;
}
void menu ()
{
    printf("Choose an option from 1 to 11.\n");
    printf("1- Load data from file.\n");
    printf("2- Create the AVL tree.\n");
    printf("3- Insert a word to the AVL tree.\n");
    printf("4- Delete a word from the AVL tree.\n");
    printf("5- Print the words as sorted in the AVL tree.\n");
    printf("6- Create the hash table.\n");
    printf("7- Insert a word to the hash table.\n");
    printf("8- Delete a word from the hash table.\n");
    printf("9- Search for a word in the hash table and print its frequency.\n");
    printf("10- Print words statistics.\n");
    printf("11- Exit the application.\n");
}

int max (int x, int y)
{
    if (x>y)
        return x;
    else return y;
}

int getHeight(Tnode T)
{
    if (T == NULL)
        return -1;
    else 
        return T->height;
}

Tnode singleRotateLeft (Tnode T)
{
    Tnode newRoot = T->right;
    T->right = newRoot->left;
    newRoot->left = T;
    newRoot->height = 1 + max( getHeight(newRoot->left), getHeight(newRoot->right) );
    T->height = 1 + max( getHeight(T->left), getHeight(T->right) );
    return newRoot;
}

Tnode singleRotateRight (Tnode T)
{
    Tnode newRoot = T->left;
    T->left = newRoot->right;
    newRoot->right = T;
    newRoot->height = 1 + max(getHeight(newRoot->left), getHeight(newRoot->right));
    T->height = 1 + max( getHeight(T->left), getHeight(T->right));
    return newRoot;
}

Tnode leftRightDoubleRotate (Tnode T)
{
    T->left = singleRotateLeft(T->left);
    T = singleRotateRight(T);
    return T;
}

Tnode rightLeftDoubleRotate(Tnode T)
{
    T->right = singleRotateRight(T->right);
    T = singleRotateLeft(T);
    return T;
}

Tnode insert (Tnode T, char addedWord[])
{
    if (T == NULL)
    {
        T = (Tnode)malloc(sizeof(struct node));
        if (T == NULL) //if memory allocation fails
        {
            printf("Out of memory.\n");
            return NULL;
        }

        T->left = T->right = NULL;
        T->height = 0;
        T->frequency = 1;
        strcpy(T->word, addedWord);
    }

    else if (strcmp(addedWord,T->word) < 0 ) //if addedWord < T->word, insert it at the left of T
    {
        T->left = insert(T->left, addedWord);
        if (getHeight(T->left) - getHeight(T->right) > 1) // if the node balance >=2 (since we are adding to the left), do rotation
        {
            if (strcmp(addedWord, T->left->word) > 0) // if the added word is at the right of T->left (addedWord > T->left->word)
                T = leftRightDoubleRotate(T);
            else // if the added word is at the left of T->left (addedWord < T->left->word)
                T = singleRotateRight(T);
        }
    }

    else if (strcmp(addedWord, T->word) > 0) // if addedWord > T->word, insert it at the right of T
    {
        T->right = insert(T->right, addedWord);
        if (getHeight(T->left) - getHeight(T->right) < -1 ) //if the node balance < -1 (since we are adding to the right), do rotation
        {
            if (strcmp(addedWord, T->right->word) > 0) //if the added word is at the right of T->right 
                T = singleRotateLeft(T);
            else //if the added word is at the left of T->right
                T = rightLeftDoubleRotate(T);
        }
    }

    else // if addedWord = T->word, increment the frequency (no inserting a new node)
    {
        T->frequency = T->frequency + 1;
        return T; //so that the height does not change if a new node is not added
    }

    // update tree height if a new node is inserted
    T->height = 1 + max(getHeight(T->left), getHeight(T->right));
    return T;
}

Tnode loadFile ()
{
    FILE* f = fopen("input.txt","r");
    if (f == NULL)
    {
        printf("Error opening the file.\n");
        return NULL;
    }
    printf("Loading the input file...\n");

    Tnode T = NULL;
    char fileWord[50];
    while (fscanf(f, "%s", fileWord) != EOF) 
    {
        int length = strlen(fileWord);
        char addedWord[50]; //the word to be inserted to AVL tree
        int j=0; //index for addedWord
        for(int i=0; i<length ;i++)
            if ((fileWord[i] >= 'a' && fileWord[i] <= 'z') || (fileWord[i] >= 'A' && fileWord[i] <= 'Z')) //only taking the alphabetical char
                {
                    addedWord[j] = fileWord[i];
                    j++;
                }
        addedWord[j] = '\0'; 
        if (j>0)
        {
            strlwr(addedWord); // converting the string to lower case
            T = insert(T, addedWord);
        }
    }

    printf("Input file loaded.\n\n");
    return T;
}

void printInorder (Tnode T)
{
    if (T != NULL)
    {
        printInorder(T->left);
        printf("word: '%s',\tfrequency: %d\n",T->word, T->frequency);
        printInorder(T->right);
    }
}

Tnode find (char word[], Tnode T) //to find a node in the AVL tree
{
    if (T == NULL)
        return NULL; //the word is not found in the tree
    else if (strcmp(word, T->word) < 0) //if the word < T->word, search in the left side of T
        find(word, T->left);
    else if (strcmp(word, T->word) > 0) // if the word > T->word, search in the right side of T
        find(word, T->right);
    else 
        return T; // the word is found
}

Tnode findMin (Tnode T) // to find the minimum node in the AVL tree
{
    if (T == NULL)
    {
        printf("Tree is not found.\n");
        return NULL;
    }
        
    while(T->left != NULL)
        T = T->left;
    return T;
}

Tnode delete (char delWord[], Tnode T) // to delete a node from the AVL tree 
{
    int isDeleted =0;
    if (T == NULL)
        printf("Word '%s' is not found so it can't be deleted.\n\n", delWord);
    else if (strcasecmp(delWord, T->word) < 0) //if the word to be deleted < T->word, go left
       T->left = delete(delWord, T->left);
    else if (strcasecmp(delWord, T->word) > 0) //if the word > T->word, go right
        T->right = delete(delWord, T->right);
    else // the word to be deleted is found
    {
        if (T->left != NULL && T->right != NULL) //if the word to be delted has two children, replace it with the smallest in right subtree
        {
            Tnode temp = findMin(T->right); // finding smallest in right subtree
            strcpy(T->word, temp->word);
            T->frequency = temp->frequency;
            T->right = delete(T->word, T->right);
            isDeleted = 1;
        }
        else //if the word has one or zero children
        {
            Tnode temp = T;
            if (T->left == NULL)
                T = T->right;
            else if (T->right == NULL)
                T = T->left;
            free(temp);
            isDeleted = 1;
        }
    }
    if (isDeleted == 1)
        printf("Word '%s' has been deleted.\n\n", delWord);

    //doing rotation if necessary
    if (T != NULL)
    {
    //updating the height of the node to check the new balance
    T->height = 1 + max(getHeight(T->left), getHeight(T->right));

    //if the node is balanced, no rotation
    if ((getHeight(T->left) - getHeight(T->right) >= -1) && (getHeight(T->left) - getHeight(T->right) <=1))
        return T;
    
    else if (getHeight(T->left) - getHeight(T->right) < -1)
    {
        if (T->right->right != NULL) //right of right: single rotation to the left
            T = singleRotateLeft(T);
        else if (T->right->left != NULL) //left of right: RLDR
            T = rightLeftDoubleRotate(T);
    }
    else if (getHeight(T->left) - getHeight(T->right) > 1)
    {
        if (T->left->left != NULL) //left of left: single right totation
            T = singleRotateRight(T);
        else if (T->left->right != NULL) // right of left: LRDR
            T = leftRightDoubleRotate(T);
    }
        
    }
    return T;
}

//hash function of strings
int hashString (char word[], int tableCapacity)
{
    int hashValue = 0;
    int i =0;
    while (word[i] != '\0')
    {
        hashValue = ((hashValue * 32) + word[i]) %tableCapacity; //32 is bit shifting by 5
        i++;
    }    
    return hashValue;
}

int numberOfNodes(Tnode T) //returns the number of items in the tree, to determine the table capacity at first
{
    if (T == NULL)
        return 0;
    else
        return 1 + numberOfNodes(T->left) + numberOfNodes(T->right);
}

int calcTableCapacity() // capacity = smallest prime > # of elements in table / load factor
{
    int x = (int)(numberOfNodes(AVL_T) / 0.6); // desired load factor: 0.6
    return nextPrime(x); 
}

int nextPrime(int x) // returns the first prime number after x (used to get the table capacity)
{
    x++;
    while (x>0)
    {
        if (isPrime(x) == 1)
            return x;
        else
            x++;
    }
}

int isPrime(int x) //determines if a number is prime or not
{
    if (x<2)
        return 0;

    int isPrime = 1;
    for(int i = 2; i<= x/2; i++)
        if(x % i == 0)
        {
            isPrime = 0; //not prime
            break;
        }    

    return isPrime;
}

HashTable createHashTable () //creating and initializing the hash table 
{
    HashTable table = (HashTable)malloc(sizeof(struct hashCell) * tableCapacity);
    if (table == NULL)
    {
        printf("Out of memory.\n");
        return NULL;
    }
    for (int i = 0; i<tableCapacity; i++)
    {
        table[i].frequency = 0;
        table[i].state = 0; // 0 for empty
    }
    return table;
}

void printHashTable(HashTable table)
{   
    for(int i=0; i<tableCapacity; i++) {
        if(table[i].state == 1)
        {
            printf("%d) state: Occupied\tword: %s\tfrequency: %d\n", i, table[i].word, table[i].frequency);
        }
        else if(table[i].state == 2)
            printf("%d) state: Deleted\tword: %s\tfrequency: %d\n", i, table[i].word, table[i].frequency);
        else
            printf("%d) state: Empty\n",i);
    }
    printf("\n");
}

int primeNumberLess() //returns first prime less than table capacity for double hashing
{
    int x = tableCapacity-1;
    while (x>1) //prime numbers start from 2
    {
        if (isPrime(x) == 1)
            return x;
        else
            x--;
    }
}

int doubleHash(int hashValue, int i) //for handling collisions
{
    int x = primeNumberLess(); //less than tableCapacity
    return (hashValue + i*(x - (hashValue % x))) % tableCapacity; 
}

void insertHashTableFromAVL (char Word[], int Frequency) //for creating hash table and inserting AVL words into it
{
    int hashValue = hashString(Word, tableCapacity); 
    int tableIndex = hashValue;
    
    for(int i = 0; i<tableCapacity && table[tableIndex].state == 1; i++) // while the cells are occupied, go through them until an empty cell is found
        tableIndex = doubleHash(hashValue, i); //double hashing to find the right index in the table
           
    //inserting into the hash table
    table[tableIndex].state = 1; //change state from 0 (empty) to 1(occupied)
    table[tableIndex].frequency = Frequency;
    strcpy(table[tableIndex].word, Word);
    tableSize++;
}

void inorderTraverse (Tnode T) //to insert the words from AVL tree to hash table
{
    if (T != NULL)
    {
        inorderTraverse(T->left);
        insertHashTableFromAVL(T->word, T->frequency);
        inorderTraverse(T->right);
    }
}

int findInHashTable(char Word[]) //returns the index of the word if it exists
{
    if(tableSize == 0)
    {
        printf("The table is empty\n");
        return -1;
    }
    
    int hashValue = hashString(Word,tableCapacity); //hashing the word first
    int tableIndex = hashValue; //initializing index

    for(int i = 1; i<tableCapacity && table[tableIndex].state == 1; i++ ) // while the cells are occupied, go through them until an empty cell is found
    {
        if (strcmp(table[tableIndex].word, Word) == 0) //check if it has the same word as the passed word
            return tableIndex; // the word is found

        tableIndex = doubleHash(hashValue, i);
        if (tableIndex == hashValue) //if the whole table was searched
            return -1;
    }
    return -1; // the word is not found
}

void insertHashTableFromUser (char Word[]) 
{
    int hashValue = hashString(Word, tableCapacity); //331 is the table capacity
    int tableIndex = hashValue;
    double loadFactor = (double)tableSize / tableCapacity;

    if (loadFactor > 0.6) ///////////////////////////////changed from 0.7 to 0.6
    {
        if (findInHashTable(Word) != -1) //check if the word exists in the table first
        {
            int wordIndex = findInHashTable(Word); 
            table[wordIndex].frequency ++; //increment word frequency if already exists
            printf("Word '%s' already exists, so its frequency has been incremented.\n\n", Word);
            return; // the word already exists so no insertion
        }
        else    
        {
            rehash(); 
            for(int i = 0; i<tableCapacity && table[tableIndex].state == 1; i++)
                tableIndex = doubleHash(hashValue, i); //double hashing 
            //inserting into the hash table
            table[tableIndex].state = 1; //change state from 0 (empty) to 1(occupied)
            strcpy(table[tableIndex].word, Word);
            table[tableIndex].frequency = 1;
            tableSize++;
            printf("Word '%s' has been inserted to the hash table.\n\n", Word);
        }      

    }

    else 
    {
        for(int i = 0; i<tableCapacity && table[tableIndex].state == 1; i++) // while the cells are occupied, go through them until an empty cell is found
        {
            if (findInHashTable(Word) != -1) //check if the word exists in the table
            {
                int wordIndex = findInHashTable(Word);
                table[wordIndex].frequency ++; 
                printf("Word '%s' already exists, so its frequency has been incremented.\n\n", Word);
                return; // the word already exists so no insertion
            }    
            tableIndex = doubleHash(hashValue, i); //double hashing   
        }
        //inserting into the hash table
        table[tableIndex].state = 1; //change state from 0 (empty) to 1(occupied)
        strcpy(table[tableIndex].word, Word);
        table[tableIndex].frequency = 1;
        tableSize++;
        printf("Word '%s' has been inserted to the hash table.\n\n", Word);
    }
}

void rehash ()
{
    int x = tableCapacity * 2;
    int newTableCapacity = nextPrime(x); //getting the first prime number > twice the size of old table capacity
    HashTable newTable = (HashTable)malloc(sizeof(struct hashCell) * newTableCapacity); //creating new hash table 
    if (newTable == NULL)
    {
        printf("Out of memory.\n");
        return;
    }

    //initializing new table
    tableSize = 0; //resetting the global size

    for(int i = 0; i < newTableCapacity; i++)
        newTable[i].state = 0; // 0 for empty
    //traversing through the old table to get the words
    for (int i = 0; i < tableCapacity; i++)
    {
        if (table[i].state == 1)
        {
            insertForRehashing(table[i].word, table[i].frequency, newTable, newTableCapacity);
        }
    }

    free(table); //freeing old table
    table = newTable;
    tableCapacity = newTableCapacity;
}

void insertForRehashing (char Word[], int Frequency, HashTable newTable, int newTableCapacity) //same as inserting from AVL tree
{
    int hashValue = hashString(Word, newTableCapacity);
    int tableIndex = hashValue;

    for (int i = 0; i<newTableCapacity && newTable[tableIndex].state == 1; i++)
        tableIndex = doubleHash(hashValue, i);
    
    newTable[tableIndex].state = 1;
    newTable[tableIndex].frequency = Frequency;
    strcpy(newTable[tableIndex].word, Word);
    tableSize ++;
}

void deleteFromHashTable (char word[])
{
    if (findInHashTable(word) != -1)
    {
        int wordIndex = findInHashTable(word);
        table[wordIndex].state = 2; // 2 means deleted
        table[wordIndex].frequency = 0;
        printf("Words '%s' has been deleted from the hash table.\n\n", table[wordIndex].word);
    }
    else 
        printf("Word '%s' does not exist in the hash table.\n\n",word);
}

int getMaxFrequency()
{
    int maxFrequency = 0;
    for(int i = 0; i<tableCapacity; i++)
    {
        if (table[i].state == 1)
            if(table[i].frequency > maxFrequency)
                maxFrequency = table[i].frequency;
    }
    return maxFrequency;
}

int numberOfUniqueWords()
{
    int counter = 0;
    for(int i =0; i<tableCapacity; i++)
    {
        if (table[i].frequency == 1)
            counter++;
    }
    return counter;
}