#include "func.h"
#include <pthread.h>
pthread_mutex_t mut;
int prgs;
struct DCommander press_enter(struct DCommander DCom)
{
                  // Если нажата первая строка с ..  -  выход в вышестоящий каталог
                 if(((DCom.current_panel)&&(DCom.L.current_position==0)) || ((!DCom.current_panel)&&(DCom.R.current_position==0)))
                     if(DCom.current_panel) // левая панель
                              {  if(strlen(DCom.L.Current_Dir)>2)
                                 strcpy(strrchr(DCom.L.Current_Dir,'/'),""); // находим / с конца строки,  все, что после него - убиваем
                                 DCom.L= ReadDir(DCom.L.Current_Dir);}
                              else
                              { if(strlen(DCom.R.Current_Dir)>2)
                                strcpy(strrchr(DCom.R.Current_Dir,'/'),"");
                                DCom.R= ReadDir(DCom.R.Current_Dir);}
                  // Если нажата не первая строка - обрабатываем
                    if(DCom.current_panel) // левая панель
                               {if(!strcmp(DCom.L.Type[DCom.L.current_position],"<DIR>"))  //проверяем, чтоб это был каталог
                                  {strcat(DCom.L.Current_Dir,"/");
                               strcat(DCom.L.Current_Dir,DCom.L.List[DCom.L.current_position]);
                               DCom.L= ReadDir(DCom.L.Current_Dir);}
				else // не каталог - бинарный файл
				  {  int child_status;
					  if (fork() == 0) {// дублируем процесс - 
			                    char  bi[4096];         // дочерний процесс
                                            endwin();// разрушаем окно*/
				            strcpy(bi,DCom.L.Current_Dir);// формируем полное имя бинарного файла
                                            strcat(bi,"/");
				            strcat(bi,DCom.L.List[DCom.L.current_position]);
                                            char *arg[] = { bi,  0 };
					    execv(arg[0],  arg);}// заменяем процесс на bi
				          else{// родительский процесс
				           wait(0);// ждем завершения потомка
                    			   endwin();// разрушаем окно*/
				           initscr();// возвражаем исходное положение командера
				           start_color();
				           keypad (stdscr, TRUE);
				           noecho();	
				       	   update_screen(DCom);} // выводим начальное состояние
				  }
			       }
                              else
                               {if(!strcmp(DCom.R.Type[DCom.R.current_position],"<DIR>"))  //проверяем, чтоб это был каталог
                                  {strcat(DCom.R.Current_Dir,"/");
                               strcat(DCom.R.Current_Dir,DCom.R.List[DCom.R.current_position]);
                               DCom.R= ReadDir(DCom.R.Current_Dir);}
				else // не каталог - бинарный файл
				  {  int child_status;
					  if (fork() == 0) {// дублируем процесс - 
			                    char  bi[4096];         // дочерний процесс
                                            endwin();// разрушаем окно*/
				            strcpy(bi,DCom.R.Current_Dir);// формируем полное имя бинарного файла
                                            strcat(bi,"/");
				            strcat(bi,DCom.R.List[DCom.R.current_position]);
                                            char *arg[] = { bi,  0 };
					    execv(arg[0],  arg);}// заменяем процесс на bi
				          else{// родительский процесс
				           wait(0);// ждем завершения потомка
                    			   endwin();// разрушаем окно*/
				           initscr();// возвражаем исходное положение командера
				           start_color();
				           keypad (stdscr, TRUE);
				           noecho();	
				       	   update_screen(DCom);} // выводим начальное состояние
				  }
			       }
return DCom;
}


//int Copy_file(char* Sourse_Dir,char * Dest_Dir, char* File_Name )
int Copy_file(void * f_data)
{
struct _f_name_data f_name_data= * (struct _f_name_data * ) f_data;
     // * f_name_data=f_data;
     // int loc_id = * (int *) arg;
	       // Sourse_Dir=f_name_data.Sourse_Dir;
		//Dest_Dir=f_name_data.Dest_Dir;
		//File_Name=f_name_data.File_Name;
	char  sourse_file[256];
	char  dest_file[256];
	char  str[256];
	strcpy(sourse_file,f_name_data.Sourse_Dir);// формируем полные имена файлов
	strcat(sourse_file,"/");
	strcat(sourse_file,f_name_data.File_Name);
	strcpy(dest_file,f_name_data.Dest_Dir);
	strcat(dest_file,"/");
	strcat(dest_file,f_name_data.File_Name);
FILE *Soursefile;
FILE *Destfile;
long File_Size;		
            // открываем исходный файл
     Soursefile = fopen (sourse_file, "r");
     if(Soursefile==NULL)// файл не открылся
            { printw ("%s\n", "Do not open sourse file. Press enter");
               getstr(str); //Считываем строку
	    return 0;}
    // открываем конечный файл
     Destfile = fopen (dest_file, "w");
     if(Destfile==NULL)// файл не открылся
            { printw ("%s\n", "Do not open destination file. Press enter");
		    char *str;
               getstr(str); //Считываем строку
	    return 0;}
   // получаем размер файла
   fseek(Soursefile, 0L, SEEK_END);// устанавливаем в конец
   File_Size = ftell(Soursefile);// получем текущее положение в конце файла
   fseek(Soursefile,0, SEEK_SET);// устанавливаем в начало файла
  unsigned char  buf[2097152]; // буфер в 2Mb
  int buf_size;
  long Ostatok=File_Size;
 // int progress; 
       // addstr(File_Size);
       // int ch = getch();
  while(Ostatok>0)  // пока не скопируем весь файл
  { 
    if(Ostatok<2097152)
       buf_size=Ostatok;
    else
       buf_size=2097152;
    fread(&buf,1,buf_size , Soursefile);
    fwrite(&buf, buf_size, 1, Destfile);
    Ostatok=Ostatok-buf_size;
   pthread_mutex_lock(&mut);// блокируем prgs
   // f_name_data.copy_progress=(File_Size-Ostatok)*100/File_Size; //прогресс копирования файла в процентах  
    prgs=(File_Size-Ostatok)*100/File_Size; //прогресс копирования файла в процентах  
   pthread_mutex_unlock(&mut);
    
   // int ch = getch();
  }
   fclose(Soursefile);
   fclose(Destfile);
pthread_exit(0); }  

int Copy_Progress(void * f_data)
 {
  struct _f_name_data f_name_data= * (struct _f_name_data * ) f_data;
    // статусная строка
    char stat[256];
  int prgs_last=prgs;

    while(prgs<100)
    {
	if(prgs_last!=prgs)
	{  	
           strcpy(stat,"copying a file ");
           strcat(stat,f_name_data.File_Name);
           strcat(stat, " [");
           int start=strlen(stat);
           for(int i=start;i<(COLS-2);i++)
             {
                //  if(( (i-start)*100/(COLS-2-start))<f_name_data.copy_progress)
                    if(( (i-start)*100/(COLS-2-start))<prgs)
                     strcat(stat, "#");
                    else
                      strcat(stat, " ");
             }
           strcat(stat, "]");
           mvaddstr(LINES-1,0,stat);
           refresh();
	}  
    }   
	   pthread_exit(0);
 }


int Th_Copy_file(char* Sourse_Dir,char * Dest_Dir, char* File_Name )
   {
   struct _f_name_data f_name_data;
    pthread_t Copy_tid; // идентификатор потока копирования 
    pthread_t Status_tid; // идентификатор потока статуса копирования 
    pthread_attr_t Copy_attr; // атрибуты потока копирования 
    pthread_attr_t Status_attr; // атрибуты потока статуса копирования 
    pthread_attr_init(&Copy_attr);
    pthread_attr_init(&Status_attr);
    f_name_data.Sourse_Dir=Sourse_Dir;// назначаем аргументы
    f_name_data.Dest_Dir=Dest_Dir;
    f_name_data.File_Name=File_Name;
    f_name_data.copy_progress=30;
    pthread_mutex_init(&mut,NULL);
  pthread_create(&Copy_tid,&Copy_attr,Copy_file,&f_name_data);// создаем новый поток
  pthread_create(&Status_tid,&Status_attr,Copy_Progress,&f_name_data);
  pthread_join(Copy_tid,NULL);
  return 1;
   } 
