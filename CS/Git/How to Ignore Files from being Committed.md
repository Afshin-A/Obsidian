It is possible to configure git to ignore tracking or committing certain files by creating the `.gitignore` file in the root dir of the repository. This file will then contain the directory of all the files and folders we wish Git to ignore. 
For example, for our Obsidian notes, we are ignoring the configuration files for the application, which are stored in the `.obsidian` folder. Thus, the `.gitignore` file for this repository simply includes:
```
.obsidian/
```
Each new line contains a dir to be ignored.

Example `.gitignore` file for my Flask project:
```
# Log files
*.log
*.txt

# Database files
*.db

# Instance folder (Flask-specific)
instance/

# Logs folder
logs/

# IDE files
.idea/

# Virtual environment
venv/

# Python bytecode
__pycache__/

# Dependency files
requirements.txt

# Scraped backend logic
scrap/

# Enviroemtal Variables
.env
*.env

# Docker
Dockerfile
docker-compose.yml

# PyCharm files
.idea/
```


# How to ignore files that are already tracked?
If a file is already being tracked by git, simply adding it to the `.gitignore` file doesn't help. Instead, we must first untrack all files, then add them again as follows:

```bash
git rm -r --cached .
git add .
git commit -m "Remove ignored files"
```

