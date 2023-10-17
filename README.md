# ADS_CP
It contains code of Event scheduling by using AVL Tree


This project is a calendar scheduling system implemented in C using an AVL tree data structure to efficiently manage events and check for conflicts. Here's an overview of the project's components and functionality:

Structures and Data Representation:

The project uses two main data structures: Event to represent an event with a start and end time, and AVLTreeNode to represent a node in the AVL tree with associated event data.
AVL Tree Implementation:

The AVL tree is a self-balancing binary search tree where each node represents an event. Events are inserted and deleted in a way that maintains the balance of the tree.
Functionality:

Adding Events (1): Users can add events by providing a description, start time, and end time. The system assigns a unique event ID and checks for conflicts with existing events using the AVL tree.

Listing Events (2): The system displays all events in the calendar using in-order traversal of the AVL tree.

Checking for Conflicts (3): Users can input a time slot (start and end times) to check for conflicts with existing events in the calendar.

Deleting Events (4): Users can delete events by specifying their event ID. The system updates the AVL tree and removes the event while maintaining balance.

Exiting the Program (5): Allows the user to exit the program and free allocated memory.

Conflict Detection:

The AVL tree efficiently handles conflict detection by comparing the start and end times of events to identify overlapping time intervals.
User Interaction:

The program provides a simple text-based interface for users to interact with the calendar system, guiding them through options to manage events effectively.
Overall, this project offers a basic calendar management system utilizing an AVL tree to efficiently organize and handle events, making it easy for users to schedule, view, and manage their events while avoiding conflicts in time slots.
