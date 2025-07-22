#include<stdio.h>
#include<stdlib.h>

// Define the Node structure globally using typedef
typedef struct Node 
{
    int data;
    struct Node* next; //a pointer ti the next node in the sequence
} Node; //'typedef' allows 'Node' to be used as a shorthand or struct Node

void insertAtEnd(Node** head_ref, int new_data)
{
    Node* new_node = (Node*)malloc(sizeof(Node)); //dynamic moemoryy allocation
    if(new_node == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(EXIT_FAILURE); //command to exit program
    }
    new_node->data = new_data;
    new_node->next = NULL; 
    
    // If the linked list at that index is empty, new_node becomes the head
    if(*head_ref == NULL)
    {
        *head_ref = new_node;
        return; 
    }
    
    // Traverse to the last node
    Node* last = *head_ref; //inilizalizes a temporary pointer to the head of the linked list
    while(last->next != NULL)
    {
        last = last->next;
    }
    // Change the next of the last node pointing to the new node
    last->next = new_node; 
}

// Standard main function signature
int main()
{
    int shl,q; // Number of shelves (linked lists in the array); and number of queries
    // Removed the '\n' from scanf format string for cleaner input handling
    if(scanf("%d", &shl) != 1) return 0;
    if(scanf("%d", &q) != 1) return 0;// using if together with scanf to check for numbers only
    
    // VLA(variable length array) declaration: Array of pointers to Node, size 'shl'
    Node* Darray[shl]; 

    // Initialize array heads to NULL
    for(int i = 0; i < shl; i++)
    {
        Darray[i] = NULL;
    }
    
    // Process queries
    for (int j = 0; j < q; j++)
    {
        int qtype, x, y;
        // Read query type
        if(scanf("%d", &qtype) != 1) break;//checking for number in same line
        if(qtype == 1)
        {
            // Type 1: Insert (y pages into x shelf)
            // Read x (shelf index) and y (data/pages)
            if(scanf("%d %d", &x, &y) != 2) break;
            
            // Basic validation for x (shelf index)
            if (x >= 0 && x < shl) {
                // Insert y data into the linked list at Darray[x]
                insertAtEnd(&Darray[x], y); 
            } else {
                // Handle invalid shelf index if necessary
            }
        }
        else if(qtype == 2)
        {
            // Type 2: Retrieve (yth book/node data in xth shelf)
            // Read x (shelf index) and y (book index, 0-indexed assumed)
            if(scanf("%d %d", &x, &y) != 2) break;
            
            Node* current = Darray[x];
            int i = 0;

            // Traverse to the y-th node (0-indexed)
            // Error Fix: The original loop was `i <= y`, which moves past the desired node. 
            // We also added a check for NULL to prevent crashes if the index is out of bounds.
            while (i < y && current != NULL/*checks if the list at that index is not comprised of head node only*/)
            {
                current = current->next;
                i++;
            }

            // Print the data if the node was found
            if (current != NULL) {
                printf("%d\n", current->data);
            } else {
                // Handle case where index 'y' is out of bounds for the list at 'x'
                // printf("Error: Index out of bounds\n"); 
            }
        }
        else if(qtype == 3)
        {
            // Type 3: Length of the linked list at shelf x
            if(scanf("%d", &x) != 1) break;

            int n = 0;
            Node* current = Darray[x];

            // Error Fix: The original code used a flawed do-while loop that risked a crash 
            // (segmentation fault) on single-node lists or lists traversed to NULL.
            // A simple while loop correctly traverses and counts.
            while (current != NULL)
            {
                n++;
                current = current->next;
            }
            printf("%d\n", n);
        }
    }
    
    // Note: To fully complete this code and prevent memory leaks, 
    // you should add a free_lists() function as shown in the previous response.
    
    return 0;
}