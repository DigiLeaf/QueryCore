# QueryCore — Offline Search Engine in C++

QueryCore is an offline search engine written in C++ that indexes a local corpus
of public-domain text files and supports Boolean queries with TF-IDF–based
relevance ranking.

## Features
- Recursive File crawling using std::filesystem
- Tokenization and text normalization
- Inverted index construction
- Boolean AND/OR query support
- TF-IDF based relevance ranking
- User-friendly command-line interface wit formatted output

## Project Structure
- src/: source files
- include/: header files
- data/: test documents

## Corpus 
The data/ directory contains a collection of public-domain text files,
including books and documents sourced from publicly available archives.
These files are used solely for testing and demonstrating the search engine.

## How it Works
1. On startup, QueryCore crawls the data/ directory and discovers supported text files
2. An inverted index is built, mapping tokens to the documents in which they appear.
3. The user is presented with a simple CLI menu.
4. When a search query is entered:
    - The query is tokenized and normalized.
    - Boolean Logic (AND / OR) is applied)
    - Documents are ranked using TF-IDF scoring
5. Results are displayed in a fomratted table showing:
    - File name
    - Relevance Score
6. The user may run additonal queries or exit the program.

## Query Support
 - OR queries (default): returns documents containing any query term
 - AND queries: returns documents containing all query terms
 - Mixed AND/OR queries are rejected with clear error message

## Ranking
Query Core uses TF-IDF (Term Frequency - Inverse Document Frequency) to rank results:
 - Term Frequency (TF): how often a term appears in a document
 - Inverse Document Frequency (IDF): how rare a term is across the corpus
 - Final relevance scores are nomralized and displayed as percentages

## Build & Run

This project was developed and tested using Visual Studio 2022 on Windows.

### Using Visual Studio (Recommended)
1. Open the soultion file (.sln) in Visual Studio 2022
2. Selected the desired build configuration (Debug or Release)
3. Build the project (Build -> Build Solution)
4. Run the executable from Visual Studio or from the output directory

### Data Directory
Ensure a data/ folder exists in the project root containing text file (.txt, .md) to be indexed.
The program builds the index at startup.

### Notes
 - No external libraries or dependencies are required
 - Uses only the C++ standard Library
 -Although developed with Visual Studio, the code only uses standard C++ and
  should compile with other mondern C++ compilers with minimal changes