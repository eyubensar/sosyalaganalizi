# sosyalaganalizi
# 👥 Sosyal Ağ Grafiği ve Red-Black Tree Uygulaması (C)

Bu proje, C dili kullanılarak yazılmış basit bir **sosyal ağ simülasyonudur**. Kullanıcılar arasında arkadaşlık ilişkileri kurulabilir, derinlikli etkileşimler analiz edilebilir ve sosyal gruplar (topluluklar) keşfedilebilir. Kullanıcılar, **Red-Black Tree** veri yapısında saklanır; etkileşimler **graf yapısıyla** modellenmiştir.

## 📌 Özellikler

- ✔️ Kullanıcı ekleme
- ✔️ Arkadaşlık tanımlama (çift yönlü)
- ✔️ Kullanıcıları Red-Black Tree ile sıralı ve dengeli şekilde saklama
- ✔️ DFS (Derinlik Öncelikli Arama) ile kullanıcı etkileşimleri ve erişim alanı analizi
- ✔️ Ortak arkadaş bulma
- ✔️ Topluluk (bağlantılı bileşen) tespiti
- ✔️ Verilerin `veriseti.txt` dosyasına yazılması

---

## 🏗️ Kurulum

### Gerekli Araçlar

- GCC (C derleyici)
- Terminal / Komut Satırı
 Kullanım
Program çalıştırıldığında menü üzerinden işlem seçebilirsiniz:

1. Kullanıcı Ekle
2. Arkadaşlık Ekle
3. DFS ile Etkileşim Analizi
4. Ortak Arkadaş Bul
5. Toplulukları Göster
6. Veriyi Dosyaya Kaydet
0. Çıkış



🧠 Veri Yapıları
Red-Black Tree
Her kullanıcı Red-Black Tree içine ID’ye göre yerleştirilir.

Arama ve ekleme işlemleri logaritmik sürede yapılır.

Graph (Graf)
Her kullanıcı, bir komsular listesi tutar.

İlişkiler çift yönlü olarak kaydedilir.

DFS (Derinlik Öncelikli Arama)
Kullanıcının kaç kişiye kadar erişebileceği hesaplanır.

Derinlik parametresiyle sınırlandırılabilir.

📁 Dosya Çıkışı
Tüm kullanıcılar ve arkadaşlıkları veriseti.txt dosyasına yazılır:


Kullanıcı ID: 1
Arkadaşlar: 2, 3

Kullanıcı ID: 2
Arkadaşlar: 1



Örnek Kod Parçası
c

kullanici *agac = NULL;
agaca_ekle(&agac, 1);
arkadaslik_ekle(agac, 1, 2);
etki_alani(agac, 1, 2);



