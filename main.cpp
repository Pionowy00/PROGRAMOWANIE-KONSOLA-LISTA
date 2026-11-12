
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <chrono>

using namespace std;
using namespace chrono;

// Maximum number of elements used for sorting time comparison
#define SIZE 50000

// Structure representing a node of a doubly linked list
struct lista
{
    int liczba;                 // Value stored in the node
    struct lista *next, *prev;  // Pointers to the next and previous nodes
};

// LOAD DATA FROM FILE
void load_data(lista *&l, string filename)
{
    ifstream file(filename);    // Open the file for reading
    int x;

    // Check whether the file was opened successfully
    if (!file.is_open())
    {
        cout << "Cannot open file.\n";
        return;
    }

    // Read integers from the file until there is no more data
    while (file >> x)
    {
        // Create a new node containing the read value
        // Both pointers are initially set to nullptr
        lista *new_list = new lista{x, nullptr, nullptr};

        // If the list is empty, the new node becomes its first element
        if (l == nullptr)
        {
            l = new_list;
        }
        else
        {
            // Find the last node in the list
            lista *temp = l;

            while (temp->next != nullptr)
            {
                temp = temp->next;
            }

            // Connect the new node to the end of the list
            temp->next = new_list;
            new_list->prev = temp;
        }
    }

    // Close the file after reading all values
    file.close();

    cout << "Data loaded successfully from " << filename << ".\n";
}

// DELETE NODE WITHOUT FREEING ITS MEMORY
void delete_node(lista *&l, lista *node)
{
    // Do nothing if the provided node does not exist
    if (node == nullptr)
        return;

    // If the node is not the first element,
    // connect its previous node to its next node
    if (node->prev != nullptr)
        node->prev->next = node->next;
    else
        // If the node is the first element, update the list head
        l = node->next;

    // If the node is not the last element,
    // connect its next node to its previous node
    if (node->next != nullptr)
        node->next->prev = node->prev;

    // Disconnect the removed node from the list
    // Its memory is preserved so it can be reused elsewhere
    node->next = nullptr;
    node->prev = nullptr;
}

// SORT DOUBLY LINKED LIST USING SELECTION SORT
// Sorts the list in descending order (highest to lowest)
void insert_sort(lista *&l)
{
    lista *new_list = nullptr;   // Head of the new sorted list
    lista *tail = nullptr;      // Last node of the new sorted list

    // Continue until all nodes have been moved to the new list
    while (l != nullptr)
    {
        lista *temp = l;         // Pointer used to traverse the original list
        lista *highest = l;      // Pointer to the node containing the highest value

        // Find the node containing the highest value
        while (temp != nullptr)
        {
            if (temp->liczba > highest->liczba)
            {
                highest = temp;
            }

            temp = temp->next;
        }

        // Remove the highest node from the original list
        // The node is disconnected but its memory is not freed
        delete_node(l, highest);

        // Insert the extracted node at the end of the new list
        if (new_list == nullptr)
        {
            // If the new list is empty, the node becomes its first element
            new_list = highest;
        }
        else
        {
            // Connect the last node with the extracted node
            tail->next = highest;
            highest->prev = tail;
        }

        // Update the tail pointer to the newly inserted last node
        tail = highest;
    }

    // Replace the original list with the sorted list
    l = new_list;
}

// FIND THE HIGHEST VALUE IN THE LIST
lista* find_max(lista *l)
{
    // Return nullptr if the list is empty
    if (l == nullptr)
        return nullptr;

    lista *temp = l;            // Pointer used to traverse the list
    lista *highest = l;         // Pointer to the node with the highest value

    // Traverse the entire list to find the highest value
    while (temp != nullptr)
    {
        if (highest->liczba < temp->liczba)
        {
            highest = temp;
        }

        temp = temp->next;
    }

    // Return the address of the node containing the highest value
    return highest;
}

// PRINT ALL VALUES IN THE LIST
void print_values(lista *l)
{
    // Check whether the list is empty
    if (l == nullptr)
    {
        cout << "The list is empty.\n";
        return;
    }

    cout << "--- Current List ---\n";

    lista *temp = l;

    // Traverse the list and print every node's value
    while (temp != nullptr)
    {
        cout << temp->liczba << endl;
        temp = temp->next;
    }

    cout << "--------------------\n";
}

// FREE MEMORY ALLOCATED FOR THE LIST
void free_memory(lista *&l)
{
    // Delete nodes one by one until the list is empty
    while (l != nullptr)
    {
        lista *temp = l;    // Save the address of the current node

        l = l->next;        // Move the head to the next node

        delete temp;        // Release memory occupied by the previous head
    }
}

// SELECTION SORT ON AN ARRAY
// Sorts the array in descending order
void array_sort(int t[], int n)
{
    // Each iteration selects the highest value
    // from the remaining unsorted part of the array
    for (int i = 0; i < n; i++)
    {
        int highest = i;    // Index of the highest value found so far

        // Search for the highest value in the remaining elements
        for (int j = i + 1; j < n; j++)
        {
            if (t[j] > t[highest])
            {
                highest = j;
            }
        }

        // Swap the highest value with the first element
        // of the unsorted part of the array
        int temp = t[i];
        t[i] = t[highest];
        t[highest] = temp;
    }
}

// COMPARE SORTING EXECUTION TIMES
void compare_sorting_time()
{
    int t[SIZE];                    // Array containing 50,000 integers

    lista *test_list = nullptr;     // Head of the test linked list
    lista *tail = nullptr;          // Last node of the test linked list

    // GENERATE RANDOM DATA
    // Both the array and linked list receive identical values
    for (int i = 0; i < SIZE; i++)
    {
        // Generate a random integer between 0 and 999999
        t[i] = rand() % 1000000;

        // Create a new linked list node containing the same value
        // Its prev pointer is initialized to the current tail
        lista *new_node = new lista{t[i], nullptr, tail};

        // If the list is empty, the new node becomes its head
        if (test_list == nullptr)
        {
            test_list = new_node;
        }
        else
        {
            // Connect the previous last node with the new node
            tail->next = new_node;
        }

        // Update the tail pointer
        tail = new_node;
    }

    // MEASURE LINKED LIST SORTING TIME

    // Save the starting time before sorting
    auto start_list = high_resolution_clock::now();

    // Sort the linked list using selection sort
    insert_sort(test_list);

    // Save the ending time after sorting
    auto end_list = high_resolution_clock::now();

    // Calculate the execution time in milliseconds
    duration<double, milli> list_time = end_list - start_list;


    // MEASURE ARRAY SORTING TIME

    // Save the starting time before sorting
    auto start_array = high_resolution_clock::now();

    // Sort the array using selection sort
    array_sort(t, SIZE);

    // Save the ending time after sorting
    auto end_array = high_resolution_clock::now();

    // Calculate the execution time in milliseconds
    duration<double, milli> array_time = end_array - start_array;


    // DISPLAY COMPARISON RESULTS
    cout << "\n===== SORTING TIME COMPARISON =====\n";

    cout << "Number of elements: " << SIZE << endl;

    cout << "Doubly linked list: "
         << list_time.count() << " ms\n";

    cout << "Array: "
         << array_time.count() << " ms\n";

    cout << "===================================\n";

    // Release memory allocated for the test linked list
    free_memory(test_list);
}

// MAIN PROGRAM
int main()
{
    lista *l = nullptr;     // Initialize an empty linked list
    int choice;             // Variable storing the user's menu choice

    // Initialize the random number generator using the current time
    // This makes generated numbers different between program executions
    srand(time(nullptr));

    // Display the menu repeatedly until the user chooses to exit
    do
    {
        cout << "\n=== MENU ===\n";
        cout << "1. Load data from file\n";
        cout << "2. Print list values\n";
        cout << "3. Find the highest value\n";
        cout << "4. Sort list\n";
        cout << "5. Compare sorting time (50k values)\n";
        cout << "6. Exit\n";

        cout << "Your choice: ";
        cin >> choice;

        // Execute the operation corresponding to the selected option
        switch (choice)
        {
            case 1:
            {
                // Load integers from lista.txt into the linked list
                load_data(l, "lista.txt");
                break;
            }

            case 2:
            {
                // Display all values stored in the linked list
                print_values(l);
                break;
            }

            case 3:
            {
                // Find the node containing the highest value
                lista *x = find_max(l);

                // Display the highest value if the list is not empty
                if (x != nullptr)
                    cout << "Highest value in lista: "
                         << x->liczba << endl;
                else
                    cout << "The list is empty.\n";

                break;
            }

            case 4:
            {
                // Sort the linked list in descending order
                insert_sort(l);

                cout << "List sorted successfully.\n";
                break;
            }

            case 5:
            {
                // Generate 50,000 random values and compare
                // sorting execution times for the list and array
                cout << "Starting performance comparison...\n";

                compare_sorting_time();
                break;
            }

            case 6:
            {
                // Free all allocated memory before exiting
                cout << "Exiting program and freeing memory...\n";

                free_memory(l);
                break;
            }

            default:
            {
                // Handle invalid menu selections
                cout << "Wrong value inserted. Please try again.\n";
                break;
            }
        }

    } while (choice != 6);

    return 0;   // End the program successfully
}
