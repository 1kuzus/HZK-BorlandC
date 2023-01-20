#ifndef _PRINTCC_H_ 
#define _PRINTCC_H_

#define FANGSONG 0
#define HEI 1
#define KAI 2
#define SONG 3
#define SONG_BOLD 4
#define TRADITIONAL 5
#define FANGSONG_VERT 6
#define HEI_VERT 7
#define KAI_VERT 8
#define SONG_VERT 9
#define SONG_BOLD_VERT 10
#define TRADITIONAL_VERT 11

void PrintCC(int x0,int y0,unsigned char str[],int font,int size,int tracking,int color);
void PrintText(int x0,int y0,unsigned char str[],int font,int size,int tracking,int color);

#endif 
