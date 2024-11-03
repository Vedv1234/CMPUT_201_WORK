/*
Author: Ved Vyas
Co-Author / Exercise provided by: University of Alberta CMPUT 201 Course Team & Instructors (2023)
Functionality of code: This is my implementation of a graph data structure using linked lists. 
I've created this code to handle various graph operations like adding/removing nodes and edges, 
checking if paths exist, and calculating path weights. It's pretty cool how I've used 
linked lists to represent both the nodes and their edges - it makes the whole thing really 
flexible for adding and removing elements. The main function acts like a command processor, 
taking different commands to manipulate the graph structure I built.
*/

#include <stdio.h>
#include <stdlib.h>

// In my edge structure, I'm storing all the information I need about connections between nodes
typedef struct Edge {
    int dest;     // I'm keeping track of where this edge points to (destination node ID)
    int weight;   // Each of my edges has a weight - useful for path calculations
    struct Edge* next;  // I'm using this to link to the next edge - creates a linked list of edges
} Edge;

// This is my node structure - it's the backbone of my graph
typedef struct Node {
    int id;       // Each node gets its own unique ID
    Edge* edges;  // I'm storing all edges coming out of this node
    struct Node* next;  // This lets me link to the next node in my graph
} Node;

// I'm starting with an empty graph - this pointer will be my entry point to the whole structure
Node* graph = NULL;

// I wrote this helper function to find nodes quickly
Node* findNode(int id) {
    Node* current = graph;  // Starting at the beginning of my graph
    while (current != NULL) {  // I'll keep looking until I hit the end
        if (current->id == id) return current;  // Found it! Returning the node
        current = current->next;  // Moving to the next node in my list
    }
    return NULL;  // If I got here, I didn't find the node
}

// This helper function lets me find specific edges between nodes
Edge* findEdge(Node* source, int dest_id) {
    Edge* current = source->edges;  // Starting with the first edge
    while (current != NULL) {  // Checking all edges
        if (current->dest == dest_id) return current;  // Found the edge I want
        current = current->next;  // Moving to the next edge
    }
    return NULL;  // No matching edge found
}

// Quick check to see if a node exists
int nodeExists(int id) {
    return findNode(id) != NULL;  // Using my findNode function to do the heavy lifting
}

// Checking if there's an edge between two nodes
int edgeExists(int source_id, int dest_id) {
    Node* source = findNode(source_id);  // First finding the starting node
    if (!source) return 0;  // Can't have an edge if the source node doesn't exist
    return findEdge(source, dest_id) != NULL;  // Looking for the edge
}

// This is where I add new nodes to my graph
int insertNode(int id) {
    if (nodeExists(id)) return 0;  // No duplicates allowed in my graph
    
    Node* newNode = (Node*)malloc(sizeof(Node));  // Making space for my new node
    if (!newNode) return 0;  // Making sure memory allocation worked
    
    // Setting up my new node
    newNode->id = id;
    newNode->edges = NULL;  // Starting with no edges
    newNode->next = graph;  // Putting the new node at the start of my list
    graph = newNode;
    return 1;  // Success!
}

// Adding edges between nodes
int insertEdge(int source_id, int dest_id, int weight) {
    if (source_id == dest_id) return 0;  // I don't allow self-loops in my graph
    
    Node* source = findNode(source_id);
    if (!source || !nodeExists(dest_id)) return 0;  // Both nodes need to exist
    
    Edge* existingEdge = findEdge(source, dest_id);
    if (existingEdge) {  // If the edge exists, I just update the weight
        existingEdge->weight = weight;
        return 1;
    }
    
    // Creating a new edge
    Edge* newEdge = (Edge*)malloc(sizeof(Edge));
    if (!newEdge) return 0;  // Memory check
    
    // Setting up my new edge
    newEdge->dest = dest_id;
    newEdge->weight = weight;
    newEdge->next = source->edges;
    source->edges = newEdge;
    return 1;
}

// Removing edges from my graph
int removeEdge(int source_id, int dest_id) {
    Node* source = findNode(source_id);
    if (!source) return 0;
    
    Edge* current = source->edges;
    Edge* prev = NULL;
    
    while (current != NULL) {
        if (current->dest == dest_id) {  // Found the edge I want to remove
            if (prev) prev->next = current->next;  // Bypassing the edge in my list
            else source->edges = current->next;  // Special case for first edge
            free(current);  // Cleaning up memory
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

// Helper function to clean up all edges from a node
void freeEdges(Edge* edge) {
    while (edge != NULL) {
        Edge* temp = edge;
        edge = edge->next;
        free(temp);  // Making sure I don't leave any memory leaks
    }
}

// Removing nodes from my graph
int removeNode(int id) {
    Node* current = graph;
    Node* prev = NULL;
    
    while (current != NULL) {
        if (current->id == id) {  // Found the node to remove
            // Updating my linked list
            if (prev) prev->next = current->next;
            else graph = current->next;
            
            // Cleaning up all edges from this node
            freeEdges(current->edges);
            free(current);
            
            // I also need to remove any edges pointing to this node
            Node* node = graph;
            while (node != NULL) {
                removeEdge(node->id, id);
                node = node->next;
            }
            return 1;
        }
        prev = current;
        current = current->next;
    }
    return 0;
}

// This function calculates the total weight of a path through my graph
int path(int source_id) {
    int total_weight = 0;
    int current_id = source_id;
    int next_id;
    
    while (scanf("%d", &next_id) == 1) {  // Reading the path one node at a time
        Node* current = findNode(current_id);
        if (!current) return -1;  // Path isn't valid if a node doesn't exist
        
        Edge* edge = findEdge(current, next_id);
        if (!edge) return -1;  // Path isn't valid if an edge doesn't exist
        
        total_weight += edge->weight;  // Adding up the weights as I go
        current_id = next_id;
    }
    
    return total_weight;
}

// Initialize my graph
void start() {
    graph = NULL;  // Starting fresh with an empty graph
}

// Clean up all my graph memory
void end() {
    Node* current = graph;
    while (current != NULL) {
        Node* temp = current;
        freeEdges(current->edges);  // First cleaning up all edges
        current = current->next;
        free(temp);  // Then removing the node
    }
    graph = NULL;
}

// Main function - this was provided by the course team
int main(int argc, char **argv) {
    start();
    
    // Input loop for processing commands
    int result;
    while (1) {
        char command;
        scanf("%c", &command);

        if (command == 't') {
            break;  // Time to end the program
        }
        else if (command == 'n') {
            int id;
            scanf("%d", &id);
            result = nodeExists(id);
            printf("%d\n", result);
        }
        else if (command == 'e') {
            int source_id, dest_id;
            scanf("%d %d", &source_id, &dest_id);
            result = edgeExists(source_id, dest_id);
            printf("%d\n", result);
        }
        else if (command == 'i') {
            int id;
            scanf("%d", &id);
            result = insertNode(id);
            printf("%d\n", result);
        }
        else if (command == 'l') {
            int source_id, dest_id, weight;
            scanf("%d %d %d", &source_id, &dest_id, &weight);
            result = insertEdge(source_id, dest_id, weight);
            printf("%d\n", result);
        }
        else if (command == 'd') {
            int id;
            scanf("%d", &id);
            result = removeNode(id);
            printf("%d\n", result);
        }
        else if (command == 'r') {
            int source_id, dest_id;
            scanf("%d %d", &source_id, &dest_id);
            result = removeEdge(source_id, dest_id);
            printf("%d\n", result);
        }
        else if (command == 'p') {
            int source_id;
            scanf("%d", &source_id);
            result = path(source_id);
            printf("%d\n", result);
        }
    }

    end();
    return 0;
}