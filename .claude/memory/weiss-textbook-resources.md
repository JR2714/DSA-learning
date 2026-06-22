---
name: weiss-textbook-resources
description: "Paths, page numbering, chapter locations for the Weiss textbook (PDF + text)"
metadata: 
  node_type: memory
  type: reference
  originSessionId: a89a0388-247e-4c65-aa6a-fa021546d0f6
---

## Weiss Textbook: Data Structures and Algorithm Analysis in C++ (4th Edition)

### File Locations

| Format | Path | Use |
|--------|------|-----|
| PDF (original) | `/home/jacob/DSA/DataStructuresAndAlgorithmsInC++.pdf` | Reference only — cannot render without poppler-utils |
| Text (preprocessed) | `/home/jacob/DSA/DSAA_Weiss.text` | **Primary reference** — 31,164 lines, fully readable |
| Source code | https://users.cs.fiu.edu/~weiss/ | Author's website with book's C++ code |

### Page Numbering

- Use the **printed page number** shown at the bottom-left of each page, NOT PDF absolute page number
- In `DSAA_Weiss.text`: page numbers appear as standalone numbers on their own line at the end of each page's content
- Example: line 3004 contains just `51`, and line 3005 reads `52   Chapter 2    Algorithm Analysis`
- When citing: "Weiss p.51" or "Weiss §2.4.3, p.XX"

### Chapter Locations in DSAA_Weiss.text

| Chapter | Line | Printed Page |
|---------|------|-------------|
| Ch.1 Programming: A General Overview | 593 | 1 |
| Ch.2 Algorithm Analysis | 2970 | 51 |
| Ch.3 Lists, Stacks, and Queues | 4232 | ~75 |
| Ch.4 Trees | 6323 | 121 |
| Ch.5 Hashing | 9751 | 193 |
| Ch.6 Priority Queues (Heaps) | 12237 | ~231 |
| Ch.7 Sorting | 14391 | ~283 |
| Ch.8 The Disjoint Sets Class | 17277 | 351 |
| Ch.9 Graph Algorithms | 18594 | ~367 |
| Ch.10 Algorithm Design Techniques | 21963 | 449 |
| Ch.11 Amortized Analysis | 26020 | 533 |
| Ch.12 Advanced Data Structures | 27245 | ~557 |

### How to Read in Conversations

Use the Read tool with `file_path` and `offset`/`limit` parameters:
```
Read /home/jacob/DSA/DSAA_Weiss.text offset=4232 limit=150
```
This reads lines 4232-4382 (start of Ch.3).

### DSA Learning Plan Alignment

The full 16-week learning plan at `/home/jacob/DSA/DSA学习计划.md` is now aligned with Weiss chapter order. See [[dsa-learning-plan]] for the phase→chapter mapping.

### Preprocessing Command (for reference)

The text file was generated with:
```bash
pdftotext -layout DataStructuresAndAlgorithmsInC++.pdf DSAA_Weiss.text
```
If the text file ever needs regeneration, install `poppler-utils` and re-run this command.
