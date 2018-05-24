#include "func.h"

#include <dirent.h>

//#include <ncurses.h>

struct  Panel  ReadDir(char * Dir_Name)
{
   struct  Panel Pan;
   Pan.Current_Dir=Dir_Name;
   Pan.current_position=0;
   struct dirent *F;

    //while(searchpath("*.*"))
      strcpy(Pan.List[0],"..");// нулевая строка ..
      strcpy(Pan.Type[0],"");
      int i=1;
    DIR *dir=opendir(Dir_Name);
     if(dir)
     {while((F=readdir(dir))!=NULL)
       if(F->d_name[0]!='.')  // if(F->d_name!=".")&&(F->d_name!="..")
        if(F->d_type==4) // читаем только папки
        {strcpy(Pan.List[i],F->d_name);// имя файла
         strcpy(Pan.Type[i],"<DIR>");
         i++;}
     closedir(dir);}

      dir=opendir(Dir_Name);
     if(dir)
     {while((F=readdir(dir))!=NULL)
       if(F->d_name[0]!='.')  // if(F->d_name!=".")&&(F->d_name!="..")
        if(F->d_type==8) // читаем только файлы
        {char * rt;
          strcpy(Pan.List[i],F->d_name);
          if ((rt=strrchr(Pan.List[i],'.'))!=NULL)
           { rt++;
             strcpy(Pan.Type[i],rt);
             rt--;
             strcpy(rt,"");

             }
             i++;}
     closedir(dir);}
     Pan.str_count=i;
       /*
        int y=strlen(F->d_name);
        int s=y;
        while((F->d_name[y]!='.') && (y>0))
               y--;
          if(F->d_name[y]=='.')
         //if(y>0)
          {y++;
            for(int u=0;u<(s-y);u++)
              Pan.Type[i][u]=F->d_name[u+y];}*/
        //Pan.Files_size=
        //Pan.Type=ent->d_type;
     //printf("%i\n",Pan.str_count);
    return Pan;}

