#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct Node {
    char value[50];
    struct Node* next;
};

typedef struct Node* Linklist;

// Khởi tạo danh sách liên kết
void firstNode(Linklist *head) {
    *head = NULL;
}

// Thêm một node vào đầu danh sách
void firstAdd(Linklist *head, char name[]) {
    struct Node* newNode = malloc(sizeof(struct Node));
    strcpy(newNode->value, name);
    newNode->next = *head;
    *head = newNode;
}

// Kiểm tra trùng tên trong danh sách liên kết
int isDuplicate(Linklist head, char name[]) {
    Linklist temp = head;
    while (temp != NULL) {
        if (strcmp(temp->value, name) == 0) {
            return 1; // Trùng tên
        }
        temp = temp->next;
    }
    return 0;
}

// Thêm nhiều tên
void addNames(Linklist *head) {

    FILE *pF = fopen("userName.txt", "a");
    if (pF == NULL) {
        printf("Khong the mo file.\n");
        return;
    }

    char name[50];
    while (1) {
        printf("Nhap ten (hoac nhap STOP de dung): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0; // Xóa ký tự xuống dòng

        if (strcmp(name, "STOP") == 0) {
            break;
        }

        // Kiểm tra trùng lặp
        if (isDuplicate(*head, name)) {
            printf("Ten '%s' da ton tai, vui long nhap ten khac.\n", name);
        } else {
            fprintf(pF, "%s\n", name);
            firstAdd(head, name);
            printf("Da them ten '%s'.\n", name);
        }
    }

    fclose(pF);
}

// Tìm kiếm tên
void searchNames(Linklist head) {
    char keyword[50];
    while (1) {
        printf("Nhap chuoi de tim kiem (hoac nhap STOP de dung): ");
        fgets(keyword, sizeof(keyword), stdin);
        keyword[strcspn(keyword, "\n")] = 0;

        if (strcmp(keyword, "STOP") == 0) {
            break;
        }

        int found = 0;
        Linklist temp = head;
        while (temp != NULL) {
            if (strstr(temp->value, keyword) != NULL) {
                printf("Tim thay: %s\n", temp->value);
                found = 1;
            }
            temp = temp->next;
        }
        if (!found) {
            printf("Khong tim thay ten nao chua '%s'.\n", keyword);
        }
    }
}

// Xóa tên
void deleteNames(Linklist *head) {
    while (1) {
        char name[50];
        printf("Nhap ten can xoa (hoac nhap STOP de dung): ");
        fgets(name, sizeof(name), stdin);
        name[strcspn(name, "\n")] = 0;

        if (strcmp(name, "STOP") == 0) {
            break;
        }

        Linklist temp = *head, prev = NULL;
        int deleted = 0;

        while (temp != NULL) {
            if (strcmp(temp->value, name) == 0) {
                if (prev == NULL) {
                    *head = temp->next;
                } else {
                    prev->next = temp->next;
                }
                free(temp);
                printf("Da xoa ten '%s'.\n", name);
                deleted = 1;
                break;
            }
            prev = temp;
            temp = temp->next;
        }

        if (!deleted) {
            printf("Khong tim thay ten '%s' de xoa.\n", name);
        }

        // Cập nhật file
        FILE *pF = fopen("userName.txt", "w");
        if (pF == NULL) {
            printf("Khong the mo file.\n");
            return;
        }
        Linklist current = *head;
        while (current != NULL) {
            fprintf(pF, "%s\n", current->value);
            current = current->next;
        }
        fclose(pF);
    }
}

// Xóa toàn bộ danh sách liên kết
void clearList(Linklist *head) {
    struct Node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

// Đọc dữ liệu từ file vào danh sách liên kết
void readFromFile(Linklist *head) {
    FILE *pF = fopen("userName.txt", "r");
    if (pF == NULL) {
        return; // Không có file thì không cần xử lý
    }

    char name[50];
    while (fgets(name, sizeof(name), pF) != NULL) {
        name[strcspn(name, "\n")] = 0; // Xóa ký tự xuống dòng
        firstAdd(head, name);
    }

    fclose(pF);
}

// Chương trình chính
int main() {
    Linklist head;
    firstNode(&head);
    readFromFile(&head);

    int choice;
    do {
        printf("\n=== Menu ===\n");
        printf("1. Them ten.\n");
        printf("2. Tim ten.\n");
        printf("3. Xoa ten.\n");
        printf("4. Thoat.\n");
        printf("Nhap lua chon: ");
        scanf("%d", &choice);
        getchar(); // Xóa ký tự xuống dòng dư

        switch (choice) {
            case 1:
                addNames(&head);
                break;
            case 2:
                searchNames(head);
                break;
            case 3:
                deleteNames(&head);
                break;
            case 4:
                printf("Thoat chuong trinh.\n");
                break;
            default:
                printf("Lua chon khong hop le. Vui long thu lai.\n");
        }
    } while (choice != 4);

    clearList(&head);
    
    return 0;

}
