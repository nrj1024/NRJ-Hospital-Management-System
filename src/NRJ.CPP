/* NRJ HOSPITAL MANAGEMENT SYSTEM */

#include<fstream.h>
#include<graphics.h>
#include<generic.h>
#include<conio.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<process.h>
#include<dos.h>
#include<ctype.h>

int x,y,cl;

union REGS in,out;

void callmouse()
{
   in.x.ax=1;
   int86(0x33,&in,&out);
}

void mouseposi(int &xpos,int &ypos,int &click)
{
   in.x.ax=3;
   int86(0x33,&in,&out);
   click=out.x.bx;
   xpos=out.x.cx;
   ypos=out.x.dx;
}

void click()
{

do
    {
	mouseposi(x,y,cl);
	//gotoxy(10,9);
	//cout<<"    Mouse Position : "<<x<<","<<y;
	//cout<<"\t\tClick : "<<cl;

    }while(cl!=1);
}

void colo(int);
int bmp(char *,int,int,int,int);
int CANVASSX=50,CANVASSY=40,CANVASEX=600,CANVASEY=450;
int colo1,colo2;

void colo(int no)
{
  int num[8]={0,0,0,0,0,0,0,0},i=0;
  while(no!=0)
  {
    num[i]=no%2;
    no=no/2;
    i++;
  }
  colo1=8*num[7]+4*num[6]+2*num[5]+num[4];
  colo2=8*num[3]+4*num[2]+2*num[1]+num[0];
}

void canvasresize(int px=0,int py=0)
{
  if(CANVASEX>600)
  CANVASEX=600;
  if(CANVASEY>450)
  CANVASEY=450;
  if(px!=0||py!=0)
  {
    setfillstyle(1,15);
    if(px<CANVASEX)
    bar(px,CANVASSY,CANVASEX,py);
    if(py<CANVASEY)
    bar(CANVASSX,py,CANVASEX,CANVASEY);
  }
  setfillstyle(1,7);
  if(CANVASEX!=600)
  bar(CANVASEX+1,CANVASSY+1,599,449);
  if(CANVASEY!=450)
  bar(CANVASSX+1,CANVASEY+1,599,449);
  setcolor(0);
  rectangle(CANVASSX,CANVASSY,CANVASEX,CANVASEY);
}

void initiatebmp()
{
  struct palettetype pal;
  getpalette(&pal);
  setrgbpalette(pal.colors[1],96,0,0);         // MAROON
  setrgbpalette(pal.colors[2],0,96,0);         // DARK GREEN
  setrgbpalette(pal.colors[3],96,96,0);        // DARK YELLOW
  setrgbpalette(pal.colors[4],0,0,96);         // DARK BLUE
  setrgbpalette(pal.colors[5],96,0,96);        // MAGENTA
  setrgbpalette(pal.colors[6],0,96,96);        // CYAN
  setrgbpalette(pal.colors[7],48,48,48);       // LIGHT GRAY
  setrgbpalette(pal.colors[8],96,96,96);       // DARK GRAY
  setrgbpalette(pal.colors[9],63,0,0);         // RED
  setrgbpalette(pal.colors[10],0,63,0);        // GREEN
  setrgbpalette(pal.colors[11],63,63,0);       // YELLOW
  setrgbpalette(pal.colors[12],0,0,63);        // BLUE
  setrgbpalette(pal.colors[13],63,0,63);       // PINK
  setrgbpalette(pal.colors[14],0,63,63);       // LIGHT CYAN
}


int bmp(char *ptr,int shiftx,int shifty,int use=0,int type=0)
{
  char ch;
  long i,filesize=0,blankspace,Xlimit=0,Ylimit=0;
  ifstream fi;
  fi.open(ptr,ios::binary);
  fi.get(ch);
  while(fi)
  {
    filesize++;
    fi.get(ch);
  }
  fi.close();
  fi.open(ptr,ios::binary);
  fi.get(ch);
  if(ch!='B')
   return 0;
  fi.get(ch);
  if(ch!='M')
   return 0;
  fi.seekg(18);
  fi.get(ch);
  Xlimit=int(ch);
  if(Xlimit<0)
   Xlimit=256+Xlimit;
  fi.get(ch);
  if(int(ch)<0)
   Xlimit=256*(256+int(ch))+Xlimit;
  else
   Xlimit=256*int(ch)+Xlimit;
  fi.seekg(22);
  fi.get(ch);
  Ylimit=int(ch);
  if(Ylimit<0)
   Ylimit=256+Ylimit;
  fi.get(ch);
  if(int(ch)<0)
   Ylimit=256*(256+int(ch))+Ylimit;
  else
   Ylimit=256*int(ch)+Ylimit;
  int size=(Xlimit+1)/2,y=Ylimit-1,num;
  blankspace=filesize-118-Ylimit*size;
  blankspace/=(Ylimit-1);
  i=0;
  fi.seekg(118);
  fi.get(ch);
  if(use==1)
  {
    CANVASEX=CANVASSX+Xlimit+1;
    CANVASEY=CANVASSY+Ylimit+1;
    canvasresize();
  }
  while(fi)
  {
    for(int j=0;j<size;j++)
    {
      num=int(ch);
      if(num<0)
      num+=256;
      colo(num);
      if(type==1)
      {
	if(shiftx+(j*2)<CANVASEX&&shifty+y<CANVASEY)
	 putpixel(shiftx+(j*2),shifty+y,colo1);
	if(shiftx+(j*2)<CANVASEX-1&&shifty+y<CANVASEY)
	 putpixel(shiftx+1+(j*2),shifty+y,colo2);
      }
      else
      {
	putpixel(shiftx+(j*2),shifty+y,colo1);
	putpixel(shiftx+1+(j*2),shifty+y,colo2);
      }
      fi.get(ch);
    }
    i++;
    y--;
    fi.seekg(118+(size+blankspace)*i);
    fi.get(ch);
  }
  return 0;
}

void mm();
void dm();
void dt();
void pm();
void q();
void bg();
void ad();
void dd();
void md();
void at();
void dti();
void mt();
void ap();
void dp();
void mp();
void dq();
void pq();
void back()
{

  if(x>=557 && x<=602 && y>=407 && y<=452)
	{
	  mm();
	}

}

void exit()
{

  if(x>=552 && x<=600 && y>=34 && y<=81)
    {
     cleardevice();
     exit(0);
    }

}

struct Date
{
  int dd,mm,yy;
};

   class Doctor
   {
   public:
   int dn;
   char name[20];
   char fname[20];
   char address[50];
   char mobile[15];
   char qual[20];
   char spc[20];
   char expr[20];
   char salary[20];
   void gdoctor();
   void ddoctor();
   };

void Doctor::gdoctor()
{
 gotoxy(47,11);
 gets(name);
 gotoxy(47,13);
 gets(fname);
 gotoxy(47,15);
 gets(address);
 gotoxy(47,17);
 gets(mobile);
 gotoxy(47,19);
 gets(qual);
 gotoxy(47,21);
 gets(spc);
 gotoxy(47,23);
 gets(expr);
 gotoxy(47,25);
 gets(salary);
}

void Doctor::ddoctor()
{
 gotoxy(24,8);
 cout<<dn;
 gotoxy(47,11);
 puts(name);
 gotoxy(47,13);
 puts(fname);
 gotoxy(47,15);
 puts(address);
 gotoxy(47,17);
 puts(mobile);
 gotoxy(47,19);
 puts(qual);
 gotoxy(47,21);
 puts(spc);
 gotoxy(47,23);
 puts(expr);
 gotoxy(47,25);
 puts(salary);
}

class Time
{
   public:
   int dn;
   char mon[50];
   char tue[50];
   char wed[50];
   char thu[50];
   char fri[50];
   char sat[50];
   char sun[50];
   void gtime();
   void dtime();
};

void Time::gtime()
{
 gotoxy(47,11);
 gets(mon);
 gotoxy(47,13);
 gets(tue);
 gotoxy(47,15);
 gets(wed);
 gotoxy(47,17);
 gets(thu);
 gotoxy(47,19);
 gets(fri);
 gotoxy(47,21);
 gets(sat);
 gotoxy(47,23);
 gets(sun);
}

void Time::dtime()
{
 gotoxy(47,11);
 puts(mon);
 gotoxy(47,13);
 puts(tue);
 gotoxy(47,15);
 puts(wed);
 gotoxy(47,17);
 puts(thu);
 gotoxy(47,19);
 puts(fri);
 gotoxy(47,21);
 puts(sat);
 gotoxy(47,23);
 puts(sun);
}

   class Patient
   {
   public:
   int pn;
   Date vdate;
   char name[20];
   char address[50];
   char phone[15];
   char mobile[15];
   char problem[20];
   char fee[20];
   void gpatient();
   void dpatient();
   };

void Patient::gpatient()
{
 gotoxy(47,11);
 cin>>vdate.dd;
 gotoxy(50,11);
 cout<<"/";
 gotoxy(52,11);
 cin>>vdate.mm;
 gotoxy(54,11);
 cout<<" / ";
 gotoxy(57,11);
 cin>>vdate.yy;
 if(vdate.mm>12)
 {
   bmp("inv.bmp",0,0,640,480);
   ap();
 }
 else if(vdate.mm==1)
 {
   if(vdate.dd>31)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==2)
 {
   if(vdate.dd>29)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==3)
 {
   if(vdate.dd>31)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==4)
 {
   if(vdate.dd>30)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==5)
 {
   if(vdate.dd>31)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==6)
 {
   if(vdate.dd>30)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==7)
 {
   if(vdate.dd>31)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }

 else if(vdate.mm==8)
 {
   if(vdate.dd>31)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==9)
 {
   if(vdate.dd>30)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==10)
 {
   if(vdate.dd>31)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==11)
 {
   if(vdate.dd>30)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 else if(vdate.mm==12)
 {
   if(vdate.dd>31)
   {
     bmp("inv.bmp",0,0,640,480);
     ap();
   }
 }
 gotoxy(47,13);
 gets(name);
 gotoxy(47,15);
 gets(address);
 gotoxy(47,17);
 gets(phone);
 gotoxy(47,19);
 gets(mobile);
 gotoxy(47,21);
 gets(problem);
 gotoxy(47,23);
 gets(fee);
}

void Patient::dpatient()
{
 gotoxy(24,8);
 cout<<pn;
 gotoxy(47,11);
 cout<<vdate.dd<<"/"<<vdate.mm<<"/"<<vdate.yy;
 gotoxy(47,13);
 puts(name);
 gotoxy(47,15);
 puts(address);
 gotoxy(47,17);
 puts(phone);
 gotoxy(47,19);
 puts(mobile);
 gotoxy(47,21);
 puts(problem);
 gotoxy(47,23);
 puts(fee);
}

void mm()
{
    cleardevice();
    bmp("mm.bmp",0,0,640,480);
    callmouse();
    start:

    click();

    dm();
    dt();
    pm();
    q();
    bg();
    back();
    exit();

    goto start;

}

void dm()
  {

	if(x>=103 && x<=272 && y>=155 && y<=183)
	{
	  cleardevice();
	  bmp("dm.bmp",0,0,640,480);
	  start:

	  click();
	  ad();
	  dd();
	  md();
	  back();
	  exit();

	  goto start;

	}



  }

void dt()
      {
	if(x>=103 && x<=272 && y>=219 && y<=247)
	{
	  cleardevice();
	  bmp("dt.bmp",0,0,640,480);
	  start:

	  click();
	  at();
	  dti();
	  mt();
	  back();
	  exit();

	  goto start;
	}

      }


void pm()
      {

	if(x>=103 && x<=272 && y>=248 && y<=310)
	{
	  cleardevice();
	  bmp("pm.bmp",0,0,640,480);
	  start:

	  click();
	  ap();
	  dp();
	  mp();
	  back();
	  exit();

	  goto start;
	}

      }

void q()
      {

	if(x>=103 && x<=272 && y>=346 && y<=373)
	{
	  cleardevice();
	  bmp("q.bmp",0,0,640,480);
	  start:

	  click();
	  dq();
	  pq();
	  back();
	  exit();

	  goto start;

	}

      }

void bg()
      {

	if(x>=103 && x<=272 && y>=410 && y<=438)
	{
	  startbg:
	  cleardevice();
	  bmp("bg.bmp",0,0,640,480);
	  fstream file("Patient.dat",ios::in||ios::binary);
	  Patient P;
	  int p;
	  gotoxy(53,16);
	  cin>>p;
	  while(file.read((char*)&P,sizeof(P)))
	  {
	    if(P.pn==p)
	      {
		bmp("bill.bmp",0,0,640,480);
		gotoxy(50,13);
		cout<<P.pn;
		gotoxy(50,16);
		puts(P.name);
		gotoxy(50,19);
		puts(P.address);
		gotoxy(50,22);
		puts(P.problem);
		gotoxy(50,25);
		puts(P.fee);
		gotoxy(50,28);
		break;
	       }
	  }
       file.close();
       getch();
       bmp("abg.bmp",0,0,640,480);
       click:
       click();
       if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startbg;
		}
       else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		mm();
		}
       else
       goto click;

	 }
      }

void ad()
{
   if(x>=109 && x<=277 && y>=180 && y<=208)
    {
      startad:
      cleardevice();
      bmp("dme.bmp",0,0,640,480);
      fstream filer("Doctor.dat",ios::in|ios::binary);
      fstream filew("Doctor.dat",ios::out|ios::app|ios::binary);
      Doctor D;
      int d=1;
      while(filer.read((char*)&D,sizeof(D)))
      {
	if(D.dn==d)
	 {
	   d++;
	 }
	 else if(D.dn!=d)
	 {
	   break;
	 }
      }
      filer.close();
      gotoxy(24,8);
      cout<<d;
      D.dn=d;
      D.gdoctor();
      filew.write((char *)&D,sizeof(D));
      filew.close();
      bmp("su.bmp",0,0,640,480);
      bmp("as.bmp",0,0,640,480);
      click:
      click();
      if(x>=176 && x<=309 && y>=252 && y<=283)
      {
	goto startad;
      }
      else if(x>=340 && x<=465 && y>=252 && y<=283)
      {
	mm();
      }
      else
      goto click;
    }

}

void dd()
{
   if(x>=109 && x<=277 && y>=244 && y<=271)
    {
      startdd:
      cleardevice();
      bmp("dda.bmp",0,0,640,480);
      fstream filer("Doctor.dat",ios::in|ios::binary);
      fstream filew("temp.dat",ios::out|ios::app|ios::binary);
      Doctor D;
      int d;
      gotoxy(53,16);
      cin>>d;
      while(filer.read((char*)&D,sizeof(D)))
      {
	  if(D.dn!=d)
	  {
	    filer.close();
	    filew.write((char*)&D,sizeof(D));
	    filew.close();
	  }
	  else if(D.dn==d)
	  {
	    cleardevice();
	    bmp("dme.bmp",0,0,640,480);
	    D.ddoctor();
	    getch();
	    bmp("ds.bmp",0,0,640,480);
	    click3:
	    click();
	    if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		 remove("Doctor.dat");
		 rename("temp.dat","Doctor.dat");
		 bmp("del.bmp",0,0,640,480);
		 bmp("da.bmp",0,0,640,480);
		 click1:
		 click();
		 if(x>=176 && x<=309 && y>=252 && y<=283)
		  {
		   goto startdd;
		  }
		 else if(x>=340 && x<=465 && y>=252 && y<=283)
		  {
		   mm();
		  }
		  else
		  goto click1;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		remove("temp.dat");
		bmp("da.bmp",0,0,640,480);
		 click2:
		 click();
		 if(x>=176 && x<=309 && y>=252 && y<=283)
		  {
		   goto startdd;
		  }
		 else if(x>=340 && x<=465 && y>=252 && y<=283)
		  {
		   mm();
		  }
		  else
		  goto click2;
		}
	     else
	     goto click3;

	  }

       else
       {
	bmp("nd.bmp",0,0,640,480);
	mm();
       }

      }


    }

}

void md()
{
   if(x>=109 && x<=277 && y>=308 && y<=355)
    {
      startmd:
      cleardevice();
      bmp("dda.bmp",0,0,640,480);
      fstream filer("Doctor.dat",ios::in,ios::binary);
      fstream filew("temp.dat",ios::out,ios::binary);
      Doctor D;
      gotoxy(53,16);
      int d;
      cin>>d;
      while(filer.read((char *)&D,sizeof(D)))
      {
	if(D.dn!=d)
	  {
	    filer.close();
	    filew.write((char *)&D,sizeof(D));
	    filew.close();
	  }
	else if(D.dn==d)
	  {
	    bmp("dme.bmp",0,0,640,480);
	    gotoxy(24,8);
	    cout<<D.dn;
	    D.gdoctor();
	    bmp("ms.bmp",0,0,640,480);
	    click3:
	    click();
	    if(x>=176 && x<=309 && y>=252 && y<=283)
	    {
	      filew.write((char *)&D,sizeof(D));
	      remove("Doctor.dat");
	      rename("temp.dat","Doctor.dat");
	      bmp("su.bmp",0,0,640,480);
	      bmp("ma.bmp",0,0,640,480);
	      click1:
	      click();
	      if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startmd;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		mm();
		}
		else
		goto click1;
	     }
	     else if(x>=340 && x<=465 && y>=252 && y<=283)
	     {
	       remove("temp.dat");
	       bmp("ma.bmp",0,0,640,480);
	      click2:
	      click();
	      if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startmd;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		mm();
		}
		else
		goto click2;
	     }
	    else
	    goto click3;

	  }

	else
       {
	bmp("nd.bmp",0,0,640,480);
	mm();
       }

      }

   }
}

void at()
{
   if(x>=109 && x<=277 && y>=194 && y<=222)
    {
       startat:
       cleardevice();
       bmp("dta.bmp",0,0,640,480);
       fstream filer("Time.dat",ios::in|ios::binary);
       fstream filew("Time.dat",ios::out|ios::app|ios::binary);
       fstream filed("Doctor.dat",ios::in|ios::binary);
       Time T;
       Doctor D;
      int d;
      gotoxy(53,16);
      cin>>d;
      int flag;
      while(filer.read((char*)&T,sizeof(T)))
      {
	if(T.dn!=d)
	 {
	   flag=1;
	 }
	else if(T.dn==d)
	{
	  flag=0;
	  break;
	}

      }
      filer.close();
      if (flag==0)
      {
	bmp("tae.bmp",0,0,640,480);
	getch();
	mm();
      }
      else
      {
       while(filed.read((char*)&D,sizeof(D)))
       {
	  if(D.dn==d)
	    {
	      flag=3;
	      break;
	    }
	  else
	   {
	      flag=4;
	   }
       }
       if(flag==3)
       {
       T.dn=d;
       bmp("dte.bmp",0,0,640,480);
       gotoxy(24,8);
       cout<<T.dn;
       T.gtime();
       filew.write((char *)&T,sizeof(T));
       filew.close();
       bmp("su.bmp",0,0,640,480);
       bmp("as.bmp",0,0,640,480);
       click:
       click();
       if(x>=176 && x<=309 && y>=252 && y<=283)
      {
	goto startat;
      }
      else if(x>=340 && x<=465 && y>=252 && y<=283)
      {
	mm();
      }
      else
      goto click;
      }

       else
       {
	 bmp("adf.bmp",0,0,640,480);
	 getch();
	 mm();
       }

     }
  }

}

void dti()
{
   if(x>=109 && x<=277 && y>=258 && y<=286)
    {
      startdti:
      cleardevice();
      bmp("dta.bmp",0,0,640,480);
      fstream filer("Time.dat",ios::in|ios::binary);
      fstream filew("temp.dat",ios::out|ios::binary);
      Time T;
      int d;
      gotoxy(53,16);
      cin>>d;
      while(filer.read((char*)&T,sizeof(T)))
      {
	  if(T.dn!=d)
	  {
	    filer.close();
	    filew.write((char*)&T,sizeof(T));
	    filew.close();
	  }
	  else if(T.dn==d)
	  {
	    cleardevice();
	    bmp("dte.bmp",0,0,640,480);
	    T.dtime();
	    getch();
	    bmp("ds.bmp",0,0,640,480);
	    click3:
	    click();
	    if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		 remove("Time.dat");
		 rename("temp.dat","Time.dat");
		 bmp("del.bmp",0,0,640,480);
		 bmp("da.bmp",0,0,640,480);
		 click1:
		 click();
		 if(x>=176 && x<=309 && y>=252 && y<=283)
		  {
		   goto startdti;
		  }
		 else if(x>=340 && x<=465 && y>=252 && y<=283)
		  {
		   mm();
		  }
		  else
		  goto click1;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		remove("temp.dat");
		bmp("da.bmp",0,0,640,480);
		 click2:
		 click();
		 if(x>=176 && x<=309 && y>=252 && y<=283)
		  {
		   goto startdti;
		  }
		 else if(x>=340 && x<=465 && y>=252 && y<=283)
		  {
		   mm();
		  }
		  else
		  goto click2;
		}
	      else
	      goto click3;

	  }

	else
       {
	bmp("nd.bmp",0,0,640,480);
	mm();
       }

      }

    }

}

void mt()
{
   if(x>=109 && x<=277 && y>=322 && y<=351)
    {
      startmt:
      cleardevice();
      bmp("dta.bmp",0,0,640,480);
      fstream filer("Time.dat",ios::in,ios::binary);
      fstream filew("temp.dat",ios::out,ios::binary);
      Time T;
      gotoxy(53,16);
      int d;
      cin>>d;
      while(filer.read((char *)&T,sizeof(T)))
      {
	if(T.dn!=d)
	  {
	    filer.close();
	    filew.write((char *)&T,sizeof(T));
	    filew.close();
	  }
	else if(T.dn==d)
	  {
	    bmp("dte.bmp",0,0,640,480);
	    gotoxy(24,8);
	    cout<<T.dn;
	    T.gtime();
	    bmp("ms.bmp",0,0,640,480);
	    click3:
	    click();
	    if(x>=176 && x<=309 && y>=252 && y<=283)
	    {
	      filew.write((char *)&T,sizeof(T));
	      filew.close();
	      remove("Time.dat");
	      rename("temp.dat","Time.dat");
	      bmp("su.bmp",0,0,640,480);
	      bmp("ma.bmp",0,0,640,480);
	      click1:
	      click();
	      if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startmt;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		mm();
		}
		else
		goto click1;
	     }
	     else if(x>=340 && x<=465 && y>=252 && y<=283)
	     {
	       remove("temp.dat");
	       bmp("ma.bmp",0,0,640,480);
	      click2:
	      click();
	      if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startmt;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		mm();
		}
		else
		goto click2;
	     }
	    else
	    goto click3;

	  }

	else
       {
	bmp("nd.bmp",0,0,640,480);
	mm();
       }

      }

    }

}

void ap()
{
   if(x>=109 && x<=277 && y>=194 && y<=222)
    {
      startap:
      cleardevice();
      bmp("pme.bmp",0,0,640,480);
      fstream filer("Patient.dat",ios::in|ios::binary);
      fstream filew("Patient.dat",ios::out|ios::app|ios::binary);
      Patient P;
      int p=1;
      while(filer.read((char*)&P,sizeof(P)))
      {
	if(P.pn==p)
	 {
	   p++;
	 }
	 else if(P.pn!=p)
	 {
	   break;
	 }
      }
      filer.close();
      gotoxy(24,8);
      cout<<p;
      P.pn=p;
      P.gpatient();
      filew.write((char *)&P,sizeof(P));
      filew.close();
      bmp("su.bmp",0,0,640,480);
      bmp("as.bmp",0,0,640,480);
      click:
      click();
      if(x>=176 && x<=309 && y>=252 && y<=283)
      {
	goto startap;
      }
      else if(x>=340 && x<=465 && y>=252 && y<=283)
      {
	mm();
      }
      else
      goto click;
  }

}

void dp()
{
   if(x>=109 && x<=277 && y>=258 && y<=286)
    {
      startdp:
      cleardevice();
      bmp("pda.bmp",0,0,640,480);
      fstream filer("Patient.dat",ios::in|ios::binary);
      fstream filew("temp.dat",ios::out|ios::binary);
      Patient P;
      int d;
      gotoxy(53,16);
      cin>>d;
      while(filer.read((char*)&P,sizeof(P)))
      {
	  if(P.pn!=d)
	  {
	    filer.close();
	    filew.write((char*)&P,sizeof(P));
	    filew.close();
	  }
	  else if(P.pn==d)
	  {
	    cleardevice();
	    bmp("pme.bmp",0,0,640,480);
	    P.dpatient();
	    getch();
	    bmp("ds.bmp",0,0,640,480);
	    click3:
	    click();
	    if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		 remove("Patient.dat");
		 rename("temp.dat","Patient.dat");
		 bmp("del.bmp",0,0,640,480);
		 bmp("da.bmp",0,0,640,480);
		 click1:
		 click();
		 if(x>=176 && x<=309 && y>=252 && y<=283)
		  {
		    goto startdp;
		  }
		 else if(x>=340 && x<=465 && y>=252 && y<=283)
		  {
		   mm();
		  }
		  else
		  goto click1;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		remove("temp.dat");
		bmp("da.bmp",0,0,640,480);
		 click2:
		 click();
		 if(x>=176 && x<=309 && y>=252 && y<=283)
		  {
		   goto startdp;
		  }
		 else if(x>=340 && x<=465 && y>=252 && y<=283)
		  {
		   mm();
		  }
		 else
		 goto click2;
		}
	     else
	     goto click3;

	  }

       else
       {
	bmp("nd.bmp",0,0,640,480);
	mm();
       }

      }


    }

}

void mp()
{
   if(x>=109 && x<=277 && y>=322 && y<=351)
    {
      startmp:
      cleardevice();
      bmp("pda.bmp",0,0,640,480);
      fstream filer("Patient.dat",ios::in,ios::binary);
      fstream filew("temp.dat",ios::out,ios::binary);
      Patient P;
      gotoxy(53,16);
      int d;
      cin>>d;
      while(filer.read((char *)&P,sizeof(P)))
      {
	if(P.pn!=d)
	  {
	    filer.close();
	    filew.write((char *)&P,sizeof(P));
	    filew.close();
	  }
	else if(P.pn==d)
	  {
	    bmp("pme.bmp",0,0,640,480);
	    gotoxy(24,8);
	    cout<<P.pn;
	    P.gpatient();
	    bmp("ms.bmp",0,0,640,480);
	    click3:
	    click();
	    if(x>=176 && x<=309 && y>=252 && y<=283)
	    {
	      filew.write((char *)&P,sizeof(P));
	      filew.close();
	      remove("Patient.dat");
	      rename("temp.dat","Patient.dat");
	      bmp("su.bmp",0,0,640,480);
	      bmp("ma.bmp",0,0,640,480);
	      click1:
	      click();
	      if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startmp;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		mm();
		}
		else
		goto click1;
	     }
	     else if(x>=340 && x<=465 && y>=252 && y<=283)
	     {
	       remove("temp.dat");
	       bmp("ma.bmp",0,0,640,480);
	      click2:
	      click();
	      if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startmp;
		}
		else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		mm();
		}
		else
		goto click2;
	     }
	    else
	    goto click3;

	  }

	else
       {
	bmp("nd.bmp",0,0,640,480);
	mm();
       }

      }


    }

}

void dq()
{
   if(x>=109 && x<=277 && y>=204 && y<=231)
    {
       startdq:
       cleardevice();
       bmp("dda.bmp",0,0,640,480);
       fstream filer("Doctor.dat",ios::in,ios::binary);
       fstream filert("Time.dat",ios::in,ios::binary);
       Doctor D;
       Time T;
       int d;
       gotoxy(53,16);
       cin>>d;
       int flag;
       while(filer.read((char*)&D,sizeof(D)))
       {
	 if(D.dn==d)
	   {
	     bmp("dd.bmp",0,0,640,480);
	     D.ddoctor();
	     flag=1;
	     break;
	   }
	   else if(D.dn!=d)
	   {
	     flag=0;
	   }
       }
       filer.close();
       getch();
       if(flag==0)
       {
	 bmp("nd.bmp",0,0,640,480);
	 mm();
       }
       else if(flag==1)
       {
       while(filert.read((char*)&T,sizeof(T)))
       {
	  if(T.dn==d)
	  {
	   bmp("dte.bmp",0,0,640,480);
	   gotoxy(24,8);
	   cout<<T.dn;
	   T.dtime();
	   break;
	  }
       }
       filert.close();
       getch();
       bmp("asd.bmp",0,0,640,480);
       click:
       click();
       if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startdq;
		}
       else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		  mm();
		}
       else
       goto click;
       }
    }

}

void pq()
{
   if(x>=109 && x<=277 && y>=281 && y<=310)
    {
       startpq:
       cleardevice();
       bmp("pda.bmp",0,0,640,480);
       fstream file("Patient.dat",ios::in,ios::binary);
       Patient P;
       int p;
       gotoxy(53,16);
       cin>>p;
       int flag;
       while(file.read((char*)&P,sizeof(P)))
       {
	 if(P.pn==p)
	   {
	     flag=1;
	     bmp("pd.bmp",0,0,640,480);
	     P.dpatient();
	     break;
	   }
	   else if(P.pn!=p)
	   {
	     flag=0;
	   }
       }
       file.close();
       getch();
       if(flag==0)
       {
	 bmp("nd.bmp",0,0,640,480);
	 mm();
       }
       else if(flag==1)
       {
       bmp("asd.bmp",0,0,640,480);
       click:
       click();
       if(x>=176 && x<=309 && y>=252 && y<=283)
		{
		  goto startpq;
		}
       else if(x>=340 && x<=465 && y>=252 && y<=283)
		{
		  mm();
		}
       else
       goto click;
       }
   }

}

void main()
{
   /* request auto detection */
   int gdriver = DETECT, gmode, errorcode;

   /* initialize graphics mode */
   initgraph(&gdriver, &gmode, "");

   /* read result of initialization */
   errorcode = graphresult();

if (errorcode != grOk)  /* an error occurred */
{
   printf("Graphics error: %s\n", grapherrormsg(errorcode));
   printf("Press any key to halt:");
   getch();
   exit(1);             /* return with error code */
}

   bmp("SS.bmp",0,0,640,480);
   setcolor(15);
   settextstyle(6,0,5);
   for(int i=-50;i<200;i++)
   { outtextxy(i,400,"]");
     delay(10);
   }
   for(i=200;i<700;i++)
   { outtextxy(i,400,"]");
     delay(2);
   }
password:
int z=350;
int flag;
char a[5]={"nrj"};
char c[5];
bmp("P.bmp",0,0,640,480);
gotoxy(48,15);
i=-1;
char ch;
do
{
   ch=getch();
   if(ch==13)
   {
     break;
   }

   else if(ch==8)
   {
     c[i]='\0';
     --i;
     setcolor(BLACK);
     outtextxy(z,208,"*");
     z=z-18;

   }

   else
   {
     setcolor(WHITE);
     z=z+18;
     outtextxy(z,208,"*");
     c[++i]=ch;
   }

}while(ch!=13);

c[++i]='\0';
if (strncmp(c,a,20))
{
    bmp("D.bmp",0,0,640,480);
    flag=0;
    delay(1000);
}
else
{
    bmp("G.bmp",0,0,640,480);
    flag=1;
    delay(1000);
}
if (flag==1)
{
   mm();
}

else

{
    goto password;
}
   delay(1000);
}