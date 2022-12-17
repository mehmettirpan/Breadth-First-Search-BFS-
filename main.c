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

//Kuyruk yapisi için gerekli parametreler.
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

//Kuyruğa veri ekleme fonk.
void enQueue(int x){
    //Bu fonk tamamlayiniz.
    
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
    
    //Kuyruğa ekleme ve ziyaret etme işlemleri
    //Bir düğümün birden fazla komşusu olabilir. Bunu kontrol etmek amacıyla döngü ve if bloğu eklenmiştir.
    //Koşul olarak düğümün daha önceden ziyaret edilmemiş ve o anki düğüm için aradaki ilişkinin olmasına bakılması gerekir
    //yani 1 mi diye bakmamız gerekir.
    //Bu koşullar sağlandıysa artık ziyaret edildi ve kuyruğa eklendi.
    
}

//Matris formunu txt dosyasından okuyan fonk.
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
