typedef struct profile {
    char name[11];
    int numberOfGames;
    int numberOfWins;
    int maxScore;
} profile;
/*This sturcture is used to store profiles.*/

profile* getProfiles(int*NumberOfProfiles);
/*This function is used to retrieve profiles data from the profiles.sav file, and put them in an array
it takes a pointer to an Int wich is modified to be the number of profiles that were loaded
it returns a pointer to an array of profiles
*/
void emergencyExit();
/*This fuction is called when something goes wrong during the loading of the profiles. It just crash the programm after printing a warning */

void printProfiles(profile* profileArray, int NumberOfProfiles);
/*this fuction is used to print all the profiles and the stats linked to it
the parameters are
-the array of profile
-the number of profiles
*/
profile* addNewProfile(profile* profileArray, int* NumaberOfProfiles);
/*this function is used  to add a new profile to the array
the parameters are
-the array of profile
-the number of profiles
it returns the new pointeur to the relocated array
*/
void saveProfiles(profile* profileArray, int NumberOfProfiles);
/*this function is used  to save the array of profile into the profiles.sav file, and to free the array
the parameters are
-the array of profile
-the number of profiles
*/
profile* selectProfile(profile* profileArray, int* numberOfProfiles, int* profileNumber);
/*this function is used to select a profile before the game
the parameters are
-the array of profile
-the a pointer to the numberOfProfiles wich can be modififed because addNewProfile is inside
-pointer to an int wich is modified to the selected profile.
it returns the new pointeur to the relocated array
*/
void updateProfile(profile* profileArray, int profileNumber, int win, int score);
/*this function is used  to update the profile
the parameters are
-the array of profiles
-the number of the profile to update
-if the player won (it will add a win if its set to 1)
- the score, wich will replace the score of the profile if it higher
*/
