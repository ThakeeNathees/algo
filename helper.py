
import os, sys

if __name__ == '__main__':
    if sys.argv[1] == 'gen-tester':
        os.chdir('mydbg')
        os.system('python gen.py')
        os.chdir('..')
        os.system('move "%s\\mydbg\\mydbg.h" "%s\\mydbg.h"'% (os.getcwd(), os.getcwd()))
        
