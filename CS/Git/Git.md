# Branches
Additional, short-lived branches are typically made when a new feature is being developed, when a bug is being fixed, or when we're experimenting to avoid fucking up the main branch. Once that feature is completed, reviewed and tested, it can be merged to the main branch. 
##### Viewing Branches
To view a list of local branches, use
```
git branch
git branch -v //shows a verbose list with more details
```
##### Comparing Branches
The `dif` command shows the changes made since the previous commit:
```
git diff
```
It can optionally take the name of a branch as argument to show the difference between that branch and the main branch:
```
git diff branch-name
```

When local and remote branches **diverge**, it means they've become inconsistent. There are local changes that haven't been pushed yet, or remote changes that haven't been pulled.

```
git log main..master
```
This will show what commits are in the `master` branch but not in `main`.
##### Creating Branches
We can only create local branches. Remote branches are created when we push local branches online. To create a branch:
```
git branch new-branch-name //creates a branch, but doesn't switch your current branch
```
This will cause a branch-off at the current commit. But we can choose at which node (commit) we want to branch off of our current branch by using that node's id in the `branch` command:
```
git branch new-branch-name-1 commit-id
```
##### Switching Branches
To switch branches, use
```
git checkout -b new-branch-name //creates and switches to the new branch
git switch new-branch-name //this command is exlusively used for switching branches. checkout has multiple uses.
``` 
**Tip:** When using the checkout command, press tab to autocomplete branch names  
**Tip:** You must commit or stash changes before switching to another branch or progress would be lost.
##### Renaming Branches
To rename the HEAD branch:
```
git branch -m new-name
```
To rename another branch:
```
git branch -m branch-name new-name-for-that-branch
```
##### Deleting Branches
To delete a branch:
```
git branch -d branch-name  
```

### Branching Models
Git doesn't enforce how many branches should be created or where. But there are common branching models projects follow.
#### GitHub Flow Workflow
This is a simple model with one long-lasting, main branch, usually named `master` or `main`. This branch holds stable, tested code. There may be multiple (relatively) short-lived branches created (and they may exist at the same time) for developing features, but are merged to the main branch. ==When there's a change to the main branch, other branches need to pull from it to make sure they don't fall behind too much.== The more you fall behind, the bigger headache you will get when it's time to merge your branch to main and there are merging conflicts.
#### Git Flow Workflow
There are 2 main branches: main and develop. This model is similar to GitHub flow, but it adds another long-lasting branch, named "release", into which the product is released when the project hits a milestone. Before releasing, a temporary branch is created for bug fixes, and is then merged to the `release`, and by extension to the other branches. Releases are labeled as `V0.1.0`, `V0.1.1`, and so on.
A **hotfix** is a short lived branch created on the release branch to fix any issues after release. It gets merged back to release, then to the reset of the branches.

<iframe width="532" height="298" src="https://www.youtube.com/embed/1SXpE08hvGs" title="The gitflow workflow - in less than 5 mins." frameborder="0" allow="accelerometer; autoplay; clipboard-write; encrypted-media; gyroscope; picture-in-picture; web-share" allowfullscreen></iframe>

## Merging Branches and Conflicts
Merge conflict happens when the same file is modified at the same line in different ways, and git can't infer which changes to keep.
Suppose you want to merge a branch `test` to the `main` branch. First, change to the branch `test`:
```
git checkout test
```
Then, use the `merge` command to merge to `main`:
```
git merge main
```
If at this point there are merge conflicts, one helpful thing to do is to abort the merge:
```
git merge --abort
```

Git will mark the files with symbols that show us what the p
```python
<<<<<<< HEAD 
# conflicting code in the current branch
=======
# conflicting code in the other branch
>>>>>>> test
```
Resolve the conflict by removing the symbols and selecting what code to keep (maybe a combination of both branches?), after which we can resume the merge as follows:
```
git merge --continue
```

When merging, git will automatically create a "merge commit" in `main` that has all the combined changes, and connects the two branches.

```tikz
\begin{document}
\begin{tikzpicture}[node distance={30mm}, very thick, main/.style={draw, circle}, every node/.style={fill=white, scale=1}, invisible/.style={draw=none, fill=none}] 

\node[main, fill=yellow] (1) {C1};
\node[main, fill=green] [below right of=1] (2) {C2};
\node[main, fill=green] [right of=2] (3) {C3};
\node[main, fill=yellow] [right of=1] (4) {C4};
\node[main, fill=lime] [above right of=3] (5) {C5};

\draw[->] (1) -- (2);
\draw[->] (2) -- (3);
\draw[->] (1) -- (4);
\draw[->] (4) -- (5);
\draw[->] (3) -- (5);

% 'invisible' is a custom style defined earlier
\node[invisible, left of=1] (start-main) {};
\node[invisible] [right of=5] (end-main) {};
\node[invisible] [right of=3] (end-test) {};

\draw[->] (start-main) -- (1);
\draw[->, dashed] (5) -- node {main} (end-main);
\draw[->, dashed] (3) -- node {test} (end-test);

\end{tikzpicture}
\end{document}
```

The [[Git#Comparing Branches|diff]] command can also be used to view changes made in a file since the previous commit:
```
git diff filename
```
These changes are shown in **patches**. Each patch is marked with blue, the color used to signify modification in git. Additions in the patches are shown in green, and deletions in red.

# Rebase
Merging is perfectly fine, but some people don't like the way it leaves the commit history to look like. With rebase, the commit history will look more linear, not so convoluted by branches.
The purpose of `git rebase` is similar to `git merge`, however it works differently behind the scenes. First, it stashes away `C4`. Then, it adds `C2` and `C3` to the main branch. Finally, it adds (or "rebases") `C4`. This modifies the parent of node (commit) `C4`, changing its hash id. We should not use rebasing for commits that are already pushed to a remote repository because it will change the commit history for the branch and other developers can't pul ==????More information needed==

```tikz
\begin{document}
\begin{tikzpicture}[node distance={30mm}, very thick, main/.style={draw, circle}, every node/.style={fill=white, scale=1}, invisible/.style={draw=none, fill=none}] 

\node[main, fill=yellow] (1) {C1};
\node[main, fill=green] [right of=1] (2) {C2};
\node[main, fill=green] [right of=2] (3) {C3};
\node[main, fill=lime] [right of=3] (4) {C4};

\draw[->] (1) -- (2);
\draw[->] (2) -- (3);
\draw[->] (3) -- (4);

\node[invisible, left of=1] (start-main) {};
\node[invisible] [right of=4] (end-main) {};

\draw[->] (start-main) -- (1);
\draw[->, dashed] (4) -- node {main, test} (end-main);

\end{tikzpicture}
\end{document}
```


The HEAD branch is the current active or checked-out branch.
To rebase, first switch to the desired HEAD branch.
```
git switch test
```
Then,
```
git rebase main
```
We just *rebased* on `main`. We merged changes from `test` to `main` in effect, but technically it is different than merging.
# Pushing and Pulling
The following two commands are identical:  
```
git push --set-upstream origin branch-name  
git push -u origin branch-name  
```
**Tip:** once upstream is set, subsequent pushes and pulls can be shortened to just `git push` and `git pull`. We've tied the local branch to the remote branch.

`origin` is the name of the remote server.
`branch-name` is the name of the branch on the remote server we are pushing to.

Another example. Here, we're pushing to the `feature-1` branch that erupts from the develop branch on the remote repository.
```
git push -u -origin develop/feature-1
```

**Another way to track branches:**
```
git branch --checkout local-branch remote-branch
```


# Staging Files
Any new or modified files must be tracked by git before they can be committed:
```
git add FILENAME
git add .
```
These are added to what's called the **staging area**.

There's a shortcut to simultaneously add and [[Git#Commit|commit]] **modified** files (**does not work with new files**).
```
git add -a -m "message title" -m "more details"  
```

We can even add specific patches in a file to the staging area:

```
git add -p filename
```
### Unstaging Files
Unstaging a file means removing it from the staging area.
```
git reset filename
```

# Committing
A good commit should
- only have 1 purpose. All changes in a commit should be about 1 topic. So if there are multiple changes, only stage those pertaining to the current topic. 
- have a good message. What's changed? Why? Any notes to be on the lookout?

```
git commit -m "short description" -m "detailed description"
```

## Uncommitting
This is done via the `reset` command. There are 3 variants: default, soft, and hard.
- **Soft**. `reset --soft HEAD~1`. Doesn't affect any unstaged changes in the current working directory. Does not affect any files/changes added to the staging area. However, the commit head is reverted to the specified pointer (`HEAD~1` in this case). It's commonly used to undo the last commit, make changes, and commit again (because no changes are lost).
- **Default**. `reset HEAD~1`. Just like a soft reset, it doesn't affect any unstaged changes. However, staged files are cleared, and staging area now holds the state of the project from the commit we're resetting to. So, if we commit now, we reset the project to that state. ==This also means any commits in between are unreachable and will be deleted by git's garbage collection.==
- **Hard**. `reset --hard HEAD~1`. A hard reset also removes unstaged changes in the working directory. All commits in between become unreachable.

**`HEAD`** is a pointer to the most recent commit. We can use it to point to previous commits. For example **`HEAD~1`** points to 1 commit before the most recent commit. To go back to that commit:
```
git reset HEAD~1
```
This is effectively undoing the previous commit.

We can also use commit ids for `rest`. These are retrieved from the commit log:
```
git log
```
**Tip:** Press space to view more items in list. Press `Q` at the end to quit.

The log reveals a list of made commits in reverse chronological order (newest to oldest). Each commit will have an id, author, date, commit descriptions, merge conflict details, etc.. The id can be used to unstage files further to a previous commit. For example, an id would look something like `b012bac9eea83d89rgawefdsgaert42d06331a3d070b3b`.
```
git reset id
```

# Pull Requests
This is a GitHub (or other git hosting website) feature, not git.
You can configure a GitHub repository with roles, so that only owner and admins can push commits. Everyone else must submit a **pull request**. The proposed changes would then be reviewed and the request would either be accepted or rejected (until necessary changes are made).
It's possible to fork a public repository, make changes, and submit a pull request for your changes to be merged with the repository.
  
  

# Cloning
When cloning a repo, files from the main branch will be downloaded into the git directory. Attempting to view the repo branches locally will only show the main branch:
```bash
git branch
```
To view all hidden/remote branches, we use,
```bash
git branch -a
```



# https://marklodato.github.io/visual-git-guide/index-en.html
