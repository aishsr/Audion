//Project: Audion
//Group Members: Sarah Kang, Grace Tian, Aishwarya Srinivas
//Description: Using Omega, an embedded system that acts as a MP3 player is created.
//Date: November 2017

/////////////////////////////////////////////////////////////////////HEADER FILES////////////////////////////////////////////////////////////////////////////////////

#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <ugpio/ugpio.h> 

using namespace std;

////////////////////////////////////////FUNCTION DECLARATIONS///////////////////////////////////////////////////////////////////////////

void explore (char* dir_name, string *songArray, int size);
string shuffle (string *array, int size);
string play (string *array, int size, int songIndex);
string previous (string *array, int size, int songIndex);
string next (string *array, int size, int songIndex);
int system(const char *command);

///////////////////////////////////////////////////FUNCTIONS FOR FILES/////////////////////////////////////////////////////////

//FUNCTION TO DISPLAY LIST OF FILES AND STORE INTO ARRAY
 void explore (char* dir_name, string *songArray, int size)
{
	DIR *dir;
	struct dirent *entry;             //each entry in the folder
	struct stat info;                 //the entry's relevant information
	dir = opendir (dir_name);
	if (!dir)	// if program cannot detect the designated folder
	{
		cout << "Directory was not found." << endl;
		return;
	}
	
	int i =0;
	
		
	if ((dir = opendir ("C:/Users/HP/Music/Undertale")) != NULL) 	// if there is still content inside this folder
	{
		while (((entry = readdir(dir)) != NULL) && (i < size))
		{
			
			if (entry->d_name[0] != '.')
			{
				string path = string (dir_name) + "/" + string (entry->d_name);		//  string (entry->d_name) is name of file
				
				stat (path.c_str(), &info);
				songArray [i] = string (entry->d_name);		//  storing the music files into the music array 	
				
				if (S_ISDIR(info.st_mode))  		// recursive function that goes through each entry and stores music files into array
				{
					explore (((char*)path.c_str()), songArray, size);		// reads file from directaor and puts them to array
				}
			}
			i++;
			
		}
	}
	

	closedir (dir);
}


//RETURN A SHUFFLED SONG
string shuffle (string *array, int size)
{
	int randNum = rand()%((size - 1) - 2 + 1) + 2;           //generating a random number
	return array [randNum];                                  //returning element from array
	
}

//RETURN SONG THAT WILL BE PLAYED
string play (string *array, int size, int songIndex)
{
	return array [songIndex];                                //returning element from array
}

//RETURN PREVIOUS SONG THAT WILL BE PLAYED
string previous (string *array, int size, int songIndex)
{
	return array [songIndex - 1];                             //returning previous element from array
}

//RETURN NEXT SONG THAT WILL BE PLAYED
string next (string *array, int size, int songIndex)
{
	return array [songIndex + 1];                             //returning next song in the array
}



/////////////////////////////////////////////////////////////////////////////////MAIN////////////////////////////////////////////////////////////////////////////////////////
int main(const int argc, const char* const argv[])
{
	
////////////////////////////////////////////////////////////SETTING UP GPIO PINS///////////////////////////////////////////////////////////////////

	//SETTING DIRECTIONS FOR THE PINS
	
	//Set the direction of Pin 1 to be input (Quit)    
	ugpio_get_direction (1);

	//Set the direction of Pin 2 to be input (Play)
	ugpio_get_direction (2);


	//Set the direction of Pin 4 to be input (Previous)
	ugpio_get_direction (6);

	//Set the direction of Pin 5 to be input (Next)
	ugpio_get_direction (7);
	
	//Set the direction of Pin 6 to be input (Like)
	ugpio_get_direction (8);
	
								  
	//VARIABLES FOR DIFFERENT BUTTONS AND ASSOCIATING PINS FOR THEM
	const int quitButtonPin = 3;           //to switch off the system              
	const int playButtonPin = 9;           //to play the current song         
	const int previousButtonPin = 8;       //to go to the previous song
	const int nextButtonPin = 7;           //to go to the next song
	const int likeButtonPin = 1;           //to favorite a song
	
	int reading;                          //reading input from the gpio pins
	
	//NUMBER OF BUTTONS
	const int numberOfButtons = 5;
	
	
	//////////////////////////////////////////////OVERALL STATE OF MP3 PLAYER///////////////////////////////////////////////
	//For example, if music s playing, the MP3 player is in 'playState'. If music is paused, it is in 'pauseState'. If user clicked on next, 'nextState', etc...
	
	int quitState = 0;		// Setting them as 0 means that the input from the GPIO pins is LOW.
	int playState = 0;              
	int previousState = 0;
	int nextState = 0;
	int likeState = 0;
	
	string aplay  = "aplay ";             //to play the music
	 
	int size = 50;	                      //max size of the playlist
	string array [size];	              //playlist array
	int favs [size];	                  //favorites array

	for (int i =0; i < size; i ++)
	{
		favs[i] = 0;			          // setting all the elements in the favorites array to 0
	}

	int songIndex = 2;

///////////////////////////////////////////////////////MAIN CODE//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	

	//terminal options
	string option;

	cout << "\t Welcome to Audion. \t" << endl;	// Welcoming the user when they start our program
	cout << " " << endl;
	cout << " " << endl;
	cout << "To navigate: " << endl;                    
	
	cout << "Keys: " << endl;
	cout << " 1. list \t See all music available in the folder. " << endl;
	cout << " 2. fav \t List of favorited music. " << endl;                          
	cout << " 3. shuffle \t Shuffle music. " << endl;
	cout << " 4. button \t List of buttons to use." << endl;		// Option 4 explains the function of each of the buttons on the hardawre  
	cout << " 5. quit \t To shut down." << endl;
	
	cout << " " << endl;

		while (true)
		{
			//LIST
			if (option == "1")		// lists all the songs in the file
			{
				cout << " " << endl;
				explore (((char*)"."), array, size);
				for (int i = 2; i < size; i++)
				{
					cout << "--- " << (i - 1) << ". " << array [i] << endl;
				}	

			}
			
			//FAVORITES
			if (option == "2")
			{
				int emptyCounter = 0;		// initial value is 0 
				cout << " " << endl;
				explore (((char*)"."), array, size);	
				cout << "Favourites: " << endl;
				for (int i = 2; i < size; i++)
				{
					if ((favs [i - 2]) != 0)		// checking if the array is not empty
					{
						emptyCounter++;
					}
				}
				if (emptyCounter == 0)		// if the array is empty, display "no favourties yet"
				{
					cout << "No favourites yet." << endl;
				}
				else 
				{
					for (int i = 2; i < size; i++)
					{
						if (favs[i - 2] == 1)	           // showing all the songs that were favorited 
						{
							cout << "--- " << (i - 1) << ". " << array [i] << endl;
						}
					}
				}
			}
			
			//SHUFFLE
			if (option == "3")		// if user selects "shuffle" function, this code will run  
			{
				cout << " " << endl;
				explore (((char*)"."), array, size);		// reads file from directaor and puts them to array
				cout << "  " << shuffle (array, size) << " is now selected." << endl;

			}
			
			//BUTTONS
			if (option == "4")	 
			{
				cout << " " << endl;
				explore (((char*)"."), array, size);		// Typing "4" displays pin numbers associated with the buttons
				cout << "---[9] Play" << endl;
				cout << "---[8] Previous" << endl;
				cout << "---[7] Next" << endl;
				cout << "---[1] Like" << endl;
				cout << "---[3] Quit" << endl;

			}
			
			//QUIT
			if (option == "5")		// if user pressed the turn off button, this code tell system to shut down  
			{
				cout << "Exiting..." << endl;
				break;
			}
			
			
			
			//////////////////////////////////////////////////////////BUTTON OPERATIONS////////////////////////////////////////////////////////////
			
			
			//PLAY
			playState = gpio_get_value (playButtonPin);		// reading the state of button, either HIGH or LOW
			if (playState == 1)		// if the "play music" button is pressed
			{				
				explore (((char*)"."), array, size);
				if (option == "3")		// if user types "3", it will shuffle some random array element which will play the song stored in the playlist
				{
					cout << shuffle (array, size) << endl;
				}
				{
				cout << array [songIndex] << " is being played." << endl;                //displaying what is being played.
				system(aplay + array [songIndex]);
				}
			}
			
			//PREVIOUS
			previousState = gpio_get_value (previousButtonPin);
			if (previousState == 1)		// if the "previous song" button is pressed
			{
				explore (((char*)"."), array, size);
				cout << previous (array, size, songIndex) << " is being played." << endl;
				system (aplay + previous (array, size, songIndex));
				songIndex--;	// playlist decrements the array element which will play the previous song stored in the file
			}
			
			//NEXT
			nextState = gpio_get_value (nextButtonPin);
			if (nextButton == 1)		// if the "next song" button is pressed
			{
				explore (((char*)"."), array, size);
				cout << next (array, size, songIndex) << " is being played." << endl;
				system (aplay + next (array, size, songIndex));
				songIndex++;		// playlist increaseS the array element which will play the next song stored in the file
			}
			
			//FAVORITE
			likeState = gpio_get_value (likeButtonPin);
			if (likeButton == 1)	// if the "like" button is pressed
			{	
				explore (((char*)"."), array, size);
				favs[songIndex] = 1;	// the corresponding song index is incremented by 1
			}
			
			//QUIT
			quitButton = gpio_get_value (quitButtonPin);
			if (quitButton == 1)	// if the "quit" button is pressed
			{ 
				cout << "Exiting..." << endl;
				break;		// breaking the code means to "shut down" the playlist
			}
	
			cout << " " << endl;
			cout << "Enter a number for your input: ";		//the loop continues and this statement is present on every loop
			cin >> option;

		}
		
return 0;
}
