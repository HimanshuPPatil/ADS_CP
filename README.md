# ADS_CP

This project is a C program that implements an Interval Tree data structure for managing events with time intervals. The program provides a menu-driven interface for various operations:

Insert Event: Allows users to add events with descriptions and time intervals, checking for conflicts with existing events.

Explain Events at Time: Given a specific time, the program explains the events that occur at that time, including delivering scheduled notifications.

Delete Event by ID: Enables the removal of events by their unique IDs.

Display Intervals (In-order): Lists the events in the Interval Tree in in-order traversal, displaying their descriptions and time intervals.

Schedule Notification for Event: Allows users to set notification details (time, method, recipient) for a specific event.

The program maintains the Interval Tree to efficiently manage and query events. It also performs conflict checks during insertion to ensure that overlapping events are not added. The code is organized into functions for various tree operations, including rotations and balancing.

The project is suitable for managing events with time intervals, scheduling notifications, and quickly retrieving events relevant to a specific time. It provides a practical example of how to implement an Interval Tree and offers a basic command-line interface for user interaction
