\# Doubly Linked List – Selection Sort \& Performance Comparison



A C++ project implementing a \*\*doubly linked list\*\*, basic list operations, and Selection Sort. The project also compares the execution time of sorting 50,000 integers using a doubly linked list and a static array.



\---



\## 📌 Features



\- \*\*Load data from file\*\* – Read integers from `lista.txt` and store them in a doubly linked list.

\- \*\*Print list\*\* – Display all elements stored in the list.

\- \*\*Find maximum\*\* – Find the node containing the highest value.

\- \*\*Sort list\*\* – Sort the doubly linked list in descending order using Selection Sort.

\- \*\*Performance comparison\*\* – Compare sorting execution times for a doubly linked list and an array containing 50,000 random integers.

\- \*\*Memory management\*\* – Allocate, disconnect, and free dynamically allocated nodes.



\---



\## 🛠️ Technologies



\- C++

\- Standard Library

\- `<iostream>` – Input and output operations.

\- `<fstream>` – File handling.

\- `<cstdlib>` – Random number generation.

\- `<ctime>` – Random number generator initialization.

\- `<chrono>` – Measuring sorting execution time.



\---



\## 🔗 Data Structure



The project uses a doubly linked list.



```cpp

struct lista

{

&#x20;   int liczba;

&#x20;   struct lista \*next, \*prev;

};

```



Each node contains:

\- `liczba` – Integer stored in the node.

\- `next` – Pointer to the next node.

\- `prev` – Pointer to the previous node.



\*\*Example:\*\*



```text

nullptr <- \[5] <-> \[2] <-> \[8] <-> \[1] -> nullptr

```



\---



\## ⚙️ Sorting Algorithm



The project uses \*\*Selection Sort\*\* to sort both data structures in descending order.



\### How it works



1\. Find the highest value in the unsorted collection.

2\. Move that value to the end of the sorted section.

3\. Repeat until all elements are sorted.



\### Doubly Linked List



Instead of swapping values, the algorithm:

\- Finds the node containing the highest value.

\- Disconnects it from the original list.

\- Appends it to a new sorted list.

\- Repeats until the original list is empty.



Existing nodes are reused, so no additional nodes are allocated during sorting.



\### Array



The array implementation:

\- Searches for the highest remaining value.

\- Swaps it with the first element of the unsorted section.

\- Repeats until the entire array is sorted.



\---



\## ⏱️ Performance Comparison



The program includes a benchmark comparing both implementations.



\*\*Benchmark configuration:\*\*



| Parameter | Value |

|---|---|

| Number of elements | 50,000 |

| Generated values | 0–999,999 |

| Sorting algorithm | Selection Sort |

| Sorting order | Descending |

| Time unit | Milliseconds |

| Timing library | `<chrono>` |



Both data structures receive exactly the same randomly generated values.



The benchmark measures only the sorting operations. Data generation and linked list allocation happen before the timers start.



\### Time Complexity



| Operation | Doubly Linked List | Array |

|---|---|---|

| Find maximum | O(n) | O(n) |

| Selection Sort | O(n²) | O(n²) |

| Additional sorting space | O(1) | O(1) |



\### Benchmark Results



Results depend on the hardware, compiler, optimization settings and operating system.



| Data Structure | Execution Time |

|---|---|

| Doubly Linked List | To be measured |

| Array | To be measured |



\---



\## 📂 Project Structure



```text

Project/

│

├── main.cpp

├── lista.txt

└── README.md

```



\- `main.cpp` – Main program containing all functions and the menu.

\- `lista.txt` – Input file containing integers to load into the linked list.

\- `README.md` – Project documentation.



\---



\## 🚀 How to Run



1\. Clone or download this repository.

2\. Make sure you have a C++ compiler installed.

3\. Place `lista.txt` in the program's working directory.

4\. Compile the program:



```bash

g++ main.cpp -o main -std=c++17

```



5\. Run the executable:



```bash

./main

```



\---



\## 📋 Program Menu



```text

=== MENU ===

1\. Load data from file

2\. Print list values

3\. Find the highest value

4\. Sort list

5\. Compare sorting time (50k values)

6\. Exit

```



\---



\## 🎯 Project Goals



The main purpose of this project is to:



\- Understand how doubly linked lists work.

\- Practice pointer manipulation and dynamic memory allocation.

\- Implement Selection Sort on different data structures.

\- Learn how to measure algorithm execution time using `<chrono>`.

\- Compare the practical performance of arrays and linked lists.



\---



\*\*Language:\*\* C++  

\*\*Sorting Algorithm:\*\* Selection Sort  

\*\*Data Structure:\*\* Doubly Linked List \& Static Array

