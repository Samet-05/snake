#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <termios.h>        
#include <sys/ioctl.h>
#include <sys/select.h>
#include <fcntl.h>

int kbhit(void)
{
  struct termios oldt, newt;
  int ch;
  int oldf;

  tcgetattr(STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON | ECHO);
  tcsetattr(STDIN_FILENO, TCSANOW, &newt);
  oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
  fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

  ch = getchar();

  tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
  fcntl(STDIN_FILENO, F_SETFL, oldf);

  if(ch != EOF)
  {
    ungetc(ch, stdin);
    return 1;
  }

  return 0;
}



int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    return ch;
}


void gotoxy(int x,int y)
{
    printf("%c[%d;%df",0x1B,x,y);
}



     int snakex=12;
    int snakey=25;
     
    int baitx=21;
    int baity=21;
    int a;
    int length=0;
    int dir;
    int snakesx[100];
    int snakesy[100];
    int off=0;
    

void direction(){
    
   if(kbhit())
   dir=getch();


    switch (dir)
    {
        case 'w': snakex-=1;
                  usleep(80000);
            break;
        case 's': snakex+=1;
                  usleep(80000);        
            break;
        case 'a': snakey-=1;
                  usleep(80000);
            break;
        case 'd': snakey+=1;
                  usleep(80000);
            break; 
            default: usleep(80000);
            
    }


}
 void random_number(){
      srand(time(NULL));
      baitx=3+ rand()%23;
      baity=3+ rand()%48;



 }

void field(){

   char *range[25][50];
    int i,j;
    
    
     
    for(i = 0; i < 25; i++){

        for(j = 0; j < 50; j++){

         if(i==0 || i==24)
         range[i][j]="▒";
         else if(j==0 || j==49)
         range[i][j]="▒";
         else
         range[i][j]=" ";

          
      
        
       


        printf("%s",range[i][j]);
        }    
      
        printf("\n");

    }


            gotoxy(baitx,baity);
            printf("0");
     gotoxy(snakex,snakey);
    printf("▪");




             snakesy[0]=snakey;
         snakesx[0]=snakex;



          for(a=0;a<=length;a++)
        {
            gotoxy(snakesx[a],snakesy[a]);
            printf("▪");

        }  

      for(a=length;a>0;a--)
        {
            snakesx[a]=snakesx[a-1];
            snakesy[a]=snakesy[a-1];
        }
   

         




}






void main(){
     
 


    

    do{
            for(a=1; a<=length; a++){
                     if(snakex==snakesx[a] && snakey==snakesy[a]){
            off++;
            gotoxy(snakex,snakey);
            printf("GAME OVER");
            getch();
         }
            }
 
         
         field();
         direction();

      

         if(snakex==baitx && snakey==baity){
         random_number();
         length++;
         }
 




         if(snakex<1)
         snakex=23;
         if(snakex>25)
         snakex=1;
         if(snakey<1)
         snakey=48;
         if(snakey>50)
         snakey=1;






         system("clear");


       
      
    
    }while(off==0);
    
  
}