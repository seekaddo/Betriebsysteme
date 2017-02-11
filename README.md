# Betriebsysteme(BICCS)
My personal notes for the semester course. System programming in Linux. Basically i will be keeping all the light things here,
sometimes is not easy to remember all the times i learn. This page will be my refresh page es live progress with a lot of stuffs.
Fill free to use the code and also learn from me as we go along. If you find any errors or disagreements you can always open an issue

###INTRODUCTION

    ##USEFUL BOOKS FOR THE SEMESTER
    * [The Linux Programming Interface](http://shop.oreilly.com/product/9781593272203.do)
    * [Linux System Programming](http://shop.oreilly.com/product/9780596009588.do)
    
    
###LECTURE[1] Linux Filesystem and Management
    ##USEFUL METHODS
          #stat family
            *int stat (const char *path, struct stat *buf);
            *int fstat (int fd, struct stat *buf);
            *int lstat (const char *path, struct stat *buf);
            
            ##File permission bits
            * S_IFMT     0170000   bit mask for the file type bit field used with (mode & S_IFMT)
            
             Mash          | 12 Bits cor   | file type   | symbol
             --- |  --- | ---  | --- 
            | S_IFSOCK      | 0140000       |socket       | s     |
            | S_IFLNK       | 0120000       |symbolic link| l     |
            | S_IFREG       | 0100000       | regular file| -     | 
            | S_IFBLK       | 0060000       | block device| b     |
            | S_IFDIR       | 0040000       | directory   | d     |
            | S_IFCHR       | 0020000       | cha.-device | c     |
            | S_IFIFO       | 0010000       | FIFO        | p     |
            
 #more here [Linux man Page](http://man7.org/linux/man-pages/man2/stat.2.html)
  #Layout of mode_t bit mask for the file permission
<---File--> | <-----------------type Permissions--------------> |
...   |  |  |  |U | G | T | R | W | X | R | W | X | R | W | X |
| ------------- ------------- -----------------------:|

fieltype | <------- | permission----------->
--- | --- | ---
*Still* | `renders` | **nicely**
1 | 2 | 3
