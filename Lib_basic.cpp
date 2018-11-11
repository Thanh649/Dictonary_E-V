#include <iostream>
#include <conio.h>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <iomanip>
#include <string.h>
using namespace std;

struct node{
	char vWord[20];
	char eWord[20];
	node *next;
};

typedef node *List;

void displayMenu(int w){
	cout<<left<<setw(w)<<"English"<<right<<setw(w)<<"Vietnamese"<<endl;
	cout<<"========================================"<<endl;
}

void displayList(List &L){
	system("cls");
	node *temp = new node;
	if(L == NULL){
		cout<<"Danh sach rong\n";
		getch();
		return;
	}
	int w = 20;
	displayMenu(20);
	temp = L;
	while(temp != NULL){
		int num = strlen(temp->eWord);
		cout<<left<<setw(w)<<temp->eWord;
		cout<<right<<setw(w)<<temp->vWord<<endl;
		temp = temp->next;
	}
}

void addWord(List &L){
	system("cls");
	cin.ignore();
	node *word = new node;
	word->next = NULL;
	cout<<"Nhap tu tieng anh: ";
	cin.getline(word->eWord, 20);
	cout<<"Nhap tu tieng viet: ";
	cin.getline(word->vWord, 20);
	if(L == NULL)
		L = word;
	else{
		node *temp = L;
		while(temp->next != NULL)
			temp = temp->next;
		temp->next = word;
	}
}

void searchWord(List &L){
	system("cls");
	cout<<"<1>- Search Viet - Anh\n";
	cout<<"<2>- Search Anh - Viet\n";
	int Op;
	cout<<"Nhap lua chon: ";
	cin>>Op;
	node *temp = new node;
	cin.ignore();
	char vword[20];
	char eword[20];
	switch(Op){
	case 1:
		cout<<"Nhap tu can tra (viet->anh): ";
		cin.getline(vword, 20);
		temp = L;
		while(strcmp(temp->vWord, vword) !=0){
			temp = temp->next;
			if(temp->next == NULL)
				break;
		}
		if(strcmp(temp->vWord, vword) ==0){
		system("cls");
		displayMenu(20);
		int w = 20;
		cout<<left<<setw(w)<<temp->eWord;
		cout<<right<<setw(w)<<temp->vWord<<endl;
		}
		else{
			cout<<"Tu can tim khong co trong danh sach\n ";
		}
		break;
	case 2:
		cout<<"Nhap tu can tra (anh->viet): ";
		cin.getline(eword, 20);
		temp = L;
		while(strcmp(temp->eWord, eword) !=0){
			temp = temp->next;
			if(temp->next == NULL)
				break;
		}
		if(strcmp(temp->eWord, eword) == 0){
		system("cls");
		displayMenu(20);
		int w = 20;
		cout<<left<<setw(w)<<temp->eWord;
		cout<<right<<setw(w)<<temp->vWord<<endl;
		}
		else{
			cout<<"Tu can tim khong co trong danh sach\n ";
		}
		break;
	}
}

FILE *fp;
void readFile(List &L){
	fp = fopen("data.txt", "r");
	node *t= new node;
	char eword[20], vword[20];
	char c;
	int index;
	while((c=fgetc(fp)) != -1){
		cout<<c;
		index = 0;
		eword[index]=c;
		index++;
		while((c = fgetc(fp)) != '#'){
			eword[index] = c;
			index++;
		}
		eword[index]= '\0';
		index=0;
		while((c = fgetc(fp)) != '\n'){
			vword[index] = c;
			index++;
		}
		vword[index] = '\0';
		node *word = new node;
		word->next = NULL;
		strcpy(word->eWord, eword);
		strcpy(word->vWord, vword);
		if(L == NULL)
			L = word;
		else{
			t = L;
			while(t->next != NULL)
				t = t->next;
			t->next = word;
		}
	}
	fclose(fp);
}

void writeFile(List &L){
	fp = fopen("data.txt", "w+");
	node *temp = L;
	while(temp != NULL){
		fputs(temp->eWord, fp);
		fputc('#', fp);
		fputs(temp->vWord, fp);
		fputc('\n', fp);
		temp = temp->next;
	}
	fclose(fp);
	free(L);
}

void menuMain(List &L){
	int Op;
	system("cls");
	cout<<" *****LIBRARY ENGLISH - VIETNAM BASIC*****\n\n";
	cout<<"<1>- Display list words\n";
	cout<<"<2>- Add words\n";
	cout<<"<3>- Search words\n";
	cout<<"<4>- Exit\n";
	cout<<"Nhap lua chon: ";
	cin>>Op;
	char Yn;
	switch(Op){
	case 1: displayList(L);
			cout<<"\nAn phim bat ky de thoat...";
			getch();
			menuMain(L);
			break;
	case 2: do{
				addWord(L);
				cout<<"Ban muon nhap them tu khong?<Y/N>: ";
				cin>>Yn;
			}while(Yn == 'Y' || Yn =='y');
			menuMain(L);
			break;
	case 3: do{
				searchWord(L);
				cout<<"Ban muon tim tu khac khong?<Y/N>: ";
				cin>>Yn;
			}while(Yn == 'Y' || Yn == 'y');
			menuMain(L);
			break;
	case 4: break;
	}
}

int main(){
	
	int line = 0;
	List L = NULL;
	readFile(L);
	menuMain(L);
	writeFile(L);
	return 0;
}