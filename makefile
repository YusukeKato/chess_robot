#makefile for chess_main
#target: chess_main.exe
all: chess_main.exe

chess_main.exe: chess_main.obj chess_robot.obj chess_ai.obj

chess_main.obj: chess_main.c chess.h
		  		bcc32 -c chess_main.c
				
chess_robot.obj: chess_main.c
				 bcc32 -c chess_main.c
				 
chess_ai.obj: chess_main.c
			  bcc32 -c chess_main.c
			  
chess_opencv.obj: chess_main.c
				  bcc32 -c chess_opencv.c