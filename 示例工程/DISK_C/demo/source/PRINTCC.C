#include <graphics.h>
#include <stdlib.h>
#include <stdio.h>
#include "printcc.h"
typedef unsigned char BYTE;

/***********************************************
Function:PrintCC
Description:输出一行(或竖排模式下的一列)汉字 
Input:
	x0,y0为字符串左上角的位置，str为纯汉字字符串，font为字体
	size为字体大小，tracking为字间距，color为字体颜色 
Return:void 
Remark:
	1.str必须为纯汉字字符串(可以包含空格)
	2.tracking是字间距，tracking=0时两个汉字紧邻而不是重合 
	3.font可选的值为
		FANGSONG(仿宋)
		HEI(黑体)
		KAI(楷体) 
		SONG(宋体)
		SONG_BOLD(粗宋体)
		TRADITIONAL(繁宋体)
		FANGSONG_VERT(竖排仿宋)
		HEI_VERT(竖排黑体)
		KAI_VERT(竖排楷体)
		SONG_VERT(竖排宋体)
		SONG_BOLD_VERT(竖排粗宋体)
		TRADITIONAL_VERT(竖排繁宋体)
	4.size可选值为12/16/24/32/48
	5.并不是每一种字体与字号的组合都有 
***********************************************/
void PrintCC(int x0,int y0,unsigned char str[],int font,int size,int tracking,int color)
{
	FILE *fpHZK=NULL;
	int vertical=0;//是否为纵向排版
	if(font>5)
	{
		vertical=1;
		font-=6;
	}
	//根据参数打开对应的字库文件
	//目前支持的字库列表(字体名称:支持的字体大小) 
	//     FANGSONG(仿宋):16,24,32,48
	//          HEI(黑体):16,24,32,48
	//          KAI(楷体):16,24,32,48
	//         SONG(宋体):12,16,24,32,48
	//  SONG_BOLD(粗宋体):16,32
	//TRADITIONAL(繁宋体):16
	if(font==FANGSONG)
	{
		if(size==16)
		{
			fpHZK=fopen(".\\font\\HZK16F","rb");
		}
		else if(size==24)
		{
			fpHZK=fopen(".\\font\\HZK24F","rb");
		}
		else if(size==32)
		{
			fpHZK=fopen(".\\font\\HZK32F","rb");
		}
		else if(size==48)
		{
			fpHZK=fopen(".\\font\\HZK48F","rb");
		}
	}
	else if(font==HEI)
	{
		if(size==16)
		{
			fpHZK=fopen(".\\font\\HZK16H","rb");
		}
		else if(size==24)
		{
			fpHZK=fopen(".\\font\\HZK24H","rb");
		}
		else if(size==32)
		{
			fpHZK=fopen(".\\font\\HZK32H","rb");
		}
		else if(size==48)
		{
			fpHZK=fopen(".\\font\\HZK48H","rb");
		}
	}
	else if(font==KAI)
	{
		if(size==16)
		{
			fpHZK=fopen(".\\font\\HZK16K","rb");
		}
		else if(size==24)
		{
			fpHZK=fopen(".\\font\\HZK24K","rb");
		}
		else if(size==32)
		{
			fpHZK=fopen(".\\font\\HZK32K","rb");
		}
		else if(size==48)
		{
			fpHZK=fopen(".\\font\\HZK48K","rb");
		}
	}
	else if(font==SONG)
	{
		if(size==12)
		{
			fpHZK=fopen(".\\font\\HZK12S","rb");
		}
		else if(size==16)
		{
			fpHZK=fopen(".\\font\\HZK16S","rb");
		}
		else if(size==24)
		{
			fpHZK=fopen(".\\font\\HZK24S","rb");
		}
		else if(size==32)
		{
			fpHZK=fopen(".\\font\\HZK32S","rb");
		}
		else if(size==48)
		{
			fpHZK=fopen(".\\font\\HZK48S","rb");
		}
	}
	else if(font==SONG_BOLD)
	{
		if(size==16)
		{
			fpHZK=fopen(".\\font\\HZK16S_B","rb");
		}
		else if(size==32)
		{
			fpHZK=fopen(".\\font\\HZK32S_B","rb");
		}
	}
	else if(font==TRADITIONAL)
	{
		if(size==16)
		{
			fpHZK=fopen(".\\font\\HZK16S_T","rb");
		}	
	}
	//判断指定字库文件是否存在，即是否打开成功
	if(fpHZK!=NULL)
	{
		int i,x,y;
		int Q,W;//当前汉字的区位码
		int BytePerCC=(size<=16?16:size)*size/8;//储存每个汉字所用字节数
		long offset;//当前汉字在字库文件中的位置偏移量
		BYTE fontMatrix[288];//字体点阵信息
		//遍历汉字字符串，每次处理两个字节
		for(i=0;str[i];i+=2)
		{
			//特殊判断空格 
			if(str[i]==' '&&str[i+1]==' ')
			{
				if(vertical)
				{
					y0+=size;
					y0+=tracking;
				}
				else
				{
					x0+=size;
					x0+=tracking;
				}
				continue;
			}
			//当前汉字的区位码
			Q=str[i]-0xA0; 
			W=str[i+1]-0xA0;
			//区位码从1开始标号，此处转换为从0开始 
			Q--,W--;
			//根据每个汉字所用字节数确定偏移量 
			offset=(long)(Q*94+W)*BytePerCC;
			//读取汉字字模，保存到fontMatrix中 
			fseek(fpHZK,offset,SEEK_SET);
			fread(fontMatrix,1,BytePerCC,fpHZK);
			//在屏幕上输出汉字 
			for(y=0;y<size;y++)
			{
				for(x=0;x<size;x++)
				{
					//当前像素点在fontMatrix中的位号
					//注意12*12汉字会被保存在16*12点阵中 
					int pos=(size<=16?16:size)*y+x;
					//判定出界 
					if(fontMatrix[pos/8]&(128>>(pos%8)))
					if(0<=x0+x&&x0+x<640&&0<=y0+y&&y0+y<480)
					{
						putpixel(x0+x,y0+y,color);
					}
				}
			}
			if(vertical)
			{
				y0+=size;
				//竖排文字向下移字间距的宽度 
				y0+=tracking;
			}
			else
			{
				x0+=size;
				//横排文字向右移字间距的宽度 
				x0+=tracking;
			}
		}
		fclose(fpHZK); 
	}
	return;
}

/***********************************************
Function:PrintText 
Description:输出一行文本
Input:
	x0,y0为字符串左上角的位置，str为文本字符串，font为字体
	size为字体大小，tracking为字间距，color为字体颜色 
Return:void 
Remark:
	1.此函数可以输出中英混排的字符串 
	2.tracking是汉字字间距，ASCII字符字间距为tracking/2
	3.font可选的值为
		FANGSONG(仿宋)
		HEI(黑体)
		KAI(楷体)
		SONG(宋体)
		SONG_BOLD(粗宋体)
		TRADITIONAL(繁宋体)
	4.size可选值为12/16
	5.12号字只可选择宋体，16号字六种字体均可选择
	6.ASCII字符的字体样式不随font的取值而改变
	7.为了排版的整体效果，12号英文整体下移1px，16号英文整体下移2px
***********************************************/
void PrintText(int x0,int y0,unsigned char str[],int font,int size,int tracking,int color)
{
	FILE *fpASC=NULL;
	FILE *fpHZK=NULL;
	//根据参数打开对应的字库文件
	//目前支持的字库列表(字体大小:支持的字体名称)
	//12:ASC12,SONG(宋体)
	//16:ASC16,FANGSONG(仿宋),HEI(黑体),KAI(楷体),SONG(宋体),SONG_BOLD(粗宋体),TRADITIONAL(繁宋体)
	if(size==12&&font==SONG)
	{
		fpASC=fopen(".\\font\\ASC12","rb");
		fpHZK=fopen(".\\font\\HZK12S","rb");
	}
	else if(size==16)
	{
		fpASC=fopen(".\\font\\ASC16","rb");
		if(font==FANGSONG)
		{
			fpHZK=fopen(".\\font\\HZK16F","rb");
		}
		else if(font==HEI)
		{
			fpHZK=fopen(".\\font\\HZK16H","rb");
		}
		else if(font==KAI)
		{
			fpHZK=fopen(".\\font\\HZK16K","rb");
		}
		else if(font==SONG)
		{
			fpHZK=fopen(".\\font\\HZK16S","rb");
		}
		else if(font==SONG_BOLD)
		{
			fpHZK=fopen(".\\font\\HZK16S_B","rb");
		}
		else if(font==TRADITIONAL)
		{
			fpHZK=fopen(".\\font\\HZK16S_T","rb");	
		}
	}
	if(fpASC!=NULL&&fpHZK!=NULL)
	{
		int i,x,y;
		int Q,W;//当前汉字的区位码
		int BytePerCC=2*size;//储存每个汉字所用字节数
		int BytePerChar=size;//储存每个ASCII字符所用字节数 
		long offset;//当前字符在字库文件中的位置偏移量
		BYTE fontMatrix[32];//字体点阵信息
		for(i=0;str[i];i++)
		{
			int isChar;//当前字符是ASCII字符则值为1 
			int width,height;
			//每个字符的宽高，其中高必为size，宽可能为size或者size/2
			height=size;
			//根据字符种类不同(汉字/ASCII字符)确定相应变量
			//小于128的是ASCII字符 
			if(str[i]<128)
			{
				isChar=1;
				//ASC12库中没有控制字符，从偏移量中减去32个字符的大小 
				offset=(long)str[i]*BytePerChar-32*12*(size==12);
				fseek(fpASC,offset,SEEK_SET);
				fread(fontMatrix,1,BytePerChar,fpASC);
				width=size/2;
			}
			//否则为汉字 
			else
			{
				isChar=0;
				Q=str[i]-0xA0;
				W=str[++i]-0xA0;//汉字要读两个字符 
				Q--,W--;
				offset=(long)(Q*94+W)*BytePerCC;
				fseek(fpHZK,offset,SEEK_SET);
				fread(fontMatrix,1,BytePerCC,fpHZK);
				width=size;
			}
			for(y=0;y<height;y++)
			{
				for(x=0;x<width;x++)
				{
					int pos=(isChar?8:16)*y+x;
					//判定出界
					if(fontMatrix[pos/8]&(128>>(pos%8)))
					if(0<=x0+x&&x0+x<640&&0<=y0+y&&y0+y<480)
					{
						//为了中英混排的整体效果，将ASCII字符向下平移1px或2px
						if(!isChar)
							putpixel(x0+x,y0+y,color);
						else if(isChar&&size==12)
							putpixel(x0+x,y0+y+1,color);
						else if(isChar&&size==16)
							putpixel(x0+x,y0+y+2,color);
					}
				}
			}
			//ASCII字符宽度为size的一半 
			if(isChar)
			{
				x0+=size/2;
				x0+=tracking/2;
			}
			else
			{
				x0+=size;
				x0+=tracking;
			}
		}
		fclose(fpASC); 
		fclose(fpHZK); 
	}
	return;
}
