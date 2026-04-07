# Word Indexer — AVL Tree & Hash Table

A C project developed as part of the Data Structures and Algorithms course. It efficiently indexes words from a text file using an AVL tree for balanced sorting and fast retrieval, and a hash table for direct access by word frequency.

## Overview

The program reads words from a text file, ignores non-alphabetical characters, treats uppercase and lowercase as the same word, and builds both an AVL tree and a hash table to store each word alongside its frequency count.

## Features

- Reads and parses words from `input.txt`, alphabetical characters only
- Case-insensitive (e.g. "Hello" and "hello" are the same word)
- AVL tree maintains words in sorted order with automatic balancing on insert/delete
- Hash table provides fast word lookup with collision handling
- Word frequency statistics including most frequent word and words above a given threshold

## Data Structures

- **AVL Tree** — self-balancing BST used to store words in sorted order; each node holds a word and its frequency count
- **Hash Table** — built from the AVL tree after construction; allows O(1) average-case word lookup

## Menu Options

1. Load data from the file
2. Create the AVL tree
3. Insert a word to the AVL tree
4. Delete a word from the AVL tree
5. Print words sorted using in-order traversal
6. Create the hash table
7. Insert a word to the hash table
8. Delete a word from the hash table
9. Search for a word in the hash table and print its frequency
10. Print word statistics (unique word count, most frequent word, words above a threshold)
11. Exit

## Input Format

A plain text file (`input.txt`) containing one or more lines of text. Non-alphabetical characters are ignored during parsing.

## How to Compile and Run

```bash
gcc project3.c -o project3
./project3
```

Make sure `input.txt` is in the same directory as the executable.
