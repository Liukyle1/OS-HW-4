# Homework 4 for opertaing systems

## A fully functional exmaple of a code that aims to understand and implement different page replacement algorithms
This project uses these following page replacement algorithms:
• LRU(Least Recently Used)
• Optimal 
• FIFO(First In First Out)
This project also creates a mechanism to accept the given page reference string and the specified
number of frames (4 frames in this case) as input to simulate page replacement.

## User instructions
Lets breakdown how this code works
* The code starts off by initializing a PageReplacement Class
  1. Class represents the simulation of page replacement algorithms
  2. It has private member variables to store the page reference string,the number of frames, the current frames, and the number of page faults
* The constructor initializes the PageReplacement object with the given..
  1. Given page reference string (prs)
  2. Number of frames (nf)
* Reset() Function
  1. This function resets the frames and page_faults variables, preparing the object for a new simulation
* lru() Function:
  1.  This function simulates the LRU algorithm. It iterates through the page reference string
  2.  Maintains a page table to keep track of the last usage index of each page in the frames
  3.  When a page fault occurs, it replaces the least recently used page in the frames 
* optimal() Function
  1. Iterates through the page reference string and predicts which page in the frames will not be used for the longest time in the future
  2. When a page fault occurs, it replaces the page that will not be used for the longest time
* fifo() Function
  1. Uses a queue to keep track of the order in which pages were brought into memory
  2. When a page fault occurs, it replaces the oldest page in the frames based on the order in the queue
* main() Function
  1. An instance of the PageReplacement class is created for each algorithm
  2. Their respective functions (lru(), optimal(), and fifo()) are called to simulate the algorithms with the given page reference string and number of frames.
  

## User Warnings
* The code assumes that the input page reference string and the number of frames are valid. It does not include input validation to check if the page reference string contains valid page numbers and if the number of frames is within a reasonable range. Users should ensure that the input provided to the program is valid to avoid unexpected behavior.
* The code uses additional data structures such as unordered_map and queue to simulate the page replacement algorithms. Users should be aware of the memory usage, especially when simulating with a large number of frames or a long page reference string, to avoid potential memory issues or slowdowns.
