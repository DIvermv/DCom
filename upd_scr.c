#include "func.h"

#include <ncurses.h>

void update_screen(struct DCommander DCommander)
{
    erase(); //чистим экран
   update_panel(DCommander.L,0,DCommander.current_panel);
   update_panel(DCommander.R,COLS>>1,!DCommander.current_panel);
//int current_element; //номер текущего элемента
//int curposX,curposY;
//getsyx(curposY, curposX);

//выводим содержимое массива MyNote на экран построчно


       // Подписываем функциональные клавиши внизу экрана
           attron (COLOR_PAIR(3));
        	mvaddstr(LINES-2, (COLS/3-sizeof("F1 - LEFT PANEL"))/2,"F1 - LEFT PANEL");
	        mvaddstr(LINES-2, (COLS/3-sizeof("F2 - RIGHT PANEL"))/2+COLS/3,"F2 - RIGHT PANEL");
         	mvaddstr(LINES-2, (COLS/3-sizeof("F3 - Close File"))/2+COLS*2/3,"F3 - Close File");
           attroff (COLOR_PAIR(3));

           //move(curposY,curposX);// установка курсора на конец текста для дальнейшего ввода
}

void update_panel(struct Panel Pan, int delta, int activ) // отрисовываем панель
{

           attron (COLOR_PAIR(4));
            mvaddstr(0, delta+1,Pan.Current_Dir);
        	mvaddstr(1, delta+1,"Name");
           //attroff (COLOR_PAIR(3));
           //attron (COLOR_PAIR(4));
	        mvaddstr(1,delta+COLS/2-14,"Tipe");
           //attroff (COLOR_PAIR(4));
           //attron (COLOR_PAIR(5));
         	mvaddstr(1,delta+COLS/2-7,"Size");
           attroff (COLOR_PAIR(4));
           //mvaddstr(LINES-1,0,MyNote.Status);

     for (size_t i = 0; i < Pan.str_count; i++)
      {
           attron (COLOR_PAIR(2)); // устанавливаем общий цвет
             if(activ && (i==Pan.current_position)) // выделяем текущую строку
                 attron (COLOR_PAIR(1));
            mvaddstr(i+2, delta+1,Pan.List[i]);//
	        mvaddstr(i+2,delta+COLS/2-14,Pan.Type[i]);
         	//mvaddstr(1,delta+COLS/2-7,Pan.Files_size[i]);
         	if(activ && (i==Pan.current_position))// отключаем выделение
               attroff (COLOR_PAIR(1));
             else
           attroff (COLOR_PAIR(2));
      }


}
