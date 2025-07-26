# 🧵 Multithreaded Matrix Multiplication (Updated) in C and Java

This guide explains how to perform multithreaded matrix multiplication using **Pthreads in C** and **Java Threads**, utilizing **WSL2** on Windows with updated matrices.

---

## 🖥️ System Environment

- **OS**: Windows 11 Pro (Version 24H2)
- **Linux**: Ubuntu 24.04.2 LTS via WSL2
- **C Compiler**: GCC 13.4
- **Java Compiler**: OpenJDK 21.0.4
- **Text Editor**: `nano`
- **IDE**: Visual Studio Code (v1.101)

---

## 🎯 Objective

- Implement matrix multiplication with multithreading using C (Pthreads) and Java (Thread class).
- Assign one thread per matrix row for concurrent computation.
- Explore differences in thread handling between both languages.

---

## 📂 Assumptions

- Matrices are 3×3 (square).
- Each thread calculates one row of the resulting matrix.
- Matrix values are hardcoded in the programs.
- No execption handling is implemented
- Thread synchronization is not required beyond joining

---

## ⚙️ Step 1: Environment Setup (via WSL2)

Follow WSL2 setup steps as shown in [Microsoft Docs](https://learn.microsoft.com/en-us/windows/wsl/install) or your prior setup:

```bash
sudo apt update && sudo apt upgrade
sudo apt install build-essential gcc openjdk-24-jdk
```

---

## 🧾 Step 2: C Implementation

1. **Create File**
```bash
nano pthreads.c
```

2. **Paste Code**
```c
#include <stdio.h>
#include <pthread.h>

#define SIZE 3

int A[SIZE][SIZE] = {
    {1, 2, 3},
    {4, 5, 6},
    {7, 8, 9}
};

int B[SIZE][SIZE] = {
    {9, 8, 7},
    {6, 5, 4},
    {3, 2, 1}
};

int C[SIZE][SIZE]; // Result matrix

void* multiplyRow(void* arg) {
    int row = *(int*)arg;
    for (int col = 0; col < SIZE; col++) {
        C[row][col] = 0;
        for (int k = 0; k < SIZE; k++) {
            C[row][col] += A[row][k] * B[k][col];
        }
    }
    return NULL;
}

int main() {
    pthread_t threads[SIZE];
    int row_indices[SIZE];

    for (int i = 0; i < SIZE; i++) {
        row_indices[i] = i;
        pthread_create(&threads[i], NULL, multiplyRow, &row_indices[i]);
    }

    for (int i = 0; i < SIZE; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("Resultant Matrix C = A x B:\\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf("%4d", C[i][j]);
        }
        printf("\\n");
    }

    return 0;
}
```

3. **Compile and Run**
```bash
gcc pthreads.c -o pthreads -lpthread
./pthreads
```

---

## ☕ Step 3: Java Implementation

1. **Create File**
```bash
nano MatrixMultiply.java
```

2. **Paste Code**
```java
class MatrixMultiply {

    static final int SIZE = 3;
    static int[][] A = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    static int[][] B = {
        {9, 8, 7},
        {6, 5, 4},
        {3, 2, 1}
    };

    static int[][] C = new int[SIZE][SIZE]; // Result

    static class Worker extends Thread {
        int row;

        Worker(int row) {
            this.row = row;
        }

        public void run() {
            for (int col = 0; col < SIZE; col++) {
                C[row][col] = 0;
                for (int k = 0; k < SIZE; k++) {
                    C[row][col] += A[row][k] * B[k][col];
                }
            }
        }
    }

    public static void main(String[] args) throws InterruptedException {
        Thread[] threads = new Thread[SIZE];

        for (int i = 0; i < SIZE; i++) {
            threads[i] = new Worker(i);
            threads[i].start();
        }

        for (int i = 0; i < SIZE; i++) {
            threads[i].join();
        }

        System.out.println("Resultant Matrix C = A x B:");
        for (int i = 0; i < SIZE; i++) {
            for (int j = 0; j < SIZE; j++) {
                System.out.printf("%4d", C[i][j]);
            }
            System.out.println();
        }
    }
}
```

3. **Compile and Run**
```bash
javac MatrixMultiply.java
java MatrixMultiply
```

---
- Also Java thread code can compile and run using VS Code save as main class name.java.

## 🧪 Output Example

Expected output for the given matrices:

```
 30  24  18
 84  69  54
138 114  90
```

---

## 🔍 Pthreads vs Java Threads

| Feature           | Pthreads (C)        | Java Threads       |
|------------------|---------------------|--------------------|
| Style            | Procedural          | Object-Oriented    |
| Creation         | `pthread_create()`  | `new Thread().start()` |
| Join             | `pthread_join()`    | `thread.join()`    |
| Complexity       | More boilerplate    | Simpler            |
| Portability      | Platform-dependent  | Platform-independent |
| Ease of Use      | Requires linking    | Native support     |

---

## 📁 Directory Structure

```
.
├── pthreads.c
├── MatrixMultiply.java
└── README.md
```

---

## 📌 Notes

- Files can be accessed at:
  ```
  \\\\wsl$\\Ubuntu\\home\\<username>\\
  ```

---

## 🔗 References


- GeeksforGeeks (2018). Multithreading in Operating System. [online] GeeksforGeeks. Available at: https://www.geeksforgeeks.org/operating-systems/multithreading-in-operating-system/. 
- GeeksforGeeks (2016). Multithreading in Java. [online] GeeksforGeeks. Available at: https://www.geeksforgeeks.org/java/multithreading-in-java/  [Accessed 26 Jul. 2025].
- HowDev. (2015). What are pthreads in C/C++? [online] Available at: https://how.dev/answers/what-are-pthreads-in-c-cpp  [Accessed 26 Jul. 2025]. 
- Silberschatz, A., Galvin, P.B. and Gagne, G. (n.d.). Operating System Concepts

---

## ✅ Conclusion

This lab solidified the understanding of **parallelism** using **threads in C and Java**, managing task execution with one thread per matrix row. WSL2 helped simulate a full Linux OS for coding, compiling, and testing efficiently inside Windows.# Markdown syntax guide
