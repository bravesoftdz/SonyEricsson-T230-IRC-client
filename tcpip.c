// *******************************************************
//
// NAME:    Simple IRC Client
// PROJECT: IRC in Mophun
// DATE:    2004-10-20
// BY:      Ilya
// 
// *******************************************************
#include <vstream.h> // ��� �������
#include <stdio.h>   // ��� Fopen � �.�...
#include <stdlib.h>  // 

#include <string.h>  // ��� ������ �� ��������. strcat � �.�...

#include <vmgputil.h> // Waitkey
#include "res.h" // ��� ������ ��������
#include <ctype.h>

	char lines[100][21];
	int linenum=0;

VMGPFONT g_MainFont =
{
    MAINFONT + MAINFONT_CHARTBLSIZE,
    MAINFONT,
	MAINFONT_BPP,
	MAINFONT_WIDTH,
	MAINFONT_HEIGHT,
	MAINFONT_PALINDEX
};

typedef struct
{
	char str[40];
}
CONSOLELINE;

static CONSOLELINE consoleline[50];

static char *key_map[] = 
{" ",
",.!?@$%1",
"abc2ABC2",
"def3DEF3",
"ghi4GHI4",
"jkl5JKL5",
"mno6MNO6",
"pqrs7PQRS7",
"tuv8TUV8",
"wxyz9WXYZ9"
};

void consoleInit(void)
{	
    
    vSetActiveFont(&g_MainFont);
	vSetForeColor(VMGP_WHITE);
    vClearScreen(40);
}

// ���������� ������
void consoleRender(void)
{
	int i;
	vClearScreen(40);
	vSetForeColor(255);
	for(i=0;i<10;i++)
		vPrint(MODE_TRANS,0,i*8,consoleline[i].str);
	vFlipScreen(1);
	
}

// ���������� 9 ����� �� 10 � ������ �����
// ����� �������� ����� ������
void consolePrint(char *_str)
{
  int i,x;
  for(i=0;i<8;i++)
    vStrCpy(consoleline[i].str,consoleline[i+1].str);
  vStrCpy(consoleline[8].str,_str);

//  for (x=0;x<20;x++) lines[linenum][x]=0;  
  for (x=0;x<vStrLen(_str);x++)
  {
	  lines[linenum][x]=_str[x];
  }
 // lines[linenum][20]=0;
	linenum++;
  
  consoleRender();
}

// ���� ������... Enter ��� �� ���������. 
// ����� � ��������� ������
void consolePrint2(char *_str)
{
  int i,x;
  vStrCpy(consoleline[9].str,_str);

 // for (x=0;x<20;x++) lines[linenum][x]=0;
 // for (x=0;x<vStrLen(_str)-1;x++)
 // {
//	  lines[linenum][x]=_str[x];
 // }
//  lines[linenum][20]=0;
//  linenum++;
  consoleRender();
  
}

// ����� �� ����� ��� ������� �� Enter
void consolePrint3(char *_str)
{
  int i,x;
  for(i=0;i<10;i++)
    vStrCpy(consoleline[i].str,consoleline[i+1].str);
  vStrCpy(consoleline[9].str,_str);
  
 // for (x=0;x<20;x++) lines[linenum][x]=0;
  for (x=0;x<vStrLen(_str);x++)
  {
	  lines[linenum][x]=_str[x]; 
  }
//  lines[linenum][20]=0;
  linenum++;
 
  consoleRender();
}

// *************************************************
// ADRESS TO SERVER
// *************************************************
#define ip_adress "irc.wenet.ru"//  irc.wenet.ru
//#define _ip_adress "localhost"
#define localhost "localhost" 
//#define FILENAME	"testfile.txt"

// *************************************************
// test                                           //
// *************************************************
void chat_start(void)
{

	int f_w=8;
	int f_h=5;

	char str[150];
	char *str2;
	char str3[50];
	char str4[50]; 
	char str5[50];
	char *str12,*word,*tmp;
	char buf[256], buf2[256], temp[100],tmp2[20];
	// BUF ��� 512
	
	int i;
	int delay=1;

	int readyFlags;
//	FILE *out;

	int num;
	uint32_t stream,stream2;
	int res;
	unsigned char tkn;
	int lastsend,time;
	int quit;
	unsigned char keys;
	int data_to_send;
	int	iTem;

	int x,y, xxx;

	uint32_t key,key2;
	char p_key=0;
	char keys2[50],mmm[50];
	int      keyind;

	int *addr;

	int port=6667;
	char nick[30], username[30], realname[30], channel[30];
	char name[50];
	int *kkk;
	int timer = 0;
	
	for (keyind=0;keyind<sizeof(keys2);keyind++)
	{
		keys2[keyind]=0;
		mmm[keyind]=0;
	}
	keyind=0;
	x=0;
	y=0;

	// CONNECT
	
	consolePrint("CONNECTING TO");
	consolePrint(ip_adress);
	

	// ������ ����� �� ����
	stream = vStreamConnect(ip_adress, port);
	stream2 = vStreamConnect(ip_adress, port);
	
	// ���� ����� � ���������
	//out=fopen("output.txt","w");

	// ���� �� �� ������
	if(stream != -1)
	{
		consolePrint("TCP CONNECTED");		
		lastsend = vGetTickCount();
	
		strcpy(nick,"jack7");
		strcpy(username,"Il100");
		strcpy(realname,"Il");
		strcpy(channel,"#dzerginsk");


		strcpy(str, "NICK ");
		strcat(str, nick);
		strcat(str, "\r\nUSER ");
		strcat(str, username);
		strcat(str, " 0 * :");
		strcat(str, realname);
		strcat(str, "\r\n");
		
	// �������������� ������ PONG host � ����� �� PING
	
	
	
		strcpy(str4,"JOIN ");
		strcat(str4, channel);
		strcat(str4, "\r\n");
		
		//x = vMsgBox (VMB_YESNO, "Hello");
		// ����������� ������� JOIN
	//	strcpy(str4, "JOIN ");
	//	strcat(str4, channel);
	//	strcat(str4, "\r\n"+'\0');
		
		//str4="JOIN #dust\r\n";


		

		// PONG
	//	sleep(delay);
	//	vStreamWrite(stream,str3,vStrLen(str3)+2);
	//	consolePrint("PONG");
	//	fprintf(out,"send nick and ident");
	//	sleep(delay);
		if(vStreamReady(stream,STREAM_WRITE)==STREAM_WRITE)
			vStreamWrite(stream,str,vStrLen(str));

		consolePrint("NICK AND IDENT");


	//	sleep(delay);
	//	vStreamWrite(stream,str2,vStrLen(str)+1);
	//	consolePrint("PORT USERID");

	///	str5="PONG :localhost\r\n";
	///	sleep(delay);
	///	vStreamWrite(stream,str3,vStrLen(str3));
	///	consolePrint("PONG");

	//	sleep(delay);
		if(vStreamReady(stream,STREAM_WRITE)==STREAM_WRITE)
			vStreamWrite(stream,str4,vStrLen(str4));
		consolePrint("JOIN CHANNEL");
		

		quit=0;

		

		while (!quit)
		{

			// INCOMING MESSAGE
			// ������ �������� �����
			for (i=0;i<sizeof(buf);i++) buf[i]=0;
		
			if(vStreamReady(stream2,STREAM_READ)==STREAM_READ)
			{
			res = vStreamRead(stream2,buf, sizeof(buf)-1);
			//fprintf(out,"%s",buf);
			//fprintf(out,"%d ����",res);
			}
			
			for (x=0;x<64;x++)
			{
			   buf[x] =  tolower( buf[x] );

			}

			// ���� � ����������� ����� PING � ��������
			str12=strstr((char *)buf, "ping :");
			
			if (str12!=NULL)
			{
			// sending ping
				i=6;
				while (str12[i]!=13)
				{
					temp[i-6]=str12[i];
					i++;
				}
				strcpy(str3, "PONG ");
				strcat(str3, temp);
				strcat(str3, "\r\n");

				//fprintf(out,"\n%s\n",str3);
				if(vStreamReady(stream,STREAM_WRITE)==STREAM_WRITE)
				vStreamWrite(stream,str3,vStrLen(str3));
				consolePrint("PONG TO SERVER");
			}

			
			
			// ���� PRIVMSG
			str12=strstr((char *)buf, "privmsg ");
			word=strstr((char *)buf, "privmsg ");
			
			
			while (str12!=NULL)
			{
				x=0;
				str12=strstr(str12,":");
				
				tmp=strstr(word, ":");
				//fprintf(out,"\n%d\n", (sizeof(buf)-sizeof(str12)) );
				x=sizeof(buf) - sizeof(str12);
				
				// ���� �� �������� � ������
				while(buf[x]!=':') {x--;}
				x--;
				while(buf[x]!=':') {x--;}
				i=1;
				x++;
				name[0]=':';
				while (buf[x]!='!') 
				{
					name[i]=buf[x];
					i++;
					x++;
				}
				name[i]=':';
				name[i+1]=0;
				

			//	���������� NAME, ����� �������� ���� ��������, ����� ������ � �����
			//  ���� �� �������� �� 5�8 � 101�80
				consolePrint(name);

				i=0;
				x=1;
				for (xxx=0;xxx<20;xxx++) tmp2[xxx]=0;
				while ( tmp[x]!=13 )
				{
					tmp2[i]=tmp[x];
					i++;
					x++;
					if (i>19)
					{
						consolePrint(tmp2);
						for (xxx=0;xxx<20;xxx++) {tmp2[xxx]=0;}
						i=0;
					}
				}
				consolePrint(tmp2);
				
				for (x=0;x<64;x++)
				{
				  buf[x] =  tolower( buf[x] );

				}
				str12=strstr(str12+1, "privmsg ");
				word=strstr(tmp, "privmsg ");
			}

			
			key = vScanKeys();

			if (key&&((key!=p_key)||(timer>150))) 	{ //������ �� ����������� ������
				timer = 0;
				p_key = key;
			} else {
				
				timer++;
				key = 0;
			}
		

			
			//if(keys&KEY_FIRE) quit=1;

			// KEY_DOWN
//			if (key==KEY_DOWN)
//			{
//				linenum++;
//				for(i=0;i<9;i++)
//				vStrCpy(consoleline[i].str,lines[linenum-9+i]);		
//				consoleRender();
//			}


			// KEY_UP
			//if (key&&KEY_UP) quit=1;
//			{
				
//				linenum--;
//				for(i=0;i<9;i++)
//				vStrCpy(consoleline[i].str,lines[linenum-9+i]);
//				consoleRender();
//			}
			

		
			// ������ 1
			if(key==49)
			{
							
				keys2[keyind]=toupper((char)key);
//				keys2[keyind]='1';			
				keyind++;
				consolePrint2(keys2);
				key=0;
			}
				
			// ������ 2
			if(key==50)
			{
							
//				keys2[keyind]=toupper((char)key);
				keys2[keyind]='2';			
				keyind++;
				//vPrint(MODE_TRANS, 0, 70, keys2 );
				consolePrint2(keys2);
				key=0;
			}
				
			//������ 3
			if(key==51)
			{
							
//				keys2[keyind]=toupper((char)key);
				keys2[keyind]='3';			
				keyind++;
				//vPrint(MODE_TRANS, 0, 70, keys2 );
				consolePrint2(keys2);
				key=0;
			}


				// ����� �� �����
				if (key==204) 
				{ 
					keys2[keyind-1]=0;  
					keys2[keyind-2]=0;
					keyind--; 
					keyind--; 
					consolePrint2(keys2);
					key=0;
				}
				

				//if (key==13)
				// FIRE = 202
				if( (key==202) || (key==KEY_FIRE) || (key==13) )
				{
					keys2[keyind+1]=0;
						
					strcpy(str5,"PRIVMSG ");
					strcat(str5, channel); //dustrap :");
					strcat(str5, " :");
					strcat(str5, keys2);
					strcat(str5,"\r\n");

					if(vStreamReady(stream,STREAM_WRITE)==STREAM_WRITE)
						vStreamWrite(stream,str5,vStrLen(str5));
					consolePrint3(keys2);

					for (keyind=0;keyind<sizeof(keys2);keyind++) 
					{
						keys2[keyind]=0;
						mmm[keyind]=0;
					}
						keyind=0;
					consolePrint2(keys2);
					key=0;
				}
			
		}
			
			//	if(vStreamReady(stream,STREAM_WRITE)==STREAM_WRITE)
			//	{
			//		vStreamWrite(stream,str3,vStrLen(str)+1);
			//		lastsend = time;
			//	}
			
			
	}
	
		// DISCONNECT
		sleep(1);
//		vStreamWrite(stream,"QUIT quit\r\n",12);
		consolePrint("QUIT");
		//fclose(out);
		vStreamClose(stream);
		vStreamClose(stream2);
		
}

// ************************
// MAIN
// ************************
int main(void)
{	

	// INIT
	consoleInit();	

	// test
	chat_start();

	// END
	return 0;
}
