import os
import serial
import subprocess

# Open serial port
ser = serial.Serial('/dev/ttyACM0', 115200, timeout=1)

# Initialize current working directory
cwd = os.getcwd()

while True:
    # Read a line from the serial device
    command = ser.readline().decode('utf-8').strip()

    if command:
        print(f"Executing: {command}")
        
        # Check if the command is 'cd' and handle it specially
        if command.startswith("cd"):
            try:
                # Extract the directory to change to
                directory = command.split(None, 1)[1]
                # Change the current working directory
                os.chdir(directory)
                # Update the cwd variable to reflect the change
                cwd = os.getcwd()
                output = f"Changed directory to {cwd}"
            except IndexError:
                # 'cd' command without directory, change to home directory
                os.chdir(os.path.expanduser("~"))
                cwd = os.getcwd()
                output = f"Changed directory to {cwd}"
            except Exception as e:
                # Handle errors (e.g., directory does not exist)
                output = str(e)
        else:
            # Execute other commands
            process = subprocess.run(command, shell=True, capture_output=True, text=True, cwd=cwd)
            output = process.stdout if process.stdout else process.stderr

        # Send back the output
        ser.write(output.encode('utf-8'))
