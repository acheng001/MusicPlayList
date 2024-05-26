// Angus Cheng, December 1,2023
#include "PlayList.h"
#include <iostream>
using namespace std;
// PlayList method implementations go here

// Constructors
// Sets the head to be NULL and number of songs to be zero
PlayList::PlayList(){
    head = NULL;
    numSongs = 0;
}
// Creating a completely new playlist which pl is the playlist we are copying from
// A copy constructor creates an exact copy of an object and stores it into a new object
PlayList::PlayList(const PlayList& pl){
    // If the head of pl is NULL, then the head of our deep copy is NULL as well
    if(pl.head == NULL){
        head = NULL;
    }
    // Else there are nodes inside of the pl playlist
    else{
        // The head is pointing to a new node that copied the song from pl
        head = new PlayListNode(pl.head->song);
        PlayListNode* oldPtr = pl.head->next;
        PlayListNode* newPtr = head;
        // Keep track of the number of songs
        unsigned track = 0;
        // Iterate through the pl playlist
        while(oldPtr!= NULL){
            newPtr->next = new PlayListNode(oldPtr->song);
            newPtr= newPtr->next;
            oldPtr = oldPtr->next;
            track++;
        }
        numSongs = track+=1;
    }
    
    
    
}
// Delete all the nodes since it's a destructor
PlayList::~PlayList(){
    
    PlayListNode* curr = head;
    PlayListNode* prev = NULL;
    // Iterate through all the nodes and delete them
    while(numSongs != 0){
        prev= curr;
        curr = curr->next;
        head = curr;
        delete prev;
        numSongs--;
    }
    
    
}
// Copying from the playlist and returning its reference
PlayList& PlayList::operator=(const PlayList& pl){
    // *this is a dereferenced pointer and this is just a pointer
    // *this is a clone of the current object (pl)
    this->head = new PlayListNode(pl.head->song);
    PlayListNode* plPtr = pl.head->next;
    PlayListNode* curr = head;
    PlayListNode* prev = NULL;
    PlayListNode* track = this->head;
    // Deleting all the nodes
    while(curr != NULL){
        prev = curr;
        curr = curr->next;
        head = curr;
        delete prev;
    }
    // Copying from the playlist pl
    while(plPtr != NULL){
        PlayListNode* copy = new PlayListNode(plPtr->song);
        track->next = copy;
        track = track->next;
        plPtr = plPtr->next;
    }
    return *this;
}

// Methods/Functions
// Modifying the size in a linked list is much more simple than changing the size in an array
void PlayList::insert(Song sng, unsigned int pos){
    // Create a new node and a current and previous pointer
    PlayListNode* newNode = new PlayListNode(sng);
    PlayListNode* curr = head;
    PlayListNode* prev = NULL;

    // Check to see if the Linked List is empty and if it is, set the newNode to have a next of NUL and head to be that nods
    if(curr == NULL){
        newNode->next = NULL;
        head = newNode;
        numSongs = 1;
    }
    // Else if there already is a node, run this part of the code
    else{
        numSongs++;
        unsigned int specialCase = 1;
        // If the position is one, then the newNode points to the head of our current node
        if(specialCase == pos){
            newNode->next = curr;
            // We have to set head to newNode or else it won't be able to properly print out the nodes
            head = newNode;
        }
        // Else if it is nto inserting at the front, run this code
        else{
            for(unsigned int i = 1; i <pos; i++){
                prev = curr;
                curr = curr->next;
            }
            prev->next = newNode;
            newNode->next = curr;
        }
    }

}

// Remove a node at a certain posiiton
Song PlayList::remove(unsigned int pos){
    // Initalize node pointers
    PlayListNode* remove = head->next;
    PlayListNode* curr = head;
    unsigned int count = 1;

    // If there is only one song in the playlist, delete it
    if(count == pos && numSongs ==1){
        numSongs =0;
        // Storing the song in a temporary song variable 
        Song temp = curr->song;
        delete curr;
        head = NULL;
        return temp;
    }
    // Else if there is more than one song in the playlist but we want to delete the first node do this
    else if(count == pos){
        numSongs --;
        Song tempTwo = curr->song;
        head = curr->next;
        delete curr;
        return tempTwo;
    }
    // Else run this part of the code
    else{
        
        while(curr!= NULL && count != pos-1){
            curr = curr->next;
            remove = remove-> next;
            count++;
        }
        Song temp= remove->song;
        curr->next = remove->next;
        delete remove;
        numSongs--;
        return temp;
    }
}
// Swap two nodes with each other 
void PlayList::swap(unsigned int pos1, unsigned int pos2){
    //Swapping two nodes so create two pointers from the start
    // We need two previous pointers
    PlayListNode* firstNode = head;
    PlayListNode* secondNode = head;
    PlayListNode* prevOne = NULL;
    PlayListNode* prevTwo = NULL;
    PlayListNode* tempNode = NULL;
    unsigned int countOne = 1;
    unsigned int countTwo = 1;

    // If there are only two songs in the playlist
    if(numSongs == 2){
        secondNode = firstNode->next;
        firstNode->next = NULL;
        secondNode->next = firstNode;
        head = secondNode;
    }
    // Else run this 
    else{
        // If the first position is one that we are trying to swap
        if(pos1 == 1){
         
         while(countTwo != pos2){
            prevTwo = secondNode;
            secondNode= secondNode->next;
            countTwo++;
         }
         tempNode = firstNode->next;
         firstNode->next = secondNode->next;
         secondNode->next = tempNode;
         tempNode->next = firstNode;
         head = secondNode;
        }
        // Else If the first position is one that we are trying to swap
        else if(pos2 == 1){
            while(countOne != pos1){
            prevOne = firstNode;
            firstNode= firstNode->next;
            countOne++;
         }
         tempNode = secondNode->next;
         secondNode->next= firstNode->next;
         firstNode->next = tempNode;
         tempNode->next = secondNode;
         head = firstNode;
        }
        // Else swap regularly
        else{
            while(countOne != pos1){
                prevOne = firstNode;
                firstNode= firstNode->next;
                countOne++;
            }
            while(countTwo != pos2){
                prevTwo = secondNode;
                secondNode= secondNode->next;
                countTwo++;
            }
            prevOne->next = secondNode;
            prevTwo->next = firstNode;
            tempNode = firstNode->next;
            firstNode->next = secondNode ->next;
            secondNode->next = tempNode;
        }
    }
    

}

// Get a value at a certain position
Song PlayList:: get(unsigned int pos) const{
    PlayListNode* curr = head;
    unsigned int count = 1;
    // Iterate through the playlist
    while(curr!= NULL && count!=pos){
        curr = curr->next;
        count++;
    }
    return curr->song;
}

// Return the number of songs
unsigned int PlayList :: size() const{
    return numSongs;
}
