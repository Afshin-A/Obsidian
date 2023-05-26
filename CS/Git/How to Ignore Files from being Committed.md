It is possible to configure Git to ignore tracking or committing certain files by creating the `.gitignore` file in the root dir of the repository. This file will then contain the directory of all the files and folders we wish Git to ignore. 
For example, for our Obsidian notes, we are ignoring the configuration files for the application, which are stored in the `.obsidian` folder. Thus, the `.gitignore` file for this repository simply includes:
```
.obsidian/
```
Each new line contains a dir to be ignored.