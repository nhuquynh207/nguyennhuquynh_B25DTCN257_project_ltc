#include <stdio.h>
#define MAX 100
#include <string.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
typedef struct Patient {
	char cardId[10];
	char name[50];
	char phone[15];
	double debt;
	int visitDays;
}Patient;
typedef struct Record{
	char recId[20];
	char cardId[10];
	char date[20];
	char status[20];
}Record;
struct Record listRecords[MAX];//Danh sach lich su kham
int n_records=5;
struct Patient listPatients[MAX];//Danh sach benh nhan
int n_patients=10;
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
void medicalHistory();
int main(){
	struct Patient pt;
	Patient pt1={"101","Nguyen Bao Anh","0912345678",500000,5};
	Patient pt2={"102","Nguyen Nhu Quynh","0925478136",100000,6};
	Patient pt3={"103","Nguyen Nhu Hoa","0922578136",100000,6};
	Patient pt4={"104","Le Van Huy","0912478136",200000,6};
	Patient pt5={"105","Tran Van Nam","0925456136",300000,8};
	Patient pt6={"106","Nguyen Thi Nhu Quynh","0925478136",0,3};
	Patient pt7={"107","Cao Xuan Cuong","0925478198",200000,90};
	Patient pt8={"108","Nguyen Thi Khanh Huyen","0925426136",100000,9};
	Patient pt9={"109","Pham Anh Dung","0895426136",0,30};
	Patient pt10={"110","Pham Thi Dung","0894526136",20000000,1};
	
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
	
	struct Record r;
	Record r1={"RC001","101","12/1/2025","Tai kham"};
	Record r2={"RC002","102","21/1/2025","Tai kham"};
	Record r3={"RC003","103","20/8/2025","Theo doi"};
	Record r4={"RC004","104","12/11/2025","Tai kham"};
	Record r5={"RC005","105","31/10/2025","Theo doi"};
	
	listRecords[0]=r1;
	listRecords[1]=r2;
	listRecords[2]=r3;
	listRecords[3]=r4;
	listRecords[4]=r5;
	
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
		printf("||7.Ghi nhan kham benh.                   ||\n");
		printf("||8.Xem lich su kham benh.                ||\n");
		printf("||9.Thoat chuong trinh.                   ||\n");
		printf("++----------------------------------------++\n");
		printf("\n");
		printf("Nhap lua chon:");
		scanf("%d",&choose);
		fflush(stdin);
		switch (choose){
			case 1:{
				createNewPatient();
				getchar();
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
				getchar();
				break;
			}
			case 8:{
				medicalHistory();
				break;
			}
			case 9:{
				printf("Hen gap lai.\n");
				exit(0);
				break;
			}default:
				printf("=>LOI:chuc nang khong ton tai!!!");
				getchar();		
		}
	}
}
int patientIdExisted(const char cardId[]){ //const dam bao khong thay doi du lieu,kiem tra cardid
	int i=0;
	for(i=0;i<n_patients;i++){
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
int isValidDate(const char *dateStr) {//Kiem tra ngay thang hop le
    int day, month, year;
    int maxDay;
    if (sscanf(dateStr, "%d/%d/%d", &day, &month, &year) != 3) {
        return 0; 
    }
    if (year < 1 || month < 1 || month > 12) {
        return 0; 
    }
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) {
        maxDay = 31;
    } else if (month == 4 || month == 6 || month == 9 || month == 11) {
        maxDay = 30;
    } else { 
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0)) {
            maxDay = 29; 
        } else {
            maxDay = 28; 
        }
    }
    if (day < 1 || day > maxDay) {
        return 0;
    }
    return 1;
}
int availble(char phone[]){//Kiem tra sdt co hop le ko
	int i=0;
    for (i = 0; phone[i] != '\0'; i++) {
        if (phone[i] < '0' || phone[i] > '9')
            return 0;  
    }
    return 1;      
}
int onlyAlphabet(const char *str) {
    int i = 0;
    while (str[i] != '\0') {
        if (!isalpha(str[i])&& str[i]!=' ') {
            return 0;
        }
        i++;
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
		}else if(!onlyAlphabet(listPatients[pos].name)){
			printf("Ten benh nhan chi chua ky tu chu cai.\n");
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
		break;
	}
	listPatients[pos].visitDays=0;
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
        int i=0;
        for (i = 0; i < n_patients; i++) {
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
        printf("Nhap so dien thoai moi(10-14 so),(hien tai:%s): ",listPatients[index].phone);
        fgets(listPatients[index].phone, sizeof(listPatients[index].phone), stdin);
        listPatients[index].phone[strcspn(listPatients[index].phone, "\n")] = '\0';
		if(strlen(listPatients[index].phone)==0){
				printf("=>Khong duoc de trong!\n");
				continue;
        }else if (strlen(listPatients[index].phone) < 9 || strlen(listPatients[index].phone) > 15) {
            printf("=>So dien thoai khong hop le (9?15 so)!\n");
            continue;
        }else if(!availble(listPatients[index].phone)){
        	printf("=>Chi duoc nhap so!\n");
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
        int i=0;
        for (i = 0; i < n_patients; i++) {
            if (strcmp(listPatients[i].cardId, findId) == 0) {
                index = i;
                break;
            }
        }
        if (index == -1) {
            printf("=>Khong tim thay benh nhan nay!\n");
            continue;
        }
        printf("Da tim thay thong tin benh nhan:%s!\n",listPatients[index].name);
        break; 
    }
    if(listPatients[index].debt>0){
    	printf("CANH BAO BENH NHAN CHUA DONG TIEN VIEN PHI!!!KHONG THE XUAT VIEN.\n");
    	printf("Cong no hien tai:%.lfVND\n",listPatients[index].debt);
 		printf("Xac nhan benh nhan da hoan thanh cong no ?\n1:Co\n2:khong\nNhap:");
		scanf("%d",&choice);
		switch (choice){
			case 1:{
				int i=0;
				for(i=index;i<n_patients-1;i++){
					listPatients[i]=listPatients[i+1];
				}
				printf("Xuat vien thanh cong!\n");
				n_patients--;
				getchar();
				break;
			}
			case 2:{
				printf("Benh nhan phai hoan thanh vien phi truoc khi xuat vien!\n");
				getchar();
				break;
			}
		}     	
    	getchar();
	}
	if(listPatients[index].debt==0){
		int i=0;
		for(i=index;i<n_patients-1;i++){
			listPatients[i]=listPatients[i+1];
		}
			printf("Benh nhan da hoan thanh vien phi.\n.");
			printf("Xuat vien thanh cong!");
			n_patients--;
			getchar();

	}
}
	
//F04:Hien thi danh sach benh nhan 
void showCurrentPatients(){
	int pageSize=4;
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
		int i=0;
		for(i=0;i<93;i++){
			printf("-");
		}
		printf("\n");
		start=(page-1)*pageSize;
		end=start+pageSize;
		if(end>n_patients){
			end=n_patients;
		}
		int j=start;
		for(j=start;j<end;j++){
			printf("|%-10s|%-30s|%-15s|%-15.0lf|%-17d|\n",listPatients[j].cardId,listPatients[j].name,listPatients[j].phone,listPatients[j].debt,listPatients[j].visitDays);
		}
		for(i=0;i<93;i++){
			printf("-");
		}
		printf("\n");
		printf("Nhan 'N'=Trang sau,'P'=Trang truoc;'R'=Thoat\n");
		printf("Nhap:");
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
			if(page>1){
				page--;
			}else{
				printf("Dang o trang dau!!!\n");
				getchar();
			}
		}else if(choice=='r'||choice=='R'){
			break;
		}else{
			printf("Phim nhap vao khong hop le.\n");
			getchar();	
		}			
	}
}
void searchPatient(){//F05:Tim kiem benh nhan 
	char findName[50];
	char lowerFindName[50]; 
    char lowerPatientName[50];
    int i=0,j=0;
	printf("\nTIM KIEM BENH NHAN\n");
	printf("Nhap ten benh nhan:");
	fgets(findName,sizeof(findName),stdin);
	findName[strcspn(findName,"\n")]='\0';
	strcpy(lowerFindName,findName);
    for(i = 0; lowerFindName[i]; i++){
        lowerFindName[i] = tolower(lowerFindName[i]);
    }
	int found=0;
	for(i=0;i<93;i++){
		printf("=");
	}
	printf("\n");
	printf("|Ma BN     |Ten BN                        |SDT            |debt(VND)      |So ngay kham benh|\n");
	for(i=0;i<n_patients;i++){
		strcpy(lowerPatientName, listPatients[i].name);
		for(j = 0; lowerPatientName[j]; j++){
            lowerPatientName[j] = tolower(lowerPatientName[j]);
        }
		if(strstr(lowerPatientName, lowerFindName) != NULL){
			found=1;
			printf("|%-10s|%-30s|%-15s|%-15.lf|%-17d|\n",listPatients[i].cardId,listPatients[i].name,listPatients[i].phone,listPatients[i].debt,listPatients[i].visitDays);
		}
	}
	for(i=0;i<93;i++){
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
			int i=0,j=0;
			for(i=0;i<n_patients-1;i++){
				for(j=0;j<n_patients-i-1;j++){
					if(listPatients[j].debt>listPatients[j+1].debt){
						temp=listPatients[j];
						listPatients[j]=listPatients[j+1];
						listPatients[j+1]=temp;
					}							
				}
			}
			printf("DANH SACH BENH NHAN\n");
			for(i=0;i<93;i++){
				printf("=");
			}
			printf("\n");
			printf("|Ma BN     |Ten BN                        |SDT            |debt(VND)      |So ngay kham benh|\n");
			for(i=0;i<n_patients;i++){  
				printf("|%-10s|%-30s|%-15s|%-15.lf|%-17d|\n",listPatients[i].cardId,listPatients[i].name,listPatients[i].phone,listPatients[i].debt,listPatients[i].visitDays);
			}
			for(i=0;i<93;i++){
				printf("=");
			}
			printf("\n");
			getchar();			
			break;
		}
		case 2:{
			struct Patient temp;
			int i=0,j=0;
			for(i=0;i<n_patients-1;i++){
				for(j=0;j<n_patients-i-1;j++){
					if(listPatients[j].debt<listPatients[j+1].debt){
						temp=listPatients[j];
						listPatients[j]=listPatients[j+1];
						listPatients[j+1]=temp;
					}							
				}
			}
			printf("DANH SACH BENH NHAN\n");
			for(i=0;i<93;i++){
				printf("=");
			}
			printf("\n");
			printf("|Ma BN     |Ten BN                        |SDT            |debt(VND)      |So ngay kham benh|\n");
			for(i=0;i<n_patients;i++){  
				printf("|%-10s|%-30s|%-15s|%-15.lf|%-17d|\n",listPatients[i].cardId,listPatients[i].name,listPatients[i].phone,listPatients[i].debt,listPatients[i].visitDays);
			}
			for(i=0;i<93;i++){
				printf("=");
			}
			printf("\n");
			getchar();						
			break;
		}
			
			}
	
}
void medicalCheck(){//F07:Ghi nhan kham benh
	char checkId[10];
	char date[15];
	int choice;
	int index=-1;
	struct Record r;
	
	while(1){
		printf("Nhap ma BN:");
		fgets(checkId,sizeof(checkId),stdin);
		checkId[strcspn(checkId,"\n")]='\0';
		if(strlen(checkId)==0){
			printf("Khong duoc de trong!\n");
			continue;
		}
		int i=0;
		for(i=0;i<n_patients;i++){
			if(strcmp(listPatients[i].cardId,checkId)==0){
				index=i;
				break;
			}
		}
		if(index==-1){
			printf("Khong tim thay benh nhan co ID %s\n",checkId);
			continue;
		}
		break;
	}
	while(1){
		printf("Nhap ngay kham benh (day/month/year):");
		fgets(date,sizeof(date),stdin);
		date[strcspn(date,"\n")]='\0';
		
		if(strlen(date)==0){
			printf("Ngay kham benh khong duoc de trong.\n");
			continue;
		}
		if(!isValidDate(date)){
			printf("Ngay thang nam khong hop le!Vui long nhap lai.\n");
			continue;
		}
		int duplicated=0;
		int i=0;
		for(i=0; i<n_records; i++){
    		if(strcmp(listRecords[i].cardId, checkId) == 0 && strcmp(listRecords[i].date, date) == 0){
       		duplicated = 1;
        	break;
    		}
		}
		if(duplicated==1){
    		printf("Benh nhan %s da co lich kham vao ngay %s\n", checkId, date);
    		getchar();
    		return;
		}
			printf("Nhap trang thai (1.Tai kham/2.Theo doi):");
			scanf("%d",&choice);
			sprintf(r.recId, "RC%03d", n_records + 1);
			strcpy(r.cardId,checkId);
			strcpy(r.date,date);
			switch(choice){
				case 1:{
					strcpy(r.status,"Tai kham");
					printf("Cong no benh nhan tang them 100.000VND.\n");
					listPatients[index].debt+=100000;
					break;
				}
				case 2:{
					strcpy(r.status,"Theo doi");
					printf("Cong no benh nhan tang them 200.000VND.\n");
					listPatients[index].debt+=200000;
					break;
				}
			}
			listRecords[n_records]=r;
			n_records++;
			listPatients[index].visitDays++;
			printf("Tao record thanh cong\n");
			break;
		}
	getchar();
}
void medicalHistory(){ //F04:lich su kham benh cua benh nhan 
	char inputId[10];
	int index=-1;
	int found = 0;
	while(1){
		printf("Nhap ma benh nhan can xem lich kham:");
		fgets(inputId,sizeof(inputId),stdin);
		inputId[strcspn(inputId,"\n")]='\0';
		if(strlen(inputId)==0){
			printf("Khong duoc de trong!\n");
			continue;
		}
		int i=0;
		for(i=0;i<n_patients;i++){
			if(strcmp(listPatients[i].cardId,inputId)==0){
				index=i;
				break;
			}
		}
		if(index==-1){
			printf("Khong tim thay benh nhan co ID %s\n",inputId);
			continue;
		}
		break;
	}
 	printf("\nLich kham cua benh nhan: %s\n", listPatients[index].name);
    printf("| ID Rec |  Ng?y kham  |Trang thai|\n");
    printf("-----------------------------------\n");
    int i=0;
    for (i = 0; i < n_records; i++) {
        if (strcmp(listRecords[i].cardId, inputId) == 0) {
            printf("|%-8s|%-13s|%-10s|\n",listRecords[i].recId,listRecords[i].date,listRecords[i].status);
            found = 1;
        }
    }
    printf("-----------------------------------\n");
    if (!found) {
        printf("Chua co lich su kham!\n");
    }
	getchar();	
}
