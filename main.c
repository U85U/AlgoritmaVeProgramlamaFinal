#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void parkurbilgileri();
void engelYerleri();
void yarisYaz();
int asallik(int a, int b);




struct yarismaci{
    int HP;

} yarismacibilgisi;

struct parkur{
    int uzunluk;
    int engelsayisi;
    int *engeller;
} parkurbilgisi;



int main()
{
    srand(time(NULL));
    yarismacibilgisi.HP = 100;
    int i;

    // Parkur Bilgilerini Belirle

    parkurbilgileri();


    // Dinamik Bellek Yönetimi Ýle Engel Yerleri

    engelYerleri();

    // Yarýþma Ve Dosyaya Yazdýrma

    yarisYaz();


    return 0;
}


void parkurbilgileri(){

    parkurbilgisi.uzunluk =50 + rand() %51;
    parkurbilgisi.engelsayisi =2 + rand() % 4;

    parkurbilgisi.engeller = (int *)  malloc( sizeof(int)* parkurbilgisi.engelsayisi );

    if( parkurbilgisi.engeller == NULL ){
        puts("Yetersiz bellek alaný");
        exit(1);
       }

}

void engelYerleri(){

    int i;

    for(i=0;i<parkurbilgisi.engelsayisi; i++){

    parkurbilgisi.engeller[i] =5 +  rand() % ((parkurbilgisi.uzunluk + 1) - 5);

    };

}

void yarisYaz(){
    int i, j;
    FILE *pDosya;

    pDosya = fopen("log.txt", "w+");

    if(pDosya == NULL){
        printf("log.txt dosyasi acilamadi !\n");
        exit(1);
    };

    fprintf(pDosya, "Yarisma Basladi !!!\nYarismaci HP= %d\n", yarismacibilgisi.HP);

    for(i=0; i <= parkurbilgisi.uzunluk; i++){
        for(j=0; j<parkurbilgisi.engelsayisi; j++){

            if((i == parkurbilgisi.engeller[j]) && (asallik(yarismacibilgisi.HP, i) == 1 ) ){
                // Engel İle Karşılaşıldı Ve Aralarında Asal Değiller
                fprintf(pDosya, "Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n", i);
                fprintf(pDosya, "%d. metrede bir engel var. %d ve %d aralarında asal degildir.\n", i, yarismacibilgisi.HP, i);
                fprintf(pDosya, "Yarismaci HP= %d\n", yarismacibilgisi.HP);

            }
            else if((i == parkurbilgisi.engeller[j]) && (asallik(yarismacibilgisi.HP, i) == 0 )){
                // Engel İle Karşılaşıldı Ve Aralarında Asal
                fprintf(pDosya, "Yarismaci %d. metreye kadar bir engelle karsilasmadi.\n", i);
                fprintf(pDosya, "%d. metrede bir engel var. %d ve %d aralarında asaldir.\n", i, yarismacibilgisi.HP, i);
                yarismacibilgisi.HP -= i;
                fprintf(pDosya, "Yarismaci HP= %d\n", yarismacibilgisi.HP);

                if(yarismacibilgisi.HP <= 0){
                    // Oyun Bitti
                    fprintf(pDosya, "Uzgunum !!! Yarismayi Tamamlayamadin.\n");
                    goto bitti;

                };

            };
        };

    };




    fprintf(pDosya, "Yarismaci %d. metreye adar bir engelle karsilasmadi.\nTebrikler !!! Yarisamayi %d HP ile bitirdiniz.\n", parkurbilgisi.uzunluk, yarismacibilgisi.HP);


    bitti:
    fclose(pDosya);

}


int asallik(int a, int b){

    int kucuksayi, buyuksayi, i;
    int dondur = 0;

    if (a > b){
        buyuksayi = a;
        kucuksayi = b;
    }
    else{
        buyuksayi = b;
        kucuksayi = a;
    };

    for(i=2; i<=kucuksayi; i++){
        if( (buyuksayi % i == 0) && (kucuksayi % i == 0) ){
            dondur = 1;
            break;
        };
    };

    return dondur;

}

