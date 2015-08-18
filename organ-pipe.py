#!~/bin/python

#Elizabeth Krenkel
#August 13, 2015

#A short script that rewrites a sequence of LBAs from most-to-least
#    frequent order into organ-pipe order, and then prints the
#    result to stdout.

import sys, argparse

def main():
    EXIT_STATUS = 0
    #For every line...
    result = []
    start = True
    for line in sys.stdin:
    #if the line number of the line we're looking at is even,
    #    we add it to the start of the list.
        if start:
            result.insert(0, line)
            start = False
        else:
        #If it is odd-numbered, we append it to the end. 
            result.append(line)
            start = True
    #We print out the resulting list. 
    for i in range(len(result)):
        print result[i]
    #and exit.  
    exit(EXIT_STATUS)

main()
    

        
        
    
