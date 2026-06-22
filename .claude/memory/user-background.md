---
name: user-background
description: "Jacob's programming background, learning context for DSA, and available resources"
metadata: 
  node_type: memory
  type: user
  originSessionId: 4e91eb79-44a5-45f9-9c0c-efc8a268fb7d
---

Jacob is learning Data Structures and Algorithms using C++. Background:
- Took a C++ Programming course 3 years ago, but has forgotten much of it
- Recently completed basic Python syntax learning
- Has MATLAB programming experience from 1 year ago
- Current learning progress: see [[learning-progress]]

Textbook: Mark Allen Weiss, Data Structures and Algorithm Analysis in C++ (4th edition)
- PDF: `/home/jacob/DSA/DataStructuresAndAlgorithmsInC++.pdf`
- Text (preprocessed, primary reference): `/home/jacob/DSA/DSAA_Weiss.text` (31,164 lines)
- Website with source code: https://users.cs.fiu.edu/~weiss/
- Page numbers: Use printed page number (bottom-left of page), not PDF absolute page
- Chapter→line mapping: see [[weiss-textbook-resources]]

**Teaching preferences:**
- Role: Teacher — teach, don't modify student's code
- Cycle: Teach concept → Assign exercises → Jacob writes code → I review → Jacob fixes → repeat
- Pacing: ~2-3 sessions per Phase, each session 15-20 min teaching + 1-3 exercises
- Exercise mix: Theory (analysis questions) and programming tasks balanced
- Weiss citations: Use §X.Y.Z + printed page number; quote original text for definitions, explain in own words otherwise
- Review standards: syntax, edge cases, style, efficiency, stability (see [[code-review-standards]])

**Environment:**
- Working directory: /home/jacob/DSA
- Compiler: g++ with `-std=c++17 -Wall -Wextra -fsanitize=address -g`
- Executable output: `./bin/` (gitignored)
- Editor: VS Code
- memory_error_test.cpp was NOT written by Jacob — don't assume knowledge from it

DSA Learning Plan: see [[dsa-learning-plan]]
Teaching Methodology: see [[user-preference-hands-on]]
