# Song-Management-System
First Data Structures assignment using Linked Lists in C

-- --
This assignment aims to help you practice linked list data structure and basic linked list operations. Your main task in this assignment is to write a C program to create a simple application that will allow you manage your songs. This application will mainly keep your songs in a simple text file but when loaded to your application, your application will keep your songs in an internal Linked List. For each song, your application will store the following details: a unique identification number for each song which can be maximum of 4 digit integer, the name of the song (max 50 characters), the song genre (max 50 characters), the album name of this song (max 50 characters) and the artist name that sings this song (max 50 characters), the year that this song was released and the date-time (Format: DD/MM/YYYY HH:MM) that you added this song to your song list.

When you start the application, it will read your songs from an external text files (songMan.txt), create a linked list and then populate this list with the songs stored in that file. This application will then provide some operations for you to manage your song. When you exit from the application, the application will overwrite the external file with the latest version of the list to include the latest
songs in your application. Therefore, the SongMan application needs to support the following operations.

-- --
* **Reading your songs from an external file and initialising your song lists**: The application will start by reading the songs from an      external text file called SongMan.txt. The sonMan.txt file will include the details of the songs that you have, including unique id,      songName, songGenre, albumName, artistName, release year of this song, and date-time separated by a semicolon. We assume that there is    no semicolon in the contents of your songs (name, artist name and also the album name), for example, please assume that a song name        itself does not include a semicolon. Example content file is shown below:
   *Song_Man.txt*
```
   1;Unutmamali;Pop;Aacayipsin;Tarkan;1994;22/10/2019 14:11
   2;Huzurum Kalmadi;Arabesque;Huzurum Kalmadi;Ferdi Tayfur;1976;22/10/2019 15:15
   3;Time to say Goodbye; Classical Crossover;Timeless; Andrea Bocelli and Sarah
   Brightman;1995; 22/11/2019 15:18
```
  The application will then internally store these songs in a linked list. Please note that you cannot make any assumptions about the       number of songs you have in your list and there is no upper limit for the number of songs. In your internal representation, you will       need to decide about the structure of your linked list based on the txt files given above.
* **Adding a new song**: After the initialisation of the application with the external file, you may want to add a new song to your         storage. In this case, the application will ask you to enter the song details, including the name, the genre, the artist, the release     date and also the album. In addition to these details, the application will take the current date-time from the system and add the new     song with all the details in the list of songs maintained. You can find the date-time from the system as follows:
```C
  #include <stdio.h>
  #include <time.h>
  int main() {
  time_t ti = time(NULL);
  struct tm t = *localtime(&ti);
  printf("Date: %02d/%02d/%04d\n", t.tm_mday, t.tm_mon+1,
  t.tm_year+1900);
  printf("Time: %02d:%02d\n", t.tm_hour, t.tm_min);
  return 0;
  }
```
* **Deleting a song**: This application will allow you to select a specific song by using its unique id from the list and delete it.
* **Printing your songs**: This application will allow you to print the songs that you manage in your application. Deleted songs should   not be displayed.
* **Searching for a song**: This application will allow you to search for a song by using the following details: song name, artist name   or genre. More than one song can be listed after searching. You can make use of external libraries in C, such as string.h library.
* **Create a playlist**: This application will also allow you to create a playlist. The user will give three song names, and a new          playlist will be created and the song details will be stored in an external text file. The file name should be created automatically    and every time a new playlist is created, a new file should be created, such as “PlayList-1.txt”, “PlayList-2.txt”. Your application    does not need to be smart to check if the playlist was already created or not.
* **Overwriting the external file**: When the application is closed, the external file (ManSong.txt) should be overwritten with the       latest version of the list.

## **Programming Requirements**
When you write this application, you need to consider the data structure(s) that will be necessary. Therefore, it is recommended that you implement your basic linked list operations first (add/delete/search/print, etc). By using these basic operations on linked lists, you can implement other required operations. You also need to define and use a structure for date-time.
To achieve the steps you need to have the following functions. Please strictly follow the requirements of the functions given below! In addition to these functions, you can write some helper/auxiliary functions.


**Function**| **Explanation**| **Take**| **Return**
------------|----------------|---------|-----------
initialiseSongs | To create and initialise the lists of songs that you have in SongMan.txt file | - | A list of songs you manage
addSong | To insert a new song in to your list of songs by taking the required details. | A list of songs you manage, song name, genre, release date, album name and also album artist | A list of songs you manage
deleteSong | To delete a song from the list of songs you manage by using one of its unique id. | A list of songs you manage, a unique id | A list of songs you manage
printSongs | To show the details of the songs you manage. | A list of songs you manage | -
searchSongs | To search for a song by using song name, artist name or genre. More than one song can be listed based on search keys. | A list of songs you manage | -
createPlaylist | To create a playlist with the song details provided. | A list of songs you manage, a list of song names to create the playlist and playlistID. | -
Overwrite | To overwrite the external files with the latest versions of the list. | A list of songs you manage. | -

**Grading**

**Grading Point** | **Mark(out of 100)**
------------------|---------------------
Structures  to represent  a list of songs and  date-time | 5
Main function to control and coordinate commands | 15
initialiseSongs | 10
addSong | 10
deleteSong | 5
printSongs | 5
searchSongs | 20
createPlaylist | 15
Overwrite | 15

**Note:** Remember to have good programming style (Appropriate comments, variable names, formulation of selection statements and loops, reusability, extensibility etc.). Each of the items above will include10% for good programming style.

**Sample Run** 

```
The SonMan.txt file has been loaded successfully
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option: 1
Enter name of the song: The hills
Enter genre of the song: pop
Enter name of the album: Beauty Behind the madness
Enter name of the artist: The weekend
Enter year of the song: 2013
The song has been added!!
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option: 3
Songs in your database:
-----------------------
ID: 1
Song Name: Unutmamali
Song Genre: Pop
Album Nam: Aacayipsin
Artist Name: Tarkan
Year: 1994
Date: 22/10/2019
Time: 14:11
Page 5 of 8
ID: 2
Song Name: Huzurum Kalmadi
Song Genre: Arabesque
Album Nama: Huzurum Kalmadi
Artist Name: Ferdi Tayfur
Year: 1976
Date: 22/10/2019
Time: 15:15
ID: 3
Song Name: Time to say Goodbye
Song Genre: Classical Crossover
Album Name: Timeless
Artist Name: Andrea Bocelli and Sarah Brightman
Year: 1995
Date: 22/11/2019
Time: 15:18
ID: 4
Song Name: Huzurum Kalmadi
Song Genre: Arabesque
Album Name: Huzurum Kalmadi
Artist Name: Ferdi Tayfur
Year: 1976
Date: 22/10/2019
Time: 15:15
ID: 5
Song Name: The hills
Song Genre: Pop
Album Name: Beauty Behind the madness
Artist Name: The weekend
Year: 2013
Date: 18/10/2019
Time: 11:06
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option: 2
Enter the ID of the song you want to delete: 2
Page 6 of 8
Song with ID 2 has been deleted from your list!!!
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option: 4
---- Searching by ----
(1) song name
(2) artist name
(3) genre
Enter Search by option: 3
Enter Song Genre: pop
Results:
---------------------
ID: 1
Song Name: Unutmamali
Song Genre: Pop
Album Name: Aacayipsin
Artist Name: Tarkan
Year: 1994
Date: 22/10/2019
Time: 14:11
ID: 5
Song Name: The hills
Song Genre: Pop
Album Name: Beauty Behind the madness
Artist Name: The weekend
Year: 2013
Date: 18/10/2019
Time: 11:06
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option:4
Page 7 of 8
---- Searching by ----
(1) song name
(2) artist name
(3) genre
Enter Search by option: 2
Artist Name : katty
No song has this artist name!
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option:4
---- Searching by ----
(1) song name
(2) artist name
(3) genre
Enter Search by option:2
Artist Name : The weekend
Results:
---------------------
ID: 5
Song Name: The hills
Song Genre: pop
Album Name: Beauty Behind the madness
Artist Name: The weekend
Year: 2013
Date: 18/10/2019
Time: 11:06
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option:5
Page 8 of 8
Enter the names of songs for your playlist:
Enter (1) song name: The hills
Enter (2) song name: Unutmamali
Enter (3) song name: Time say goodbye
The playList cannot be created! Not all songs found!!!
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option:5
Enter the names of songs for your playlist:
Enter (1) song name: The hills
Enter (2) song name: Unutmamali
Enter (3) song name: Time to say Goodbye
The playList has been created and stored in the file: PlayList-1.txt!
----- MENU-----
1. Add Song
2. Delete Song
3. Print Songs
4. Search Songs
5. Create PlayList
6. Exit
Enter your option: 6
The SonMan.txt file has been updated successfully!!
Goodbye!!
```
