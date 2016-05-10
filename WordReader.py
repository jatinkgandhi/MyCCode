# -*- coding: utf-8 -*-
from Tkinter import *
import tkMessageBox
import subprocess
import time
import os
import sys
import os.path
import random
from tkFileDialog import askopenfilename
import string;

# For timestamp
import datetime
import time;
# from espeak import espeak


delaytable = (0.2,0.3,0.4,0.5);

def Spritz_StartReading():
	TextToRead = Txt_StatusText.get(1.0,END);
	Txt_StatusText.delete(1.0,END);
	
	# print TextToRead;

	words = TextToRead.split(' ');
	for word in words:
		EntryList.delete(0, END);
		EntryList.insert(0, word);
		root.update_idletasks();
		root.update();
		delay = 0;
		if(len(word) > 6):
			delay = 0.4;
		elif(len(word) > 4):
			delay = 0.3;
		else:
			delay = 0.2;
		
		
		time.sleep(delay);
	
		# Additional delay at the end of line.
		if(word.find('.') != -1):
			time.sleep(1);

	EntryList.delete(0, END);
	pass;
	return;


root = Tk()
Txt_StatusText          = Text(root,  height=18,width=87,bd=2);
EntryList				= Entry(root,  justify="center",bd=2);
Btn_StartReading		= Button(root, text = "Start Reading", command = Spritz_StartReading,width=20,bd=3);


def main():

	# espeak.synth("Hi All...")

	# get screen width and height
	ws = root.winfo_screenwidth();#This value is the width of the screen
	hs = root.winfo_screenheight();#This is the height of the screen
	#Set screen dimentions
	w = 720;# 570; # width
	h = 480;# 400; # height
	# calculate position x, y
	x = (ws/2) - (w/2);
	y = (hs/2) - (h/2);
    
	#This is responsible for setting the dimensions of the screen and where it is placed
	root.geometry('%dx%d+%d+%d' % (w, h, x, y));

	# disable resize else it will spoil the layout.
	root.resizable(0,0); # only minimize or close allowed
	
	Txt_StatusText.grid(row=1, column=0,columnspan=2, rowspan=4,padx=10, pady=10);
	EntryList.grid(row=0, column=0,columnspan=2, rowspan=1,padx=10, pady=10);
	Btn_StartReading.grid(row=6, column=0,columnspan=2, rowspan=1,padx=10, pady=10);
	root.mainloop();


	return;

if __name__ == '__main__':	main();
