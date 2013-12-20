#include "stdio.h"
#include "string.h"
#include <stdlib.h>
typedef struct Song{//the Song structure
	char name[31];
	long double quality;
}Song;
void swapSong(struct Song* song1, struct Song* song2){//swap between 2 songs
    char stringBuffer[31];
    long double qualityBuffer;
    strcpy(stringBuffer,song1->name);
    qualityBuffer=song1->quality;
    strcpy(song1->name,song2->name);
    song1->quality=song2->quality;
    strcpy(song2->name,stringBuffer);
    song2->quality=qualityBuffer;
}
int sortAlbum(struct Song** theAlbum,int length){//receive the pointer to the album as input, sort the album be ascending quality
    int i,k;
    if(length==1){
	return 0;
    }
    if(length==2){
	if(theAlbum[0]->quality>theAlbum[1]->quality){
	    swapSong(theAlbum[0],theAlbum[1]);
	}
	return 0;
    }
    for(i=2;i<length;i++){
        for(k=i;(theAlbum[k-1]->quality>theAlbum[k]->quality)&(k>1);k-- ){
            swapSong(theAlbum[k-1],theAlbum[k]);
        }
    }
    return 0;
}
int main(){
    struct Song *album[50000];
    struct Song *theSong;
    int albumLength;
    int selectedNumber;
    int songNumber=0;
    char songName[30];
    char * temp_songName;
    long int listenTime;
    long double songQuality;
    char nextLines[45];
    char firstLine[15];
    fgets(firstLine,15,stdin);
    if(firstLine==NULL){
	fprintf(stderr,"No input.\n");
	return 1;
    }
    albumLength=atoi(strtok(firstLine," "));
    if(albumLength==0){
	fprintf(stderr,"Wrong input!\n");
	return 1;
    }
    selectedNumber=atoi(strtok(NULL, " "));
    for (songNumber=0;songNumber<albumLength;songNumber++){
        fgets(nextLines, 45, stdin);
	if(nextLines==NULL){
	    fprintf(stderr,"Not enough input songs.\n");
	    return 1;
	}
        listenTime=atol(strtok(nextLines," ,\n"));
        temp_songName= strtok( NULL ," ,\n");
	if(temp_songName==NULL){
	    fprintf(stderr,"Not enough input parameters!\n");
	    return 1;
	}
        strcpy(songName,temp_songName);
        songQuality = (listenTime*1.0)/(albumLength-songNumber);
        theSong = (Song*)malloc(sizeof(Song));
        strcpy(theSong->name,songName);
        theSong->quality=songQuality;
        album[songNumber]=theSong;
    }
    //for testing
    //for(songNumber=0;(songNumber<albumLength)&(album[songNumber]!= NULL);songNumber++){
    //    printf("Song name: %Lf \n",album[songNumber]->quality);
    //}
    //for testing
    sortAlbum(album,albumLength);
    if(selectedNumber==0){
	getchar();
	return 0;
    }
    for (songNumber=albumLength-1;songNumber>=(albumLength -selectedNumber);songNumber--){
        fprintf(stdout,"%s\n",album[songNumber]->name);
    }
    for (songNumber=0;songNumber<albumLength;songNumber++){
        free(album[songNumber]);
    }
 
    getchar();
    return 0;
}
