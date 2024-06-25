#include <stdio.h>
#include <ctype.h>   //isdigit fonksiyonu icin
#include <stdlib.h>  // for atoi funct to convert to key an integer
#include <string.h>  // strlen fonksiyonu icin
#include <stdbool.h> // bool false true mevzusu icin

int check_key(char *key);
char encipher_letters(char *text, char *key);

int main(int argc, char *argv[])
{

    if (argc != 2)
    {
        printf("usage ./subs KEY");
        return 1;
    }
    char *key = argv[1];
    // check_key(key); // keyi gonderdigimiz icin * kullanamayiz. ya &key[] diye ya da direkt key diye.

    if (*key) // eger key gecerliyse koşula girilir
    {
        if (check_key(key) == 0) // 0 dönerse valid keydir
        {
            printf("valid key\n");
        }
        else
        {
            printf("unvalid key\n");
            return 1;
        }
    }
    else
    {
        printf("usage ./subs KEY");
        return 1;
    }

    char text[100];
    printf("plaintext : ");
    fgets(text, sizeof(text), stdin);
    printf("\n");

   
   
      printf("ciphertext: %s",text);    

    return 0;
}

int check_key(char *key)
{
    // check key length
    if (strlen(key) != 26)
    {
        printf("Key must contain 26 characters");
        return 1;
    }

    // check for non-alphabetic characters we'll use isalpha function.this helps us to control characters these are alphabetic or not.
    for (int i = 0; i < strlen(key); i++)
    {
        if (isalpha(key[i]) == false)
        {
            printf("The key must consist of only letters of the alphabet.\n");
            return 1;
        }
    }

    // check for repeated characters
    // tolower() funct ile tüm karakterleri kücük harfe cevirip küçük/büyük fark etmeksizin kontrol yapabiliriz
    // ya da bunu toupper() funct ile yapabiliriz.
    int letter_count[26] = {0};

    for (int i = 0; i < strlen(key); i++)
    {
        char uppercase_char = toupper(key[i]);

        if (isalpha(key[i])) // ya da if (uppercase_char >= 'a' && uppercase_char <= 'z') yani aslinda tekrardan alfabetikligi kontrol ettik.harfse hepsi ona gore islem olcak.
        {
            letter_count[uppercase_char - 'A']++; // indexi belirlenip bir arttırıldı
            /*burada diyelim ki uppercase_char kısmında toupper(key[i]) kısmında A harfi geldi o bir kere arttı demi.indexi
            de belirlendi zaten eger bir daha o indexten gelirse o index 2 olursa eger bu olmaz cunku
            biz her harften bir kez istiyouz.*/
            if (letter_count[uppercase_char - 'A'] > 1)
            {
                printf("the key has repeated characters.\n");
                return 1;
            }
        }
    }
    return 0;
}

char encipher_letters(char *text, char *key)
{
    for (int i = 0; i < 26; i++)
    {
        if (isupper(text[i]))
        {
            int map_index = text[i] - 'A';
            text[i]= toupper(key[map_index]); // simdi bz indeksi bulduk hangisini degiseceğimizi.Girilen textin sırasını yani.
                                                       /*encipher_letters() fonksiyonunda
                                                        toupper() fonksiyonu, text içindeki büyük harfleri key içindeki o indexteki
                                                        karşılık gelen büyük harflerle değiştirmek için kullanılabilir*/ 
        }
        if (islower(text[i]))
        {
            int map_index = text[i] - 'a';
            text[i] = tolower(key[map_index]); /*burada suanda o indexi bulduk mesela soyle
           girdigimiz abcd ya şifrede de mesela efgh var indexi bulduk digerinde 2.index b ya biz ise changehalini buluyoruz
           yani keydeki o indexte ne varsa onu kucuk harf yapmak istiyoruz cunku kural ne girildiyse ona gore yapilacak ya
           ha ona gore mesela keydeki 2.indexte de f var o zaman f döndürürüz böyle böyle yazariz.*/ 
        }
    }
 }
