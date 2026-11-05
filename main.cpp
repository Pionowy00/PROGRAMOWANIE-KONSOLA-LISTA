#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct lista
{
    int id;
    lista *next;
};

// ==========================================
// Function: load_data
// Parameters:
//   l        - reference to a pointer to the first node of the linked list (inout)
//   filename - name of the file containing integers (input)
// Input: A text file containing integers.
// Output: None (void). The linked list is modified in place.
// Purpose: Reads integers line by line or space-separated from a file
//          and appends them as new nodes to the end of the linked list.
// ==========================================
void load_data(lista *&l, string filename)
{
    ifstream file(filename);
    int x;
    while (file >> x)
    {
        lista *new_list = new lista{x, nullptr};
        if (l == nullptr)
        {
            l = new_list;
        }
        else
        {
            lista *temp = l;
            while (temp->next != nullptr)
            {
                temp = temp->next;
            }
            temp->next = new_list;
        }
    }
    file.close();
    cout << "Data loaded successfully from " << filename << ".\n";
}

// ==========================================
// Function: find_value
// Parameters:
//   l  - pointer to the first node of the linked list (input)
//   id - the integer value to search for (input)
// Input: The linked list and the target value.
// Output: Returns the 0-based index of the first occurrence of 'id', or -1 if not found.
// Purpose: Traverses the list to locate a specific value and returns its position.
// ==========================================
int find_value(lista *l, int id)
{
    int index = 0;
    lista *temp = l;
    while (temp != nullptr)
    {
        if (temp->id == id)
        {
            return index;
        }
        temp = temp->next;
        index++;
    }
    return -1; // Not found
}

// ==========================================
// Function: delete_value
// Parameters:
//   l     - reference to a pointer to the first node of the linked list (inout)
//   index - the 0-based index of the node to delete (input)
// Input: The linked list pointer and target index.
// Output: None (void). Modifies the list by removing the node at the specified index.
// Purpose: Safely removes a node at a given index, handling head deletion
//          and updating pointers to prevent memory leaks or broken links.
// ==========================================
void delete_value(lista *&l, int index)
{
    if (l == nullptr)
    {
        cout << "List is empty.\n";
        return;
    }

    lista *temp = l;

    // If deleting the head node
    if (index == 0)
    {
        l = l->next;
        delete temp;
        cout << "Node at index 0 deleted.\n";
        return;
    }

    // Find the node before the one we want to delete
    for (int i = 0; temp != nullptr && i < index - 1; i++)
    {
        temp = temp->next;
    }

    // If index is out of bounds
    if (temp == nullptr || temp->next == nullptr)
    {
        cout << "Index out of range.\n";
        return;
    }

    lista *node_to_delete = temp->next;
    temp->next = node_to_delete->next;
    delete node_to_delete;
    cout << "Node at index " << index << " deleted.\n";
}

// ==========================================
// Function: mirror_list
// Parameters:
//   l - reference to a pointer to the first node of the linked list (inout)
// Input: The linked list.
// Output: None (void). Reverses the pointers of the nodes in place.
// Purpose: Reverses the direction of the linked list so that the last
//          node becomes the new head.
// ==========================================
void mirror_list(lista *&l)
{
    lista *prev = nullptr;
    lista *current = l;
    lista *next = nullptr;

    while (current != nullptr)
    {
        next = current->next; // Store next node
        current->next = prev; // Reverse current node's pointer
        prev = current;       // Move prev one step forward
        current = next;       // Move current one step forward
    }
    l = prev; // Update head pointer to the new first element
    cout << "List has been mirrored/reversed.\n";
}

// ==========================================
// Function: print_values
// Parameters:
//   l - pointer to the first node of the linked list (input)
// Input: The linked list.
// Output: Prints each node's id to the console standard output.
// Purpose: Traverses the linked list sequentially and displays its values.
// ==========================================
void print_values(lista *l)
{
    if (l == nullptr)
    {
        cout << "The list is empty.\n";
        return;
    }
    cout << "--- Current List ---\n";
    lista *temp = l;
    while (temp != nullptr)
    {
        cout << temp->id << endl;
        temp = temp->next;
    }
    cout << "--------------------\n";
}

// ==========================================
// Function: free_memory
// Parameters:
//   l - reference to a pointer to the first node of the linked list (inout)
// Input: The linked list allocated in dynamic memory.
// Output: None (void).
// Purpose: Iterates through the list and safely deletes all nodes to
//          prevent memory leaks before program termination.
// ==========================================
void free_memory(lista *&l)
{
    while (l != nullptr)
    {
        lista *temp = l;
        l = l->next;
        delete temp;
    }
}

// ==========================================
// Function: main
// Parameters: None
// Input: User menu choices and data via console or files.
// Output: Execution status code (int).
// Purpose: Serves as the entry point of the program, driving an interactive
//          menu loop that allows the user to perform various linked list operations.
// ==========================================
int main()
{
    lista *l = nullptr;
    int choice;

    do
    {
        cout << "\n=== MENU ===\n";
        cout << "1. Load data from file\n";
        cout << "2. Print list values\n";
        cout << "3. Find value\n";
        cout << "4. Delete node by index\n";
        cout << "5. Mirror (reverse) list\n";
        cout << "6. Exit\n";
        cout << "Your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
            {
                load_data(l, "lista.txt");
                break;
            }
            case 2:
            {
                print_values(l);
                break;
            }
            case 3:
            {
                int val;
                cout << "Enter value to find: ";
                cin >> val;
                int idx = find_value(l, val);
                if (idx != -1)
                    cout << "Value found at index: " << idx << endl;
                else
                    cout << "Value not found in the list.\n";
                break;
            }
            case 4:
            {
                int idx;
                cout << "Enter index to delete: ";
                cin >> idx;
                delete_value(l, idx);
                break;
            }
            case 5:
            {
                mirror_list(l);
                break;
            }
            case 6:
            {
                cout << "Exiting program and freeing memory...\n";
                free_memory(l);
                break;
            }
            default:
            {
                cout << "Wrong value inserted. Please try again.\n";
                break;
            }
        }
    } while (choice != 6);

    return 0;
}
