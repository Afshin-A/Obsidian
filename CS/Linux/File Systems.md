# Union File System
This file system is made up of 3 layers. Each layer consists of files and directories.
- Lower layer - this is a read-only file. If we attempt to modify a file in this layer, a copy of the modified layer is created in the upper layer, while the original file remains untouched.
- Upper layer
- Overlay or merged layer - this layer is a union (hence the name of the file system) of the lower and upper layers. When there's a duplicate file in both the lower and upper layer, the file from the upper layer shows in the merged layer.

[[Computer Networking#Containers|Docker]] images use this file system. Each instruction adds a layer on top of the previous instruction.