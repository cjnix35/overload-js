import os
from threading import Thread


OS = os.name    # Windows - "nt"  ,  Mac/Linux - "posix"

# POSIX cd build/ && ./preview
# Windows cd build\\Release && preview.exe
POSIXCMD = "cd build/ && ./preview"
NTCMD = "cd build\\Release && preview.exe"

NPMCMD = "npm start"


def executeCommand(command: str):
    try:

        os.system(command)
    except Exception as e:
        print("ERROR IN executeCommand():", e)


def openDev(system):
    try:

        npm_thread = Thread(target=executeCommand, args=[NPMCMD])

        if system == "nt":
            preview_thread = Thread(target=executeCommand, args=[NTCMD])
        else:
            preview_thread = Thread(target=executeCommand, args=[POSIXCMD])

        npm_thread.start()
        preview_thread.start()

        npm_thread.join()
        preview_thread.join()

    except Exception as e:
        print("ERROR IN openDev():", e)


if __name__ == "__main__":

    openDev(OS)
