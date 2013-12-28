#define _CRT_SECURE_NO_WARNINGS 1
#include "stdio.h"
#include "string.h"
#include <stdlib.h>
typedef struct Song{
	char name[31];
	long double quality;
	int order;
}Song;
void swapSong(struct Song* song1, struct Song* song2){
    char stringBuffer[31];
    long double qualityBuffer;
    int orderBuffer;
    strcpy(stringBuffer,song1->name);
    qualityBuffer=song1->quality;
    orderBuffer=song1->order;
    strcpy(song1->name,song2->name);
    song1->quality=song2->quality;
    song1->order=song2->order;
    strcpy(song2->name,stringBuffer);
    song2->quality=qualityBuffer;
    song2->order=orderBuffer;
}
int sortAlbumByQuality(struct Song** theAlbum,int length){//sort album by the song quality
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
    for(i=1;i<length;i++){
		for(k=i;(k>0)&&(theAlbum[k-1]->quality>theAlbum[k]->quality);k--){
			swapSong(theAlbum[k-1],theAlbum[k]);
		}
    }
    return 0;
}
int sortAlbumByOrder(struct Song** theAlbum, int length){//after sorting by song Quality, put the song with higher order after the song with lower order (ascending order for songs with same quality)
    int songNumber=0;//pointer for going through list of the songs
    int songPointer=0;//pointer for going through list of same quality songs
    long double qualityLevel;//specify the quality of song group
    int memberNumber=0;//Number of members in a song group with same quality
    int i,k;
    while (songNumber<length){
        qualityLevel=theAlbum[songNumber]->quality;//change to while loop for better management
		songPointer=songNumber;
		while((songPointer<length)&&(theAlbum[songPointer]->quality==qualityLevel)){
			songPointer++;
			memberNumber++;
		}
		if(memberNumber==1){}
		else{
			for(i=1;i<songNumber+memberNumber;i++){
				for(k=i;(k>songNumber)&&(theAlbum[k-1]->order>theAlbum[k]->order);k--){
					swapSong(theAlbum[k-1],theAlbum[k]);
				}
			}
		}
		/*printf("memberNumber: %d\n",memberNumber);*/
		songNumber+=memberNumber;
		memberNumber=0;
    }
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
        theSong->order=albumLength-songNumber;
        album[songNumber]=theSong;
    }
    //for testing
    //for(songNumber=0;(songNumber<albumLength)&(album[songNumber]!= NULL);songNumber++){
    //    printf("Song name: %Lf \n",album[songNumber]->quality);
    //}
    //for testing
    sortAlbumByQuality(album,albumLength);
	//for testing
	/*printf("Songs after sorting by quality:\n");
	for(songNumber=0;songNumber<albumLength;songNumber++){
		printf("Song Name: %s; Song quality: %Lf;Song order: %d\n",album[songNumber]->name,album[songNumber]->quality,album[songNumber]->order);
	}*/
    sortAlbumByOrder(album, albumLength);
	//for testing
	/*printf("Songs after sorting by order:\n");
	for(songNumber=0;songNumber<albumLength;songNumber++){
		printf("Song Name: %s; Song quality: %Lf;Song order: %d\n",album[songNumber]->name,album[songNumber]->quality,album[songNumber]->order);
	}*/
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

