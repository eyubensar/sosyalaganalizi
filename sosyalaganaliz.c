#include <stdio.h>
#include <stdlib.h>

#define MAKS_KISI 100

typedef enum { KIRMIZI, SIYAH } Renk;

typedef struct Kisi {
    int kimlik;
    struct Kisi* baglilar[MAKS_KISI];
    int bagli_sayisi;

    struct Kisi* sol;
    struct Kisi* sag;
    struct Kisi* ebeveyn;
    Renk renk;
} Kisi;

Kisi* kisi_listesi[MAKS_KISI];
int kisi_sayisi = 0;
Kisi* agac_kok = NULL;

// -------------------- RBT Yardýmcý Fonksiyonlar --------------------

void sola_cevir(Kisi** kok, Kisi* x) {
    Kisi* y = x->sag;
    x->sag = y->sol;
    if (y->sol) y->sol->ebeveyn = x;
    y->ebeveyn = x->ebeveyn;
    if (!x->ebeveyn)
        *kok = y;
    else if (x == x->ebeveyn->sol)
        x->ebeveyn->sol = y;
    else
        x->ebeveyn->sag = y;
    y->sol = x;
    x->ebeveyn = y;
}

void saga_cevir(Kisi** kok, Kisi* y) {
    Kisi* x = y->sol;
    y->sol = x->sag;
    if (x->sag) x->sag->ebeveyn = y;
    x->ebeveyn = y->ebeveyn;
    if (!y->ebeveyn)
        *kok = x;
    else if (y == y->ebeveyn->sag)
        y->ebeveyn->sag = x;
    else
        y->ebeveyn->sol = x;
    x->sag = y;
    y->ebeveyn = x;
}

void agac_duzenle(Kisi** kok, Kisi* z) {
    while (z->ebeveyn && z->ebeveyn->renk == KIRMIZI) {
        if (z->ebeveyn == z->ebeveyn->ebeveyn->sol) {
            Kisi* y = z->ebeveyn->ebeveyn->sag;
            if (y && y->renk == KIRMIZI) {
                z->ebeveyn->renk = SIYAH;
                y->renk = SIYAH;
                z->ebeveyn->ebeveyn->renk = KIRMIZI;
                z = z->ebeveyn->ebeveyn;
            } else {
                if (z == z->ebeveyn->sag) {
                    z = z->ebeveyn;
                    sola_cevir(kok, z);
                }
                z->ebeveyn->renk = SIYAH;
                z->ebeveyn->ebeveyn->renk = KIRMIZI;
                saga_cevir(kok, z->ebeveyn->ebeveyn);
            }
        } else {
            Kisi* y = z->ebeveyn->ebeveyn->sol;
            if (y && y->renk == KIRMIZI) {
                z->ebeveyn->renk = SIYAH;
                y->renk = SIYAH;
                z->ebeveyn->ebeveyn->renk = KIRMIZI;
                z = z->ebeveyn->ebeveyn;
            } else {
                if (z == z->ebeveyn->sol) {
                    z = z->ebeveyn;
                    saga_cevir(kok, z);
                }
                z->ebeveyn->renk = SIYAH;
                z->ebeveyn->ebeveyn->renk = KIRMIZI;
                sola_cevir(kok, z->ebeveyn->ebeveyn);
            }
        }
    }
    (*kok)->renk = SIYAH;
}

void rb_ekle(Kisi* yeni) {
    Kisi* y = NULL;
    Kisi* x = agac_kok;

    while (x != NULL) {
        y = x;
        if (yeni->kimlik < x->kimlik)
            x = x->sol;
        else
            x = x->sag;
    }

    yeni->ebeveyn = y;
    if (!y)
        agac_kok = yeni;
    else if (yeni->kimlik < y->kimlik)
        y->sol = yeni;
    else
        y->sag = yeni;

    yeni->sol = yeni->sag = NULL;
    yeni->renk = KIRMIZI;

    agac_duzenle(&agac_kok, yeni);
}

Kisi* rb_ara(Kisi* kok, int kimlik) {
    if (!kok || kok->kimlik == kimlik) return kok;
    return kimlik < kok->kimlik ? rb_ara(kok->sol, kimlik) : rb_ara(kok->sag, kimlik);
}

// -------------------- Grafik Ýþlemleri --------------------

Kisi* kisi_uret(int kimlik) {
    Kisi* k = (Kisi*)malloc(sizeof(Kisi));
    k->kimlik = kimlik;
    k->bagli_sayisi = 0;
    k->sol = k->sag = k->ebeveyn = NULL;
    k->renk = KIRMIZI;
    return k;
}

void kisi_ekle(int kimlik) {
    Kisi* yeni = kisi_uret(kimlik);
    kisi_listesi[kisi_sayisi++] = yeni;
    rb_ekle(yeni);
}

Kisi* kisi_bul(int kimlik) {
    return rb_ara(agac_kok, kimlik);
}

void baglanti_kur(int a, int b) {
    Kisi* k1 = kisi_bul(a);
    Kisi* k2 = kisi_bul(b);
    if (k1 && k2) {
        k1->baglilar[k1->bagli_sayisi++] = k2;
        k2->baglilar[k2->bagli_sayisi++] = k1;
    }
}

// DFS ile gezinme
void derinlik_gez(Kisi* kisi, int limit, int izlenen[], int seviye) {
    if (!kisi || seviye > limit || izlenen[kisi->kimlik]) return;
    izlenen[kisi->kimlik] = 1;
    printf("Kisi %d (seviye %d)\n", kisi->kimlik, seviye);

    for (int i = 0; i < kisi->bagli_sayisi; i++) {
        derinlik_gez(kisi->baglilar[i], limit, izlenen, seviye + 1);
    }
}

void ortaklari_goster(Kisi* a, Kisi* b) {
    int ortak_var = 0;
    printf("\nOrtak Baglantilar: ");
    for (int i = 0; i < a->bagli_sayisi; i++) {
        for (int j = 0; j < b->bagli_sayisi; j++) {
            if (a->baglilar[i]->kimlik == b->baglilar[j]->kimlik) {
                printf("%d ", a->baglilar[i]->kimlik);
                ortak_var = 1;
            }
        }
    }
    if (!ortak_var) printf("Bulunamadi");
    printf("\n");
}

void etki_hesapla(Kisi* kisi) {
    int izlenen[MAKS_KISI] = {0};
    printf("\nEtki Alani (Kisi %d):\n", kisi->kimlik);

    derinlik_gez(kisi, 10, izlenen, 0);

    int toplam = 0;
    for (int i = 0; i < MAKS_KISI; i++) {
        if (izlenen[i]) toplam++;
    }

    printf("Toplam Etki: %d kisi\n", toplam);
}

void topluluk_bul(Kisi* kisi, int izlenen[]) {
    izlenen[kisi->kimlik] = 1;
    printf("%d ", kisi->kimlik);

    for (int i = 0; i < kisi->bagli_sayisi; i++) {
        if (!izlenen[kisi->baglilar[i]->kimlik]) {
            topluluk_bul(kisi->baglilar[i], izlenen);
        }
    }
}

void veri_dosyasi_yaz() {
    FILE* dosya = fopen("veriseti.txt", "w");
    if (!dosya) {
        printf("Dosya yazma hatasi!\n");
        return;
    }

    fprintf(dosya, "# Kisiler\n");
    for (int i = 0; i < kisi_sayisi; i++) {
        fprintf(dosya, "KISI %d\n", kisi_listesi[i]->kimlik);
    }

    fprintf(dosya, "\n# Baglantilar\n");
    for (int i = 0; i < kisi_sayisi; i++) {
        for (int j = 0; j < kisi_listesi[i]->bagli_sayisi; j++) {
            if (kisi_listesi[i]->kimlik < kisi_listesi[i]->baglilar[j]->kimlik) {
                fprintf(dosya, "BAG %d %d\n", kisi_listesi[i]->kimlik, kisi_listesi[i]->baglilar[j]->kimlik);
            }
        }
    }

    fclose(dosya);
    printf("veriseti.txt olusturuldu.\n");
}

// -------------------- Ana Fonksiyon --------------------

int main() {
    int kisi_adet, bag_sayisi;
    int izlenen[MAKS_KISI] = {0};

    printf("Kac kisi eklenecek? ");
    scanf("%d", &kisi_adet);

    for (int i = 0; i < kisi_adet; i++) {
        int id;
        printf("Kisi ID: ");
        scanf("%d", &id);
        kisi_ekle(id);
    }

    printf("Kac baglanti kurulacak? ");
    scanf("%d", &bag_sayisi);

    for (int i = 0; i < bag_sayisi; i++) {
        int a, b;
        printf("Baglanti (id1 id2): ");
        scanf("%d %d", &a, &b);
        baglanti_kur(a, b);
    }

    veri_dosyasi_yaz();

    int basla_id;
    printf("\nDFS baslangic ID: ");
    scanf("%d", &basla_id);
    Kisi* basla = kisi_bul(basla_id);
    if (basla) derinlik_gez(basla, 2, izlenen, 0);

    int id1, id2;
    printf("\nOrtak baglantilar icin iki ID girin: ");
    scanf("%d %d", &id1, &id2);
    Kisi* k1 = kisi_bul(id1);
    Kisi* k2 = kisi_bul(id2);
    if (k1 && k2) ortaklari_goster(k1, k2);

    printf("\nEtki alani icin ID girin: ");
    scanf("%d", &id1);
    Kisi* etkili = kisi_bul(id1);
    if (etkili) etki_hesapla(etkili);

    printf("\nTopluluklar:\n");
    for (int i = 0; i < kisi_sayisi; i++) {
        if (!izlenen[kisi_listesi[i]->kimlik]) {
            printf("\nTopluluk: ");
            topluluk_bul(kisi_listesi[i], izlenen);
            printf("\n");
        }
    }

    printf("\nveriseti.txt icerigi:\n\n");
    FILE* oku = fopen("veriseti.txt", "r");
    if (!oku) {
        printf("Dosya okunamadi!\n");
        return 1;
    }

    char satir[256];
    while (fgets(satir, sizeof(satir), oku)) {
        printf("%s", satir);
    }

    fclose(oku);
    return 0;
}
