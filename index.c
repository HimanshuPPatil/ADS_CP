#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int start;
    int end;
    char description[100];
    int id;
} Event;

int eventIdCounter = 1; 

typedef struct AVLTreeNode {
    int low;
    int high;
    Event event;
    struct AVLTreeNode* left;
    struct AVLTreeNode* right;
    int height; 
} AVLTreeNode;

int height(AVLTreeNode* node) {
    if (node == NULL) return 0;
    return node->height;
}

int max(int a, int b) {
    return (a > b) ? a : b;
}

AVLTreeNode* createNode(Event event) {
    AVLTreeNode* newNode = (AVLTreeNode*)malloc(sizeof(AVLTreeNode));
    newNode->low = event.start;
    newNode->high = event.end;
    newNode->event = event;
    newNode->left = newNode->right = NULL;
    newNode->height = 1;
    return newNode;
}

AVLTreeNode* rightRotate(AVLTreeNode* y) {
    AVLTreeNode* x = y->left;
    AVLTreeNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;

    return x;
}

AVLTreeNode* leftRotate(AVLTreeNode* x) {
    AVLTreeNode* y = x->right;
    AVLTreeNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;

    return y;
}

int getBalance(AVLTreeNode* node) {
    if (node == NULL) return 0;
    return height(node->left) - height(node->right);
}

AVLTreeNode* insertEvent(AVLTreeNode* root, Event event) {
    if (root == NULL) return createNode(event);

    int low = event.start;

    if (low < root->low) root->left = insertEvent(root->left, event);
    else root->right = insertEvent(root->right, event);

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1) {
        if (low < root->left->low) return rightRotate(root);
    }
    if (balance < -1) {
        if (low > root->right->low) return leftRotate(root);
    }

    return root;
}

// Function to check for conflicts in the AVL tree
int hasConflictInAVLTree(AVLTreeNode* root, Event event) {
    if (root == NULL) return 0;

    int low = event.start;
    int high = event.end;

    if (low < root->high && high > root->low) {
        return 1;
    }

    if (low == root->high) {
        return 1;
    }

    if (low < root->low) {
        return hasConflictInAVLTree(root->left, event);
    }

    return hasConflictInAVLTree(root->right, event);
}

// Function to display events in the AVL tree (in-order traversal)
void displayEvents(AVLTreeNode* root) {
    if (root == NULL) return;

    displayEvents(root->left);
    printf("Event %d: %s (Start: %d, End: %d)\n", root->event.id, root->event.description, root->event.start, root->event.end);
    displayEvents(root->right);
}

// Function to delete an event by ID
AVLTreeNode* deleteEventById(AVLTreeNode* root, int id, int* deleted) {
    if (root == NULL) return root;

    if (id < root->event.id) root->left = deleteEventById(root->left, id, deleted);
    else if (id > root->event.id) root->right = deleteEventById(root->right, id, deleted);
    else {
        *deleted = 1;

        if (root->left == NULL) {
            AVLTreeNode* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            AVLTreeNode* temp = root->left;
            free(root);
            return temp;
        }

        AVLTreeNode* temp = root->right;
        while (temp->left != NULL) temp = temp->left;

        root->event = temp->event;
        root->low = temp->low;
        root->high = temp->high;

        root->right = deleteEventById(root->right, temp->event.id, deleted);
    }

    root->height = 1 + max(height(root->left), height(root->right));

    int balance = getBalance(root);

    if (balance > 1) {
        if (getBalance(root->left) >= 0) return rightRotate(root);
    }
    if (balance < -1) {
        if (getBalance(root->right) <= 0) return leftRotate(root);
    }

    return root;
}

int main() {
    AVLTreeNode* root = NULL;

    while (1) {
        printf("\nCalendar Scheduling System\n");
        printf("1. Add Event\n");
        printf("2. List Events\n");
        printf("3. Check for Conflicts\n");
        printf("4. Delete Event\n");
        printf("5. Exit\n");
        printf("Enter your choice: ");

        int choice;
        scanf("%d", &choice);

        switch (choice) {
            case 1: {
                Event newEvent;

                printf("Enter event description: ");
                getchar(); // Consume the newline character
                fgets(newEvent.description, sizeof(newEvent.description), stdin);
                newEvent.description[strcspn(newEvent.description, "\n")] = '\0'; // Remove newline character

                printf("Enter event start time: ");
                scanf("%d", &newEvent.start);
                printf("Enter event end time: ");
                scanf("%d", &newEvent.end);

                if (newEvent.start >= newEvent.end) {
                    printf("Invalid event time. End time must be after start time.\n");
                } else {
                    newEvent.id = eventIdCounter++; // Assign a unique event ID
                    if (hasConflictInAVLTree(root, newEvent)) {
                        printf("Conflict detected. Event not added to the calendar.\n");
                    } else {
                        root = insertEvent(root, newEvent);
                        printf("Event added to the calendar with ID %d.\n", newEvent.id);
                    }
                }
                break;
            }

            case 2:
                printf("Events in the calendar:\n");
                displayEvents(root);
                break;

            case 3: {
                if (root == NULL) {
                    printf("No events in the calendar.\n");
                } else {
                    Event timeSlot;
                    printf("Enter time slot to check for conflicts:\n");
                    printf("Start time: ");
                    scanf("%d", &timeSlot.start);
                    printf("End time: ");
                    scanf("%d", &timeSlot.end);

                    if (hasConflictInAVLTree(root, timeSlot)) {
                        printf("Conflict detected in the specified time slot.\n");
                    } else {
                        printf("No conflicts in the specified time slot.\n");
                    }
                }
                break;
            }

            case 4: {
                int eventIdToDelete;
                printf("Enter the event ID to delete: ");
                scanf("%d", &eventIdToDelete);

                int deleted = 0;
                root = deleteEventById(root, eventIdToDelete, &deleted);
                if (deleted) {
                    printf("Event deleted from the calendar.\n");
                } else {
                    printf("Specified event is not in the calendar.\n");
                }
                break;
            }

            case 5:
                // Free memory
                free(root);
                exit(0);

            default:
                printf("Invalid choice. Please enter a valid option.\n");
        }
    }

    return 0;
}