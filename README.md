# Bare Min C
This guide will hopefully guide our developers in gaining a better understanding of the C programming language.  It is expected to grow as we identify common issues that our developers encounter or gaps in their knowledge.  It is not expected to be an all encompassing guide to the C programming language. Below is a rough idea of the topics that will be covered.  Topics may or may not survive in this order or at all. 

**This book is not finished and I don't know when I will get to it because I'm lazy...**

## General Outline
1. Getting started
	1. Basic Structure of a C Program
	1. Compilation
1. Data Types
	1. Basic Types
	1. Enum
	1. Void
	1. Operators
	1. Arrays
	1. Pointers
	1. Dynamic Memory
1. Control Flow
	1. If / Else
	1. Switch
	1. While
	1. For
	1. Goto
1. Command Line Args
	1. Manual Parsing
	1. getopt
1. Structures
1. Working with Files
	1. Opening
	1. Reading
	1. Reading and Writing Binary
	1. File Stats
1. Concurency
	1. Forking
	1. Multithreading
1. Networking
	1. getaddrinfo
	1. sigaction
1. Data Structures
	1. Linked-List
	1. Queue
	1. Stack (Incomplete)
	1. Binary Search Tree (Incomplete)
	1. HashTable (Incomplete)

## Documents
I have decided to use Latex for writing this document.  I'll probably end up regretting this down the road but for now, it stays.

### Template
I have downloaded a book template from: [Latex Templates](latextemplates.com/cat/books).  I'll probably modify it slightly but wanted to get some of the hard stuff out of the way early on.

### Required Software
Not sure if this is an all inclusive list, but I could compile the above template on PoP!_OS 20.04 after installing the below packages.  Your mileage may vary.

```bash
sudo apt-get install texstudio texworks texlive-latex-extra texlive-bibtex-extra biber valgrind gdb
```
