#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

#define FALSE 0;
#define TRUE 1;

struct dateTime //Creating a structure for the date and time to make storing the date and time from the system easier.
{
    int day;
    int month;
    int year;
    int hour;
    int min;
};
typedef struct dateTime D_T; //renamed my struct definition call D_T for easier usage in the program.
struct Node //This is the struct definition for the node that will store the song details.
{
    int ID;
    char songName[50];
    char songGenre[50];
    char albumName[50];
    char artistName[50];
    int yearReleased;
    D_T date;
    struct Node *next;
};
struct ListRecord//Using a list struct here so that I can keep track of the size of my list and also the head and tail.
{
    struct Node *head;
    struct Node *tail;
    int size;
};
typedef struct ListRecord *List;

List CreateList();//function to declare lists
void MakeEmptyList(List);//function to initialize lists to empty
void DisplayList(List);
List initialiseSongs(void);
List addSong(List,D_T,char [],char [],char [],char [],int);
List deleteSong(List, int);
void removeSpaces(char *);//This remove spaces function will help me make better string comparisons by removing all spaces from any given strings.
char * ConverttoLower(char *);//This function will help convert the strings to lowercase that way it makes for even more efficient string comparisons.
void searchSongs(List);
void createPlaylist(List,char[],char[],char[],int *);
void Overwrite(List);

int main()
{
    time_t ti = time(NULL);
    struct tm t = *localtime(&ti);
    List myList;
    int option,exit,yearReleased,uID,PiD;//uID stands for unique ID and is used when deleting a song.PiD stands for playlist ID which we need for the createPlaylsit function.
    char songName[50],songGenre[50],album[50],artist[50];
    char song1[50],song2[50],song3[50];//these song name strings are to be taken by the createPlaylist function.
    D_T date;//To help store date from the system.
    PiD=0;//Whenever playlist is created this value shall be incremented that way number of playlists is known!
    myList = initialiseSongs();

    printf("The SongMan.txt file has been loaded successfully\n\n");
    exit = FALSE;
    while(!exit)
    {
        fflush(stdin);
        printf("----- MENU -----\n");
        printf("1. Add song\n");
        printf("2. Delete song\n");
        printf("3. Print songs\n");
        printf("4. Search songs\n");
        printf("5. Create PlayList\n");
        printf("6. Exit\n\n");
        printf("Enter your option: ");
        scanf("%d",&option);

        switch (option)
        {
            case 1:
                fflush(stdin);
                printf("Enter name of the song: ");
                gets(songName);
                fflush(stdin);
                printf("Enter genre of the song: ");
                gets(songGenre);
                fflush(stdin);
                printf("Enter name of the album: ");
                gets(album);
                fflush(stdin);
                printf("Enter name of the artist: ");
                gets(artist);
                printf("Enter year of the song: ");
                scanf("%d",&yearReleased);
                date.day = t.tm_mday;
                date.month = t.tm_mon+1;
                date.year = t.tm_year+1900;
                date.hour = t.tm_hour;
                date.min = t.tm_min;
                myList = addSong(myList,date,songName,songGenre,album,artist,yearReleased);
                printf("The song has been added!!\n\n");
                break;
            case 2:
                fflush(stdin);
                printf("Enter the ID of the song you want to delete: ");
                scanf("%d",&uID);
                myList = deleteSong(myList,uID);
                break;
            case 3:
                DisplayList(myList);
                break;
            case 4:
                searchSongs(myList);
                break;
            case 5:
                fflush(stdin);
                printf("\n\nEnter the names of songs for your playlist:\n");
                printf("Enter (1) song name: ");
                gets(song1);
                printf("Enter (2) song name: ");
                gets(song2);
                printf("Enter (3) song name: ");
                gets(song3);

                createPlaylist(myList,song1,song2,song3,&PiD);
                break;
            case 6:
                exit = TRUE;
                Overwrite(myList);
                printf("Goodbye!!\n\n");
                break;
            default:
                printf("Option key not recognized!!\n");
                break;
        }
    }

    return 0;
}
List CreateList()
{
    List l;

    l = (struct ListRecord *) malloc(sizeof(struct ListRecord));
    if (l == NULL)
        printf("Out of memory!\n");
    else
        MakeEmptyList(l);

    return l;
}
void MakeEmptyList(List l)
{
    l->head = (struct Node *) malloc(sizeof(struct Node));
    if (l->head == NULL)
        printf("Out of memory!\n");

    l->head->next = NULL;
    l->tail = l->head;
    l->size = 0;
}
void DisplayList(List l)
{
    struct Node *p;

    p = l->head->next;
    printf("\nSongs in your database:\n");
    printf("-----------------------\n");
    while (p != NULL)
    {
        printf("ID: %d\n",p->ID);
        printf("Song Name: %s\n",p->songName);
        printf("Song Genre: %s\n",p->songGenre);
        printf("Album Name: %s\n",p->albumName);
        printf("Artist Name: %s\n",p->artistName);
        printf("Year: %d\n",p->yearReleased);
        printf("Date: %2d/%2d/%4d\n",p->date.day,p->date.month,p->date.year);
        printf("Time: %d:%d",p->date.hour,p->date.min);
        printf("\n\n");
        p = p->next;
    }
    printf("\n");
}
List initialiseSongs(void)
{
    char filename1[20];
    char line[350];//When iterating through the textfile this shall help store one line worth of one song's information in the file.
    // 350 is the maximum characters that a text file can show on one line.
    FILE *inFile;
    char dateTime[20];//I'll use this character array to read the date and time from within the file as one string.
    int SIZE=0,i=0;
    // SIZE -- This variable will be used to record number of songs in the textfile
    // so that during copying to List we can exit the loop once the whole file is checked. i will help with loop iteration.
    printf("Enter name of the file to read from: ");
    scanf("%s",filename1);

    inFile = fopen(filename1,"r");
    while(inFile==NULL)//Checking to see if the file indeed exists and was read from.
    {
        fflush(stdin);
        printf("Error creating file!!\n");//Then asks the user to type the filename again correctly.
        printf("Enter filename correctly please: ");
        scanf("%s",filename1);
        inFile = fopen(filename1,"r");
    }
    while(fgets(line,350,inFile))
        SIZE++;//This helps iterate through the file to find out how many songs we will be adding to our list.

    fseek(inFile,0L,SEEK_SET);//This command will set the cursor back to the start of the file so we can now read the data into our linked list.
    List temp = CreateList();

    while((fgets(line,350,inFile))&& i<SIZE)
    {
        struct Node *songNode;
        songNode = malloc(sizeof(struct Node));
        songNode->next = NULL;
        //initialize a new song node to be added to the list as we iterate through the file

        sscanf(line,"%d;%[^;];%[^;];%[^;];%[^;];%d;%[^\n]",&songNode->ID,songNode->songName,songNode->songGenre,songNode->albumName,songNode->artistName,&songNode->yearReleased,
                dateTime);
        sscanf(dateTime,"%2d/%2d/%4d %2d:%2d",&songNode->date.day,&songNode->date.month,&songNode->date.year,&songNode->date.hour,&songNode->date.min);
        //Since I created a separate structure for the date and time, after reading the date and time from the files as one string,
        // I then again read it so that I can now insert the information into the node via it's struct definition.
        temp->tail->next = songNode;
        temp->tail = songNode;
        temp->size++;
        i++;
    }

    fclose(inFile);
    return temp;
}
List addSong(List l,D_T Date,char Name[],char Genre[],char Album[],char Artist[],int YearReleased)
{
    //new songNode declaration is needed to create node for new song
    struct Node *songNode = malloc(sizeof(struct Node));
    songNode->next = NULL;
    //fill Node information with data from user.
    songNode->ID = l->tail->ID + 1;
    strcpy(songNode->songName,Name);
    strcpy(songNode->songGenre,Genre);
    strcpy(songNode->albumName,Album);
    strcpy(songNode->artistName,Artist);
    songNode->yearReleased = YearReleased;
    songNode->date.day = Date.day;
    songNode->date.month = Date.month;
    songNode->date.year = Date.year;
    songNode->date.hour = Date.hour;
    songNode->date.min = Date.min;

    l->tail->next = songNode;
    l->tail = songNode;
    l->size++;

    return l;
}
List deleteSong(List l, int uID)
{
    struct Node *p;
    p=l->head->next;
    while((p!=NULL) && (p->next->ID!=uID))
        p=p->next;

    if(p->next == NULL)
        printf("Song with specified ID not in list!!!\n\n");
    else
    {
        struct Node *removeSong;
        removeSong = p->next;
        p->next = p->next->next;
        free(removeSong);
        l->size--;
        if(l->size == 0)
            l->tail = l->head;
        printf("Song with ID %d has been deleted from your list!!!\n\n",uID);
    }
    return l;
}
void removeSpaces(char *str)
{
    // To keep track of non-space character count
    int count = 0;
    // If current character is not space, then place it at index 'count' then increment index for count.
    for (int i = 0; str[i]; i++)
    {
        if (str[i] != ' ')
        {
            str[count] = str[i];
            count++;
        }
    }
    str[count] = '\0';
}
char * ConverttoLower(char *str)
{
    int i = 0;
    while(str[i]){
        str[i] = (char) tolower(str[i]);
        i++;
    }
    return str;
}
void searchSongs(List l)
{
    int option,notFound;
    notFound=0;//This sentinel value will help me keep track of cases where the search parameter is not within my list.
    char search[50],temp[50];//Using a character array to help me store the strings of data that need to be searched for.
    //The temp array will be used to store the string from the list that we are to compare with
    struct Node *p;
    p=l->head->next;
    fflush(stdin);
    printf("---- Searching by ----\n");
    printf("(1) song name\n");
    printf("(2) artist name\n");
    printf("(3) genre\n");
    printf("Enter search by option: ");
    scanf("%d", &option);

    switch (option)
    {
        case 1:
            fflush(stdin);
            printf("Enter song name:");
            gets(search);
            printf("Results:\n ");
            printf("---------------------\n");
            while(p!=NULL)
            {
                strcpy(temp,p->songName);
                removeSpaces(search);
                removeSpaces(temp);
                if(strncmp(ConverttoLower(search),ConverttoLower(temp),strlen(search))==0)
                {
                    notFound++;
                    printf("ID: %d\n",p->ID);
                    printf("Song Name: %s\n",p->songName);
                    printf("Song Genre: %s\n",p->songGenre);
                    printf("Album Name: %s\n",p->albumName);
                    printf("Artist Name: %s\n",p->artistName);
                    printf("Year: %d\n",p->yearReleased);
                    printf("Date: %2d/%2d/%4d\n",p->date.day,p->date.month,p->date.year);
                    printf("Time: %d:%d",p->date.hour,p->date.min);
                    printf("\n\n");
                }
                p = p->next;
            }
            if(notFound==0)
                printf("This song does not exist in your list!!\n\n");
            break;
        case 2:
            fflush(stdin);
            printf("Enter Artist name: ");
            gets(search);
            printf("Results:\n ");
            printf("---------------------\n");
            while(p!=NULL)
            {
                strcpy(temp,p->artistName);
                removeSpaces(search);
                removeSpaces(temp);
                if(strncmp(ConverttoLower(search),ConverttoLower(temp),strlen(search))==0)
                {
                    notFound++;
                    printf("ID: %d\n",p->ID);
                    printf("Song Name: %s\n",p->songName);
                    printf("Song Genre: %s\n",p->songGenre);
                    printf("Album Name: %s\n",p->albumName);
                    printf("Artist Name: %s\n",p->artistName);
                    printf("Year: %d\n",p->yearReleased);
                    printf("Date: %2d/%2d/%4d\n",p->date.day,p->date.month,p->date.year);
                    printf("Time: %d:%d",p->date.hour,p->date.min);
                    printf("\n\n");
                }
                p = p->next;
            }
            if(notFound==0)
                printf("No artist in your list has this name!!\n\n");
            break;
        case 3:
            fflush(stdin);
            printf("Enter genre:");
            gets(search);
            printf("Results:\n ");
            printf("---------------------\n");
            while(p != NULL)
            {
                strcpy(temp,p->songGenre);
                removeSpaces(search);
                removeSpaces(temp);
                if(strncmp(ConverttoLower(search),ConverttoLower(temp),strlen(search))==0)
                {
                    notFound++;
                    printf("ID: %d\n",p->ID);
                    printf("Song Name: %s\n",p->songName);
                    printf("Song Genre: %s\n",p->songGenre);
                    printf("Album Name: %s\n",p->albumName);
                    printf("Artist Name: %s\n",p->artistName);
                    printf("Year: %d\n",p->yearReleased);
                    printf("Date: %2d/%2d/%4d\n",p->date.day,p->date.month,p->date.year);
                    printf("Time: %d:%d",p->date.hour,p->date.min);
                    printf("\n\n");
                }
                p = p->next;
            }
            if(notFound==0)
                printf("No song in your list is of this genre!!\n\n");
            break;
        default:
            printf("The option you've entered is wrong!! Please try again!!\n\n");
    }
}
void createPlaylist(List l,char song1[],char song2[],char song3[],int *PiD)
{
    List Playlist;
    Playlist = CreateList();
    char temp[50];//temp char string once again to store string to be compared from within list information.
    int notFound = 0;
    struct Node *p;
    p=l->head->next;
    while(p!=NULL)
    {
        strcpy(temp,p->songName);
        removeSpaces(temp);
        removeSpaces(song1);
        removeSpaces(song2);
        removeSpaces(song3);
        if((strncmp(ConverttoLower(song1), ConverttoLower(temp), strlen(song1)) == 0)
                        || (strncmp(ConverttoLower(song2), ConverttoLower(temp), strlen(song2)) == 0)
                                    || (strncmp(ConverttoLower(song3), ConverttoLower(temp), strlen(song3)) == 0))
        {
            struct Node *songNode = malloc(sizeof(struct Node));
            songNode->next = NULL;
            songNode->ID = p->ID;
            strcpy(songNode->songName,p->songName);
            strcpy(songNode->songGenre,p->songGenre);
            strcpy(songNode->albumName,p->albumName);
            strcpy(songNode->artistName,p->artistName);
            songNode->yearReleased = p->yearReleased;
            songNode->date = p->date;
            Playlist->tail->next=songNode;
            Playlist->tail=songNode;
            Playlist->size++;
            notFound++;
        }
        p=p->next;
    }
    if(notFound<3)
    {
        printf( "The playList cannot be created! Not all songs found!!!\n\n");
        free(Playlist);//Playlist needs 3 songs so in the event that only 2 songs can be located rather than have the created list exist,
        //And take space in memory we free it for now. And when the user  tries to create a playlist with songs within the list we create a new playlist.
    }
    else
    {
        FILE *outFile;
        char filename[20];//strings to store filename and another to store the conversion of the playlist ID from int to char.
        *PiD = *PiD + 1;
        //This next piece of code helps me convert the Playlist ID to string so I can add it to the filename.
        sprintf(filename,"Playlist-%d.txt",*PiD);
        outFile = fopen(filename,"w");
        if(outFile==NULL)
        {
            printf("Error creating file!");
            printf("Check code again!!");
            exit(1);
        }
        else
        {
            struct Node *k;
            k=Playlist->head->next;
            while(k!=NULL)
            {
                fprintf(outFile,"%d;%s;%s;%s;%s;%d;%2d/%2d/%4d %d:%d\n",k->ID,k->songName,k->songGenre,k->albumName,k->artistName,k->yearReleased,
                        k->date.day,k->date.month,k->date.year,k->date.hour,k->date.min);
                k=k->next;
            }
        }
        fclose(outFile);
        printf("The playList has been created and stored in the file: %s\n\n",filename);
    }
}
void Overwrite(List l)
{
    FILE *outFile;
    char filename[20];
    fflush(stdin);
    printf("\nEnter name of the file to overwrite: ");
    gets(filename);

    outFile = fopen(filename,"w");
    while(outFile==NULL)//Checking to see if the file indeed exists and was read from.
    {
        fflush(stdin);
        printf("Error creating file!!\n");//Then asks the user to type the filename again correctly.
        printf("Enter filename correctly please: ");
        scanf("%s",filename);
        outFile = fopen(filename,"r");
    }
    struct Node *p;
    p=l->head->next;
    while(p!=NULL)
    {
        fprintf(outFile,"%d;%s;%s;%s;%s;%d;%d/%d/%d %d:%d\n",p->ID,p->songName,p->songGenre,p->albumName,p->artistName,p->yearReleased,
        p->date.day,p->date.month,p->date.year,p->date.hour,p->date.min);
        p=p->next;
    }
    fclose(outFile);
    printf("\nThe %s file has been updated successfully!!\n\n",filename);
}
