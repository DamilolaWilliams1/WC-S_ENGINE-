Web Crawler & Search Indexer<br>

Overview<br>
This project implements a web crawler, indexer, and search engine that retrieves webpages, extracts relevant terms, and ranks them using TF-IDF scoring.<br>

Features<br>
Web Crawler: Uses curl to fetch webpages and extract links.<br>
Indexer: Implements a trie-based structure to store word occurrences.<br>
Search Engine: Uses TF-IDF ranking to find and rank relevant pages.<br>
Memory Management: Allocates and deallocates memory efficiently to prevent leaks.<br>

Files

File Description<br>
crawler.c: Crawls web pages and extracts links.<br>
index.c: Indexes web pages and builds a trie structure for word storage.<br>
webSearch.c: Processes user queries and ranks results using TF-IDF.<br>

Compilation & Usage<br>
Compile the program: gcc -o crawler crawler.c index.c webSearch.c -lm<br>
Run the web crawler: ./crawler <urlFile> <maxPages> <seed><br>
<urlFile>: File containing seed URLs. <maxPages>: Maximum number of pages to crawl. <seed>: Random seed for link selection.
Query the indexed pages: ./webSearch <urlFile> <maxPages> <seed>

![Example](example.png)
![Example1](example1.png)
![Example](example2.jpeg)

