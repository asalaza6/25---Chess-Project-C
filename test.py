import subprocess
import os
import sys
import shutil as SH
import signal
import time
import argparse as ap
import base64
make_process = subprocess.Popen("make clean; make", shell=True, stdout=subprocess.PIPE, stderr=sys.stdout.fileno())
while True:
    line = make_process.stdout.readline()
    if not line:break
    print (line) #output to console in time
    sys.stdout.flush()

p = subprocess.Popen("./Main",shell=True, stdin=subprocess.PIPE, stderr=sys.stdout.fileno())
def valueTesterFunction(mylist, mySubprocess):
    for i in listofMoves:
        p.stdin.write(i.encode())
        p.stdin.write('\n'.encode())
        #p.stdin.write('')


# **************************    Don't  Touch the Above Code   ************************************

# Only addnew List & if you add new list please delete the current list. and 
# in the valueTesterFunction change the first value of the argument to accomodate to your need, but don't change 'p'
# run the fucking program using 'python3 test.py'

# **************************    Don't  Touch the Above Code   ************************************

# this is the list of moves
listofMoves= ["1", "A2", "A4", "A7", "A5","B2", "B4","B7", "B5","C2", "C4","C7", "C5","D2", "D4","D7", "D5","E2", "E4","E7", "E5","F2", "F4","F7", "F5","G2", "G4","G7", "G5","H2", "H4","H7", "H5", "B1", "A3", "B8", "A6"]
# this is the function running the listofMoves, make sure to change the name of list if you change it.
valueTesterFunction(listofMoves,p)


     