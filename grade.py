# Put this script in the root directory with
# everyones monorepo.
# You can download all of the repos from 'github classroom assistant'
# This should help speed the grading of the labs.
# Run this with `python grade.py`
#
#
#
import os

# compiles a file and runs it
def compileFile(msg,command,run):
    os.system(command)
    os.system(run)

# pick an assignment to grade
def lab2(assignment_name):
    # grab all of the directories
    for d in os.listdir(os.getcwd()):
        print("======== Grading "+d+" ========")
        for root, dirs, files in os.walk(d,topdown=False):
            for name in files:
                if assignment_name in os.path.join(root,name):
                    if "linkedlist.c" in name:
                        cwd = os.getcwd()
                        os.chdir(os.path.dirname(os.path.join(root,name)))
                        compileFile("running part 3","gcc linkedlist.c -o linkedlist","./linkedlist")
                        os.chdir(cwd)

def main():
    # Grading lab 1
    lab2("Lab2_")

if __name__ == "__main__":
    main()
