#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct qlysinhvien{
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
    printf("Nhap Lab1: ");
    scanf("%f",&a->Lab1);
    printf("Nhap Lab2: ");
    scanf("%f",&a->Lab2);
    printf("Nhap ProgressTest1: ");
    scanf("%f",&a->Progresstest1);
    printf("Nhap ProgressTest2: ");
    scanf("%f",&a->Progresstest2);
    printf("Nhap Presentation: ");
    scanf("%f",&a->Presentation);
    printf("Nhap FinalTest: ");
    scanf("%f",&a->Finaltest);
}
void nhapsinhvien(struct qlysinhvien a[], int *n){
    if(*n >= 30){
        printf("Danh sach day!\n");
        return;
    }
    printf("Nhap ma sinh vien: ");
    scanf("%s", a[*n].msv);
    getchar();
    printf("Nhap ten sinh vien: ");
    fgets(a[*n].ten, 50, stdin);
    a[*n].ten[strcspn(a[*n].ten, "\n")] = 0;
    nhapdiem(&a[*n]);
    (*n)++;
    printf("Them sinh vien thanh cong!\n");
}
void xemdiem(struct qlysinhvien a[], int n){
    char msv[30];
    int check = 0;
    printf("Nhap ma sinh vien: ");
    scanf("%s",msv);
    for(int i=0;i<n;i++){
        if(strcmp(a[i].msv,msv)==0){
            printf("\n===== THONG TIN SINH VIEN =====\n");
            printf("MSV: %s\n",a[i].msv);
            printf("Ten: %s\n",a[i].ten);
            printf("Lab1: %.2f\n",a[i].Lab1);
            printf("Lab2: %.2f\n",a[i].Lab2);
            printf("PT1: %.2f\n",a[i].Progresstest1);
            printf("PT2: %.2f\n",a[i].Progresstest2);
            printf("Presentation: %.2f\n",a[i].Presentation);
            printf("Final: %.2f\n",a[i].Finaltest);
            printf("TB: %.2f\n",tinhTB(a[i]));
            check = 1;
            break;
        }
    }
    if(!check){
        printf("Khong tim thay!\n");
    }
}
void suadiem(struct qlysinhvien a[], int n){
    char msv[30];
    printf("Nhap MSV: ");
    scanf("%s",msv);
    for(int i=0;i<n;i++){
        if(strcmp(a[i].msv,msv)==0){
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
    printf("Da sap xep theo diem trung binh giam dan!\n");
}
void indanhsach(struct qlysinhvien a[], int n){
    printf("\n------------------------------------------------------------------------------------------------------\n");
    printf("| %-10s | %-20s | %-5s | %-5s | %-5s | %-5s | %-5s | %-6s | %-6s | %-5s |\n",
           "MSV","Ten","L1","L2","PT1","PT2","Pre","Final","TB","Xep");
    printf("--------------------------------------------------------------------------------------------------------\n");
    for(int i=0;i<n;i++){
        float tb = tinhTB(a[i]);
        char xep;
        if(tb >= 8.5)
            xep='A';
        else if(tb >= 7)
            xep='B';
        else if(tb >= 5.5)
            xep='C';
        else if(tb >= 4)
            xep='D';
        else
            xep='F';
        printf("| %-10s | %-20s | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-5.1f | %-6.1f | %-6.2f | %-5c |\n",
               a[i].msv,
               a[i].ten,
               a[i].Lab1,
               a[i].Lab2,
               a[i].Progresstest1,
               a[i].Progresstest2,
               a[i].Presentation,
               a[i].Finaltest,
               tb,
               xep);
    }
    printf("========================================================================================================\n");
}
void docfile(struct qlysinhvien a[], int *n){
    const char *candidates[] = {"danhsach.dat", "danhsach.dat"};
    FILE *f = NULL;
    const char *openedFile = NULL;
    for(int i = 0; i < 2; i++){
        f = fopen(candidates[i], "r");
        if(f != NULL){
            openedFile = candidates[i];
            break;
        }
    }
    if(f == NULL){
        printf("Khong mo duoc file!\n");
        return;
    }
    char line[256];
    *n = 0;
    while(*n < 30 && fgets(line, sizeof(line), f)){
        char *p = line;
        size_t len = strlen(p);
        while(len > 0 && (p[len-1] == '\n' || p[len-1] == '\r')){
            p[--len] = '\0';
        }
        if(len == 0) continue;
        // Skip header line
        if(strstr(line, "STT") != NULL) continue;
        char *fields[11] = {0};
        int count = 0;
        fields[count++] = strtok(p, "|");
        while(count < 11 && fields[count-1] != NULL){
            fields[count++] = strtok(NULL, "|");
        }
        if(count >= 10 && fields[1] != NULL && fields[2] != NULL){
            // Trim spaces from msv and ten
            char *msv_trim = fields[1];
            while(*msv_trim == ' ') msv_trim++;
            char *end = msv_trim + strlen(msv_trim) - 1;
            while(end > msv_trim && *end == ' ') *end-- = '\0';
            
            char *ten_trim = fields[2];
            while(*ten_trim == ' ') ten_trim++;
            end = ten_trim + strlen(ten_trim) - 1;
            while(end > ten_trim && *end == ' ') *end-- = '\0';
            
            strncpy(a[*n].msv, msv_trim, sizeof(a[*n].msv) - 1);
            a[*n].msv[sizeof(a[*n].msv) - 1] = '\0';
            strncpy(a[*n].ten, ten_trim, sizeof(a[*n].ten) - 1);
            a[*n].ten[sizeof(a[*n].ten) - 1] = '\0';
            
            if(fields[3] && fields[4] && fields[5] && fields[6] && fields[7] && fields[8]){
                a[*n].Lab1 = atof(fields[3]);
                a[*n].Lab2 = atof(fields[4]);
                a[*n].Progresstest1 = atof(fields[5]);
                a[*n].Progresstest2 = atof(fields[6]);
                a[*n].Presentation = atof(fields[7]);
                a[*n].Finaltest = atof(fields[8]);
            } else {
                a[*n].Lab1 = a[*n].Lab2 = a[*n].Progresstest1 = a[*n].Progresstest2 = a[*n].Presentation = a[*n].Finaltest = 0.0f;
            }
            (*n)++;
        } else {
            printf("Bo qua dong khong hop le: %s\n", line);
        }
    }
    fclose(f);
    printf("Doc file thanh cong! Mo file: %s. So luong SV: %d\n", openedFile, *n);
}
void nhap1cot(struct qlysinhvien a[], int n){
    char msv[30];
    int chon;
    printf("Nhap MSV: ");
    scanf("%s",msv);
    for(int i=0;i<n;i++){
        if(strcmp(a[i].msv,msv)==0){
            printf("Ten: %s\n",a[i].ten);
            printf("1. Lab1\n");
            printf("2. Lab2\n");
            printf("3. PT1\n");
            printf("4. PT2\n");
            printf("5. Presentation\n");
            printf("6. Final\n");
            printf("Chon cot diem: ");
            scanf("%d",&chon);
            switch(chon){
                case 1:
                    printf("Nhap diem moi: ");
                    scanf("%f",&a[i].Lab1);
                    break;
                case 2:
                    printf("Nhap diem moi: ");
                    scanf("%f",&a[i].Lab2);
                    break;
                case 3:
                    printf("Nhap diem moi: ");
                    scanf("%f",&a[i].Progresstest1);
                    break;
                case 4:
                    printf("Nhap diem moi: ");
                    scanf("%f",&a[i].Progresstest2);
                    break;
                case 5:
                    printf("Nhap diem moi: ");
                    scanf("%f",&a[i].Presentation);
                    break;
                case 6:
                    printf("Nhap diem moi: ");
                    scanf("%f",&a[i].Finaltest);
                    break;
                default:
                    printf("Sai lua chon!\n");
            }
            return;
        }
    }
    printf("Khong tim thay!\n");
}
void ghifile(struct qlysinhvien a[], int n){
    const char *filename = "danhsach.dat";
    FILE *f = fopen(filename, "w");
    if(f == NULL){
        printf("Khong mo duoc file %s!\n", filename);
        return;
    }
    // Write header
    fprintf(f, "STT |   MSV    |       TÊN         | LAB1 | LAB2 | PT1  | PT2  | PRT  | FINAL |   TB   | XẾP LOẠI\n");
    for(int i=0;i<n;i++){
        float tb = tinhTB(a[i]);
        char xep;
        if(tb >= 8.5)
            xep='A';
        else if(tb >= 7)
            xep='B';
        else if(tb >= 5.5)
            xep='C';
        else if(tb >= 4)
            xep='D';
        else
            xep='F';
        fprintf(f, "%-3d| %-10s| %-17s| %-5.2f| %-5.2f| %-5.2f| %-5.2f| %-5.2f| %-6.2f| %-6.2f| %-9c\n",
                i+1,
                a[i].msv,
                a[i].ten,
                a[i].Lab1,
                a[i].Lab2,
                a[i].Progresstest1,
                a[i].Progresstest2,
                a[i].Presentation,
                a[i].Finaltest,
                tb,
                xep);
    }
    fclose(f);
    printf("Da luu file: %s\n", filename);
}
void menu(){
    struct qlysinhvien ds[30];
    int n = 0;
    int chon;

    do{
        printf("\n========== MENU ==========\n");
        printf("1. Nhap sinh vien\n");
        printf("2. Xem diem\n");
        printf("3. Sua diem\n");
        printf("4. Sap xep theo TB\n");
        printf("5. In danh sach\n");
        printf("6. Doc file\n");
        printf("7. Luu file\n");
        printf("8. Thoat\n");
        printf("Chon: ");
        scanf("%d",&chon);

        switch(chon){

            case 1:
                nhapsinhvien(ds,&n);
                break;

            case 2:
                xemdiem(ds,n);
                break;

            case 3:{
                int lc;

                do{
                    printf("\n===== SUA DIEM =====\n");
                    printf("1. Nhap 1 cot diem\n");
                    printf("2. Nhap toan bo diem\n");
                    printf("0. Quay lai\n");
                    printf("Chon: ");
                    scanf("%d",&lc);

                    switch(lc){

                        case 1:
                            nhap1cot(ds,n);
                            break;

                        case 2:
                            suadiem(ds,n);
                            break;

                        case 0:
                            printf("Quay lai menu chinh!\n");
                            break;

                        default:
                            printf("Sai lua chon!\n");
                    }

                }while(lc != 0);

                break;
            }

            case 4:
                sapxep(ds,n);
                break;

            case 5:
                indanhsach(ds,n);
                break;

            case 6:
                docfile(ds,&n);
                break;

            case 7:
                ghifile(ds,n);
                break;

            case 8:
                printf("Thoat chuong trinh!\n");
                break;

            default:
                printf("Sai lua chon!\n");
        }

    }while(chon != 8);
}
int main(){
    menu();
    return 0;
}