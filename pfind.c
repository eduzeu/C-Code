

#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>
#include <string.h>
#include <dirent.h>
void getpermissionstring (char filename[], char * perm){//creates the permission string for the current file using stat and its macros
    struct stat fileinfo;
    stat(filename, &fileinfo);
    if ((fileinfo.st_mode & S_IRUSR) != 0){
        perm[0] = 'r';
    }
    else{
        perm[0] = '-';
    }
    if ((fileinfo.st_mode & S_IWUSR) != 0){
        perm[1] = 'w';
    }
    else{
        perm[1] = '-';
    }
    if ((fileinfo.st_mode & S_IXUSR) != 0){
        perm[2] = 'x';
    }
    else{
        perm[2] = '-';
    }
    if ((fileinfo.st_mode & S_IRGRP) != 0){
        perm[3] = 'r';
    }
    else{
        perm[3] = '-';
    }
    if ((fileinfo.st_mode & S_IWGRP) != 0){
        perm[4] = 'w';
    }
    else{
        perm[4] = '-';
    }
    if ((fileinfo.st_mode & S_IXGRP) != 0){
        perm[5] = 'x';
    }
    else{
        perm[5] = '-';
    }
    if ((fileinfo.st_mode & S_IROTH) != 0){
        perm[6] = 'r';
    }
    else{
        perm[6] = '-';
    }
    if ((fileinfo.st_mode & S_IWOTH) != 0){
        perm[7] = 'w';
    }
    else{
        perm[7] = '-';
    }
    if ((fileinfo.st_mode & S_IXOTH) != 0){
        perm[8] = 'x';
    }
    else{
        perm[8] = '-';
    }
}
void checkdir(char* directory, char* permstring){
    DIR* dp;
    if ((dp = opendir(directory)) != NULL){
        struct dirent* dirp;
        char *tempdir = malloc(strlen(directory) + 256); // allocate memory dynamically
        if (!tempdir) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        strcpy(tempdir, directory);
        char* matchs = permstring;
        while((dirp = readdir(dp)) != NULL ){
            if (!strcmp(dirp->d_name, ".") || !strcmp(dirp->d_name, "..")){
                continue;
            }
            strcat(tempdir, "/");
            strcat(tempdir, dirp->d_name);
            struct stat fileinfo;
            char perm[10]; // increase the size by 1 for the null terminator
            char* dirsend = tempdir;
            if(stat (dirsend, &fileinfo) == 0){
                getpermissionstring(dirsend, perm);
                int match = 1;
                if (strcmp(matchs, perm) != 0){
                    match = 0;
                }
                if (match == 1 && S_ISREG(fileinfo.st_mode) == 1){
                    printf("%s\n", dirsend);
                }
                if (S_ISDIR(fileinfo.st_mode) == 1){
                    DIR* checker;
                    if ((checker = opendir(dirsend)) == NULL){
                        closedir(dp);
                    }
                    else{
                        closedir(checker);
                    }
                    checkdir(dirsend, matchs);
                }
                strcpy(tempdir, directory);
            }
        }
        closedir(dp);
        free(tempdir); // free the allocated memory
    }
    else{
        closedir(dp);
        fprintf(stderr, "Error: Cannot open directory '%s'. Permission denied.\n", directory); 
        exit(EXIT_FAILURE);
    }
}
int main(int argc, char* argv[]){
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <directory> <permissions>\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    int valid = 0;
    if (strlen(argv[2]) != 9){
        valid = 1;
    }
    for (int i = 0; i < 9; i++){
        if (argv[2][i] != 'r' && argv[2][i] != 'w' && argv[2][i] != 'x' && argv[2][i] != '-'){
            valid = 1;
        }
    }
    
    if ((argv[2][0] != 'r' && argv[2][0] != '-') || (argv[2][3] != 'r' && argv[2][3] != '-') || (argv[2][6] != 'r' && argv[2][6] != '-')){
            valid = 1;
    }
    if ((argv[2][1] != 'w' && argv[2][1] != '-') || (argv[2][4] != 'w' && argv[2][4] != '-') || (argv[2][7] != 'w' && argv[2][7] != '-')){
            valid = 1;
    }
    if ((argv[2][2] != 'x' && argv[2][2] != '-') || (argv[2][5] != 'x' && argv[2][5] != '-') || (argv[2][8] != 'x' && argv[2][8] != '-')){
            valid = 1;
    }
    
    if (valid == 1){
        fprintf(stderr, "Error: Permissions string '%s' is invalid.\n", argv[2]); 
        exit(EXIT_FAILURE);
    }
    char permstring[10]; // increase the size by 1 for the null terminator
    strncpy(permstring, argv[2], 9);
    permstring[9] = '\0'; // null-terminate the string
    char buf[strlen(argv[1])];
    char *sdir = realpath(argv[1], buf);
    char* ps = permstring;
    checkdir(sdir,ps);
    exit(EXIT_SUCCESS);
}