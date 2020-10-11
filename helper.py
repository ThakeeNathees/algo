
import os, sys, subprocess

def copy2clip(txt):

    if 'win' in sys.platform:
        cmd='echo '+txt.strip()+'|clip'
        return subprocess.check_call(cmd, shell=True)
    elif 'darwin' in sys.platform:
        cmd='echo '+txt.strip()+'|pbcopy'
        return subprocess.check_call(cmd, shell=True)
    else:
        raise "might be the same as mac (not sure)"

## convert leetcode array to c++ array
def leet_arr_fix(arr_str):
    return arr_str.replace('[', '{').replace(']', '}')

#######################################

if __name__ == '__main__':
    if sys.stdout.isatty():
        RED = "\033[91m"
        END = "\033[0m"
    else:
        RED = ""; END = ""

    while True:
       cmd = input('>> ')
       cmd = cmd.strip()
       if cmd.startswith('leetarr'):
           cmd = cmd[7:].strip()
           if len(cmd) == 0:
               print(RED + "expected an array argument" + END)
           else:
               copy2clip(leet_arr_fix(cmd))
       elif cmd.strip() == 'exit':
           exit()
       ## TODO: add more
       else:
           if len(cmd.strip()) > 0:
               print(RED + "invalid command" + END)
