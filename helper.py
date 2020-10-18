
import os, sys

if __name__ == '__main__':
    if sys.argv[1] == 'gen-tester':
        os.chdir('tester')
        os.system('python gen.py')
        os.chdir('..')
        os.system('move "%s\\tester\\tester.h" "%s\\tester.h"'% (os.getcwd(), os.getcwd()))
        
