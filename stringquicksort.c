#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBUCKETS 8
  
 
struct node {
    char *string;
    struct node *next;
};

 
struct bucket {
    int mininit;
    int maxinit;
    int numwords;
    struct node *chainHead;
} list[] = {
    'a', 'b', 0, NULL, 
    'c', 'c', 0, NULL, 
    'd', 'f', 0, NULL, 
    'g', 'k', 0, NULL, 
    'l', 'o', 0, NULL, 
    'p', 'r', 0, NULL, 
    's', 's', 0, NULL, 
    't', 'z', 0, NULL
};

static int check(char* s, struct bucket b) {
    if (s[0] <= b.mininit) return -1;
    if (s[0] >= b.maxinit) return 1;
    return 0;
}

int add (char* s) {
    
    int high = NUMBUCKETS;
    int low = 0;
    int mid;
    
    do {
        mid = (high + low) / 2;
        switch (check(s, list[mid])) {
            case -1:
            high = mid - 1;
            break;
            case 0: // Breaks outer loop
            high = low - 1;
            break;
            case 1:
            low = mid + 1;
        }
    } while (low <= high);
    
    list[mid].numwords++;
    struct node new = { s, list[mid].chainHead };
    list[mid].chainHead = &new;
}


 
int nodecmp (struct node *a, struct node *b) {
    char* as = a->string;
    char* bs = b->string;
    int len = fmin (strlen (as), strlen (bs));
    return strncmp (as, bs, len);
}

struct node* quicksort (struct node* pivot) {
    
    // Base case
    if (!pivot || !(pivot->next)) return pivot;
    
    struct node* ptr = pivot->next;
    
    // Sublists & tails of sublists
    struct node* leftH = NULL; struct node* rightH = NULL;
    struct node* leftT = NULL; struct node* rightT = NULL;
    
    // Partition
    while (ptr) {
        
        if (nodecmp(pivot, ptr) > 0) {
            if (!leftH) {
                leftH = ptr;
                leftT = ptr;
            } else {
                leftT->next = ptr;
                leftT = ptr;
            }
            
            
        } else {
            if (!rightH) {
                rightH = ptr;
                rightT = ptr;
            } else {
                rightT->next = ptr;
                rightT = ptr;
            }
        }
        
        ptr = ptr->next;
    }
    
    // Remove dangling pointers at ends of sublists
    if (leftT) leftT->next = NULL;
    if (rightT) rightT->next = NULL;
    
    // Sort sublists
    leftH = quicksort(leftH);
    rightH = quicksort(rightH);
    
    // Concatenate left sublist with pivot
    if (leftH) {
        while (leftT->next) {
            leftT = leftT->next;
        }
        leftT->next = pivot;
    } else {
        leftH = pivot;
    }
    
    // Concatenate right sublist with pivot
    pivot->next = rightH;
    
    // Return sorted list
    return leftH;
}


 
int main () {
    
    struct node a = {"abc", NULL};
    struct node b = {"xyz", &a};
    struct node c = {"mno", &b};
    struct node d = {"def", &c};
    struct node e = {"kl", &d};
    struct node f = {"pqr", &e};
    struct node g = {"vw", &f};
    struct node h = {"ghij", &g};
    struct node i = {"stu", &h};
    
    struct node *ptr = &h;
    
    ptr = quicksort(ptr);
    
    while (ptr) {
        printf("%s", ptr->string);
        ptr = ptr->next;
    }
}