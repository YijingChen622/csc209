#include <stdio.h>
// Add your system includes here.
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ftree.h"

/*
 * Hint: consider implementing a recursive helper function that
 * takes fname and a path.  For the initial call on the 
 * helper function, the path would be "", since fname is the root
 * of the FTree.  For files at other depths, the path would be the
 * file path from the root to that file.
 */
struct TreeNode *generate_ftree_helper(char *fname, char *path) {
    // Build a file tree
    struct TreeNode *ftree = malloc(sizeof(struct TreeNode));
    // Check if there are enough space to store the ftree.
    if (ftree == NULL) {
        perror("malloc");
        exit(1);
    }

    // Get the path of the file
    int true_len = strlen(fname) + strlen(path) + 1;
    char true_path[true_len];
    strcpy(true_path, path);
    true_path[strlen(path)] = '\0';
    strcat(true_path, fname);

    // Fills in the struct stat stat_buf with information about the file
    struct stat stat_buf;
    // Check if the file exist or not
    if (lstat(true_path, &stat_buf) == -1) {
        fprintf(stderr, "The path (%s) does not point to an existing entry!\n", fname);
        exit(1);
    }

    // For regular files 
    if (S_ISREG(stat_buf.st_mode)) {
        if(fname[0] != '.') {
            ftree->fname = fname;
            int permissions = stat_buf.st_mode & 0777;
            ftree->permissions = permissions;
            ftree->type = '-';
            ftree->contents = NULL;
            ftree->next = NULL;
        }
    // For links
    } else if (S_ISLNK(stat_buf.st_mode)) {
        if(fname[0] != '.') {
            ftree->fname = fname;
            int permissions = stat_buf.st_mode & 0777;
            ftree->permissions = permissions;
            ftree->type = 'l';
            ftree->contents = NULL;
            ftree->next = NULL;
        }
    // For directories
    } else if (S_ISDIR(stat_buf.st_mode)) {
        // Open the directory
        DIR *d_ptr = opendir(true_path);
        // Error check opendir
        if (d_ptr == NULL) {
            perror("opendir");
            exit(1);
        }

        ftree->fname = fname;
        int permissions = stat_buf.st_mode & 0777;
        ftree->permissions = permissions;
        ftree->type = 'd'; 
        ftree->next = NULL;
        ftree->contents = NULL;    

        struct TreeNode *temp_ftree = NULL;

        // Allocate a struct dirent pointer, which will be used to store information
        // about a directory entry.
        struct dirent *entry_ptr;
        entry_ptr = readdir(d_ptr);

        while (entry_ptr != NULL) {         
            if (entry_ptr->d_name[0] != '.'){

                // Conctruct the path of this file, should be "<path>/<sub_name>" and null-terminated.
                int len = strlen(true_path) + 2;
                char sub_path[len];
                strcpy(sub_path, true_path);
                sub_path[strlen(true_path)] = '\0';
                strcat(sub_path, "/");
                char *sub_name = strdup(entry_ptr->d_name);

                // Construct the node in the sub-directory
                struct TreeNode *sub_node = NULL;

                sub_node = generate_ftree_helper(sub_name, sub_path);

                if (temp_ftree == NULL) {
                    ftree->contents = sub_node;
                }else {
                    temp_ftree->next = sub_node;
                }
                temp_ftree = sub_node;
            }
            entry_ptr = readdir(d_ptr);
        }
        // Close the directory
        int close = closedir(d_ptr);
        // Error check opendir
        if (close == -1) {
            perror("closedir");
            exit(1);
        }
    }
    return ftree;
}


/*
 * Returns the FTree rooted at the path fname.
 *
 * Use the following if the file fname doesn't exist and return NULL:
 * fprintf(stderr, "The path (%s) does not point to an existing entry!\n", fname);
 *
 */
struct TreeNode *generate_ftree(const char *fname) {

    // Your implementation here.
    char *name = strdup(fname);

    return generate_ftree_helper(name, "");

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
    static int depth = 0;
    printf("%*s", depth * 2, "");
    // // Your implementation here.
    if (root != NULL) {
        if (root->type == '-' || root->type == 'l') {
            printf("%s (%c%o)\n", root->fname, root->type, root->permissions);
            if (root->next) {
            print_ftree(root->next);
            }
        } else if (root->type == 'd') {
            printf("===== %s (%c%o) =====\n", root->fname, root->type, root->permissions);
            if (root->contents) {
                depth++;
                print_ftree(root->contents);
                depth--;
            }
            if (root->next) {
            print_ftree(root->next);
            }
        }
    }
}


/* 
 * Deallocate all dynamically-allocated memory in the FTree rooted at node.
 */
void deallocate_ftree(struct TreeNode *node) {
   
    // Your implementation here.
    if (node != NULL) {
        free(node->fname);
        if (node->type == 'd') {
            if (node->contents != NULL) {
                deallocate_ftree(node->contents);
            }
        }
        if (node->next != NULL) {
            deallocate_ftree(node->next);
        }
        free(node);
    }
}
