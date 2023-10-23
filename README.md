# README: Search Engine Project

## Project Summary
In this project, I have developed a simplified document search engine, similar to those used by popular search engines like Google or Bing. The primary goal was to create a search engine capable of quickly finding matching pages for user queries using map and set abstractions. I employed an inverted matrix approach for dynamic programming and developed multiple functions for tokenizing and processing data. This document serves as a guide and overview of my project.

## Primary Project Topics
- String Operations
- File IO
- Maps
- Sets
- Inverted Index Creation

## How to Compile and Run
1. Make sure you have a C++ compiler installed.
2. Navigate to the project directory in your terminal.
3. Run the `make` command to compile the project.
4. Run the compiled program using `./searchEngine` (or the appropriate executable name).

## How to Use the Search Engine
1. Upon running the program, the inverted index will be constructed, and the program will display the number of web pages processed and the number of distinct words found.
2. You will then be prompted to enter a search query.
3. Enter your query and press Enter to retrieve the matching web pages.
4. The URLs of the matching pages will be displayed.
5. Press Enter with an empty string to exit the program.

## Error Handling
If an invalid filename is provided, the program will exit the `buildIndex` function as soon as possible and return 0.

## Testing
I have implemented extensive test cases in the provided C++ file. It is crucial to test all functionalities in many different ways to ensure the robustness of the search engine.

## Conclusion
This project was an excellent opportunity to delve into the workings of a document search engine and understand the significance of data structures and algorithms in building efficient systems. I encourage you to explore and test the search engine, and I am open to any feedback or suggestions for improvement.
