First, it would be helpful to understand how disk drives work: [How do Hard Disk Drives Work?  💻💿🛠](https://youtu.be/wtdnatmVdIg)

A hard drive contains magnetic discs (*platters*) that store data. Each platter is divided into concentric circles called *tracks*. And, each track is divided into sectors. A *sector* is the smallest physical storage unit on a disk drive, defined by the drive's manufacturer. Traditionally a sector stores exactly 0.5 KB of data, but  modern drive sectors can store 4KB.  
These concepts live on the hardware layer. 

File system defines the logic of how we organize data in the drive so we can retrieve it later. 

A *cluster* (AKA *allocation unit*) is a logical unit. It's a number of continuous sectors joined together, forming the smallest logical block of space the file system can assign files to. Files are assigned to one or more clusters, not to sectors. We couldn't keep track of all disk sectors because that would be too many nodes in our data structure. Assuming a 2TB drive with 512 byte sectors, we would have to manage a data structure with 4.24 billion nodes (sectors) in memory. The same principal is used in [[Postgres]]: it divides data into 8KB pages for I/O efficiently rather than tracking individual rows directly on disk. Similarly, an operating system groups sectors into clusters to optimize disk I/O and reduce memory overhead.
==Importantly, we can only assign 1 file to each cluster.== Consequently, the downside of having 4KB sectors is that, for example, a 10 byte file will waste the remaining free space in that cluster. This inefficiency is called *slack space* or *internal fragmentation*.

A disk *partition* is when the OS divides the physical storage drive into isolated, smaller units. These act as completely separate, logical drives. The OS the *Master Boot Record*, which is a table in the absolute first sector of the entire disk, to keep track of the continuous sector boundaries that make up each partition.

*Logical Block Addressing* (LBA) is a *scheme* and an abstraction layer: it is a predefined system for organizing and numbering sectors, and finding data. It treats the drive as a large, continuous array of sectors. It lives inside the drive controller. When we say it's an abstraction, we mean that the OS doesn't need to know how the drive finds data. A process says to the OS, get this file. The OS uses the file system to find the cluster the file lives in, then does math using the file size and file system information found in the VBR) to find the sectors. Then it sends a request to the storage driver and be like, read LBA $x$ through $y$. Think of LBA as the language the OS uses to communicate with the drive. 


The *Master Boot Record*, present at the absolute first sector of the storage drive, keeps track of the range of sectors for each partition. 
The first sector of every disk partition (LBA 0) is called the *volume boot record* (VBR). It is 512 bytes of information about the number of bytes per sector, number of sectors in cluster, filesystem information, etc.. Every partition has its own VBR, and it always lives in LBA 0.

**FAT** (file allocation table), Microsoft proprietary. Originally created by Microsoft for Windows, but every major OS now supports it and has its own implementation, but the rules are defined by Microsoft.
FAT is the index of the file system. This data structure is a contiguous array of 32-bit (4 bytes) integers written directly to the disk, immediately following the VBR and a few reserved sectors. 
There is usually a backup of the FAT that follows after the first one. If the hardware detects the first table is corrupted, the OS falls back to the second table.
The OS loads the FAT (or portions of it) into the RAM memory, performs the filesystem logic, and occasionally flushes the updated array back to the physical disk.

How big is the FAT array? Well, we mentioned each array element is a 32 bit number. Of these 32 bits, the last top 4 are used internally by the file system. So that leaves us with 28 bits. Therefore, the largest integer we can represent using 28 bits is $2^{28}$. So that's how many indices, and therefore, clusters the FAT32 file system can theoretically represent. Using 4KB clusters, the maximum size FAT32 supports would be:
$$
2^{28} \times 4 \ \text{KB} = 1,073,741,824 \ \text{KB} = 1 \ \text{TB}
$$
We can use larger clusters to accommodate for more space overall. But bear in mind that the larger the clusters (and therefore sectors), the more space is wasted by smaller files (causing internal fragmentation).

The name FAT32 comes from the fact that each element in FAT is 32 bits long.

As I explained, large files are stored across several sectors. In the FAT array, the value at each index represents the index of the next cluster of the current file.
```
+--------------------------------------------------------+
|   0  |   1  |   2   |  3  |   4  |   5  |   6  |   7   | ...
|---------------------------------------------------------
|      |      |   3   |  4  |  \0  |   0  |   7  |   8   | ...    
|--------------------------------------------------------+
```
The first 2 elements are reserved. The value at index 2 is 3. That means the file continues at index 3. At index 3, we see the value is 4. At index 4, we see the value is `\0`, signifying end of file (EOF). The actual value used in FAT is `0x0FFFFFFF`, but for simplification we used `\0` here.
The value 0 at index 5 means LBA 5 is available. To store the next file, the OS will do a linear scan of the FAT and find LBA 5 is free. Linear search would be slow if it restarts from the beginning of FAT. So the drive stores the number of free remaining clusters and the index of the most recently accessed cluster. 

`0x0FFFFFF7` is used for bad sectors. 
This is a form of a linked list, which is an abstract data structure and can be implemented in different ways. Here, instead of pointers, we use array indices to find the next node.

FAT32 has been around since Windows 98. It is the most compatible file system today and is still popular for formatting external drives like USB drives and SD cards.

FAT32 filesystem is represented by 1D arrays, so how does it represent parent-child directory relationships? You would naturally think of a tree for this.
Directories are files. Just like a regular file, the FAT table keeps track of the starting cluster. However, dirs are represented as ==arrays of 32 byte rigid structs of metadata in the clusters==. By rigid I mean static. Every file and subdirectory inside a dir gets its own place in this array. The metadata includes information such as name (the first 11 bytes), **size** (4 bytes), current directory, parent directory, and attribute flags such as is hidden, is system file, is read-only, etc.. It also defines whether it is a file or a directory using an attribute named `ATTR_DIRECTORY`. If it's set to 0, the struct is a file. If it's 1, it's a directory. Most importantly, it includes the starting cluster on disk

Did you know the largest file FAT32 supports is roughly 4GB? Each element is a struct of 32 bytes. Of these 32 bytes, 4 are used for size. The maximum that can be represented is therefore:
$$
2^{32}-1
$$
The size is stored in bytes. Converting this to GBs, we see that the ==largest file that can be stored in the FAT32 file system is 4GB.== This is major limitation of this file system that cannot be overcome. That is why modern file systems such as NFTS exists. Using 64 bits, NFTS can support up to 16 exabytes (16 billion gigabytes)!

If FAT32 only uses 11 bytes for file names (8 for name, 3 for extension; each char is 1 byte), then how are we allowed to have longer names in Windows?

Every partition has a root directory. For example, the Windows partition is named `c:\` by default. ==The root directory is hard-coded in the VBR.==
Let's say we want to read the file `C:\DOCS\REPORT.TXT`

The OS reads the VBR and sees the `C:\` dir starts at sector 2. It reads the array of structs and scans for `DOCS`. When it finds it, `DOCS` has `ATTR_DIRECTORY` set to 1, so it's a directory, and the starting cluster is 5. So the OS goes to cluster 5 and does the same thing again: it scans for `REPORT.TXT` and sees it's a file and it starts at cluster 8. Then it goes to cluster 8 and starts reading the file. It goes to index 9 in the FAT table and sees the value is 9, meaning the file continues in cluster 9. Finally, it sees the value at index 9 is EOF, so it knows end of file has been reached and it can safely close the stream.

The FAT array only ever answers the question, "Where does this data continue?"  ==It doesn't know the starting files.==

In the software layer, we need a way to store and retrieve data
It's an abstract layer that sits between our application that makes system calls to the OS, translating instructions so we know where on the physical media to retrieve data 
using low level data structures to organize data on disk so that it can be retrieved later