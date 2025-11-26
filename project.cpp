#include <stdio.h>
#define MAX 100
#include <string.h>
#include <stdlib.h>
#include <conio.h>
struct Patient {
	char cardId[10];
	char name[50];
	char phone[15];
	double debt;
	int visitDays;
};
struct Record{
	char recId[20];
	char cardId[10];
	char date[20];
	char status[20];
};
Record listRecords[MAX];//Danh sach lich su kham
Patient listPatients[MAX];//Danh sach benh nhan
int n_patients=9;
int page=1;
int itemsPerPage=5;
int patientIdExisted(const char cardId[]);
void createNewPatient();
void updatePatientInfo();
void dischargePatient();
void showCurrentPatients();
void searchPatient();
void sortByDebt();
void medicalCheck();
int main(){
	struct Patient pt;
	Patient pt1={"001","Nguyen Bao Anh","0912345678",500000,5};
	Patient pt2={"002","Nguyen Nhu Quynh","0925478136",100000,6};
	Patient pt3={"003","Nguyen Nhu Hoa","0922578136",100000,6};
	Patient pt4={"004","Le Van Huy","0912478136",200000,6};
	Patient pt5={"005","Tran Van Nam","0925456136",300000,8};
	Patient pt6={"006","Nguyen Thi Nhu Quynh","0925478136",100000,3};
	Patient pt7={"007","Cao Xuan Cuong","0925478198",200000,6};
	Patient pt8={"008","Nguyen Thi Khanh Huyen","0925426136",100000,9};
	Patient pt9={"009","Pham Anh Dung","0895426136",0,9};
	Patient pt10={"010","Pham Thi Dung","0894526136",20000000,1};
	
	listPatients[0]=pt1;
	listPatients[1]=pt2;
	listPatients[2]=pt3;
	listPatients[3]=pt4;
	listPatients[4]=pt5;
	listPatients[5]=pt6;
	listPatients[6]=pt7;
	listPatients[7]=pt8;
	listPatients[8]=pt9;
	listPatients[9]=pt10;
	int choose;
	
	while(1){
		system("cls");
		printf("\n++========== Quan ly benh nhan ===========++\n");
		printf("||1.Tiep nhan benh nhan.                  ||\n");
		printf("||2.Cap nhat thong tin benh nhan.         ||\n");
		printf("||3.Xuat vien.                            ||\n");
		printf("||4.Hien thi danh sach benh nhan.         ||\n");
		printf("||5.Tim kiem benh nhan.                   ||\n");
		printf("||6.Sap xep danh sach benh nhan.          ||\n");
		printf("||7.Ghi nhan khma benh.                   ||\n");
		printf("||8.Xem lich su kham benh.                ||\n");
		printf("++----------------------------------------++\n");
		printf("\n");
		printf("Nhap lua chon:");
		scanf("%d",&choose);
		fflush(stdin);
		switch (choose){
			case 1:{
				createNewPatient();
				break;
			}
			case 2:{
				updatePatientInfo();
				break;
			}
			case 3:{
				dischargePatient();
				break;
			}
			case 4:{
				showCurrentPatients();				
				break;
			}
			case 5:{
				searchPatient();
				break;
			}
			case 6:{
				sortByDebt();
				getchar();
				break;
			}
			case 7:{
				medicalCheck();
				break;
			}
			case 8:{
				
				break;
			}
			
		}
	}
}
int patientIdExisted(const char cardId[]){ //const dam bao khong thay doi du lieu,kiem tra cardid
	for(int i=0;i<n_patients;i++){
		if(strcmp(listPatients[i].cardId,cardId)==0){
			return 0;
		}
	}
	return 1;
}
int isFull() {//kiem tra mang da day chx
    if (n_patients >= MAX) {
        return 1;
    } else {
        return 0;
    }
}
int availble(char phone[]) {//Kiem tra sdt co hop le ko
    for (int i = 0; phone[i] != '\0'; i++) {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;  
    }
    return 1;      
}
//F01:Tiep nhan benh nhan
void createNewPatient(){

	if (isFull() == 1) {
        printf("Danh sach benh nhan da day. Khong the them moi.\n");
        return; 
    }
	printf("\nNhap thong tin benh nhan\n");
	int pos = n_patients; 
	while(1){
		printf("Ma ho so:");
		fgets(listPatients[pos].cardId,sizeof(listPatients[pos].cardId),stdin);
		listPatients[pos].cardId[strcspn(listPatients[pos].cardId, "\n")] = '\0';
		if(strlen(listPatients[pos].cardId)==0){
			printf("Ma ho so khong duoc de trong !\n");
			continue;
		}else if(patientIdExisted(listPatients[pos].cardId)==0){
			printf("Ma ho so da ton tai!\n");
			continue;
		}
		break;
		}
	while(1){
		printf("Nhap ten benh nhan:");
		fgets(listPatients[pos].name,sizeof(listPatients[pos].name),stdin);
		listPatients[pos].name[strcspn(listPatients[pos].name, "\n")] = '\0';
		if(strlen(listPatients[pos].name)==0){
			printf("Khong duoc de trong!\n");
			continue;
		}
		break;
	}
	while(1){
		printf("So dien thoai:");
		fgets(listPatients[pos].phone,sizeof(listPatients[pos].phone),stdin);
		listPatients[pos].phone[strcspn(listPatients[pos].phone,"\n")]='\0';
		if(strlen(listPatients[pos].phone)==0){
			printf("Khong duoc de trong!\n");
			continue;
	 	}else if(strlen(listPatients[pos].phone)<9 || strlen(listPatients[pos].phone)>15 ){
			printf("So vua nhap khong dung dinh dang.\n");
			continue;
		}else if (!availble(listPatients[pos].phone)) {
       		printf("So dien thoai phai chi chua so!\n");
        	continue;
    	}
		break;
		}
	while(1){
		printf("Cong no ban dau:");
		scanf("%lf",&listPatients[pos].debt);
		if(listPatients[pos].debt<=0){
			printf("=> So cong no phai lon hon 0.\n");
			continue;
		}else{
			break;
		}
	}
	printf("So ngay dieu tri: 0 \n");
		
	n_patients ++;// cap nhat danh sach benh nhan
	printf("=> TIEP NHAN BENH NHAN THANH CONG.\n");
	getchar();
}
//F02: Cap nhat thong tin benh nhan
void updatePatientInfo() {
	if(n_patients==0){
		printf("Mang rong!Vui long nhap thong tin benh nhan.\n");
		return;
	}
    char findId[10];
    int index = -1;
    while (1) {
        printf("Nhap ma ho so muon sua: ");
        fgets(findId, sizeof(findId), stdin);
        fflush(stdin);
        findId[strcspn(findId, "\n")] = '\0';   
        if (strlen(findId)== 0){
            printf("Khong duoc de trong!\n");
            continue;
        }
        for (int i = 0; i < n_patients; i++) {
            if (strcmp(listPatients[i].cardId, findId) == 0) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            printf("=>Khong ton tai ID nay!\n");
            continue;
        }
        printf("Da tim thay thong tin benh nhan!!!\n");
        break; 
    }
    
    printf("=====Cap nhat thong tin benh nhan=====\n");
    printf("Ten benh nhan:%s\n",listPatients[index].name);
    while (1) {
        printf("Nhap so dien thoai moi(10-14 so),hien tai:%s): ",listPatients[index].phone);
        fgets(listPatients[index].phone, sizeof(listPatients[index].phone), stdin);
        listPatients[index].phone[strcspn(listPatients[index].phone, "\n")] = '\0';
		if(strlen(listPatients[index].phone)==0){
				printf("=>Khong duoc de trong!\n");
				continue;
        }else if (strlen(listPatients[index].phone) < 9 || strlen(listPatients[index].phone) > 15) {
            printf("=>So dien thoai khong hop le (9–15 so)!\n");
            continue;
        }else if(!availble(listPatients[index].phone)){
        	printf("=>Chi duoc nhap so!\n");
		}
        break;
    }
    while(1){
    	printf("Cap nhat cong no hien tai:");
    	scanf("%lf",&listPatients[index].debt);
    	getchar();
    	if(listPatients[index].debt<0){
    		printf("Khong hop le,vui long nhap lai!!!\n");
    		continue;
		}
		break;
	}
	while(1){
		printf("So ngay kham benh:");
		scanf("%d",&listPatients[index].visitDays);
		if(listPatients[index].visitDays<0){
			printf("Khong hop le,vui long nhap lai!!!\n");
			continue;
		}
		break;
	}
    printf("=> CAP NHAT THANH CONG!\n");
    getchar();

}
//F03:Xoa thong tin benh nhan
void dischargePatient(){
	if(n_patients==0){
		printf("Mang rong!Vui long nhap thong tin benh nhan.\n");
		return;
	}
	char findId[10];
    int index = -1;
    int choice;
    while (1) {
        printf("Nhap ma ho so can tim: ");
        fgets(findId, sizeof(findId), stdin);
        fflush(stdin);
        findId[strcspn(findId, "\n")] = '\0';   
        if (strlen(findId)== 0){
            printf("Khong duoc de trong!\n");
            continue;
        }
        for (int i = 0; i < n_patients; i++) {
            if (strcmp(listPatients[i].cardId, findId) == 0) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            printf("=>Khong tim thay benh nhan nay!\n");
            continue;
        }
        printf("Da tim thay thong tin benh nhan %s!\n",listPatients[index].name);
        break; 
    }
    if(listPatients[index].debt>0){
    	printf("CANH BAO BENH NHAN CHUA DONG TIEN VIEN PHI!!!KHONG THE XUAT VIEN.\n");
    	printf("Cong no hien tai:%.lf\n",listPatients[index].debt);
    	getchar();
	}
	if(listPatients[index].debt==0){
		printf("Benh nhan da hoan thanh dong vien phi.\n");
		printf("Xac nhan benh nhan co xuat vien hay khong?\n1:Co\n2:khong\nNhap:");
		scanf("%d",&choice);
		switch (choice){
			case 1:{
				for(int i=index;i<n_patients-1;i++){
					listPatients[i]=listPatients[i+1];
				}
				printf("Xuat vien thanh cong!\n");
				n_patients--;
				getchar();
				break;
			}
			case 2:{
				printf("Huy xuat vien!\n");
				getchar();
				break;
			}
		}  
	}
}
	
//F04:Hien thi danh sach benh nhan 
void showCurrentPatients(){
	int pageSize=5;
	int page=1;
	int totalPages;
	char choice;
	int start,end;
	if(n_patients==0){
		printf("Danh sach benh nhan trong!\n");
		return;
	}
	totalPages=n_patients/pageSize+((n_patients%pageSize==0)?0:1);
	while(1){
		system("cls");
		printf("Danh sach benh nhan (trang %d/%d)\n",page,totalPages);
		printf("|Ma BN     |Ten BN                        |SDT            |debt(VND)      |So ngay kham benh|\n");
		for(int i=0;i<93;i++){
			printf("-");
		}
		printf("\n");
		start=(page-1)*pageSize;
		end=start+pageSize;
		if(end>n_patients){
			end=n_patients;
		}
		for(int i=start;i<end;i++){
			printf("|%-10s|%-30s|%-15s|%-15.lf|%-17d|\n",listPatients[i].cardId,listPatients[i].name,listPatients[i].phone,listPatients[i].debt,listPatients[i].visitDays);
		}
		for(int i=0;i<93;i++){
			printf("-");
		}
		printf("\n");
		printf("Nhan 'N'=Trang sau,'P'=Trang truoc;'R'=Thoat\n");
		choice=getchar();
		getchar();
		if(choice=='n'||choice=='N'){
			if(page<totalPages){
				page++;
			}else{
				printf("Da o trang cuoi!!!\n");
				getchar();
			}
		}else if(choice=='p'||choice=='P'){
			if(page>totalPages){
				page--;
			}else{
				printf("Dang o trang dau!!!\n");
				getchar();
			}
		}else if(choice=='r'||choice=='R'){
			return;
		}else{
			("Phim nhap vao khong hop le.\n");	
		}			
	}
}
void searchPatient(){//F05:Tim kiem benh nhan 
	char findName[50];
	printf("\nTIM KIEM BENH NHAN\n");
	printf("Nhap ten benh nhan:");
	fgets(findName,sizeof(findName),stdin);
	findName[strcspn(findName,"\n")]='\0';
	int found=0;
		for(int i=0;i<93;i++){
		printf("=");
	}
	printf("\n");
	printf("|Ma BN     |Ten BN                        |SDT            |debt(VND)      |So ngay kham benh|\n");
	for(int i=0;i<n_patients;i++){
			if(strstr(listPatients[i].name,findName)!=NULL){
				found=1;
				printf("|%-10s|%-30s|%-15s|%-15.lf|%-17d|\n",listPatients[i].cardId,listPatients[i].name,listPatients[i].phone,listPatients[i].debt,listPatients[i].visitDays);
			}
		}
	for(int i=0;i<93;i++){
		printf("=");
	}
	printf("\n");		
	if(!found){
		printf("Khong tim thay ten trong danh sach benh nhan\n");
	}	

	getchar();	
	}
void sortByDebt(){ //F06:Sap xep danh sach benhn nhan theo debt
	if(n_patients==0){
		printf("Danh sach benh nhan trong!!!\n");
		getchar();
		return;
	}
	int choice;
	printf("Sap xep danh sach benh nhan theo cong no.\n");
	printf("Nhap kieu sap xep(1.Tang,2.Giam):\n");
	scanf("%d",&choice);
	switch(choice){
		case 1:{
			struct Patient temp;
			for(int i=0;i<n_patients-1;i++){
				for(int j=0;j<n_patients-i-1;j++){
					if(listPatients[j].debt>listPatients[j+1].debt){
						temp=listPatients[j];
						listPatients[j]=listPatients[j+1];
						listPatients[j+1]=temp;
					}							
				}
			}
			printf("DANH SACH BENH NHAN\n");
			for(int i=0;i<93;i++){
				printf("=");
			}
			printf("\n");
			printf("|Ma BN     |Ten BN                        |SDT            |debt(VND)      |So ngay kham benh|\n");
			for(int i=0;i<n_patients;i++){  
				printf("|%-10s|%-30s|%-15s|%-15.lf|%-17d|\n",listPatients[i].cardId,listPatients[i].name,listPatients[i].phone,listPatients[i].debt,listPatients[i].visitDays);
			}
			for(int i=0;i<93;i++){
				printf("=");
			}
			printf("\n");
			getchar();			
			break;
		}
		case 2:{
			struct Patient temp;
			for(int i=0;i<n_patients-1;i++){
				for(int j=0;j<n_patients-i-1;j++){
					if(listPatients[j].debt<listPatients[j+1].debt){
						temp=listPatients[j];
						listPatients[j]=listPatients[j+1];
						listPatients[j+1]=temp;
					}							
				}
			}
			printf("DANH SACH BENH NHAN\n");
			for(int i=0;i<93;i++){
				printf("=");
			}
			printf("\n");
			printf("|Ma BN     |Ten BN                        |SDT            |debt(VND)      |So ngay kham benh|\n");
			for(int i=0;i<n_patients;i++){  
				printf("|%-10s|%-30s|%-15s|%-15.lf|%-17d|\n",listPatients[i].cardId,listPatients[i].name,listPatients[i].phone,listPatients[i].debt,listPatients[i].visitDays);
			}
			for(int i=0;i<93;i++){
				printf("=");
			}
			printf("\n");
			getchar();						
			break;
		}
			
			}
	
}
void medicalCheck(){
	char checkId[10];
	int day,month,year;
	printf("Nhap ma BN:");
	fgets(checkId,sizeof(checkId),stdin);
	fflush(stdin);
	int pos=-1;
	for(int i=0;i<n_patients;i++){
		if(strcmp(listPatients[i].cardId,checkId)==0){
			pos=1;
			break;
		}
	}
	if(pos==-1){
		printf("Khong tim thay benh nhan co ma %s\n",checkId);
	}	
	printf("Nhap ngay kham:");
	scanf("%d/%d/%d",&day,&month,&year);
	getchar();

	
	
}
	
	
	
	

	
	
	


