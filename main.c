//
//  main.c
//  BFS
//
//  Created by Mehmet TIRPAN on 15.12.2022.
//

#include<stdio.h>
#include<stdlib.h>  // -TR- Malloc için gerekli lib. -EN- Malloc function need to this library.
#include<stdbool.h> // -TR- bool yapisi için gerekli lib.  -EN- Use to Bool struct need this library

int dizi[6][6];  // -TR- matris formumuzun kendisini içerir.   -EN- This integer is the Matrix form
bool ziyaret[6]; // -TR- düğümlerin ziyaret edilip edilmediği kontrolü için oluşturulan dizi.  -EN-

//-TR- Kuyruk yapisi için gerekli parametreler. -EN- Necessary parameter to queue struct
//Kuyruklar FIFO mantıginda calisir.

struct node{
    int data;
    struct node *next;
};

struct node* front = NULL; // -TR- kuyrugun önündeki elemanı gösterir. -EN- shows the element in front of the queue.
struct node* rear = NULL; // -TR- kuyrugun arkasındaki elemanı gösterir. -EN- shows the element in rear of the queue.

// -TR- Düğüm (Node) olusturma fonk. -EN- Crate node function
struct node* dugumOlustur(int x){
    struct node* dugum = (struct node*)malloc(sizeof(struct node));
    dugum->data = x;
    dugum->next = NULL;
    return dugum;
}

// -TR- Kuyruğa veri ekleme fonk.  -EN- 
void enQueue(int x){
    
    //Yeni Node olustur
    //Eğer kuyruk boş ise kuyruğu olustur.
    //değilse, Düğümde eleman var ise rear'ın bir sonrakine yeni node koy ve yeni düğümü rear'a atama yap.
    struct node* yeniNode = dugumOlustur(x);
    if(rear == NULL){
        
        front = yeniNode;
        rear=yeniNode;
    }
    else{
        rear->next=yeniNode;
        rear=yeniNode;
    }
}

//Kuyruktan veri cikarma fonk.
void deQueue(){
    //Kuyruk boşsa kontrolü
    if(front == NULL)
        return;
    
    //Düğümde tek eleman varsa.
    if(front->next == NULL){
        front = NULL;
        rear = NULL;
    }
    else{
        //Düğümde birden fazla eleman varsa
        struct node* temp = front->next;
        free(front);
        front = temp;
    }
}

bool KuyrukBosMu(){
    if(front == NULL)
        return true;
    return false;
}


//BFS fonk.
//Baslangic parametresi olarak kök değişken alıyor.
void BFS(int root){
    //1. Başlangıçta bütün node (düğüm) leri ziyaret edilmemiş olarak atansın.
    for(int i=0;i<=5;i++){
        ziyaret[i]=false;
    }
    //2. fonksiyona gelen parametre ziyaret edildi olarak işaretle ve kuyruğa (Queue) al.
    ziyaret[root]=true;
    enQueue(root);
    //3. Kuyruk boş değilse front'un datasını root yap ve ekrana bastır sonrasında kuyruktan çıkart.
    while(KuyrukBosMu()==false){
        root = front->data;
        deQueue();
        printf("%d ",root);
        
        for(int i = 0; i<6; i++){
            if(ziyaret[i] == false && dizi[root][i] == 1)
            {
                ziyaret[i] = true;
                enQueue(i);
            }
    }
    }
    
//    -TR-
    //Kuyruğa ekleme ve ziyaret etme işlemleri
    //Bir düğümün birden fazla komşusu olabilir. Bunu kontrol etmek amacıyla döngü ve if bloğu eklenmiştir.
    //Koşul olarak düğümün daha önceden ziyaret edilmemiş ve o anki düğüm için aradaki ilişkinin olmasına bakılması gerekir
    //yani 1 mi diye bakmamız gerekir.
    //Bu koşullar sağlandıysa artık ziyaret edildi ve kuyruğa eklendi.
    
//    -EN-
    //Adding to the queue and visiting operations
    //A node can have more than one neighbor. A loop and an if block have been added to check this.
    //As a condition, it is necessary to check that the node has not been visited before and that the Decoupling is for the current node
    //so we need to see if it is 1.
    //If these conditions are met, it has now been visited and added to the queue.
}

// -TR- Matris formunu txt dosyasından okuyan fonk. -EN- A function that reads the matrix form from a txt file.
void veriOku(){
    int i = 0;
    FILE *fp = fopen("matris2.txt", "r");
    while(fscanf(fp, "%d %d %d %d %d %d", &dizi[i][0], &dizi[i][1], &dizi[i][2], &dizi[i][3],&dizi[i][4],&dizi[i][5]) != EOF)
    {
        i += 1;
    }
}


int main(){
    
    veriOku();
    printf("Okunan Matris Formu : \n");
    for(int i = 0; i<6; i++){
        for(int j = 0; j<6; j++){
            printf("%d  ",dizi[i][j]);
        }
        printf("\n");
    }
    printf("\n\nBFS Ciktisi : ");
    BFS(0); //matris2.txt
    
    return 0;
}
