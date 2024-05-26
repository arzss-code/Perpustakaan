#include "strukturdata.h"
#include <stdio.h>
#include <stdlib.h>

// Implementasi Stack untuk riwayat transaksi
StackNode *stackTop = NULL;

void push(Transaksi transaksi) {
    StackNode *newNode = (StackNode *)malloc(sizeof(StackNode));
    newNode->transaksi = transaksi;
    newNode->next = stackTop;
    stackTop = newNode;
}

Transaksi pop() {
    if (isStackEmpty()) {
        Transaksi emptyTransaksi = {0, 0, 0, ""};
        return emptyTransaksi;
    }
    StackNode *temp = stackTop;
    Transaksi transaksi = temp->transaksi;
    stackTop = stackTop->next;
    free(temp);
    return transaksi;
}

int isStackEmpty() {
    return stackTop == NULL;
}

// Queue untuk daftar tunggu buku
QueueNode *queueFront = NULL;
QueueNode *queueRear = NULL;

void enqueue(int idAnggota) {
    QueueNode *newNode = (QueueNode *)malloc(sizeof(QueueNode));
    newNode->idAnggota = idAnggota;
    newNode->next = NULL;
    if (queueRear == NULL) {
        queueFront = queueRear = newNode;
        return;
    }
    queueRear->next = newNode;
    queueRear = newNode;
}

int dequeue() {
    if (isQueueEmpty()) {
        return -1;
    }
    QueueNode *temp = queueFront;
    int idAnggota = queueFront->idAnggota;
    queueFront = queueFront->next;
    if (queueFront == NULL) {
        queueRear = NULL;
    }
    free(temp);
    return idAnggota;
}

int isQueueEmpty() {
    return queueFront == NULL;
}

// Tree untuk buku berdasarkan ISBN
TreeNode *treeRoot = NULL;

void insertTreeNode(Buku buku) {
    TreeNode *newNode = (TreeNode *)malloc(sizeof(TreeNode));
    newNode->buku = buku;
    newNode->left = newNode->right = NULL;

    if (treeRoot == NULL) {
        treeRoot = newNode;
        return;
    }

    TreeNode *current = treeRoot;
    TreeNode *parent = NULL;

    while (1) {
        parent = current;
        if (buku.isbn < parent->buku.isbn) {
            current = current->left;
            if (current == NULL) {
                parent->left = newNode;
                return;
            }
        } else {
            current = current->right;
            if (current == NULL) {
                parent->right = newNode;
                return;
            }
        }
    }
}

Buku* searchTreeNode(int isbn) {
    TreeNode *current = treeRoot;

    while (current != NULL && current->buku.isbn != isbn) {
        if (isbn < current->buku.isbn) {
            current = current->left;
        } else {
            current = current->right;
        }
    }

    if (current == NULL) {
        return NULL;
    }

    return &(current->buku);
}

void inorderTraversal(TreeNode *root, void (*func)(Buku)) {
    if (root != NULL) {
        inorderTraversal(root->left, func);
        func(root->buku);
        inorderTraversal(root->right, func);
    }
}
