import os
import sys

def find_files(directory, extension):
    for root, dirs, files in os.walk(directory):
        for file in files:
            if file.endswith(extension):
                print(os.path.join(root, file))


if __name__ == "__main__":
    if len(sys.argv) > 2:
        directory = sys.argv[1]
        extension = sys.argv[2]
        find_files(directory, extension)