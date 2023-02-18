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

## touch


## grep

