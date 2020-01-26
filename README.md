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

