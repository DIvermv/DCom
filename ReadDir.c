#include "func.h"

#include <dirent.h>


struct  Panel  ReadDir(char * Dir_Name)
{
   struct  Panel Pan;
   Pan.Current_Dir=Dir_Name;
   Pan.current_position=0;
   struct dirent *F;

      strcpy(Pan.List[0],"..");// нулевая строка ..
      strcpy(Pan.Type[0],"");
      int i=1;
    DIR *dir=opendir(Dir_Name);
     if(dir)
     {while((F=readdir(dir))!=NULL)
        if(strcmp(F->d_name,".") && strcmp(F->d_name,".."))
        if(F->d_type==4) // читаем только папки
        {strcpy(Pan.List[i],F->d_name);// имя файла
         strcpy(Pan.Type[i],"<DIR>");
         i++;}
     closedir(dir);}

      dir=opendir(Dir_Name);
     if(dir)
     {while((F=readdir(dir))!=NULL)
        if(F->d_type==8) // читаем только файлы
        {char * rt;
          strcpy(Pan.List[i],F->d_name);
          if ((rt=strrchr(Pan.List[i],'.'))!=NULL)
           { rt++;
             strcpy(Pan.Type[i],rt);
             rt--;
             strcpy(rt,"");
             }
	 else
	  {strcpy(Pan.Type[i],"");}  
             i++;}
     
     closedir(dir);}
     Pan.str_count=i;
    return Pan;}

