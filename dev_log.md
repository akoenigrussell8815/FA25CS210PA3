# Developer Log - Programming Assignment 3

## Entry 1
**What I tried**
    I tried implementing my recursive function that traverses the graph.

**What I broke**
    It wasn't exactly something that I broke, but I kept receiving an error code that my program was trying to access non-dedicated memory or that the code was failing to access something.
    Initially I Thought this was because when traversing the graph my out-of-bounds case was wrong.
![img.png](img.png)

**Why it happened**
    However, the issue turned out to be that I was checked if nodes were visited, but not setting them to visited once I traversed.

**Fix**
    Luckily this was a simple fix in which I added one line of code.
```C++
visited[r+dr[i]][c+dc[i]] = true;
```

**Proof it works**
    My output runs exactly as it should as described by the "OURPUTguide" AKA OUTPUTguide
![img_1.png](img_1.png)

