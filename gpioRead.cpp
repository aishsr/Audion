//Project: Audion
//Group Members: Sarah Kang, Grace Tian, Aishwarya Srinivas
//Description: Using Omega, an embedded system that acts as a MP3 player is created.



/////////////////////////////////////////////////////////////////////HEADER FILES/////////////////////////////////////////////////////////////////////////////////////




#include <iostream>
#include <dirent.h>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/stat.h>

using namespace std;


///////////////////////////////////////////////////FUNCTIONS FOR FILES/////////////////////////////////////////////////////////

string shuffle (const (string &array));
string play (string &(array), int songIndex);



//FUNCTION TO DISPLAY LIST OF FILES AND STORE INTO ARRAY

void explore (char* dir_name, string (&array)[20])
{
	DIR *dir;
	struct dirent *entry;
	struct stat info;
	dir = opendir (dir_name);
	if (!dir)
	{
		cout << "Directory was not found." << endl;
		return;
	}

	int i =0;
	int counter = 0;
	if ((dir = opendir ("c:/Users/HP/Music/Music")) != NULL)
	{
		while ((entry = readdir(dir)) != NULL)
		{
			if (entry->d_name[0] != '.')
			{
				string path = string (dir_name) + "/" + string (entry->d_name);

				stat (path.c_str(), &info);
				array [i] = string (entry->d_name);
				counter ++;
				i++;

				if (S_ISDIR(info.st_mode))
				{
					explore ((char*)path.c_str());
				}
			}

		}
	}

	//PRINT
	for (int i =0; i < counter; i++)
	{
		cout << "--- " << (i + 1) << ". " << array [i] << endl;
	}
	closedir (dir);
}


//FAVORITES ARRAY
void favorite (const string &array, bool &favs)
{
	for (int i =0; i < 20; i++)
	{
		if (favs == true)
		{
			cout << "   " << array [i] << endl;
		}
	}

}

//RETURN A SHUFFLED SONG
string shuffle (const string (array[]))
{
	int randNum = rand()%(20-0 + 1) + 0;
	return array[randNum];

}

//RETURN SONG THAT WILL BE PLAYED
string play (string (array[]), int songIndex)
{

}

//RETURN PREVIOUS SONG THAT WILL BE PLAYED
string previous (string (array[]), int songIndex)
{

}

//RETURN NEXT SONG THAT WILL BE PLAYED
string next (string (array[]), int songIndex)
{

}



int main(const int argc, const char* const argv[])
{
	////////////////////////////////////////////////////////////SETTING UP GPIO PINS///////////////////////////////////////////////////////////////////

	//SETTING DIRECTIONS FOR THE PINS

	//Set the direction of Pin 1 to be output AS LED (On)                    //Is the pin connected to a LED to display that its on? How do we start the system?
	setDirection (1, GPIO_Output);

	//Set the direction of Pin 2 to be input (Play)
	setDirection (2, GPIO_Input);

	//Set the direction of Pin 3 to be input (Pause)
	setDirection (4, GPIO_Input);

	//Set the direction of Pin 4 to be input (previousSongious)
	setDirection (6, GPIO_Input);

	//Set the direction of Pin 5 to be input (Next)
	setDirection (7, GPIO_Input);

	//Set the direction of Pin 6 to be input (Rating)
	setDirection (8, GPIO_Input);


	//SETTING UP OLED PINS
	                                                                              //Will have to look into this?

	//VARIABLES FOR DIFFERENT BUTTONS AND ASSOCIATING PINS FOR THEM
	const int onOffButton = 1;           //to switch on or off the system         //A variable for each button, associating it with a GPIO pin. I don't think it works like this?
	const int playButton = 2;           //to play the currentSongrent song                //??????????????????
	const int pauseButton = 3;          //to pause the currentSongrent song
	const int previousButton = 4;       //to go to the previousSongious song
	const int nextButton = 5;           //to go to the next song
	const int likeButton = 6;           //to favorite a song

	int reading;

	//NUMBER OF BUTTONS
	const int numberOfButtons = 6;

	int readButton;                   //read the input from a button that is pressed

	//DEBOUNCE TIMES FOR THE BUTTONS
	long onOffDebounce;
	long playDebounce;
	long pauseDebounce;                         //What is debounce? I know its for the buttons......
	long previousSongiousDebounce;
	long nextDebounce;
	long likeDebounce;
	long debounceDelay = 30;                    //Find what's a debounce. Then find out why we need a delay
	const int buttonDelay = 30;


	//////////////////////////////////////////////OVERALL STATE OF MP3 PLAYER///////////////////////////////////////////////
	//For example, if music s playing, the MP3 player is in 'playState'. If music is paused, it is in 'pauseState'. If user clicked on next, 'nextState', etc...

	int onOffState;
	int playState;                      //associated with buttons, see
	int pauseState;
	int previousSongiousState;
	int nextState;
	int likeState;

	int lastonOffState;
	int lastplayState;                      //associated with buttons, see
	int lastpauseState;
	int lastpreviousSongiousState;
	int lastnextState;
	int lastlikeState;

	onOffDebounce, playDebounce, pauseDebounce, previousSongiousDebounce, nextDebounce, likeDebounce = 0;          //setting to 0 at first

	string array [20];
	int favs [20];

	bool filesOK = false;
	if (explore ((char*)"."))
	{
		filesOK = true;
	}

	int songIndex = 0;


///////////////////////////////////////////////////////MAIN CODE//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//terminal options
	string option;

	cout << "\t Welcome to Audion. \t" << endl;
	cout << " " << endl;
	cout << " " << endl;
	cout << "To navigate: " << endl;                     //Add better sentences

	cout << "Keys: " << endl;
	cout << " -list \t See all music available in the folder. " << endl;
	cout << " -fav \t List of favorited music. " << endl;                          //Add better sentences to display
	cout << " -shuffle \t Shuffle music. " << endl;
	cout << " -button \t List of buttons to use." << endl;

	option = argv[1];
	cout << " " << endl;

	if (argc > 1)
	{
		if (option == "list")
		{
			//display full list of songs
			if ((explore ((char*)"."), array))
			{
			cout << "     " << (explore ((char*)"."), array) << endl;
			}
			else
			{
				cout << "Sorry, there are no files in this folder." << endl;
			}
		}

		//display favs list
		if (option == "fav")
		{
			cout << "     " <<  (favs (array, favs))<< endl;
		}

		//shuffle song
		if (option == "shuffle")
		{
			cout << "Now playing: " << shuffle (array) << endl;
			cout << "Click on the play button" << endl;
		}
	}

	while (reading != get (onOffButton))
	{
		if (filesOK)
		{
			songIndex = 1;

			//play
			if (reading = get (playButton))
			{
				play(array, songIndex);
			}

			//previous
			if (reading = get (previousButton))
			{
				previous(array, songIndex);
				play(array, songIndex);
			}

			//next
			if (reading = get (nextButton))
			{
				next(array, songIndex);
				play(array, songIndex);
			}

			//like
			if (reading = get (likeButton))
			{
				favs [songIndex] = true;
			}

			//quit
			if (reading = get (onOffButton))
			{
				break;
				cout << "Shutdown...." << endl;

			}

		}
	}




    return 0;
}

