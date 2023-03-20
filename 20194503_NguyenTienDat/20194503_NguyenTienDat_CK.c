#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct yeucau {
    char maYeuCau[8];
    int soNguoi;
    int maPhong;
    char maKhachSan[4];
    char ngayDen[11];
    int soTreEm;
    struct yeucau *left, *right;
} YeuCau;
YeuCau *list = NULL, *root = NULL;

void readLog();

YeuCau *insert(YeuCau *root_t, YeuCau *node);

YeuCau *search(YeuCau *root_t, char *maYeuCau);

void freeTree(YeuCau *root_t);

void clsr();

void menu() {
    int choice = -1;
    printf("Chuong trinh quan ly dat phong\n"
           "Vui long chon mot trong cac chuc nang sau\n"
           "[1] Doc du lieu tu file log\n"
           "[2] Kiem tra so luong yeu cau khong hop le\n"
           "[3] Tra cuu theo ma yeu cau\n"
           "[4] Thay doi yeu cau\n"
           "[5] Huy yeu cau\n"
           "[6] Luu danh sach yeu cau ra file\n"
           "[7] (OP1) Thong ke khach san duoc ua thich nhat\n"
           "[8] (OP2) Ngay khong hop le\n"
           "[9] (OP3) Ngay khong hop le\n"
           "[10] Thoat\n");
    scanf("%d", &choice);
    clsr();
    switch (choice) {
        case 1: {
            readLog();
            break;
        }
        case 2: {
            YeuCau *temp = list;
            int count = 0;
            while (temp != NULL) {
                if (temp->soTreEm > temp->soNguoi - temp->soTreEm) {
                    count++;
                }
                temp = temp->right;
            }

            printf("So luong yeu cau khong hop le: %d\n", count);
            break;
        }
        case 3: {
            printf("Nhap ma yeu cau can tim: ");
            char maYeuCau[9] = {0};
            fgets(maYeuCau, 9, stdin);
            maYeuCau[strlen(maYeuCau) - 1] = '\0';
            YeuCau *result = search(root, maYeuCau);
            if (result == NULL) {
                printf("Not found\n");
            } else {
                printf("Ma yeu cau: %s\n", result->maYeuCau);
                printf("So nguoi: %d\n", result->soNguoi);
                printf("Ma phong: %d\n", result->maPhong);
                printf("Ma khach san: %s\n", result->maKhachSan);
                printf("Ngay den: %s\n", result->ngayDen);
                printf("So tre em: %d\n", result->soTreEm);
            }
            break;
        }
        case 4:
            break;
        case 5: {
            printf("Nhap ma yeu cau can huy: ");
            char maYeuCau[9] = {0};
            fgets(maYeuCau, 9, stdin);
            maYeuCau[strlen(maYeuCau) - 1] = '\0';
            delete(root, maYeuCau);
            break;
        }
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;
        case 10:
            freeTree(root);
            exit(0);
        default:
            printf("Lua chon khong hop le\n");
            break;
    }
}

int main() {
    while (1) {
        menu();
    }
}

void clsr() {
    int c;
    while ((c = getchar() != '\n' && c != EOF));
}

void readLog() {
    FILE *f = fopen("booking_orders.txt", "r");
    if (f == NULL) {
        printf("Khong the mo file booking_orders.txt\n");
        return;
    }
    list = NULL, root = NULL;

    int count = 0;
    fscanf(f, "%d", &count);

    printf("Doc %d yeu cau\n", count);
    while (!feof(f)) {
        YeuCau *temp = (YeuCau *) malloc(sizeof(YeuCau));
        fscanf(f, "%s %d %d %s %s %d", temp->maYeuCau, &temp->soNguoi, &temp->maPhong, temp->maKhachSan, temp->ngayDen,
               &temp->soTreEm);
        //them vao danh sach lien ket
        temp->right = list;
        temp->left = NULL;
        list = temp;

        //them vao cay nhi phan
        YeuCau *node = (YeuCau *) malloc(sizeof(YeuCau));
        memcpy(node, temp, sizeof(YeuCau));
        node->left = NULL;
        node->right = NULL;
        root = insert(root, node);
    }
    fclose(f);
}

YeuCau *insert(YeuCau *root_t, YeuCau *node) {
    if (root_t == NULL) {
        root_t = node;
        return root_t;
    }
    if (strcmp(root_t->maYeuCau, node->maYeuCau) > 0) {
        root_t->left = insert(root_t->left, node);
    } else if (strcmp(root_t->maYeuCau, node->maYeuCau) < 0) {
        root_t->right = insert(root_t->right, node);
    }
    return root_t;
}

YeuCau *search(YeuCau *root_t, char *maYeuCau) {
    if (root_t == NULL) {
        return NULL;
    }
    if (strcmp(root_t->maYeuCau, maYeuCau) == 0) {
        return root_t;
    }
    if (strcmp(root_t->maYeuCau, maYeuCau) > 0) {
        return search(root_t->left, maYeuCau);
    } else {
        return search(root_t->right, maYeuCau);
    }
}

void freeTree(YeuCau *root_t) {
    if (root_t == NULL) {
        return;
    }
    freeTree(root_t->left);
    freeTree(root_t->right);
    free(root_t);
}
