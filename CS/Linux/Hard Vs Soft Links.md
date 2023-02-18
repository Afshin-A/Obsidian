A hard link can only be created for a file, not directories. It is an independent file with a new name that is linked to an original file; both of these files are in the file system data structure. There can be multiple hard links to the file, and they are all unaware of each other, or that they are links. Interestingly, removing the original file does not invalidate the links. That is because, as long as there are links to the file, it is not truly removed and still exists in the data structure. Therefore, **a file is removed only when there are no references to it.**

A soft link (symbolic) link is like a shortcut to a file. If the file is moved, renamed, or removed, the links become invalid.

