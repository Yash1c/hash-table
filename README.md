
# Hash Table Project

This project is a simple implementation of a hash table using buckets (with linked lists) in C. It was developed as a small assignment for the course "Structured Problem Solving in Computing".

## Features

- Hash table with 10 buckets
- Simple hash function (sum of ASCII codes modulo number of buckets)
- Insert, search, remove, and display operations
- Input validation for key and value lengths
- Interactive menu for user operations

## How to Compile and Run

You need to have GCC installed on your system. To compile and run the program, use the following commands in your terminal:

```sh
gcc tabela.c -o hash_table
./hash_table
```

## Usage

When you run the program, you will see a menu:

```
=== MENU ===
1 - Insert
2 - Search
3 - Remove
4 - Display table
0 - Exit
```

Follow the prompts to insert, search, remove, or display entries in the hash table.

## About

This project was created for the discipline "Structured Problem Solving in Computing" as a practical exercise in data structures and C programming.
