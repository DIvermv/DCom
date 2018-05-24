
#include "func.h"

int main (int argc, char *argv[])
{
    struct DCommander DCom;
    long size;
    DCom.current_panel=1;
    size = pathconf(".", _PC_PATH_MAX);
    char * t;

   //DCom.L.Current_Dir = getcwd(t, (size_t)size);// получаем текущий каталог
   // if (strlen(DCom.L.Current_Dir)==0) // проверяем получили ли имя

   if((DCom.L.Current_Dir = getcwd(t, (size_t)size))==NULL) //получаем текущий каталог и проверяем, получили ли
     {printf("%s\n","Ошибка получения текущего каталога.");
        return 0;
        }

     //strcpy(DCom.R.Current_Dir,DCom.L.Current_Dir);
      DCom.R.Current_Dir = getcwd(t, (size_t)size);


    DCom.L.current_position=0;
    DCom.R.current_position=0;
    //printf("%s\n",DCom.L.Current_Dir);



 // /home/vovan/stud/Dcom
    //DCom.L= ReadDir("/home/vovan/stud/Dcom");
    DCom.L= ReadDir(DCom.L.Current_Dir); // читаем содержимое каталога в левой панели
    DCom.R= ReadDir(DCom.R.Current_Dir);
//return 0;

/*for(int i=0;i<DCom.L.str_count;i++)
    {       printf("%s",DCom.L.List[i]);
       printf("%s\n",DCom.L.Type[i]);}*/


//всё инициализируем
  initscr();
  start_color();
  keypad (stdscr, TRUE);
  noecho();

MEVENT event;
//создаем цветовые пары
  init_pair (1, COLOR_RED, COLOR_BLACK);
  init_pair (2, COLOR_WHITE, COLOR_BLACK);
  init_pair (3,  COLOR_BLACK,   COLOR_GREEN);
  init_pair (4, COLOR_WHITE,   COLOR_BLUE);
  init_pair (5,  COLOR_WHITE,   COLOR_RED);
  update_screen(DCom); // выводим начальное состояние
//объявляем переменную для хранения нажатой клавиши
  int ch = 0;
  //ch = getch();
  //printf("%i\n",ch);

//считываем клавиши, пока не будет нажата 'F3' (по F3 - выход)
  while (ch != KEY_F(3))
        {
         //обновляем экран
         update_screen(DCom);
         mousemask (ALL_MOUSE_EVENTS, NULL);// инициализируем считывание мыши
	      //ожидаем нажатия на клавишу и
         //получаем её код в ch
         ch = getch();

         switch (ch)
                {
//если нажата "F1", то активируем левую панель
                 case KEY_F(1):
                            DCom.current_panel=1;
                             break;
//если нажата "F2", то активируем правую панель
                 case KEY_F(2):
			       DCom.current_panel=0;
                             break;
//если нажата "вверх"
                 case KEY_UP:
			    if ( DCom.current_panel) // левая панель
				    {if(DCom.L.current_position>0)
                         DCom.L.current_position--;}
                else
                    {if(DCom.R.current_position>0)
                         DCom.R.current_position--;}
                             break;
//если нажата "вниз"
                case KEY_DOWN:
			    if ( DCom.current_panel) // левая панель
				    {if(DCom.L.current_position<DCom.L.str_count)
                         DCom.L.current_position++;}
                else
                    {if(DCom.R.current_position<DCom.R.str_count)
                         DCom.R.current_position++;}
                             break;
//если нажата "влево"
                case KEY_LEFT:
			    DCom.current_panel=1;
                             break;
                             break;
//если нажата "вправо"
                case KEY_RIGHT:
			    DCom.current_panel=0;
                             break;
                             break;
//если нажата "BACKSPACE" // выйти на каталог выше
                case KEY_BACKSPACE:
                 if(DCom.current_panel) // левая панель
                              {  if(strlen(DCom.L.Current_Dir)>2)
                                 strcpy(strrchr(DCom.L.Current_Dir,'/'),""); // находим / с конца строки,  все, что после него - убиваем
                                 DCom.L= ReadDir(DCom.L.Current_Dir);}
                              else
                              { if(strlen(DCom.R.Current_Dir)>2)
                                strcpy(strrchr(DCom.R.Current_Dir,'/'),"");
                                DCom.R= ReadDir(DCom.R.Current_Dir);}
                                break;
//обработка нажатия Enter - войти в каталог
                 case '\n':
                              if(DCom.current_panel) // левая панель
                              {//if(DCom.L.Type[DCom.L.Type.current_position]=="<DIR>")  проверяем, чтоб это был каталог
                                  strcat(DCom.L.Current_Dir,"/");
                               strcat(DCom.L.Current_Dir,DCom.L.List[DCom.L.current_position]);
                               DCom.L= ReadDir(DCom.L.Current_Dir);}
                              else
                              {strcat(DCom.R.Current_Dir,"/");
                               strcat(DCom.R.Current_Dir,DCom.L.List[DCom.L.current_position]);
                               DCom.R= ReadDir(DCom.R.Current_Dir);}
                                //{if(  DCom.L.Type[DCom.L.current_position] == "<DIR>")


                                //    }
//mvaddstr(LINES,0,DCom.L.Current_Dir);
                               break;
// обработка нажатия мыши - не контролирует, какая клавиши нажата, только факт нажатия
	         //case  KEY_MOUSE:
                              /* if (getmouse(&event) == OK)
			          if(event.y==LINES-2) // попали в функциональные клавиши
				     if(event.x<COLS/3) // F1
                                         MyNote=Open_File();
				     if((event.x>COLS/3)&&(event.x<COLS*2/3)) // F2
			                 MyNote= File_Save(MyNote);
				     if(event.x>COLS*2/3) // F3
                                        ch = KEY_F(3);
				  else	 // просто установим курсор туда, куда попала мышь
				   {
                                    curposY=event.y;
			            curposX=event.x;
				   }*/
                  //            break;
// все остальные клавиши
		default  :
                    // mvaddstr(LINES,0,ch);
                               break;
                }
        }
  endwin();// разрушаем окно*/
  return 0;
}
