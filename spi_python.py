from PyQt5 import QtCore, QtGui, QtWidgets, QtTest
from PyQt5.QtWidgets import *
from gui_spi import Ui_MainWindow
import serial
import time
import os
import sys

os.system("cls")

ser = serial.Serial('COM6', 9600)
time.sleep(2)
# ser.write(5)
i = 0

def write_x(x):
    x = x + "\n"
    ser.write(bytes(x, 'utf_8'))
    time.sleep(0.5)

class ui(object):
    
    def __init__(self, object):
        self.ui = Ui_MainWindow()
        self.ui.setupUi(object)
        object.show()

        self.c1_max = " "
        self.n_start = " "
        self.n_step = " "
        self.i = 0
        

    def first(self):
        self.ui.pushButton.clicked.connect(self.start)

    def read_line(self):
        self.c1_max = self.ui.plainTextEdit.toPlainText()
        self.n_start = self.ui.plainTextEdit_2.toPlainText()
        self.n_step = self.ui.plainTextEdit_3.toPlainText()

    def serial_print(self):
        while(1):    
            b = ser.readline()
            string_n = b.decode()
            string_f = string_n.rstrip()
            l = string_f.split()

            if(string_f.split()[0] == "Enter"):
                print(string_f)
                if self.i == 0:
                    write_x(self.c1_max)
                    self.i = self.i + 1
                if self.i == 1:
                    write_x(self.n_start)
                    self.i = i + 1
                if self.i == 2:
                    write_x(self.n_step)
                    self.i = 0

            elif(string_f.split()[0] == "Counter"):
                os.system("cls")
                print(string_f)   

    def start(self):
        self.ui.pushButton.setEnabled(False)
        write_x(str(5))
        time.sleep(2)
        self.read_line()
        self.serial_print()       

    def reset(self):
        self.ui.pushButton.toggle()
        # write_x(5)
        self.read_line()
        self.serial_print()


if __name__ == "__main__":
    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = ui(MainWindow)
    ui.first()
    sys.exit(app.exec_())     

ser.close()