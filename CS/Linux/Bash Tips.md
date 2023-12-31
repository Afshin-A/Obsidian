# Keyboard Shortcuts
| Shortcut | Explanation |
| ---------| ------|
| Ctrl + Shift + C | Copy|
| Ctrl + Shift + V | Paste |
| Ctrl + A | home |
| Ctrl + E | end |
| Ctrl + U | Delete line to end |
| Ctrl + K | Delete line to home |
| Ctrl + W | Delete previous word |
| Ctrl + R | Search history |
| Ctrl + L | Clear Screen |
| Ctrl + D | Exit terminal |

# Tips
- You can use `Tab` to auto complete a file or dir name. But this only works when there is no ambiguity in the name. For example, the `~` dir contains `Downloads` and `Documents`. If you type `cd ~/Do` and press `Tab`, the command will not auto-complete. However, `cd ~/Dow` + `Tab` will produce `cd ~/Downloads/`
- Just as `!!` refers to the previous command, `!$` refers to the last argument of the previous command.
- `echo $SHELL` prints the dir of shell executable.
- bash is a popular and commonly used shell. zsh (or Z Shell) is another shell that adds has more functionality such as auto-completion, fixing spelling errors, etc. After installing, use the command `zsh` to start. Use `Ctrl + D` to revert to bash. 
**How do I make zsh the default shell?**
- You can given an *alias* to a command:
```
alias showAllFiles='ls -la'
```
Then you can enter `showAllFiles` for the command `ls -la`. All aliases and enviromental vars are lost when we exit the teminal. But these can be permanently added into the hidden, shell start up file `~/.bashrc`. Don't forget the **dot**.


execute commands in a file
`source file.sh`


# Commands
## `cp`
Used to copy files.
For example, we can use the following to copy all files from current dir to a parent dir.
```bash
cp -R * ..
```


## `mv`
Used to move files.
It can also be used to rename a file. The effect is the same as moving a file with a new name.
```bash
mv ./file1.txt ./file2.txt
```


## `ps`
This command shows the current running processes.


## `man`
Short for manual.
```bash
man grep
```


## `touch`
Main use of this command is to *touch* a file's time stamp (change it to now). But it can also create a new file if it doesn't already exist. Use the `-c` option (short for `--no-create`) to mitigate that behavior:
```bash
touch example.txt -c` 
```


## `grep`
Powerful command that is used to find text in non-binary files like text or md. **It does not work on binary files like word or pdf.**
The basic command goes like: 
```bash
grep "someText" file.txt
```
But `grep` also has a few useful options:
```bash
grep -i -r -n "mathematics" ./*
```
Here, the search is case insensitive (`-i`), is recursive in the current directory (`-r`), and returns line number where the string "mathematics" was found (`-n`).

You can also use `grep` to search the results of another command. For example,
```bash
ls -al | grep -in "mathematics"
man find | grep "type"
```
returns all files in current directory that have "mathematics" in their names. `|` is called the pipe operator and redirects the result of one command as input for another command.


## `find`
Another useful command for finding files. It can use file attributes like name, permissions, size, and others to find files:
```bash
find ./ -perm 760 -size -10k -type f -iname "*.md" -exec grep -i "hello" {} \;
```
Find all files in the current directory and subdirectories that have their permissions as read, write, and execute for owner, read and write for the primary user group, and no permissions for others, file size of less than 10 kilobytes, type is file (not directory), and with any name that ends with the extension .md (case insensitive). Then, execute the grep command **for each file** to find the word "hello" (case insensitive). 
`{}` is a placeholder. Remember that the `grep` command needs a directory to work with. The curly braces represent each file that is returned by the `find` command.
`\;` represent the end of the `-exec` option.
Replace `\;` with **`+`** to mitigate the number of calls `grep` will make. Instead of `grep` executing for each time, `+` overrides this default behavior to call `grep` on multiple files at once and reduce the number of calls, therefore improving performance.
```bash
find ./ -perm 760 -size -10k -type f -iname "*.md" -exec grep -i "hello" {} +
```


## `chmod`
"Change mode" command changes permissions for files and directories. In Linux, permissions are represented by a score system. Reading is worth 4 points, writing (**and removing**) is 2, and executing is 1. For example, the command
```bash
chmod 777 ./example.txt
```
sets the permissions for the file example.txt to read, write, and execute for owner, user group, and everyone else.

We can also add specific privileges to certain groups by using options.

For example, the following recursively remove reading permissions for the primary group for all files in current directory:
```bash
chown g-r -R ./
```

The following adds writing permissions for others:
```bash
chown o+w ./example.txt
```

Furthermore,
- `u` represents owner user
- `g` represents group primary
- `o` represents others
- `w` represents write
- `r` represents read
- `x` represents execute
- `-` means remove
- `+` means add

The following removes writing privileges for everyone, for all files in the current and sub directories
```bash
chown ugo-w -R ./
```
and is the same as
```bash
chown -w -R ./
```
In other words, if we omit the user, the command will apply the changes to everyone by default.


## `chown`
Change ownership. This command can change the owner and the group. For example,  the following changes ownership to the user "afshin" and the group to "groupA" recursively to all files in the current directory.
```bash
chown afshin:groupA -R ./
```


## Variables
We can define variables like `name=Afshin` and retrieve them like `$name`. Variables can be used in commands:
```bash
touch $name.txt
```


## `ln`
Used to create links to files, directories, and other links. We can create a link that links to another link, and so on, before linking to a file or directory (link2->link1->file).
Soft link:
```bash
ln -s file.txt linkName
```

## `cat`
Used to concatenate or display files into terminal.
For example,
```bash
cat file.txt 
```
will display the file.
`cat` can also create files:
```bash
cat > file.txt
```
Upon entering this command, the terminal will allow you to enter contents for the file. **But this will override contents of existing files.** To concatenate content to the file, use the following:
```bash
cat >> file.txt
```
The `>` operator redirects the output of the `cat` command from the screen to the file. We can even use the `cat >` to redirect audio files to different devices ("in Linux, everything is a file.")
```bash
cat music.mp3 > /dev/audio
```
This is called **input redirection**.

## `ls`
This basic command lists files and dirs.
```bash
ls -alR
```
- `a` shows all  (including hidden) files
- `l` prints more details about the files (like perms and last modification date)
- `R` recursively applies the command to the subdirectories in the current dir and prints it in a nice way.

## `rm` & `rmdir`
Used to remove files. The latter is to remove directories.

# `mv`
Can be used for files and dirs

# `mkdir`
Used to create a dir

## `history`

## `pr` & `lp`


## `zip`
