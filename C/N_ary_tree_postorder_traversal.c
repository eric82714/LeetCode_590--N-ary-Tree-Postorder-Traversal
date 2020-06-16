/**
 * Definition for a Node.
 * struct Node {
 *     int val;
 *     int numChildren;
 *     struct Node** children;
 * };
 */

/**
 * Note: The returned array must be malloced, assume caller calls free().
 */
void length(struct Node* root, int* len) {
    if(root->numChildren != 0) {
        *len = *len + root->numChildren;
        for(int i = 0; i < root->numChildren; i++) 
            length(root->children[i], len);
    }
}

int* compute(struct Node* root, int* result, int* len) {
    if(!root) {
        int* tmp = malloc(0 * sizeof(int));
        return tmp;
    }
    
    int* tmp = malloc(100 * sizeof(int));
    if(root->numChildren != 0) {
        for(int i = 0; i < root->numChildren; i++) {            
            tmp = compute(root->children[i], result, len);
            for(int j = 0; j < 100 && *(tmp+j) > 0; j++) {
                *len = *len - 1;
                *(result+*len) = *(tmp+j); 
            } 
        }
    }
    *len = *len - 1;
    *(result+*len) = root->val;
    
    return tmp;
}

void reverse(int* arr, int size) {
    for(int i = 0, j = size-1; i < j; i++, j--) {
        int tmp = *(arr+i);
        *(arr+i) = *(arr+j);
        *(arr+j) = tmp;
    }    
}

int* postorder(struct Node* root, int* returnSize) {
    if(!root) {
        *returnSize = 0;
        int* result = malloc(*returnSize * sizeof(int));
        return result;
    }
    
    int len = 1;
    length(root, &len);
    int* result = malloc(len * sizeof(int));
    int copy = len;
    compute(root, result, &copy);
    reverse(result, len);
    
    *returnSize = len;
    return result;
}
