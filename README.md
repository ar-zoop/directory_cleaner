# Directory Cleaner

If you're a web developer, you know that managing files and folders in your project directory can be a challenge. You may have accumulated many files over time, and it's not always clear which files are still in use and which can be safely deleted. This directory cleaner script can help you organize your project by creating a new folder for all the files that are being used in your source code.

The script is written in C++ and requires the GCC compiler to compile and run. To use the script, download it and save it in the directory where your project files are located. Open a terminal window or command prompt and navigate to the directory using the 'cd' command. Then, compile the script using GCC by typing 'g++ directory_cleaner.cpp -o directory_cleaner' and pressing enter. Finally, run the script by typing './directory_cleaner' and pressing enter.

The script will prompt you to enter the relative path of your index file, which is typically the main HTML file for your website. Once you've entered the path, the script will create a new folder in the same directory called 'used_files' and move all the files that are being used in your code into that folder.

By using this script, you can clean up your project directory and make it easier to find the files you actually need. However, be sure to test your website thoroughly after running the script to make sure that everything still works as expected.
