#include <graphics.h>
#include "printcc.h"

int main()
{
	int gdriver=VGA,gmode=VGAHI;
	initgraph(&gdriver,&gmode,"C:\\BORLANDC\\BGI");
	PrintCC(5,5,"宋体十二。",SONG,12,2,WHITE);
	PrintCC(5,21,"宋体十六。",SONG,16,2,WHITE);
	PrintCC(5,41,"宋体二十四。",SONG,24,2,WHITE);
	PrintCC(5,69,"宋体三十二。",SONG,32,2,WHITE);
	PrintCC(5,105,"宋体四十八。",SONG,48,2,WHITE);
	PrintCC(5,136+21,"黑体十六。",HEI,16,2,WHITE);
	PrintCC(5,136+41,"黑体二十四。",HEI,24,2,WHITE);
	PrintCC(5,136+69,"黑体三十二。",HEI,32,2,WHITE);
	PrintCC(5,136+105,"黑体四十八。",HEI,48,2,WHITE);
	PrintCC(5,272+21,"楷体十六。",KAI,16,2,WHITE);
	PrintCC(5,272+41,"楷体二十四。",KAI,24,2,WHITE);
	PrintCC(5,272+69,"楷体三十二。",KAI,32,2,WHITE);
	PrintCC(5,272+105,"楷体四十八。",KAI,48,2,WHITE);
	PrintCC(305,21,"仿宋十六。",FANGSONG,16,2,WHITE);
	PrintCC(305,41,"仿宋二十四。",FANGSONG,24,2,WHITE);
	PrintCC(305,69,"仿宋三十二。",FANGSONG,32,2,WHITE);
	PrintCC(305,105,"仿宋四十八。",FANGSONG,48,2,WHITE);
	PrintCC(305,136+31,"粗宋体十六。",SONG_BOLD,16,2,WHITE);
	PrintCC(305,136+51,"粗宋体三十二。",SONG_BOLD,32,2,WHITE);
	PrintCC(305,136+97,"这是繁宋体十六。",TRADITIONAL,16,2,WHITE);
/*	PrintCC(5,5,"含中文标点",SONG,24,2,WHITE);
	PrintCC(5,33,"。，？！；：“”‘’（）【】《》——……￥",SONG,24,2,WHITE);
	PrintCC(5,80,"纵向排版",SONG_VERT,16,2,WHITE);
	PrintCC(35,80,"修改颜色和间距",SONG_VERT,16,10,RED);
	PrintText(100,100,"Hello, this is 12px字号中英混排。",SONG,12,2,WHITE); 
	PrintText(100,116,"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz",SONG,12,2,WHITE); 
	PrintText(100,132,",.?!;:""''()[]{}@#$%^&+-/*=",SONG,12,2,WHITE); 
	PrintText(100,160,"Hello, this is 16px字号中英混排。",SONG,16,2,WHITE); 
	PrintText(100,180,"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz",SONG,16,2,WHITE); 
	PrintText(100,200,",.?!;:""''()[]{}@#$%^&+-/*=",SONG,16,2,WHITE);*/
	delay(5000);
	closegraph();
	return 0;
}
