#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
// Add your system includes here.
// The includes listed in the lstat man page.
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ftree.h"

//gcc -Wall -std=gnu99 -g -o print ftree.c print_ftree.c


/*
 * Returns the FTree rooted at the path fname.
 *
 * Use the following if the file fname doesn't exist and return NULL:
 * fprintf(stderr, "The path (%s) does not point to an existing entry!\n", fname);
 *
 */

// void single_node(struct TreeNode *ftree, char *name, int permissions) {
//     ftree->contents = NULL;
//     ftree->next = NULL;

//     // Copy fname from readonly memory.
//     // char * name = strdup(fname);

//     ftree->fname = name;

//     ftree->permissions = permissions;
// }

struct TreeNode *generate_helper(const char *fname, char *name, char *path) {

    struct TreeNode *ftree = malloc(sizeof(struct TreeNode));

    // Realpath is the real path of file we want.
    // char *file_name = strdup(fname);

    int real_length = strlen(fname) + strlen(path) + 1;
    char real_file[real_length];

    strcpy(real_file, fname);
    real_file[real_length] = '\0';
    strncat(real_file, path, real_length);

    // We need to allocate space for a struct stat.  We'll pass
    // a pointer to this struct as an argument to lstat, and
    // the call on lstat will populate it with information about path.
    struct stat stat_buf;
    
    // Call lstat to populate stat_buf with information about path. 
    // Also, error check the system call and if it fails, return with exit code 1.
    // See the RETURN section of the man page to learn about what lstat returns.
    if (lstat(real_file, &stat_buf) == -1) {
        perror("lstat");
        fprintf(stderr, "The path (%s) does not point to an existing entry!\n", real_file);
    }

    // We'll use macro S_ISREG:
    if (S_ISREG(stat_buf.st_mode)) {
        // If fname is a Regular file.

        // printf("%s\n", path);
        // printf("%s\n", name);
        // printf("%s\n", real_file);

        if(name[0] != '.') {
            // Next, we'll use use the logical "and" operator to extract the permissions:
            int reg_permissions = stat_buf.st_mode & 0777;

            ftree->fname = name;
        
            ftree->permissions = reg_permissions;
        
            ftree->type = '-';
        
            ftree->contents = NULL;
            ftree->next = NULL;

        }

        
    }else if (S_ISLNK(stat_buf.st_mode)) {
        // If fname is a link file.

        if(name[0] != '.') {
            // Next, we'll use use the logical "and" operator to extract the permissions:
            int lin_permissions = stat_buf.st_mode & 0777;

            ftree->fname = name;
            ftree->permissions = lin_permissions;
            ftree->type = 'l';
            ftree->contents = NULL;
            ftree->next = NULL;
        }

    }else if (S_ISDIR(stat_buf.st_mode)) {
        // If fname is a directory.

        DIR *d_ptr = opendir(real_file);

        // Error check the system call (read about the return value in the man page)
        if (d_ptr == NULL) {
            perror("opendir");
            fprintf(stderr, "The path (%s) does not point to an existing entry!\n", real_file);
        }

        // Allocate a struct dirent pointer, which will be used to store information
        // about a directory entry.
        struct dirent *entry_ptr;

        // Call readdir to get struct dirent, which represents a directory entry.  The
        // order that entries are returned by readdir is not guaranteed.  

        entry_ptr = readdir(d_ptr);

        // Construct the Tree of fname.
        int dir_permissions = stat_buf.st_mode & 0777;
        ftree->permissions = dir_permissions;

        // Copy fname from readonly memory.
        // char * name = strdup(fname);
        
        ftree->fname = name;
        
        ftree->type = 'd';

        struct TreeNode *interminate = NULL;

        // Look into first directory of this file.
        while (entry_ptr != NULL) {
            
            char *sub_name = strdup(entry_ptr->d_name);

            if (strcmp(sub_name, ".") != 0 && strcmp(sub_name, "..") != 0 && sub_name[0] != '.'){

                // Conctruct the path of this file.
                int len = strlen(path) + strlen(sub_name) + 2;
                char this_path[len];

                // this_path = 'path/sub_name\0'.
                strcpy(this_path, path);
                this_path[strlen(path)] = '\0';
                strcat(this_path, "/");
                strncat(this_path, sub_name, len);

                struct TreeNode *this_node = malloc(sizeof(struct TreeNode));
                this_node = generate_helper(fname, sub_name, this_path);
               
                if (interminate == NULL) {
                    ftree->contents = this_node;
                }else {
                    interminate->next = this_node;
                }
                interminate = this_node;   

            }
            entry_ptr = readdir(d_ptr);
        }

        int close = closedir(d_ptr);

        // Close this directory and check error.
        if (close == -1) {
            perror("opendir");
            fprintf(stderr, "Occur error when close folder %s\n", real_file);
        }

    }return ftree;

}


struct TreeNode *generate_ftree(const char *fname) {
    char *name = strdup(fname);

    return generate_helper(fname, name, "");
}


/*
 * Prints the TreeNodes encountered on a preorder traversal of an FTree.
 *
 * The only print statements that you may use in this function are:
 * printf("===== %s (%c%o) =====\n", root->fname, root->type, root->permissions)
 * printf("%s (%c%o)\n", root->fname, root->type, root->permissions)
 *
 */
void print_ftree(struct TreeNode *root) {
    
    // Here's a trick for remembering what depth (in the tree) you're at
    // and printing 2 * that many spaces at the beginning of the line.
    // static int depth = 0;
    // printf("%*s", depth * 2, "");
    char link_file = 'l';
    char regular_file = '-';
    char directory = 'd';

    if (root) {
        static int depth = 0;
        // Your implementation here.
        
        char this_type = root->type;

        if (this_type - link_file == 0 || this_type - regular_file == 0) {
            printf("%s (%c%o)\n", root->fname, root->type, root->permissions);
            if (root->next) {
                printf("%*s", depth * 2, "");
                print_ftree(root->next);
            }
        
        }else if (this_type - directory == 0) {
            printf("===== %s (%c%o) =====\n", root->fname, root->type, root->permissions);
            depth ++;
            printf("%*s", depth * 2, "");
            print_ftree(root->contents);
        }
    }
}


/* 
 * Deallocate all dynamically-allocated memory in the FTree rooted at node.
 * 
 */
void deallocate_ftree (struct TreeNode *node) {
   
   // Your implementation here.
    if (node) {
        if (node->type == 'd') {
            if (node->contents) {
                deallocate_ftree (node->contents);
            }
        }else {
            if (node->next) {
                deallocate_ftree (node->next);
            }
        }
        free(node->fname);
        free(node);

    }
}