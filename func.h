#ifndef FUNC_H
#define FUNC_H
#include <string.h>
#include <ncurses.h>
#include <stdio.h>
#include <unistd.h>
#include <locale.h>
//extern int current_element; //номер текущего элемента
struct Panel {
	char List[256][256];// список файлов и папок
	int Files_size[256];
	char Type[256][16];
	int str_count;// количество файлов и папок в данной папке
	int current_position; // позиция выбранного файла
    char* Current_Dir;
               };
struct DCommander{
       struct Panel L;
       struct Panel R;
       int current_panel; // 1- Left
       char Status[256];
           };

 struct _f_name_data{
        char*	Sourse_Dir;
	char*	Dest_Dir;
	char*	File_Name;
	int copy_progress;
                    };
struct  Panel  ReadDir(char * Dir_Name); // функция смены каталога
void update_screen(struct DCommander DCommander);
void update_panel(struct Panel Pan, int delta, int activ);
struct DCommander press_enter(struct DCommander DCom);
int Th_Copy_file(char* Sourse_Dir,char * Dest_Dir, char* File_Name );
 // потоковые функции
 int Copy_file(void * f_name_data);
 int Copy_Progress(void * f_data);
#endif
