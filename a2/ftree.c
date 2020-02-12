// #include <stdio.h>
// // Add your system includes here.
// #include <stdlib.h>
// #include <string.h>
// #include <dirent.h>
// #include <sys/types.h>
// #include <sys/stat.h>
// #include <unistd.h>

// #include "ftree.h"

// /*
//  * Hint: consider implementing a recursive helper function that
//  * takes fname and a path.  For the initial call on the 
//  * helper function, the path would be "", since fname is the root
//  * of the FTree.  For files at other depths, the path would be the
//  * file path from the root to that file.
//  */
// struct TreeNode *generate_ftree_helper(char *fname, char *path) {
//     // Build a file tree
//     struct TreeNode *ftree = malloc(sizeof(struct TreeNode));
//     // Check if there are enough space to store the ftree.
//     if (ftree == NULL) {
//         perror("malloc");
//         exit(1);
//     }

//     // Get the path of the file
//     int true_len = strlen(fname) + strlen(path) + 1;
//     char true_path[true_len];
//     strcpy(true_path, path);
//     true_path[strlen(path)] = '\0';
//     strcat(true_path, fname);

//     // Fills in the struct stat stat_buf with information about the file
//     struct stat stat_buf;
//     // Check if the file exist or not
//     if (lstat(true_path, &stat_buf) == -1) {
//         fprintf(stderr, "The path (%s) does not point to an existing entry!\n", fname);
//         return NULL;
//     }

//     // For regular files 
//     if (S_ISREG(stat_buf.st_mode)) {
//         if(fname[0] != '.') {
//             ftree->fname = fname;
//             int permissions = stat_buf.st_mode & 0777;
//             ftree->permissions = permissions;
//             ftree->type = '-';
//             ftree->contents = NULL;
//             ftree->next = NULL;
//         }
//     // For links
//     } else if (S_ISLNK(stat_buf.st_mode)) {
//         if(fname[0] != '.') {
//             ftree->fname = fname;
//             int permissions = stat_buf.st_mode & 0777;
//             ftree->permissions = permissions;
//             ftree->type = 'l';
//             ftree->contents = NULL;
//             ftree->next = NULL;
//         }
//     // For directories
//     } else if (S_ISDIR(stat_buf.st_mode)) {
//         // Open the directory
//         DIR *d_ptr = opendir(true_path);
//         // Error check opendir
//         if (d_ptr == NULL) {
//             perror("opendir");
//             exit(1);
//         }

//         ftree->fname = fname;
//         int permissions = stat_buf.st_mode & 0777;
//         ftree->permissions = permissions;
//         ftree->type = 'd'; 
//         ftree->next = NULL;
//         ftree->contents = NULL;    

//         struct TreeNode *temp_ftree = NULL;

//         // Allocate a struct dirent pointer, which will be used to store information
//         // about a directory entry.
//         struct dirent *entry_ptr;
//         entry_ptr = readdir(d_ptr);

//         while (entry_ptr != NULL) {         
//             char *sub_name = strdup(entry_ptr->d_name);
//             if (sub_name[0] != '.'){

//                 // Conctruct the path of this file, should be "<path>/<sub_name>" and null-terminated.
//                 int len = strlen(true_path) + 2;
//                 char sub_path[len];
//                 strcpy(sub_path, true_path);
//                 sub_path[strlen(true_path)] = '\0';
//                 strcat(sub_path, "/");

//                 // Construct the node in the sub-directory
//                 struct TreeNode *sub_node = malloc(sizeof(struct TreeNode));
//                 // Check if there are enough space to store the sub_nade.
//                 if (sub_node == NULL) {
//                     perror("malloc");
//                     exit(1);
//                 }

//                 sub_node = generate_ftree_helper(sub_name, sub_path);

//                 if (temp_ftree == NULL) {
//                     ftree->contents = sub_node;
//                 }else {
//                     temp_ftree->next = sub_node;
//                 }
//                 temp_ftree = sub_node;
//             }
//             entry_ptr = readdir(d_ptr);
//         }
//         // Close the directory
//         int close = closedir(d_ptr);
//         // Error check opendir
//         if (close == -1) {
//             perror("closedir");
//             exit(1);
//         }
//     }
//     return ftree;
// }


// /*
//  * Returns the FTree rooted at the path fname.
//  *
//  * Use the following if the file fname doesn't exist and return NULL:
//  * fprintf(stderr, "The path (%s) does not point to an existing entry!\n", fname);
//  *
//  */
// struct TreeNode *generate_ftree(const char *fname) {

//     // Your implementation here.
//     char *name = strdup(fname);

//     return generate_ftree_helper(name, "");

// }

// /*
//  * Prints the TreeNodes encountered on a preorder traversal of an FTree.
//  *
//  * The only print statements that you may use in this function are:
//  * printf("===== %s (%c%o) =====\n", root->fname, root->type, root->permissions)
//  * printf("%s (%c%o)\n", root->fname, root->type, root->permissions)
//  *
//  */
// void print_ftree(struct TreeNode *root) {
    
//     // Here's a trick for remembering what depth (in the tree) you're at
//     // and printing 2 * that many spaces at the beginning of the line.
//     static int depth = 0;
//     printf("%*s", depth * 2, "");
//     // // Your implementation here.
//     if (root != NULL) {
//         if (root->type == '-' || root->type == 'l') {
//             printf("%s (%c%o)\n", root->fname, root->type, root->permissions);
//             if (root->next) {
//             print_ftree(root->next);
//             }
//         } else if (root->type == 'd') {
//             printf("===== %s (%c%o) =====\n", root->fname, root->type, root->permissions);
//             if (root->contents) {
//                 depth++;
//                 print_ftree(root->contents);
//                 depth--;
//             }
//             if (root->next) {
//             print_ftree(root->next);
//             }
//         }
//     }
// }


// /* 
//  * Deallocate all dynamically-allocated memory in the FTree rooted at node.
//  */
// void deallocate_ftree(struct TreeNode *node) {
   
//     // Your implementation here.
//     if (node != NULL) {
//         free(node->fname);
//         if (node->type == 'd') {
//             if (node->contents != NULL) {
//                 deallocate_ftree(node->contents);
//             }
//         }
//         if (node->next != NULL) {
//             deallocate_ftree(node->next);
//         }
//         free(node);
//     }
// }




#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "ftree.h"

/*
 * The helper function for generate_ftree.
 * 
 * Returns the FTree rooted at the file fname with path.
 *
 */
struct TreeNode *generate_helper(char *fname, char *path) {
    // Allocate space for the ftree and error check.  
    struct TreeNode *ftree = malloc(sizeof(struct TreeNode));
    if (ftree == NULL) {
        perror("malloc");
        exit(1);
    }

    // Combine path and fname to get the final_path of the file.
    int final_path_len = strlen(fname) +strlen(path) + 1;
    char final_path[final_path_len];
    strcpy(final_path, path);
    final_path[strlen(path)] = '\0';
    strncat(final_path, fname, final_path_len);

    // Fills in the struct stat stat_buf with information about the file,
    // and error checking.
    struct stat stat_buf;
    if (lstat(final_path, &stat_buf) == -1) {
        fprintf(stderr, "The path (%s) does not point to an existing entry!\n", fname);
        perror("lstat");
        exit(1);
    }

    if (S_ISREG(stat_buf.st_mode)) {
        // When fname is a regular file
        if (fname[0] != '.') {
            ftree->fname = fname;
            ftree->permissions = stat_buf.st_mode & 0777;
            ftree->type = '-';
            ftree->contents = NULL;
            ftree->next = NULL;
        }
    } else if (S_ISLNK(stat_buf.st_mode )) {
        // When fname is a link file
        if (fname[0] != '.') {
            ftree->fname = fname;
            ftree->permissions = stat_buf.st_mode & 0777;
            ftree->type = 'l';
            ftree->contents = NULL;
            ftree->next = NULL;

        }
    } else if (S_ISDIR(stat_buf.st_mode)) {
        // When fname is a directory.
        ftree->fname = fname;
        ftree->permissions = stat_buf.st_mode & 0777;
        ftree->type = 'd';
        ftree->next = NULL;
        ftree->contents = NULL;
        
        // Open the directory and error check.
        DIR *d_ptr = opendir(final_path);
        if (d_ptr == NULL) {
            perror("opendir");
            exit(1);
        }

        // Read from the directory.
        struct dirent *entry_ptr;
        entry_ptr = readdir(d_ptr);

        // The pointer for the current entry in the directory.
        struct TreeNode *content_node = NULL;

        // Loop until the last entry in the directory.
        while (entry_ptr != NULL) {
            // Get the fname of this entry.
            char *new_name = strdup(entry_ptr->d_name);
            if (new_name[0] != '.') {
                // Combine the original path and the name of the entry,
                // and get the path of this entry.
                int new_path_len = strlen(final_path) + 2;
                char new_path[new_path_len];
                strcpy(new_path, final_path);
                new_path[strlen(final_path)] = '\0';
                strcat(new_path, "/");

                // Allocate space for the node of the new entry and error check.
                struct TreeNode *new_node = malloc(sizeof(struct TreeNode));
                if (new_node == NULL) {
                    perror("malloc");
                    exit(1);
                }

                // Recursively call generate_helper to generate ftree for the entry.
                new_node = generate_helper(new_name, new_path);

                if (content_node == NULL) {
                    // If the entry is the first entry in the directory,
                    // assign the new node to the contents of the directory.
                    ftree->contents = new_node;
                } else {
                    // If the entry is not the first entry in the directory,
                    // assign the new node to the next of the previous node.
                    content_node->next = new_node;
                }
                // Save the new node to content_node.
                content_node = new_node;
            }
            // Read the next entry.
            entry_ptr = readdir(d_ptr);
        }

        // Close the directory and error checking.
        int close = closedir(d_ptr);
        if (close == -1) {
            fprintf(stderr, "Error when closing folder");
            exit(1);
        }
    }
    return ftree;
}


/*
 * Returns the FTree rooted at the path fname.
 *
 */
struct TreeNode *generate_ftree(const char *fname) {
    // Save fname in order to pass as parameter.
    char *name = strdup(fname);
    // Call the helper function.
    return generate_helper(name, "");
}


/*
 * Prints the TreeNodes encountered on a preorder traversal of an FTree.
 *
 */
void print_ftree(struct TreeNode *root) {
    // Print the ftree if it exists.
    if (root != NULL) {
        // Remembering the depth of the entry.
        static int depth = 0;

        if ((root->type == 'l') | (root->type == '-')) {
            // If the root is a link file or regular file
            printf("%*s", depth * 2, "");
            printf("%s (%c%o)\n", root->fname, root->type, root->permissions);

            // Recursively print the next node of the current entry.
            if (root->next != NULL) {
                print_ftree(root -> next);
            }   
        } else if (root->type == 'd') {
            // If the root is a directoy
            printf("%*s", depth * 2, "");
            printf("===== %s (%c%o) =====\n", root->fname, root->type, root->permissions);

            // Recursively print the contents of the directory.
            if (root->contents != NULL) {
                // Save the depth of the directory.
                int this_depth = depth;
                // Increase the depth for the files in the directory.
                depth ++;
                // Print entries
                print_ftree(root->contents);
                // Return to the depth of the directory.
                depth = this_depth;
            } 
            // Recursively print the next node of the current entry.
            if (root->next != NULL) {
                print_ftree(root->next);
            }
        }

    }
}


/* 
 * Deallocate all dynamically-allocated memory in the FTree rooted at node.
 * 
 */
void deallocate_ftree (struct TreeNode *node) {
   // Deallocate if the node exists.
   if (node != NULL) {
        // If the node is a directory
        if (node->type == 'd') {
            // Recursively deallocate the contents of the directory.
            if (node->contents != NULL) {
                deallocate_ftree(node->contents);
            }
        }
        // If the node has next.
        if (node->next != NULL) {
            // Recursively deallocate the next node.
            deallocate_ftree(node->next);
        }
        // Deallocate the current node.
        free(node);
   }
}
