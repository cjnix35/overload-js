import os
import re


def executeCommand(command: str):
    try:

        os.system(command)
    except Exception as e:
        print("ERROR IN executeCommand():", e)


def changeURI():
    # src="./assets/file.css"
    # ->
    # src="overload:/assets/file.css"

    pattern = r"(src|href)=\"\.\/[a-zA-Z0-9\.\/]+\""
    pattern_to_change = r"\./"
    replacement = r"overload:/"

    try:
        with open("./dist/index.html", "r+") as file:

            text = file.read()
            changed_text = re.sub(pattern_to_change, replacement, text)

            # Clear the file
            file.seek(0)
            file.truncate()

            file.write(changed_text)

    except Exception as e:
        print("ERROR IN changeURI():", e)


def build():
    executeCommand("npx tsc && npx vite build")
    changeURI()


if __name__ == "__main__":
    build()
