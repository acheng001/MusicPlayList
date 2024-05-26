// Angus Cheng, December 1,2023
#include <iostream>
#include <string>
#include "PlayList.h"
#include "Song.h"
using namespace std;
/* Big O Notation

 PlayList Methods
 - Default Constructor - O(1) 
    - Is constant time because we only initalize head and numSongs which only costs one operation each
 - Destructor - O(N)
    - We have to loop over all the nodes and delete them which is why it is N times
 - Copy Constructor -O(N)
    - We initalize a new playlist(Deep copy)and iterate through our entire old playlist in order to copy everything into the new one
    - By going through the whole old playlist, this demonstrates O(N)
 - Overloaded Assignment operator- O(N)
    - Unlike the copy constructor, we have an existing playlist which we first iterate through the whole thing to delete the old nodes
    - Afterwards, we iterate through the playlist we want to copy from and add the nodes into our existing playlist
 - Insert - O(N)
    - The worst case is if the element is in the last position which means we have to loop through the whole linked list
    - Results in O(N) time
 - Remove - O(N)
    - The worst case is if the element is at the end of the linked list, we have to iterate throught the whole thing
    - This is why it is O(N) as well
 - Get - O(N)
    - Assuming in the worst case the element is in the last position, we have to go through the whole thing
    - As a result, this is why it is O(N)
 - Swap - O(N)
    - In the worst case that position one or two is at the end of the linked list, we have to iterate through it
    - This would result in going through the whole thing and therefore having a worst time of O(N)
 - Size - O(1)
    - Returns the number of songs in our playlist which only costs one operation

 Main Function Commands
 - Enter a song - O(N)
    - Since our insert function is O(N), it is O(N) when we call the function to add a song
 - Remove a song - O(N)
    - Our remove function is also O(N) so when we call the remove in main, it is also O(N)
 - Swap two songs - O(N)
    - Since the swap function is O(N) as well, calling it will result in O(N) time in main
 - Print all the songs - O(N)
    - We have to iterate through the whole playlist of songs to print which is why it is O(N)

*/
// Main Function
int main(){
    // Initliazing objects used in the main program
    bool value = true;
    string song;
    string artist;
    unsigned int length;
    unsigned int position;
    unsigned int swapOne;
    unsigned int swapTwo;
    unsigned int keepTrack= 2;
    string command;
    // Create an object of PlayList that allows it to have access to all public functions
    // Since the constructor is empty we initalize it as newPlaylist instead of newPlaylist()
    PlayList newPlaylist;
    // Printing out the playlist functions
    cout<<"Menu: "<<endl;
    cout<<"1 - Enter a song in the play list at a given position "<<endl;
    cout<<"2 - Remove a song from the play list at a given position "<<endl;
    cout<<"3 - Swap two songs in the play list "<<endl;
    cout<<"4 - Print all the songs in the play list "<<endl;
    cout<<"5 - Quit "<<endl;
    cout<<""<<endl;
    // Have a while loop that keeps asking the user for commands
    while(value){
        // Creating the command menu
        cout<<"Enter 1(insert), 2 (remove), 3 (swap), 4 (print) or 5 (quit): ";
        cin>> command;

        // First command
        if(command == "1"){
            
            // Taking input of song
            // getline reads a string with spaces
            // Use ignore before a getline call
            cout<<"Song name: ";
            // Ignores input of the new line character 
            cin.ignore(256,'\n');
            getline(cin,song);
            // Taking input of artist
            cout<<"Artist: ";
            getline(cin,artist);
            // Taking input of length
            cout<<"Length: ";
            cin>>length;
            // Taking input of position
            
            // If the user enters a string for length instead of an int
            while (cin.fail()){
                cin.clear();
                cin.ignore(100,'\n');
                cout << "Please enter a valid position that is an integer: ";
                cin >> length;
            }

            // If playlist size is zero
            if(newPlaylist.size() == 0){
                cout<<"Position (1): ";
                cin>>position;
                // If statement checks to see if user enters a valid position
                if(position != 1){
                    while(true){
                        cout<<"Position (1): ";
                        cin>>position;
                        if(position == 1 ){
                            break;
                        }
                    }
                }
                
            }
            // Else if size of playlist is bigger than one, do this function
            else{
                cout<<"Position (1 to "<<keepTrack<<"): ";
                cin>>position;
                 // If statement checks to see if user enters a valid position
                if(position <1 || position > keepTrack){
                    while(true){
                        cout<<"Position (1 to "<<keepTrack<<"): ";
                        cin>>position;
                        if(position >=1 && position <= keepTrack){
                            break;
                        }
                    }
                }
                keepTrack++;
            }
            
            // Creating a song object that has access to the function
            Song newSong(song,artist,length); 
            newPlaylist.insert(newSong,position);
            cout<<"You entered "<<song<<" at position "<<position<< " in the play list"<<endl;
            cout<<" "<<endl;
            
            

        }

        // If command is 2
        else if(command == "2"){
            
            // If the size of the playlist is one
            if(newPlaylist.size() == 1){
                cout<<"Position (1): ";
                cin>>position;
                // If statement checks to see if user enters a valid position
                if(position != 1){
                    while(true){
                        cout<<"Position (1): ";
                        cin>>position;
                        if(position == 1 ){
                            break;
                        }
                    }
                }
                keepTrack--;
                Song removedSong = newPlaylist.get(position);
                newPlaylist.remove(position);
                cout<<"You removed "<<removedSong.getName()<<" from the play list"<<endl;
                cout<<" "<<endl;

            }
            // If the size of playlist is bigger than one
            else if(newPlaylist.size()>1){
                keepTrack --;
                cout<<"Position (1 to "<<keepTrack<<"): ";
                cin>>position;
                // If statement checks to see if user enters a valid position
                if(position <1 || position > keepTrack){
                    while(true){
                        cout<<"Position (1 to "<<keepTrack<<"): ";
                        cin>>position;
                        if(position>=1&&position<=keepTrack){
                            break;
                        }
                    }
                }
                keepTrack++;
                Song removedSong = newPlaylist.get(position);
                newPlaylist.remove(position);
                cout<<"You removed "<<removedSong.getName()<<" from the play list"<<endl;
                cout<<" "<<endl;
            }
            // Else there are no songs in the playlist
            else{
                cout<<"There are no songs in the play list to remove"<<endl;
                cout<<" "<<endl;
            }
            
        }

        // If command is 3
        else if(command == "3"){
            // If size of playlist is zero
            if(newPlaylist.size()== 0){
                cout<<"List is empty so there is nothing to swap!"<<endl;
            }
            // Else if size of playlist is one
            else if(newPlaylist.size()==1){
                cout<<"Swap song at position (1 to 1): ";
                cin>>swapOne;
                cout<<"with the song at position (1 to 1): ";
                cin>>swapTwo;
                while(swapOne != 1 && swapTwo != 1){
                    cout<<"Swap song at position (1 to 1): ";
                    cin>>swapOne;
                    cout<<"with the song at position (1 to 1): ";
                    cin>>swapTwo;
                    if(swapOne == 1 && swapTwo == 1){
                        break;
                    }
                }
                cout<<"You swapped the songs at positions 1 and 1"<<endl;
                cout<<" "<<endl;
            }
            // Else the size of playlist is not zero or one
            else{
                keepTrack--;
                cout<<"Swap song at position (1 to "<< keepTrack<<"): ";
                cin>>swapOne;
                cout<<"with the song at position (1 to "<< keepTrack<<"): ";
                cin>>swapTwo;
                // If statement checks to see if user enters a valid position
                while(swapOne < 1 || swapTwo > keepTrack){
                    cout<<"Swap song at position (1 to "<< keepTrack<<"): ";
                    cin>>swapOne;
                    cout<<"with the song at position (1 to "<< keepTrack<<"): ";
                    cin>>swapTwo;
                    if(swapOne >= 1 && swapTwo <= keepTrack){
                        break;
                    }
                }
                // If statement checks to see if user enters a valid position
                while(swapOne > keepTrack || swapTwo <1){
                    cout<<"Swap song at position (1 to "<< keepTrack<<"): ";
                    cin>>swapOne;
                    cout<<"with the song at position (1 to "<< keepTrack<<"): ";
                    cin>>swapTwo;
                    if(swapOne >= 1 && swapTwo <= keepTrack){
                        break;
                    }
                }
                keepTrack++;
                newPlaylist.swap(swapOne,swapTwo);
                cout<<"You swapped the songs at positions "<<swapOne <<" and "<<swapTwo<<endl;
                cout<<" "<<endl;
            }
        }
        // If command is 4
        else if(command == "4"){
            unsigned int greater = newPlaylist.size() +1;
            // If size of playlist is zero
            if(newPlaylist.size()==0){
                cout<<"Empty Playlist"<<endl;
                cout<<" "<<endl;
            }
            // Else if the size of playlist isn't zero
            else{
                // Right now it is printing the song multiple times because that is what we set it to
                for(unsigned int i = 1; i < greater;i++){
                    Song allSongs = newPlaylist.get(i);
                    cout<<" " << i << " "<< allSongs.getName()<<" "<<"("<<allSongs.getArtist()<<")"<<" "<<allSongs.getLength()<<"s"<<endl;
                }
                cout<<"There are "<<newPlaylist.size()<<" songs in the play list."<<endl;
                cout<<" "<<endl;
            }
            
        }
        // If command is 5
        else if(command == "5"){
            // End the while loop
            cout<<"You have chosen to quit the program."<<endl;
            value = false;
            //break;
        }
        
        // Else keep printing enter a valid command
        else{
            cout<<"Please enter a valid number between 1-5: "<<endl;
            cout<<" "<<endl;
        }
        
    }
    
}