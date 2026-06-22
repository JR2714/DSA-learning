---
name: executable-output-location
description: "Compiled executables are stored in ./bin, gitignored"
metadata: 
  node_type: memory
  type: reference
  originSessionId: a89a0388-247e-4c65-aa6a-fa021546d0f6
---

Compiled C++ executables are stored in `./bin/` under the project root (`/home/jacob/DSA/bin/`).

**Compile convention:**
```bash
g++ -std=c++17 -Wall -Wextra -fsanitize=address -g source.cpp -o bin/output_name
```

The `bin/` directory is listed in `.gitignore`, so executables will never be tracked by git.

**Why:** Keeps the project root clean and separates source from build artifacts.
