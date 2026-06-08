# To-Do List Application — C++

A console-based task manager built in C++.

## Features

- Add tasks with title and category
- View all tasks with status
- Mark tasks as completed
- Unmark tasks back to pending
- View pending tasks only
- View completed tasks only
- Delete tasks
- Dynamic categories (add your own)
- Input validation and error handling
- File persistence — tasks saved across sessions

## Concepts Used

- Object-Oriented Programming (Classes, Constructors, Getters)
- Vectors
- File I/O (ofstream, ifstream)
- Input Validation
- Switch/Case Menu
- Loops & Conditionals

## How to Run

**Requirements:** C++ compiler (g++ / MinGW)

```bash
g++ todo.cpp -o todo
./todo        # Linux/Mac
todo.exe      # Windows
```

## Files

| File | Description |
|------|-------------|
| `todo.cpp` | Main source code |
| `tasks.txt` | Auto-generated — stores saved tasks |
| `categories.txt` | Auto-generated — stores custom categories |

## Author

**Samin Jawad**

