all:
	gcc main.c ReadDir.c upd_scr.c key_press.c -o DComander -lncurses -lpthread
