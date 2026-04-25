#include <stdio.h>
#include <string.h>
struct sinhvien{
    char name[50];
    int id;
    float lab1;
    float lab2;
    float test1;
    float test2;
    float presentation;
    float finaltest; 
    float dtb; 
}; 
void nhapdiem(struct sinhvien a[], int n){
    printf("\n--- NHAP DIEM LAB1 ---\n");
    for(int i=0;i<n;i++){
        printf("%s: ",a[i].name);
        scanf("%f",&a[i].lab1);
    }
    printf("\n--- NHAP DIEM LAB2 ---\n");
    for(int i=0;i<n;i++){
        printf("%s: ",a[i].name);
        scanf("%f",&a[i].lab2);
    }
    printf("\n--- NHAP DIEM TEST1 ---\n");
    for(int i=0;i<n;i++){
        printf("%s: ",a[i].name);
        scanf("%f",&a[i].test1);
    }
    printf("\n--- NHAP DIEM TEST2 ---\n");
    for(int i=0;i<n;i++){
        printf("%s: ",a[i].name);
        scanf("%f",&a[i].test2);
    }
    printf("\n--- NHAP DIEM PRESENTATION ---\n");
    for(int i=0;i<n;i++){
        printf("%s: ",a[i].name);
        scanf("%f",&a[i].presentation);
    }
    printf("\n--- NHAP DIEM FINALTEST ---\n");
    for(int i=0;i<n;i++){
        printf("%s: ",a[i].name);
        scanf("%f",&a[i].finaltest);
    }
    getchar();
}
void xemdiem(struct sinhvien a[], int n){
    int idd,check=0;
    printf("\n--- BANG DIEM CUA SINH VIEN ---\n");
    printf("Nhap ma sinh vien muon xem : ");
    scanf("%d",&idd); 
    for(int i=0;i<n;i++){
        if(a[i].id==idd){
            printf("Ten: %s",a[i].name);
            printf("\nLab1: %.2f\n",a[i].lab1);
            printf("Lab2: %.2f\n",a[i].lab2);
            printf("Test1: %.2f\n",a[i].test1);
            printf("Test2: %.2f\n",a[i].test2);
            printf("Presentation: %.2f\n",a[i].presentation);
            printf("Finaltest: %.2f\n",a[i].finaltest);
            check=1;
        }
    }

    if(check==0) printf("<<MA SINH VIEN KHONG HOP LE!>>\n");
}
void suadiem(struct sinhvien a[], int n){
    int idd,x;
    int check=0;
    printf("\n--- SUA DIEM SINH VIEN ---\n"); 
    printf("|1.lab1||2.lab2||3.test1||4.test2||5.presentation||6.finaltest|\n");
    printf("Nhap ma sinh vien muon sua diem : ");
    scanf("%d",&idd);

    for(int i=0;i<n;i++){
        if(a[i].id==idd){
        	printf("Chon cot diem muon sua : ");
        	scanf("%d",&x);
            check=1;
            switch(x){
                case 1:
                    printf("Nhap diem lab1 moi: ");
                    scanf("%f",&a[i].lab1);
                    break;
                case 2:
                    printf("Nhap diem lab2 moi: ");
                    scanf("%f",&a[i].lab2);
                    break;
                case 3:
                    printf("Nhap diem test1 moi: ");
                    scanf("%f",&a[i].test1);
                    break;
                case 4:
                    printf("Nhap diem test2 moi: ");
                    scanf("%f",&a[i].test2);
                    break;
                case 5:
                    printf("Nhap diem presentation moi: ");
                    scanf("%f",&a[i].presentation);
                    break;
                case 6:
                    printf("Nhap diem finaltest moi: ");
                    scanf("%f",&a[i].finaltest);
                    break;
                default:
                    printf("Lua chon khong hop le!\n");
            }
        }
    }

    if(check==0) printf("<<MA SINH VIEN KHONG HOP LE!>>\n");
}
void diemtrungbinh(struct sinhvien a[], int n){
    for(int i=0;i<n;i++){
        a[i].dtb=(a[i].lab1+a[i].lab2+a[i].test1+a[i].test2+a[i].presentation+a[i].finaltest)/6;
    }
}

void sapxep(struct sinhvien a[], int n){
	printf("\n--- DA SAP XEP THU TU SINH VIEN ---\n"); 
    for(int i=0;i<n-1;i++){
        for(int j=i+1;j<n;j++){
            if(a[j].dtb>a[i].dtb){
                struct sinhvien temp=a[i];
                a[i]=a[j];
                a[j]=temp;
            }
        }
    }
}
void in(struct sinhvien a[], int n){
	printf("\n--- BANG DIEM SINH VIEN ---"); 
    printf("\n|ID   ||Ten                 ||Lab1   ||Lab2   ||Test1  ||Test2  ||Pre    ||Final  ||DTB    |\n");
    for(int i=0;i<n;i++){
        printf("|%-5d||%-20s||%-7.2f||%-7.2f||%-7.2f||%-7.2f||%-7.2f||%-7.2f||%-7.2f|\n",
        a[i].id,a[i].name,a[i].lab1,a[i].lab2,a[i].test1,a[i].test2,
        a[i].presentation,a[i].finaltest,a[i].dtb);
    }
}
int docFileBanDau(struct sinhvien a[], char tenFile[]) {
    FILE *f = fopen(tenFile, "r");
    if (f == NULL) {
        printf("file dau vao khong dung!\n");
        return 0;
    }
    int n;
    fscanf(f, "%d\n", &n);
    for (int i = 0; i < n; i++) {
        fscanf(f, "%[^|]|%d\n", a[i].name, &a[i].id);

        a[i].lab1 = a[i].lab2 = a[i].test1 = a[i].test2 = 0;
        a[i].presentation = a[i].finaltest = 0;
        a[i].dtb = 0;
    }
    fclose(f);
    return n;
}
void luuFile(struct sinhvien a[], int n, char tenFile[]) {
    FILE *f = fopen(tenFile, "w"); 
    if (f == NULL) {
        printf("Loi: Khong the mo file de ghi!\n");
        return;
    }
    fprintf(f, "%d\n", n); 
    for (int i = 0; i < n; i++) {
        fprintf(f, "%s|%d|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f|%.2f\n", 
                a[i].name, a[i].id, a[i].lab1, a[i].lab2, a[i].test1, 
                a[i].test2, a[i].presentation, a[i].finaltest, a[i].dtb);
    }
    fclose(f);
    printf("=> Da cap nhat du lieu vao file dau ra");
}
void menu(struct sinhvien a[], int n, char tenFile[]){
    int t;

    do{
        printf("\n===== MENU =====\n");
        printf("1.Nhap diem\n");
        printf("2.Xem diem\n");
        printf("3.Sua diem\n");
        printf("4.Sap xep theo DTB\n");
        printf("5.In danh sach\n");
        printf("6.Thoat\n");

        printf("Nhap lua chon : ");
        scanf("%d",&t);

        switch(t){
            case 1:
            	printf("\n--- NHAP DIEM SINH VIEN ---\n");
                nhapdiem(a,n);
                diemtrungbinh(a,n);
                luuFile(a, n, tenFile);
                break;
            case 2:
                xemdiem(a,n);
                break;
            case 3:
                suadiem(a,n); 
                diemtrungbinh(a,n);
                luuFile(a, n, tenFile);
                break;
            case 4:
                sapxep(a,n);
                break;
            case 5:
                in(a,n);
                break;
            case 6:
                printf("<<DA THOAT CHUONG TRINH>>\n");
                break;
            default:
                printf("<<CHUC NANG KHONG HOP LE>>\n");
        }

    }while(t!=6);
}

int main(){
	struct sinhvien a[100];
	int n=0;
	char tenfiledauvao[100];
	printf("nhap ten file ban dau : "); 
	scanf("%s", tenfiledauvao); 
	n=docFileBanDau(a,tenfiledauvao); 
	if(n==0){
		return 0; 
	} 
	else{
	    char filedaura[100]="ketqua.txt";
        luuFile(a, n, filedaura);
        menu(a, n, filedaura);
	} 
	return 0; 
} 