File Partitioning Tool (File Splitter)
Overview

This is a high-performance C-based utility designed to split any binary file into multiple smaller parts (chunks). The program calculates the file size, determines the optimal chunk size, and handles any remaining bytes by appending them to the final partition to ensure data integrity.
Features

    Dynamic Partitioning: Splits files into a user-defined number of parts (up to 8).

    Binary Safe: Works with images, videos, documents, and executable files.

    Precision Handling: Automatically manages the remainder bytes (modulus) to ensure no data is lost during the split.

    Optimized Memory: Uses dynamic memory allocation (malloc) to handle large data chunks efficiently.

How It Works

    Size Calculation: The program uses fseek and ftell to find the exact byte size of the source file.

    Memory Allocation: It allocates a buffer large enough to hold one chunk plus any extra bytes.

    Chunking Logic:

        It divides the total bytes by the number of parts.

        It reads from the source and writes to a new file named [original_name].[index].

        The final chunk is adjusted to include any leftover bytes from the division.

Usage
Compilation

Use any standard C compiler (like GCC):
Bash

gcc main.c -o file_splitter

Execution

The program requires two arguments: the filename and the number of parts (1-8).
Bash

./file_splitter <filename> <number_of_parts>

Example:
To split a photo named image.bmp into 4 parts:
Bash

./file_splitter image.bmp 4

This will generate:

    image.bmp.0

    image.bmp.1

    image.bmp.2

    image.bmp.3

Technical Specifications

    Language: C (Standard)

    Memory Management: Heap-based allocation with safety free().

    Max Partitions: 8 (Configurable in code).

    File Mode: rb (Read Binary) / wb (Write Binary).

License

This project is open-source and free to use for educational and development purposes.
