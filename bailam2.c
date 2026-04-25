#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct qlysinhvien {
    char ten[50];
    char msv[30];
    float Lab1, Lab2, Progresstest1, Progresstest2, Presentation, Finaltest;
};

float tinhTB(struct qlysinhvien a){
    return 0.1*(a.Lab1 + a.Lab2)
         + 0.15*(a.Progresstest1 + a.Progresstest2)
         + 0.1*a.Presentation
         + 0.4*a.Finaltest;
}

void nhapdiem(struct qlysinhvien *a){
    printf("Nhap Lab1: "); scanf("%f",&a->Lab1);
    printf("Nhap Lab2: "); scanf("%f",&a->Lab2);
    printf("Nhap ProgressTest1: "); scanf("%f",&a->Progresstest1);
    printf("Nhap ProgressTest2: "); scanf("%f",&a->Progresstest2);
    printf("Nhap Presentation: "); scanf("%f",&a->Presentation);
    printf("Nhap FinalTest: "); scanf("%f",&a->Finaltest);
}

void nhapsinhvien(struct qlysinhvien a[], int *n){
    if(*n >= 30){
        printf("Danh sach day!\n");
        return;
    }

    printf("Nhap ma sinh vien: ");
    scanf("%s", a[*n].msv);

    printf("Nhap ten sinh vien: ");
    getchar();
    fgets(a[*n].ten, 50, stdin);
    a[*n].ten[strcspn(a[*n].ten, "\n")] = 0;

    nhapdiem(&a[*n]);
    (*n)++;
}

void xemdiem(struct qlysinhvien a[], int n){
    char msv[30];
    int check = 0;

    printf("Nhap ma sinh vien: ");
    scanf("%s", msv);

    for(int i=0;i<n;i++){
        if(strcmp(a[i].msv, msv)==0){
            printf("Ten: %s\n", a[i].ten);
            printf("Lab1: %.2f\n", a[i].Lab1);
            printf("Lab2: %.2f\n", a[i].Lab2);
            printf("PT1: %.2f\n", a[i].Progresstest1);
            printf("PT2: %.2f\n", a[i].Progresstest2);
            printf("Presentation: %.2f\n", a[i].Presentation);
            printf("Final: %.2f\n", a[i].Finaltest);
            check = 1;
            break;
        }
    }

    if(!check) printf("Khong tim thay!\n");
}

void suadiem(struct qlysinhvien a[], int n){
    char msv[30];
    printf("Nhap MSV: ");
    scanf("%s", msv);

    for(int i=0;i<n;i++){
        if(strcmp(a[i].msv, msv)==0){
            nhapdiem(&a[i]);
            printf("Da cap nhat!\n");
            return;
        }
    }

    printf("Khong tim thay!\n");
}

void sapxep(struct qlysinhvien a[], int n){
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(tinhTB(a[i]) < tinhTB(a[j])){
                struct qlysinhvien temp = a[i];
                a[i] = a[j];
                a[j] = temp;
            }
        }
    }
    printf("Da sap xep!\n");
}

void indanhsach(struct qlysinhvien a[], int n){
    printf("\n%-10s %-20s %-5s %-5s\n","MSV","Ten","TB","Xep");

    for(int i=0;i<n;i++){
        float tb = tinhTB(a[i]);
        char xep;

        if(tb >= 8.5) xep='A';
        else if(tb>=7) xep='B';
        else if(tb>=5.5) xep='C';
        else if(tb>=4) xep='D';
        else xep='F';

        printf("%-10s %-20s %-5.2f %-5c\n",
               a[i].msv, a[i].ten, tb, xep);
    }
}
void docfile(struct qlysinhvien a[], int *n){
   FILE *f = fopen("D:/PBL1/quanlydiemsinhvien/danhsachsinhvien.txt","r");
    if(f == NULL){
        printf("Khong mo duoc file!\n");
        return;
    }
    char line[200];
    *n = 0;
    while(fgets(line, sizeof(line), f) && *n < 30){
        if(strlen(line) <= 1) continue;
        line[strcspn(line, "\n")] = 0;
        char *space = strchr(line, ' ');
        if(space == NULL) continue;
        *space = '\0';
        strcpy(a[*n].msv, line);
        strcpy(a[*n].ten, space + 1);
        a[*n].Lab1 = a[*n].Lab2 = 0;
        a[*n].Progresstest1 = a[*n].Progresstest2 = 0;
        a[*n].Presentation = a[*n].Finaltest = 0;

        (*n)++;
    }

    fclose(f);
    printf("Doc file thanh cong! Da doc %d sinh vien\n", *n);
}
void nhap1cot(struct qlysinhvien a[], int n){
    char msv[30];
    int chon;

    printf("Nhap MSV: ");
    scanf("%s", msv);

    for(int i=0;i<n;i++){
        if(strcmp(a[i].msv, msv)==0){
            printf("Ten: %s\n", a[i].ten);

            printf("1.Lab1 2.Lab2 3.PT1 4.PT2 5.Presentation 6.Final\n");
            printf("Chon: ");
            scanf("%d",&chon);

            switch(chon){
                case 1: scanf("%f",&a[i].Lab1); break;
                case 2: scanf("%f",&a[i].Lab2); break;
                case 3: scanf("%f",&a[i].Progresstest1); break;
                case 4: scanf("%f",&a[i].Progresstest2); break;
                case 5: scanf("%f",&a[i].Presentation); break;
                case 6: scanf("%f",&a[i].Finaltest); break;
                default: printf("Sai!\n");
            }
            return;
        }
    }

    printf("Khong tim thay!\n");
}
void ghifile(struct qlysinhvien a[], int n){
    FILE *f = fopen("D:\\PBL1\\quanlydiemsinhvien\\danhsachsinhvien.txt","w");

    if(f == NULL){
        printf("Khong mo duoc file!\n");
        return;
    }

    fprintf(f,"%-10s | %-20s | %-5s | %-5s | %-5s | %-5s | %-5s | %-5s\n",
            "MSV","Ten","L1","L2","PT1","PT2","Pre","Final");

    for(int i=0;i<n;i++){
        fprintf(f,"%-10s | %-20s | %-5.2f | %-5.2f | %-5.2f | %-5.2f | %-5.2f | %-5.2f\n",
            a[i].msv, a[i].ten,
            a[i].Lab1, a[i].Lab2,
            a[i].Progresstest1, a[i].Progresstest2,
            a[i].Presentation, a[i].Finaltest);
    }

    fclose(f);
    printf("Da luu file dang bang!\n");
}
void menu(){
    struct qlysinhvien ds[30];
    int n = 0;
    int chon;
    do{
        printf("\n===== MENU =====\n");
        printf("1. Nhap sinh vien\n");
        printf("2. Xem diem\n");
        printf("3. Sua diem\n");
        printf("4. Sap xep\n");
        printf("5. In danh sach\n");
        printf("6. Doc file\n");
        printf("7. Nhap 1 cot diem\n");
        printf("8. Luu file\n");
        printf("9. Thoat\n");
        printf("Chon: ");
        scanf("%d",&chon);
        switch(chon){
            case 1: nhapsinhvien(ds,&n); break;
            case 2: xemdiem(ds,n); break;
            case 3: suadiem(ds,n); break;
            case 4: sapxep(ds,n); break;
            case 5: indanhsach(ds,n); break;
            case 6: docfile(ds,&n); break;
            case 7: nhap1cot(ds,n); break;
            case 8: ghifile(ds,n); break;
            case 9: printf("Thoat!\n"); break;
            default: printf("Sai lua chon!\n");
        }

    }while(chon != 9);
}
int main(){
    menu();
    return 0;
}