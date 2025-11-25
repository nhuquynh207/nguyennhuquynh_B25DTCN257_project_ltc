#include <stdio.h>
#define MAX 100
#include <string.h>
#include <stdlib.h>
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
Record rd;
Patient listPatients[MAX];
int n_patients=0;
int patientIdExisted(const char cardId[]);
void createNewPatient();
void updatePatientInfo();
void dischargePatient();
void showCurrentPatients();

int main(){
	int choose;
	struct Patient pt;
	while(1){

		printf("\n========== Quan ly benh nhan ==========\n");
		printf("1.Tiep nhan benh nhan.\n");
		printf("2.Cap nhat thong tin benh nhan.\n");
		printf("3.Xuat vien.\n");
		printf("4.Hien thi danh sach benh nhan.\n");
		printf("5.Tim kiem benh nhan.\n");
		printf("6.Sap xep danh sach benh nhan.\n");
		printf("7.Ghi nhan khma benh.\n");
		printf("8.Xem lich su kham benh.\n");
		printf("---------------------------------------\n");
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
        printf("Da tim thay thong tin benh nhan %s!\n",listPatients[index].name);
        break; 
    }
    
    printf("=====Cap nhat thong tin benh nhan=====\n");
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
    	printf("CANH BAO BENH NHAN CHUA DONG TIEN VIEN PHI!!!\n");
	}else{
		printf("Benh nhan da xuat vien truoc do.\n");
	}
	printf("Xac nhan benh nhan co xuat vien hay khong?\n1:Co\n2:khong\nNhap:");
	scanf("%d",&choice);
	switch (choice){
		case 1:{
			for(int i=index;i<n_patients-1;i++){
				listPatients[i]=listPatients[i+1];
			}
			printf("Xuat vien thanh cong!\n");
			n_patients--;
			break;
		}
		case 2:{
			printf("Huy xuat vien!\n");
			break;
		}
	}  
}
//F04:Hien thi danh sach benh nhan 
void showCurrentPatients(){
	if(n_patients==0){
		printf("Danh sach trong!\n");
		return;
	}
	printf("+--------------DANH SACH BENH NHAN--------------+\n");
	for(int i=0;i<n_patients;i++){  
		printf("Ma benh nhan:BN%s\n",listPatients[i].cardId);
		printf("Ten benh nhan:%s\n",listPatients[i].name);
		printf("So cong no:%.lf\n",listPatients[i].debt);
		printf("So dien thoai:%s\n",listPatients[i].phone);
		printf("So ngay kham benh:%d\n",listPatients[i].visitDays);
		printf("\n");
	}
	printf("+-----------------------------------------------+\n");
	
}
void searchPatient(){
	char findName[50];
	printf("\nTIM KIEM BENH NHAN\n");
	printf("Nhap ten benh nhan:");
	fgets(findName,sizeof(findName),stdin);
	
	
}

