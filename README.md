# PMD File Splitter & MergerThis program provides a simple binary file splitter and merger with optionalfake (random) chunks injected into the output.  It generates a `.pmd` metadata file that describes how the chunks were created,and the merger uses the PMD file to reconstruct the original file.---## Features- Split any binary file into **1 to 8 chunks**- Optional insertion of **fake chunks** to obfuscate the real structure- Generates a `.pmd` metadata file describing:  - original file name  - chunk size  - number of chunks  - extra bytes in the last chunk  - bitmask describing which chunks are fake- Merge chunks back into a single file using the `.pmd`- Supports merging from a specific chunk via `-r`---## BuildCompile using GCC:

gcc code1.c -o splitter

---## Usage### 1. Split a file (`-p` mode)

./splitter -p <num_chunks>

Example:

./splitter -p image.jpeg 4

Output:

image.jpeg.0 image.jpeg.1 image.jpeg.2 image.jpeg.3 image.jpeg.pmd

---### Add fake chunks (optional)

./splitter -p <num_chunks> -R <num_fake_chunks>

Example:

./splitter -p image.jpeg 4 -R 2

This creates:- 4 real chunks  - 2 fake random chunks  - A PMD file describing which chunks are fake via a bitmask.---## 2. Merge a file (`-m` mode)### Basic merge (no fake chunks)

./splitter -m <pmd_file>

Example:

./splitter -m image.jpeg.pmd

Outputs:

image.jpeg.m

---### Merge including fake chunks (`-R`)If splitting was done using fake chunks, use:

./splitter -m <pmd_file> -R <output_file>

Example:

./splitter -m image.jpeg.pmd -R final.jpeg

---### Merge starting from a specific chunk (`-r`)

./splitter -m <pmd_file> -r <start_chunk> <output_file>

Example:

./splitter -m image.jpeg.pmd -r 0 rebuilt.jpeg

This starts merging at the given chunk index.---## How Fake Chunks WorkFake chunks are generated using a deterministic pseudo-random generator.A bitmask stored in `meta.rb` marks which chunk indices are fake.Example bitmask (binary):

001010

Meaning chunks:- 1 and 3 are fake  - All others are realDuring merge:- Fake chunks are skipped unless `-R` is used.---## File Structure (PMD)The PMD structure:```ctypedef struct pmd {    char name[256];      // original filename    long chunk_size;     // base chunk size    int extra_bytes;     // bytes added to last chunk    int num_chunks;      // number of real chunks    unsigned short rb;   // bitmask of fake chunks} pmd;

The .pmd file contains only metadata — not the actual chunk data.
Integrity Checking

During merge, the program verifies:

    All required chunk files exist
    Chunk sizes match what the PMD file expects
    Total file size is below 1MB

If any check fails, merging stops.
Notes

    This tool does not compress or encrypt data.
    Fake chunks only add noise; they do not affect real data.
    The .pmd file is required to rebuild the original file correctly.

Example Workflow

# Split into 4 parts + 2 fake parts./splitter -p e1.jpeg 4 -R 2# Rebuild original, respecting fake chunks./splitter -m e1.jpeg.pmd -R recovered.jpeg
