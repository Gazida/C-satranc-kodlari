#include <stdio.h>
#include <stdlib.h>

// 1. oyuncu için
int gecerkenAl = 0;
// 2. oyuncu için
int GecerkenAl = 0;

//Prototipler
void p(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void k(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void a(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void f(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void v(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void s(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void P(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void K(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void A(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void F(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void V(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);
void S(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q);

// Oyuncu1 piyonu
void p(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{	
	while(1)
	{					
		if(*y2-*y == 2)
		{
			//ilk defa oynanmayan piyon 1 birimden fazla oynanamaz
			if(*y != 2)
			{
				*q = 0;
				break;
			}	
			// ilk defa oynanacak piyonun iki birim ileriye gidebilme şartları
			else
			{
				// Aynı sütunda iki birim ileri oynayabilir
				if(*x2-*x == 0)
				{
					// Piyonun önü boşsa döngüden çıkılır oyun devam eder
					if(tahta[*y2-1][*x2-1] == '#')
					{
						gecerkenAl = 1; // bu komut rakip takımın piyon sürüşünde kullanılıcak  gecerkenAl ==1 olması piyonun 2 defa sürülmüş olmasını gösterir
						GecerkenAl = 0; // Her while dan çıkışımızda rakibin GecerkenAl ı 0 olmalı
						*q = 1;
						break; 
					}
					// Piyonun önünde herhangi bir taş varsa hata alınır
					else
					{
						*q = 0;
						break;
					}
				}
				// İki birim oynanan piyon hiçbir zaman başka sütuna geçemz
				else
				{
					*q = 0;
					break;
				}
			}
		}				
		//Piyonlar geriye oynayamaz ve aynı satırda hareket edemez
		else if(*y2-*y <= 0)
		{		
			*q = 0;
			break;
		}				
		//2 birimden fazla ilerlenildiğinde verilecek hata
		else if(*y2-*y > 2)
		{
			*q = 0;
			break;
		}		
		//Piyonlar genellikle 1 birim ileri oynatılabilir(Önünde herhangi bir taş olmadığı sürece) dolayısıyla artık döngüden çıkabiliriz
		else if(*y2-*y == 1)
		{			
			// Piyonlar 1 birim çapraz hareket ettrilirse
			if(*x2-*x == 1 || *x2-*x == -1)
			{
				// Piyonların çapraz hareket edebilmesi için gideceği karede rakip takımın taşları bulunmalı
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V')
				{
					GecerkenAl = 0;
					*q = 1;
					break;
				}
				// Geçerken alma	
				else if(GecerkenAl == 1)
				{
					if(tahta[*y-1][*x-1+1] == 'P' && *x2-*x == 1 && tahta[*y2-1-1][*x2-1] == 'P')
						tahta[*y-1][*x-1+1] = '#';
					else if(tahta[*y-1][*x-1-1] == 'P' && *x2-*x == -1 && tahta[*y2-1-1][*x2-1] == 'P')
						tahta[*y-1][*x-1-1] = '#';
					else
					{
						*q = 0;
						break;
					}
					GecerkenAl = 0;
					*q = 1;
					break;
				}
				// Aksi halde hatalı oynama yapılmış olur	
				else
				{
					*q = 0;
					break;
				}	 
			}
			// Piyonlar 1 birim ileri oynatılırsa 
			else
			{				
				// Piyonun önü boşsa döngüden çıkılır oyun devam eder
				if(tahta[*y2-1][*x2-1] == '#')
				{
					GecerkenAl = 0;
					*q = 1;
					break;
				}
				// Piyonun önünde herhangi bir taş varsa hata alınır
				else
				{
					*q = 0;
					break;
				}	
			}			
		}				
	}
}
// Oyuncu1 Kalesi
void k(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	int i, j;
	while(1)
	{		
		// Kale aynı sütunda istenildiği kadar ileri gidebilir
		if(*x2 == *x && *y2 != *y)
		{	
			// Kale ileri oynarsa
			if(*y2>*y)
			{	
				for(i=*y-1+1; i<*y2-1; i++)
				{	
					//  Kalenin önünde taş versa *q = 1 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[i][*x-1] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}
			// Kale geri oynarsa
			else if(*y2<*y)
			{
				for(i=*y2-1-1; i>*y-1; i--)
				{
					//  Kalenin önünde taş versa *q = 1 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[i][*x-1] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}				
		}
		else if(*y2 == *y && *x2 != *x)
		{	
			// Kale sola oynarsa
			if(*x2>*x)
			{	
				for(i=*x-1+1; i<*x2-1; i++)
				{	
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[*y-1][i] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}
			// Kale sağa oynarsa
			else if(*x2<*x)
			{
				for(i=*x2-1-1; i>*x-1; i--)
				{
					//  Kalenin önünde taş versa *q = 1 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[*y-1][i] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}				
		}
		// Kale düz hareket ettirilmezse hata alınır
		else
		{
			*q = 0;
			break;
		}
	}
}
// Oyuncu1 atı
void a(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	while(1)
	{
		// At 2 birim ileri veya geri haraket ederse
		if(*y2-*y == 2 || *y2-*y == -2)
		{
			// 1 birim sağa veya sola giderse hata yok
			if(*x2-*x == 1 || *x2-*x == -1)
			{
				// Atın gideceği konumda kendi taşları yoksa hata alınmaz
				if(tahta[*y2-1][*y2-1] == '#' || tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V')
				{
					*q = 1; 
					break;
				}
				// Aksi durumlarda hata alınır
				else
				{
					*q = 0;
					break;
				}
			} // 1 birim dışında bir oynama olursa hata alınır
			else
			{
				*q = 0;
				break;
			}
		}
		// At 2 birim sağa veya sola giderse
		else if(*x2-*x == 2 || *x2-*x == -2)
		{
			// 1 birim aşağı veya yukarı gitmeli
			if(*y2-*y == 1 || *y2-*y == -1)
			{
				// Gideceği konumda kendi taşları yoks hata alınmaz
				if(tahta[*y2-1][*y2-1] == '#' || tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V')
				{
					*q = 1; 
					break;
				}
				// Aksi durumlarda hata alınır
				else
				{
					*q = 0;
					break;
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
		else
			{
				*q = 0;
				break;
			}
	}
}
void f(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	int kontrol = 0, i;
	while(1)
	{
		// Fil aşağı hareket ederse
		if(*y2-*y>0)
		{
			kontrol = 0;
			// Fil aşağı kaç birim gittiyse sağa o kadar gitmeli
			if(*x2-*x == *y2-*y)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y+i][*x+i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'p' || tahta[*y2-1][*x2-1] != 'k' || tahta[*y2-1][*x2-1] != 'a' || tahta[*y2-1][*x2-1] != 'f' || tahta[*y2-1][*x2-1] != 'v' || tahta[*y2-1][*x2-1] != 's')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}				
			}
			// Fil aşağı kaç birim gittiyse sola o kadar gitmeli
			else if(*x2-*x == *y-*y2)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y+i][*x-2-i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'p' || tahta[*y2-1][*x2-1] != 'k' || tahta[*y2-1][*x2-1] != 'a' || tahta[*y2-1][*x2-1] != 'f' || tahta[*y2-1][*x2-1] != 'v' || tahta[*y2-1][*x2-1] != 's')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
		// Fil yukarı hareket ederse
		if(*y2-*y<0)
		{
			kontrol = 0;
			// Fil yukarı kaç birim gittiyse sağa o kadar gitmeli
			if(*x2-*x == *y-*y2)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y-2-i][*x+i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'p' || tahta[*y2-1][*x2-1] != 'k' || tahta[*y2-1][*x2-1] != 'a' || tahta[*y2-1][*x2-1] != 'f' || tahta[*y2-1][*x2-1] != 'v' || tahta[*y2-1][*x2-1] != 's')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}				
			}
			// Fil yukarı kaç birim gittiyse sola o kadar gitmeli
			else if(*x2-*x == *y2-*y)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{ 
					if(tahta[*y-2-i][*x-2-i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'p' || tahta[*y2-1][*x2-1] != 'k' || tahta[*y2-1][*x2-1] != 'a' || tahta[*y2-1][*x2-1] != 'f' || tahta[*y2-1][*x2-1] != 'v' || tahta[*y2-1][*x2-1] != 's')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
	}
}
// Oyuncu1 veziri
// Vezir, kale ve filin yapatığı her şeyi yapabilir
void v(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	int i, j, kontrol;
	while(1)
	{		
		// Kale aynı sütunda istenildiği kadar ileri gidebilir
		if(*x2 == *x && *y2 != *y)
		{	
			// Kale ileri oynarsa
			if(*y2>*y)
			{	
				for(i=*y-1+1; i<*y2-1; i++)
				{	
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[i][*x-1] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}
			// Kale geri oynarsa
			else if(*y2<*y)
			{
				for(i=*y2-1-1; i>*y-1; i--)
				{
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[i][*x-1] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}				
		}
		else if(*y2 == *y && *x2 != *x)
		{	
			// Kale sola oynarsa
			if(*x2>*x)
			{	
				for(i=*x-1+1; i<*x2-1; i++)
				{	
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[*y-1][i] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}
			// Kale sağa oynarsa
			else if(*x2<*x)
			{
				for(i=*x2-1-1; i>*x-1; i--)
				{
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[*y-1][i] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}				
		}
		// Fil aşağı hareket ederse
		if(*y2-*y>0)
		{
			kontrol = 0;
			// Fil aşağı kaç birim gittiyse sağa o kadar gitmeli
			if(*x2-*x == *y2-*y)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y+i][*x+i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'p' || tahta[*y2-1][*x2-1] != 'k' || tahta[*y2-1][*x2-1] != 'a' || tahta[*y2-1][*x2-1] != 'f' || tahta[*y2-1][*x2-1] != 'v' || tahta[*y2-1][*x2-1] != 's')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}				
			}
			// Fil aşağı kaç birim gittiyse sola o kadar gitmeli
			else if(*x2-*x == *y-*y2)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y+i][*x-2-i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'p' || tahta[*y2-1][*x2-1] != 'k' || tahta[*y2-1][*x2-1] != 'a' || tahta[*y2-1][*x2-1] != 'f' || tahta[*y2-1][*x2-1] != 'v' || tahta[*y2-1][*x2-1] != 's')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
		// Fil yukarı hareket ederse
		if(*y2-*y<0)
		{
			kontrol = 0;
			// Fil yukarı kaç birim gittiyse sağa o kadar gitmeli
			if(*x2-*x == *y-*y2)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y-2-i][*x+i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'p' || tahta[*y2-1][*x2-1] != 'k' || tahta[*y2-1][*x2-1] != 'a' || tahta[*y2-1][*x2-1] != 'f' || tahta[*y2-1][*x2-1] != 'v' || tahta[*y2-1][*x2-1] != 's')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}				
			}
			// Fil yukarı kaç birim gittiyse sola o kadar gitmeli
			else if(*x2-*x == *y2-*y)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{ 
					if(tahta[*y-2-i][*x-2-i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'p' || tahta[*y2-1][*x2-1] != 'k' || tahta[*y2-1][*x2-1] != 'a' || tahta[*y2-1][*x2-1] != 'f' || tahta[*y2-1][*x2-1] != 'v' || tahta[*y2-1][*x2-1] != 's')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
	}
}
// Oyuncu1 şahı
void s(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	int i, j;
	*q = 3; // *q değerini değiştirmeden rakibin kale fonksiyonu çağrıldığında hata aldığım için *q değerine boş bir değer atadım
	for(i=1; i<9; i++)
	{
		for(j=1; j<9; j++)
		{
			if(tahta[i-1][j-1] == 'K')
			{
				K(tahta, &j, &i, x2, y2, q);
			}
			else if(tahta[i-1][j-1] == 'A')
			{
				A(tahta, &j, &i, x2, y2, q);
			}
			else if(tahta[i-1][j-1] == 'F')
			{
				F(tahta, &j, &i, x2, y2, q);
			}
			else if(tahta[i-1][j-1] == 'V')
			{
				V(tahta, &j, &i, x2, y2, q);
			}
				if(*q == 1)
				{
					*q = 2;
					break;
				}
			// Rakip takımın şahının 1 birim yakınına oynatmaya çalışılabilir. Bunun için tüm şartlar aşağıda yazıldı
			else if(tahta[i-1][j-1] == 'S')
			{
				// Şahını rakip takımın şahının 1 sağına/soluna oynatmaya çalıştığında hata alınacak
				if((i-1 == *y2-1) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
				// Şahını rakip takımın şahının 1 sağına/soluna oynatmaya çalıştığında hata alınacak
				else if((i-1 == *y2-1) && (j-1 == *x2)) 
				{
					*q = 4;
					break;
				}
				// Şahını rakip takımın şahının 1 önüne/arkasına oynatmaya çalıştığında hata alınacak
				else if((i-1 == *y2-2) && (j-1 == *x2-1)) 
				{
					*q = 4;
					break;
				}
				// Şahını rakip takımın şahının 1 birim önüne/arkasına oynatmaya çalıştığında hata alınacak
				else if((i-1 == *y2) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
				// Rakibin şahının 1 birim çaprazına oynanmak istendiğinde hata alınır
				else if((i-1 == *y2-2) && (j-1 == *x2)) 
				{
					*q = 4;
					break;
				}
				// Rakibin şahının 1 birim çaprazına oynanmak istendiğinde hata alınır
				else if((i-1 == *y2) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
				// Rakibin şahının 1 birim çaprazına oynanmak istendiğinde hata alınır
				else if((i-1 == *y2-2) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
				// Rakibin şahının 1 birim çaprazına oynanmak istendiğinde hata alınır
				else if((i-1 == *y2-2) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
			}
		}
		if(*q == 2 || *q == 4)
		{
			printf("asma = %d\n", *q);
			break;	
		}
	}
	while(1)
	{
		if(*q == 2 || *q == 4)
		{
			*q = 0; 
			break;	
		} 
			
		// Şah ileri oynarsa
		if(*y2-*y == 1)
		{
			if(*x2-*x == 0 || *x2-*x == 1 || *x2-*x == -1) 
			{
				*q = 1;
				break;
			}
			else
			{
				*q = 0;
				break;
			}
		}
		// Şah geri oynarsa
		else if(*y2-*y == -1)
		{
			if(*x2-*x == 0 || *x2-*x == 1 || *x2-*x == -1) 
			{
				*q = 1;
				break;
			}
			else
			{
				*q = 0;
				break;
			}
		}
		// Şah y ekseninde hareket etmezse
		else if(*y2-*y == 0)
		{
			if(*x2-*x == 1 || *x2-*x == -1) 
			{
				*q = 1;
				break;
			}
			else
			{
				*q = 0;
				break;
			}
		}
		else
		{
			*q = 0;
			break;
		}
	}
}
// Oyuncu2 piyonu
void P(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{	
	while(1)
	{		
		// Piyonlar 2 birim ileri oynatılırsa
		if(*y-*y2 == 2)
		{
			//ilk defa oynanmayan piyon 1 birimden fazla oynanamaz
			if(*y != 7)
			{
				*q = 0;
				break;
			}	
			// ilk defa oynanacak piyonun iki birim ileriye gidebilme şartları
			else
			{
				// Aynı sütunda iki birim ileri oynayabilir
				if(*x-*x2 == 0)
				{
					// Piyonun önü boşsa döngüden çıkılır oyun devam eder
					if(tahta[*y2-1][*x2-1] == '#')
					{
						GecerkenAl = 1; // bu komut rakip takımın piyon sürüşünde kullanılıcak. GecerkenAl ==1 olması piyonun 2 defa sürülmüş olmasını gösterir
						gecerkenAl = 0; // Her while dan çıkışımızda rakibin gecerkenAl ı 0 olmalı
						*q = 1;
						break; 
					}
					// Piyonun önünde herhangi bir taş varsa hata alınır
					else
					{
						*q = 0;
						break;
					}
				}
				// İki birim oynanan piyon hiçbir zaman başka sütuna geçemz
				else
				{
					*q = 0;
					break;
				}
			}
		}		
		//Piyonlar geriye oynayamaz ve aynı satırda hareket edemez
		else if(*y-*y2 <= 0)
		{		
			*q = 0;
			break;
		}				
		//2 birimden fazla ilerlenildiğinde verilecek hata
		else if(*y-*y2 > 2)
		{
			*q = 0;
			break;
		}			
		//Piyonlar genellikle 1 birim ileri oynatılabilir(Önünde herhangi bir taş olmadığı sürece) dolayısıyla artık döngüden çıkabiliriz
		else if(*y-*y2 == 1)
		{			
			// Piyonlar 1 birim çapraz hareket ettrilirse
			if(*x-*x2 == 1 || *x-*x2 == -1)
			{
				// Piyonların çapraz hareket edebilmesi için gideceği karede rakip takımın taşları bulunmalı
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v')
				{
					gecerkenAl = 0;
					*q = 1; 
					break;
				}
				// Geçerken alma	
				else if(gecerkenAl == 1)
				{
					if(tahta[*y-1][*x-1+1] == 'p' && *x2-*x == 1 && tahta[*y2-1+1][*x2-1] == 'p')
						tahta[*y-1][*x-1+1] = '#';
					else if(tahta[*y-1][*x-1-1] == 'p' && *x2-*x == -1 && tahta[*y2-1+1][*x2-1] == 'p')
						tahta[*y-1][*x-1-1] = '#';
					else
					{
						*q = 0;
						break;
					}
					GecerkenAl = 0;
					*q = 1;
					break;
				}	
				// Aksi halde hatalı oynama yapılmış olur	
				else
				{
					*q = 0;
					break;
				}	 
			}
			// Piyonlar 1 birim ileri oynatılırsa 
			else
			{
				// Piyonun önü boşsa döngüden çıkılır oyun devam eder
				if(tahta[*y2-1][*x2-1] == '#')
				{
					gecerkenAl= 0; 
					*q = 1;
					break;
				}
				// Piyonun önünde herhangi bir taş varsa hata alınır
				else
				{
					*q = 0;
					break;
				}	
			}					
		}			
	}
}
// Oyuncu2 Kalesi
void K(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	int i, j;
	while(1)
	{		
		// Kale aynı sütunda istenildiği kadar ileri gidebilir
		if(*x2 == *x && *y2 != *y)
		{
			// Kale ileri oynarsa
			if(*y>*y2)
			{
				for(i=*y-1-1; i>*y2-1; i--)
				{	
					//  Kalenin önünde taş versa *q = 1 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[i][*x-1] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'K' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}
			// Kale geri oynarsa
			else if(*y<*y2)
			{
				for(i=*y-1+1; i<*y2-1; i++)
				{
					//  Kalenin önünde taş versa *q = 1 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[i][*x-1] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}				
		}
		else if(*y2 == *y && *x2 != *x)
		{	
			// Kale sağa oynarsa
			if(*x2>*x)
			{	
				for(i=*x-1+1; i<*x2-1; i++)
				{	
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[*y-1][i] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}
			// Kale sola oynarsa
			else if(*x2<*x)
			{
				for(i=*x2-1-1; i>*x-1; i--)
				{
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[*y-1][i] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}				
		}
		// Kale düz hareket ettirilmezse
		else
		{
			*q = 0;
			break;
		}
	}
}
// Oyuncu2 atı
void A(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	while(1)
	{
		// At 2 birim ileri veya geri haraket ederse
		if(*y2-*y == 2 || *y2-*y == -2)
		{
			// 1 birim sağa veya sola giderse hata yok
			if(*x2-*x == 1 || *x2-*x == -1)
			{
				// Atın gideceği konumda kendi taşları yoksa hata alınmaz
				if(tahta[*y2-1][*y2-1] == '#' || tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v')
				{
					*q = 1; 
					break;
				}
				// Aksi durumlarda hata alınır
				else
				{
					*q = 0;
					break;
				}
			} // 1 birim dışında bir oynama olursa hata alınır
			else
			{
				*q = 0;
				break;
			}
		}
		// At 2 birim sağa veya sola giderse
		else if(*x2-*x == 2 || *x2-*x == -2)
		{
			// 1 birim aşağı veya yukarı gitmeli
			if(*y2-*y == 1 || *y2-*y == -1)
			{
				// Gideceği konumda kendi taşları yoks hata alınmaz
				if(tahta[*y2-1][*y2-1] == '#' || tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v')
				{
					*q = 1; 
					break;
				}
				// Aksi durumlarda hata alınır
				else
				{
					*q = 0;
					break;
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
		else
			{
				*q = 0;
				break;
			}
	}
}
void F(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	int kontrol = 0, i;
	while(1)
	{
		// Fil aşağı hareket ederse
		if(*y2-*y>0)
		{
			kontrol = 0;
			// Fil aşağı kaç birim gittiyse sağa o kadar gitmeli
			if(*x2-*x == *y2-*y)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y+i][*x+i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'P' || tahta[*y2-1][*x2-1] != 'K' || tahta[*y2-1][*x2-1] != 'A' || tahta[*y2-1][*x2-1] != 'F' || tahta[*y2-1][*x2-1] != 'V' || tahta[*y2-1][*x2-1] != 'S')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}				
			}
			// Fil aşağı kaç birim gittiyse sola o kadar gitmeli
			else if(*x2-*x == *y-*y2)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y+i][*x-2-i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'P' || tahta[*y2-1][*x2-1] != 'K' || tahta[*y2-1][*x2-1] != 'A' || tahta[*y2-1][*x2-1] != 'F' || tahta[*y2-1][*x2-1] != 'V' || tahta[*y2-1][*x2-1] != 'S')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
		// Fil yukarı hareket ederse
		if(*y2-*y<0)
		{
			kontrol = 0;
			// Fil yukarı kaç birim gittiyse sağa o kadar gitmeli
			if(*x2-*x == *y-*y2)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y-2-i][*x+i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'P' || tahta[*y2-1][*x2-1] != 'K' || tahta[*y2-1][*x2-1] != 'A' || tahta[*y2-1][*x2-1] != 'F' || tahta[*y2-1][*x2-1] != 'V' || tahta[*y2-1][*x2-1] != 'S')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}				
			}
			// Fil yukarı kaç birim gittiyse sola o kadar gitmeli
			else if(*x2-*x == *y2-*y)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{ 
					if(tahta[*y-2-i][*x-2-i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'P' || tahta[*y2-1][*x2-1] != 'K' || tahta[*y2-1][*x2-1] != 'A' || tahta[*y2-1][*x2-1] != 'F' || tahta[*y2-1][*x2-1] != 'V' || tahta[*y2-1][*x2-1] != 'S')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
	}
}
// Oyuncu2 veziri
// Vezir, kale ve filin yapatığı her şeyi yapabilir
void V(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	int i, j, kontrol;
	while(1)
	{		
		// Kale aynı sütunda istenildiği kadar ileri gidebilir
		if(*x2 == *x && *y2 != *y)
		{
			// Kale ileri oynarsa
			if(*y>*y2)
			{
				for(i=*y-1-1; i>*y2-1; i--)
				{	
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 0 ise hata alınacaktır)
					if(tahta[i][*x-1] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'K' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 1 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}
			// Kale geri oynarsa
			else if(*y<*y2)
			{
				for(i=*y-1+1; i<*y2-1; i++)
				{
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 0 ise hata alınacaktır)
					if(tahta[i][*x-1] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 1 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}				
		}
		else if(*y2 == *y && *x2 != *x)
		{	
			// Kale sağa oynarsa
			if(*x2>*x)
			{	
				for(i=*x-1+1; i<*x2-1; i++)
				{	
					//  Kalenin önünde taş versa *q = 0 ataması yapılır (ana fonksiyonda q = 0 ise hata alınacaktır)
					if(tahta[*y-1][i] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 1 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}
			// Kale sola oynarsa
			else if(*x2<*x)
			{
				for(i=*x2-1-1; i>*x-1; i--)
				{
					//  Kalenin önünde taş versa *q = 1 ataması yapılır (ana fonksiyonda q = 1 ise hata alınacaktır)
					if(tahta[*y-1][i] != '#')
					{
						*q = 0;
						break;
					}
				}
				// *q = 0 ise while döngüsünden ve dolayısıyla 'k' fonksiyonundan çıkılır
				if(*q == 0)
					break;
				// Kalenin önü boşsa ve gitmek istediği yer boş veya rakibin herhangi bir taşı varsa  q = 0 (ana fonksiyonda hata alınmayacağı anlamına gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 1;
					break;
				}
				// Kalenin önü boşsa ve gitmek istediği konumda kendi taşlarından herhangi biri varsa hatalı seçim olacaktır
				else
				{
					*q = 0;
					break;
				}
			}				
		}
		// Fil aşağı hareket ederse
		if(*y2-*y>0)
		{
			kontrol = 0;
			// Fil aşağı kaç birim gittiyse sağa o kadar gitmeli
			if(*x2-*x == *y2-*y)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y+i][*x+i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'P' || tahta[*y2-1][*x2-1] != 'K' || tahta[*y2-1][*x2-1] != 'A' || tahta[*y2-1][*x2-1] != 'F' || tahta[*y2-1][*x2-1] != 'V' || tahta[*y2-1][*x2-1] != 'S')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}				
			}
			// Fil aşağı kaç birim gittiyse sola o kadar gitmeli
			else if(*x2-*x == *y-*y2)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y+i][*x-2-i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'P' || tahta[*y2-1][*x2-1] != 'K' || tahta[*y2-1][*x2-1] != 'A' || tahta[*y2-1][*x2-1] != 'F' || tahta[*y2-1][*x2-1] != 'V' || tahta[*y2-1][*x2-1] != 'S')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
		// Fil yukarı hareket ederse
		if(*y2-*y<0)
		{
			kontrol = 0;
			// Fil yukarı kaç birim gittiyse sağa o kadar gitmeli
			if(*x2-*x == *y-*y2)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{
					if(tahta[*y-2-i][*x+i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'P' || tahta[*y2-1][*x2-1] != 'K' || tahta[*y2-1][*x2-1] != 'A' || tahta[*y2-1][*x2-1] != 'F' || tahta[*y2-1][*x2-1] != 'V' || tahta[*y2-1][*x2-1] != 'S')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}				
			}
			// Fil yukarı kaç birim gittiyse sola o kadar gitmeli
			else if(*x2-*x == *y2-*y)
			{
				// Filin önünde taş varsa
				for(i=0; i<*y2-*y-1; i++)
				{ 
					if(tahta[*y-2-i][*x-2-i] != '#')
						kontrol++;					
				}
				if(kontrol>0)
				{
					*q = 0;
					break;
				}
				else
				{	// Gidilen konumda kendi taşları yoksa
					if(tahta[*y2-1][*x2-1] != 'P' || tahta[*y2-1][*x2-1] != 'K' || tahta[*y2-1][*x2-1] != 'A' || tahta[*y2-1][*x2-1] != 'F' || tahta[*y2-1][*x2-1] != 'V' || tahta[*y2-1][*x2-1] != 'S')
					{
						*q = 1; 
						break;
					}
					else
					{
						*q = 0;
						break;
					}
				}
			}
			else
			{
				*q = 0;
				break;
			}
		}
	}
}
// Oyuncu1 şahı
void S(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{
	int i, j;
	*q = 3; // *q değerini değiştirmeden rakibin kale fonksiyonu çağrıldığında hata aldığım için *q değerine boş bir değer atadım
	for(i=1; i<9; i++)
	{
		for(j=1; j<9; j++)
		{
			if(tahta[i-1][j-1] == 'k')
			{
				K(tahta, &j, &i, x2, y2, q);
			}
			else if(tahta[i-1][j-1] == 'a')
			{
				A(tahta, &j, &i, x2, y2, q);
			}
			else if(tahta[i-1][j-1] == 'f')
			{
				F(tahta, &j, &i, x2, y2, q);
			}
			else if(tahta[i-1][j-1] == 'v')
			{
				V(tahta, &j, &i, x2, y2, q);
			}
				if(*q == 1)
				{
					*q = 2;
					break;
				}
			// Rakip takımın şahının 1 birim yakınına oynatmaya çalışılabilir. Bunun için tüm şartlar aşağıda yazıldı
			else if(tahta[i-1][j-1] == 's')
			{
				// Şahını rakip takımın şahının 1 sağına/soluna oynatmaya çalıştığında hata alınacak
				if((i-1 == *y2-1) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
				// Şahını rakip takımın şahının 1 sağına/soluna oynatmaya çalıştığında hata alınacak
				else if((i-1 == *y2-1) && (j-1 == *x2)) 
				{
					*q = 4;
					break;
				}
				// Şahını rakip takımın şahının 1 önüne/arkasına oynatmaya çalıştığında hata alınacak
				else if((i-1 == *y2-2) && (j-1 == *x2-1)) 
				{
					*q = 4;
					break;
				}
				// Şahını rakip takımın şahının 1 birim önüne/arkasına oynatmaya çalıştığında hata alınacak
				else if((i-1 == *y2) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
				// Rakibin şahının 1 birim çaprazına oynanmak istendiğinde hata alınır
				else if((i-1 == *y2-2) && (j-1 == *x2)) 
				{
					*q = 4;
					break;
				}
				// Rakibin şahının 1 birim çaprazına oynanmak istendiğinde hata alınır
				else if((i-1 == *y2) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
				// Rakibin şahının 1 birim çaprazına oynanmak istendiğinde hata alınır
				else if((i-1 == *y2-2) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
				// Rakibin şahının 1 birim çaprazına oynanmak istendiğinde hata alınır
				else if((i-1 == *y2-2) && (j-1 == *x2-2)) 
				{
					*q = 4;
					break;
				}
			}
		}
		if(*q == 2 || *q == 4)
		{
			printf("asma = %d\n", *q);
			break;	
		}
	}
	while(1)
	{
		if(*q == 2 || *q == 4)
		{
			*q = 0; 
			break;	
		} 
			
		// Şah ileri oynarsa
		if(*y2-*y == 1)
		{
			if(*x2-*x == 0 || *x2-*x == 1 || *x2-*x == -1) 
			{
				*q = 1;
				break;
			}
			else
			{
				*q = 0;
				break;
			}
		}
		// Şah geri oynarsa
		else if(*y2-*y == -1)
		{
			if(*x2-*x == 0 || *x2-*x == 1 || *x2-*x == -1) 
			{
				*q = 1;
				break;
			}
			else
			{
				*q = 0;
				break;
			}
		}
		// Şah y ekseninde hareket etmezse
		else if(*y2-*y == 0)
		{
			if(*x2-*x == 1 || *x2-*x == -1) 
			{
				*q = 1;
				break;
			}
			else
			{
				*q = 0;
				break;
			}
		}
		else
		{
			*q = 0;
			break;
		}
	}
}
int main()
{
	char tahta[8][8], gecici;
	int i, j, n=0, x, y, x2, y2;
	int q; // foksiyona gidildikten sonra hatali seçim yapılırsa q değeri if koşulu olarak kullanılacak 
	
	//Satranc tahtasına taşları yerleştirme 
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			tahta[i][j] = '#';
		}
	}
	for(i=0; i==0 || i==7; i+=7)
	{
		for(j=0; j<8; j++)
		{
			if(i == 0)
			tahta[i+1][j] = 'p';
			else
			tahta[i-1][j] = 'P';
		}
	}
	tahta[0][0] = 'k'; tahta[7][0] = 'K';
	tahta[0][1] = 'a'; tahta[7][1] = 'A';
	tahta[0][2] = 'f'; tahta[7][2] = 'F';
	tahta[0][3] = 's'; tahta[7][3] = 'S';
	tahta[0][4] = 'v'; tahta[7][4] = 'V';
	tahta[0][5] = 'f'; tahta[7][5] = 'F';
	tahta[0][6] = 'a'; tahta[7][6] = 'A';
	tahta[0][7] = 'k'; tahta[7][7] = 'K';
	
	printf("Oyuncu bir kucuk karakterler senindir\n");
	printf("Oyuncu iki buyuk karakterler senindir\n");
	printf("Oyun basliyor...\n\n");
	//Oyun başlıyor
	while(1)
	{
		// Döngü her başladığında q = 1 olarak atanır ve alt satırlardan fonksiyonlara geçiş yapılarak o fonksiyonlarda istenmeyen durumlarda q değeri 0 yapılıp yine ana fonksiyon içinde bulunan bir if koşulunda q değeri kontrol edilip istenilen çıktı sağlanır(1586. satıra bak)  
		q = 1;
		//Satraç tahtasını yazdırma
	for(i=0; i<8; i++)
	printf("%4d", i+1);
	printf("\n  ");
	for(i=0; i<31; i++)
	printf("-");
	printf("\n");
	
	for(i=0; i<8; i++)
	{
		for(j=0; j<8; j++)
		{
			printf("%4c", tahta[i][j]);
		}
		printf(" |%d\n                                 |\n", i+1);
	}
		n++;
		printf("Oyuncu%d sende\n", n);
		printf("Oynatacagin tasi sec\n");
		scanf("%d%d", &x, &y); // x ve y oynatılacak taşın konumlarını tutuyor
		
		//Tahtadaki boş bir karakteri seçtiğinde verilecek hata
		if(tahta[y-1][x-1] == '#')
		{
			system("cls");
			printf("Hatali secim! Tekrar sec\n\n");
			n--;
			continue;
		}
		//Tahtada bulunmayan bir konum seçilirse veilecek hata
		if((x<1 || x>8) || (y<1 || y>8))
		{
			system("cls");
			printf("Hatali secim\n\n");
			n--;
			continue;
		}
		//Rakip takımın taşları seçilirse verilecek hata
		if(n == 1)
		{
			if(tahta[y-1][x-1] == 'P' || tahta[y-1][x-1] == 'K' || tahta[y-1][x-1] == 'A' || tahta[y-1][x-1] == 'F' || tahta[y-1][x-1] == 'V' || tahta[y-1][x-1] == 'S')
			{
				system("cls");
				printf("Hatali secim\n\n");
				n = 0;
				continue;
			}
		}
		else
		{
			if(tahta[y-1][x-1] == 'p' || tahta[y-1][x-1] == 'k' || tahta[y-1][x-1] == 'a' || tahta[y-1][x-1] == 'f' || tahta[y-1][x-1] == 'v' || tahta[y-1][x-1] == 's')
			{
				system("cls");
				printf("Hatali secim\n\n");
				n = 1;
				continue;
			}
		}		
		printf("Nereye oynayacaksin\n");
		scanf("%d%d", &x2, &y2); //  x2 ve y2 oynatılacak yerin konumlarını tutuyor
		
		// Oynanan konumda kendi taşları varsa alınacak hata(2.oyuncu için)
		if(n == 2)
		{
			if(tahta[y2-1][x2-1] == 'P' || tahta[y2-1][x2-1] == 'K' || tahta[y2-1][x2-1] == 'A' || tahta[y2-1][x2-1] == 'F' || tahta[y2-1][x2-1] == 'V' || tahta[y2-1][x2-1] == 'S')
			{
				system("cls");
				printf("Hatali secim\n\n");
				n = 1;
				continue;
			}
		}
		// Oynanan konumda kendi taşları varsa alınacak hata(1.oyuncu için)		
		else
		{
			if(tahta[y2-1][x2-1] == 'p' || tahta[y2-1][x2-1] == 'k' || tahta[y2-1][x2-1] == 'a' || tahta[y2-1][x2-1] == 'f' || tahta[y2-1][x2-1] == 'v' || tahta[y2-1][x2-1] == 's')
			{
				system("cls");
				printf("Hatali secim\n");
				n = 0;
				continue;
			}
		}
		//Sıra 1.oyuncudayken sadece onun fonksiyonlarını kontrol eder
		if(n == 1)
		{
			if(tahta[y-1][x-1] == 'p')
			p(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'k')
			k(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'a')
			a(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'f')
			f(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'v')
			v(tahta, &x, &y, &x2, &y2, &q);	
			if(tahta[y-1][x-1] == 's')
			s(tahta, &x, &y, &x2, &y2, &q);
		}
		//Sıra 2.oyuncudayken sadece onun fonksiyonlarını kontrol eder
		else
		{
			if(tahta[y-1][x-1] == 'P')
			P(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'K')
			K(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'A')
			A(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'F')
			F(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'V')
			V(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'S')
			S(tahta, &x, &y, &x2, &y2, &q);
		}
		//Fonksiyonların içlerinde hatalı bir seçim yapıldığında q = 0 olarak döndürülüp ana fonksiyonda bu koşul içinde hata mesajı verdirilir
		if(q == 0)
		{
			system("cls");
			printf("Hatali secim!\n");	
			n--;		
			continue;			
		}
		//Seçilen taş istenilen yere oynatılıyor
		tahta[y2-1][x2-1] = tahta[y-1][x-1];
		tahta[y-1][x-1] = '#';
		
		system("cls");
			
		if(n == 2)
			n=0;
	}
	 
	return 0;
}