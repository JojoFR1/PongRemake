import os, sys, shutil

"""
    Program created by Jojo to make the build process with
    the CMake tool easier.
    
    This program requires the CMake tool to be installed
    on your machine.
"""

PROJECT_NAME = "PongRemake"        # Name of the project
BUILD_TYPES = ["debug", "release"] # Supported build types
LIB_TYPES = ["static", "shared"] # Supported lib types

def build(build_type: str, lib_type: str):
    BUILD_DIR = f"bin-int/{lib_type}-{build_type}"
    
    # Check if the passed type is supported
    if build_type.lower() not in BUILD_TYPES: # The build type is not supported, stop the program
        print(f"\033[91m\033[1m[ERROR]\033[0m The build type has to be \033[4m", end="")
        print(*BUILD_TYPES, sep="\033[0m, \033[4m", end="\033[0m.\n")
        exit(-1)
    elif lib_type.lower() not in LIB_TYPES: # The lib type is not supported, stop the program
        print(f"\033[91m\033[1m[ERROR]\033[0m The lib type has to be \033[4m", end="")
        print(*LIB_TYPES, sep="\033[0m, \033[4m", end="\033[0m.\n")
        exit(-1)
    else:
        print(f"\033[95m\033[1m[BUILDING]\033[0m Buiding in {lib_type} {build_type} mode\033[0m...")
        # Execute the building command (check if command was successful with return code 0)
        if not os.system(f"cmake -B {BUILD_DIR} -S . -DCMAKE_BUILD_TYPE={build_type} -DBUILD_SHARED_LIBS={lib_type == 'Shared'} && cmake --build {BUILD_DIR}"):
            print(f"\033[92m\033[1m[SUCCESS]\033[0m The build files are located at {os.getcwd()}\{BUILD_DIR}\033[0m.")
        else: # An error occured during the build process, stop the program
            print(f"\033[91m\033[1m[ERROR]\033[0m The build encountered an error. See the error above\033[0m.")
            exit(-1)

def run(build_type: str, lib_type: str):
    BUILD_DIR = f"bin\{lib_type}-{build_type}"
    build(build_type, lib_type) # Build the project
    
    print(f"\033[95m\033[1m[RUNNING]\033[0m Running in {lib_type} {build_type} mode\033[0m...")
    # Execute the program (check if command was successful with return code 0)
    if not os.system(f"{BUILD_DIR}\{PROJECT_NAME}.exe"):
        print(f"\033[92m\033[1m[SUCCESS]\033[0m The program executed correcly\033[0m.")
    else: # An error occured while running the project, stop the program
        print(f"\033[91m\033[1m[ERROR]\033[0m The program encountered an error. See the error above\033[0m.")
        exit(-1)


# Check if the CMake tool is installed
if shutil.which("cmake") is None: # The CMake tool is missing, stop the program
    print(f"\033[91m\033[1m[ERROR]\033[0m You need the CMake tool installed.")
    print("        Get it at https://cmake.org/download/.")
    exit(-1)
    

# Check if there's at least one argument ('help', 'build' or 'run')
if len(sys.argv) <= 1 : # There's no argument, stop the program
    print(f"\033[91m\033[1m[ERROR]\033[0m You need one or more argument.")
    print("        Run 'python build.py help' for more information.")
    exit(-1)

# Match-case for all supported actions
match sys.argv[1].lower():
    case "help":
        print("Usage")
        print("     python build.py help                           = Get this help text.")
        print("     python build.py build [build-type] [lib_type]  = Build the project.         (build-type: default=Debug | lib_type: default=Static)")
        print("     python build.py run [build-type] [lib_type]    = Build and run the project. (build-type: default=Debug | lib_type: default=Static)")
    case "build":
        build(sys.argv[2] if len(sys.argv) > 2 else "Debug", sys.argv[3] if len(sys.argv) > 3 else "Static")
    case "run":
        run(sys.argv[2] if len(sys.argv) > 2 else "Debug", sys.argv[3] if len(sys.argv) > 3 else "Static")
    case _: #The argument is unknow, stop the program
        print(f"\033[91m\033[1m[ERROR]\033[0m Unknow argument.")
        print("        Run 'python build.py help' for more information.")
        exit(-1)
