#ifndef STRUKTURDATA_H
#define STRUKTURDATA_H

// Stack untuk riwayat transaksi
typedef struct StackNode {
    Transaksi transaksi;
    struct StackNode *next;
} StackNode;

void push(Transaksi transaksi);
Transaksi pop();
int isStackEmpty();

// Queue untuk daftar tunggu buku
typedef struct QueueNode {
    int idAnggota;
    struct QueueNode *next;
} QueueNode;

void enqueue(int idAnggota);
int dequeue();
int isQueueEmpty();

// Tree untuk buku berdasarkan ISBN
typedef struct TreeNode {
    Buku buku;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;

void insertTreeNode(Buku buku);
Buku* searchTreeNode(int isbn);
void inorderTraversal(TreeNode *root, void (*func)(Buku));

#endif
