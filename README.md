# WordSearch

Command line application, solves any word search puzzle that falls within specified dimensions. 

## The Problem

Given an input dictionary read in from a file to use for all test cases, and several word 
search grids, identify all words from the dictionary that appear in each word search grid. 
Dictionary file contains 149,000+ words.

<p align="center">
  <img width="890" height="434" src="http://appham.com/wp-content/uploads/2013/10/twisty-featured-big-890x434.png">
</p>

## Usage 

**To Compile**
```
gcc WordSearch.c
```

**To Run**
```
a
```

The first line of input will contain a single positive integer x, representing the number of input cases.

The input cases (configurations) follow, r and c, representing the number of rows and columns respectively, in the word search grid.

The following r lines will contain strings of exactly c characters, all of which will be lowercase letters for each row of the word search grid for that input case.

**Search Keyword Restrictions**
```c
#define MAX_STRING_LENGTH 19
#define MIN_STRING_LENGTH 4
```


### Sample Input

```
2         # Solve 2 puzzles

4 4       # Configuration puzzle 1
hello
oreos
mover
ender

6 6       # Configuration puzzle 2 
knowns 
bitter
owisjh
iakosl
ijeuak
nmsbwo
```

### Sample Output

```
Words Found in Grid #1:
________________________

hell
home
move

Total words: 3

Enter puzzle configuration #2

Words Found in Grid #2:
________________________

know
known
knowns
owns
wonk
bitt
bitter
tike
tikes

Total words: 9
```
