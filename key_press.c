
#include "func.h"
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
