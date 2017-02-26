# Betriebsysteme(BICCS)
My personal notes for the semester course. System programming in Linux. Basically i will be keeping all the light things here,
sometimes is not easy to remember all the times i learn. This page will be my refresh page es live progress with a lot of stuffs.
Fill free to use the code and also learn from me as we go along. If you find any errors or disagreements you can always open an issue


##C Advices with special methods

```c
/*sizeof(p) * 2 + 1 might not be enough room for the textual representation of the pointer value produced by %p. A 0x prefix
is often present, and the standard leaves a lot of room for implementations to make architecture specific choices. 
You should declare a buffer with a larger size and use snprintf to avoid a potential buffer overflow. /*

char pstr[sizeof(p) * 2 + 2 + 1]; // Each byte of the pointer is two hexadecimal character, plus a potential 0x, plus terminator
snprintf(pstr, sizeof(pstr), "%p", (void *) p); // always use snprintf instead of sprintf.



/* When using realloc don't assign directly back to the pointer you pass to the function, think about what happens 
if realloc returns a null pointer. */
oldstr = realloc (oldstr, sizeof(char) * newsize); // create a new str and assign realloc to it and check for null


```

###INTRODUCTION

    #USEFUL BOOKS FOR THE SEMESTER
    
  * [The Linux Programming Interface](http://shop.oreilly.com/product/9781593272203.do)
  * [Linux System Programming](http://shop.oreilly.com/product/9780596009588.do)
  * [Modern Operating System](https://www.pearsonhighered.com/program/Tanenbaum-Modern-Operating-Systems-4th-Edition/PGM80736.html)
    
    
*Useful Methods
```c
// when str = NULL, size = 0, returns the size of the passed arguments
// good for creating arrays without knowing the size in advance
int snprintf(char *str, size_t size, const char *format, ...); 
//then can this be used to create a fill in the array with the previous format.
int sprintf(char *str, const char *format, ...);

#include <unistd.h>
//get the working directory
//when buf NULL return a malloc to the current working dir
char * getcwd (char *buf, size_t size);

//returns malloc to the current dir
#define _GNU_SOURCE
#include <unistd.h>
char * get_current_dir_name (void);
            ***verboten****  char * getwd (char *buf);
            
//change working dir
#include <unistd.h>
int chdir (const char *path);
int fchdir (int fd);

//converting time to str
#include <time.h>
char *asctime(const struct tm *tm);
char *ctime(const time_t *timep);  // adds newline at the end of the string '\n'
size_t strftime(char *s, size_t max, const char *format, const struct tm *tm);


```
    
    
    
    
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
   ```c
   if ((statb.st_mode & S_IFMT) == S_IFREG)   //with already defined macros is easy to test the file types
    printf("regular file\n");
   `   ```
   Constant Test macro File type
   S_IFREG S_ISREG()   Regular file
   S_IFDIR S_ISDIR()    Directory
   S_IFCHR S_ISCHR()   Character device
   S_IFBLK S_ISBLK()   Block device
   S_IFIFO S_ISFIFO()  FIFO or pipe
   S_IFSOCK S_ISSOCK()  Socket
   S_IFLNK S_ISLNK()    Symbolic link   
   ```
   
   ```c
   //useful printf formats
   %ld, (long) sb->st_ino  //cast the inodes to long
   %ld  (long) sb->st_nlink // number of hard links 
   UID=%ld   (long) sb->st_uid // user id
   GID=%ld   (long) sb->st_gid // group id
   %lld  (long long) sb->st_size, sb->st_blksize and sb->st_blocks
   %s  ctime(&sb->st_ctime.tv_sec) // tv_sc for time_t
, 
   
   ```

* Permission
```c
#include <sys/types.h>
#include <sys/stat.h>

int chmod (const char *path, mode_t mode);
// needed to convert the user mode input [0600] to base 8 octal for the mode_t
long int strtol(const char *nptr, char **endptr, int base); 

int fchmod (int fd, mode_t mode);

//change owner
#include <sys/types.h>
#include <unistd.h>
// getgranam needed to get the id of the user-group
struct group *getgrnam(const char *name);
//-1 is specified if it need to be unchanged ( uid_t owner, gid_t group)
int chown (const char *path, uid_t owner, gid_t group);


int lchown (const char *path, uid_t owner, gid_t group);
int fchown (int fd, uid_t owner, gid_t group);

```
* file accessibility [man page](http://man7.org/linux/man-pages/man2/faccessat.2.html)
```c
#include <unistd.h>
int access(const char * pathname , int mode );
            Returns 0 if all permissions are granted, otherwise –1
    Constant Description   
F_OK Does the file exist?
R_OK Can the file be read?
W_OK Can the file be written?
X_OK Can the file be executed?
```
