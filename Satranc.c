#include <stdio.h>
#include <stdlib.h>

// 1. oyuncu i�in
int gecerkenAl = 0;
// 2. oyuncu i�in
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
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata(ta��n se�ildi�i konum)
		if((*x<1 || *x>8) || (*y<1 || *y>8))
		{
			*q = 1;
			break;
		}
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata(ta��n gidece�i konum)
		if((*x2<1 || *x2>8) || (*y2<1 || *y2>8))
		{
			*q = 1;
			break;
		}
		//Tahtadaki bo� bir karakteri se�ti�inde verilecek hata
		else if(tahta[*y-1][*x-1] == '#')
		{
			*q = 1;
			break;
		}		
		//Rakip tak�m�n ta�lar� se�ilirse verilecek hata		
		else if(tahta[*y-1][*x-1] == 'P' || tahta[*y-1][*x-1] == 'K' || tahta[*y-1][*x-1] == 'A' || tahta[*y-1][*x-1] == 'F' || tahta[*y-1][*x-1] == 'V' || tahta[*y-1][*x-1] == 'S')
		{
			*q = 1;
			break;
		}			
		if(*y2-*y == 2)
		{
			//ilk defa oynanmayan piyon 1 birimden fazla oynanamaz
			if(*y != 2)
			{
				*q = 1;
				break;
			}	
			// ilk defa oynanacak piyonun iki birim ileriye gidebilme �artlar�
			else
			{
				// Ayn� s�tunda iki birim ileri oynayabilir
				if(*x2-*x == 0)
				{
					// Piyonun �n� bo�sa d�ng�den ��k�l�r oyun devam eder
					if(tahta[*y2-1][*x2-1] == '#')
					{
						gecerkenAl = 1; // bu komut rakip tak�m�n piyon s�r���nde kullan�l�cak  gecerkenAl ==1 olmas� piyonun 2 defa s�r�lm�� olmas�n� g�sterir
						GecerkenAl = 0; // Her while dan ��k���m�zda rakibin GecerkenAl � 0 olmal�
						*q = 0;
						break; 
					}
					// Piyonun �n�nde herhangi bir ta� varsa hata al�n�r
					else
					{
						*q = 1;
						break;
					}
				}
				// �ki birim oynanan piyon hi�bir zaman ba�ka s�tuna ge�emz
				else
				{
					*q = 1;
					break;
				}
			}
		}				
		//Piyonlar geriye oynayamaz ve ayn� sat�rda hareket edemez
		else if(*y2-*y <= 0)
		{		
			*q = 1;
			break;
		}				
		//2 birimden fazla ilerlenildi�inde verilecek hata
		else if(*y2-*y > 2)
		{
			*q = 1;
			break;
		}		
		//Piyonlar genellikle 1 birim ileri oynat�labilir(�n�nde herhangi bir ta� olmad��� s�rece) dolay�s�yla art�k d�ng�den ��kabiliriz
		else if(*y2-*y == 1)
		{			
			// Piyonlar 1 birim �apraz hareket ettrilirse
			if(*x2-*x == 1 || *x2-*x == -1)
			{
				// Piyonlar�n �apraz hareket edebilmesi i�in gidece�i karede rakip tak�m�n ta�lar� bulunmal�
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V')
				{
					GecerkenAl = 0;
					*q = 0;
					break;
				}
				// Ge�erken alma	
				else if(GecerkenAl == 1)
				{
					if(tahta[*y-1][*x-1+1] == 'P' && *x2-*x == 1 && tahta[*y2-1-1][*x2-1] == 'P')
						tahta[*y-1][*x-1+1] = '#';
					else if(tahta[*y-1][*x-1-1] == 'P' && *x2-*x == -1 && tahta[*y2-1-1][*x2-1] == 'P')
						tahta[*y-1][*x-1-1] = '#';
					else
					{
						*q = 1;
						break;
					}
					GecerkenAl = 0;
					*q = 0;
					break;
				}
				// Aksi halde hatal� oynama yap�lm�� olur	
				else
				{
					*q = 1;
					break;
				}	 
			}
			// Piyonlar 1 birim ileri oynat�l�rsa 
			else
			{				
				// Piyonun �n� bo�sa d�ng�den ��k�l�r oyun devam eder
				if(tahta[*y2-1][*x2-1] == '#')
				{
					GecerkenAl = 0;
					*q = 0;
					break;
				}
				// Piyonun �n�nde herhangi bir ta� varsa hata al�n�r
				else
				{
					*q = 1;
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
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata(ta��n se�ildi�i konum)
		if((*x<1 || *x>8) || (*y<1 || *y>8))
		{
			*q = 1;
			break;
		}
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata(ta��n gidece�i konum)
		if((*x2<1 || *x2>8) || (*y2<1 || *y2>8))
		{
			*q = 1;
			break;
		}
		//Tahtadaki bo� bir karakteri se�ti�inde verilecek hata
		else if(tahta[*y-1][*x-1] == '#')
		{
			*q = 1;
			break;
		}		
		//Rakip tak�m�n ta�lar� se�ilirse verilecek hata		
		else if(tahta[*y-1][*x-1] == 'P' || tahta[*y-1][*x-1] == 'K' || tahta[*y-1][*x-1] == 'A' || tahta[*y-1][*x-1] == 'F' || tahta[*y-1][*x-1] == 'V' || tahta[*y-1][*x-1] == 'S')
		{
			*q = 1;
			break;
		}
		// Kale ayn� s�tunda istenildi�i kadar ileri gidebilir
		if(*x2 == *x && *y2 != *y)
		{	
			// Kale ileri oynarsa
			if(*y2>*y)
			{	
				for(i=*y-1+1; i<*y2-1; i++)
				{	
					//  Kalenin �n�nde ta� versa *q = 1 atamas� yap�l�r (ana fonksiyonda q = 1 ise hata al�nacakt�r)
					if(tahta[i][*x-1] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while d�ng�s�nden ve dolay�s�yla 'k' fonksiyonundan ��k�l�r
				if(*q == 1)
					break;
				// Kalenin �n� bo�sa ve gitmek istedi�i yer bo� veya rakibin herhangi bir ta�� varsa  q = 0 (ana fonksiyonda hata al�nmayaca�� anlam�na gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin �n� bo�sa ve gitmek istedi�i konumda kendi ta�lar�ndan herhangi biri varsa hatal� se�im olacakt�r
				else
				{
					*q = 1;
					break;
				}
			}
			// Kale geri oynarsa
			else if(*y2<*y)
			{
				for(i=*y2-1-1; i>*y-1; i--)
				{
					//  Kalenin �n�nde ta� versa *q = 1 atamas� yap�l�r (ana fonksiyonda q = 1 ise hata al�nacakt�r)
					if(tahta[i][*x-1] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while d�ng�s�nden ve dolay�s�yla 'k' fonksiyonundan ��k�l�r
				if(*q == 1)
					break;
				// Kalenin �n� bo�sa ve gitmek istedi�i yer bo� veya rakibin herhangi bir ta�� varsa  q = 0 (ana fonksiyonda hata al�nmayaca�� anlam�na gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin �n� bo�sa ve gitmek istedi�i konumda kendi ta�lar�ndan herhangi biri varsa hatal� se�im olacakt�r
				else
				{
					*q = 1;
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
					//  Kalenin �n�nde ta� versa *q = 1 atamas� yap�l�r (ana fonksiyonda q = 1 ise hata al�nacakt�r)
					if(tahta[*y-1][i] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while d�ng�s�nden ve dolay�s�yla 'k' fonksiyonundan ��k�l�r
				if(*q == 1)
					break;
				// Kalenin �n� bo�sa ve gitmek istedi�i yer bo� veya rakibin herhangi bir ta�� varsa  q = 0 (ana fonksiyonda hata al�nmayaca�� anlam�na gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin �n� bo�sa ve gitmek istedi�i konumda kendi ta�lar�ndan herhangi biri varsa hatal� se�im olacakt�r
				else
				{
					*q = 1;
					break;
				}
			}
			// Kale sa�a oynarsa
			else if(*x2<*x)
			{
				for(i=*x2-1-1; i>*x-1; i--)
				{
					//  Kalenin �n�nde ta� versa *q = 1 atamas� yap�l�r (ana fonksiyonda q = 1 ise hata al�nacakt�r)
					if(tahta[*y-1][i] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while d�ng�s�nden ve dolay�s�yla 'k' fonksiyonundan ��k�l�r
				if(*q == 1)
					break;
				// Kalenin �n� bo�sa ve gitmek istedi�i yer bo� veya rakibin herhangi bir ta�� varsa  q = 0 (ana fonksiyonda hata al�nmayaca�� anlam�na gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin �n� bo�sa ve gitmek istedi�i konumda kendi ta�lar�ndan herhangi biri varsa hatal� se�im olacakt�r
				else
				{
					*q = 1;
					break;
				}
			}				
		}
	}
}
// Oyuncu2 piyonu
void P(char tahta[][8], int *x, int *y, int *x2, int *y2, int *q)
{	
	while(1)
	{		
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata(ta��n se�ildi�i konum)
		if((*x<1 || *x>8) || (*y<1 || *y>8))
		{
			*q = 1;
			break;
		}
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata(ta��n gidece�i konum)
		if((*x2<1 || *x2>8) || (*y2<1 || *y2>8))
		{
			*q = 1;
			break;
		}
		//Tahtadaki bo� bir karakteri se�ti�inde verilecek hata
		if(tahta[*y-1][*x-1] == '#')
		{
			*q = 1;
			break;
		}
		//Rakip tak�m�n ta�lar� se�ilirse verilecek hata
		else if(tahta[*y-1][*x-1] == 'p' || tahta[*y-1][*x-1] == 'k' || tahta[*y-1][*x-1] == 'a' || tahta[*y-1][*x-1] == 'f' || tahta[*y-1][*x-1] == 'v' || tahta[*y-1][*x-1] == 's')
		{
			*q = 1;
			break;
		}
		// Piyonlar 2 birim ileri oynat�l�rsa
		if(*y-*y2 == 2)
		{
			//ilk defa oynanmayan piyon 1 birimden fazla oynanamaz
			if(*y != 7)
			{
				*q = 1;
				break;
			}	
			// ilk defa oynanacak piyonun iki birim ileriye gidebilme �artlar�
			else
			{
				// Ayn� s�tunda iki birim ileri oynayabilir
				if(*x-*x2 == 0)
				{
					// Piyonun �n� bo�sa d�ng�den ��k�l�r oyun devam eder
					if(tahta[*y2-1][*x2-1] == '#')
					{
						GecerkenAl = 1; // bu komut rakip tak�m�n piyon s�r���nde kullan�l�cak. GecerkenAl ==1 olmas� piyonun 2 defa s�r�lm�� olmas�n� g�sterir
						gecerkenAl = 0; // Her while dan ��k���m�zda rakibin gecerkenAl � 0 olmal�
						*q = 0;
						break; 
					}
					// Piyonun �n�nde herhangi bir ta� varsa hata al�n�r
					else
					{
						*q = 1;
						break;
					}
				}
				// �ki birim oynanan piyon hi�bir zaman ba�ka s�tuna ge�emz
				else
				{
					*q = 1;
					break;
				}
			}
		}		
		//Piyonlar geriye oynayamaz ve ayn� sat�rda hareket edemez
		else if(*y-*y2 <= 0)
		{		
			*q = 1;
			break;
		}				
		//2 birimden fazla ilerlenildi�inde verilecek hata
		else if(*y-*y2 > 2)
		{
			*q = 1;
			break;
		}			
		//Piyonlar genellikle 1 birim ileri oynat�labilir(�n�nde herhangi bir ta� olmad��� s�rece) dolay�s�yla art�k d�ng�den ��kabiliriz
		else if(*y-*y2 == 1)
		{			
			// Piyonlar 1 birim �apraz hareket ettrilirse
			if(*x-*x2 == 1 || *x-*x2 == -1)
			{
				// Piyonlar�n �apraz hareket edebilmesi i�in gidece�i karede rakip tak�m�n ta�lar� bulunmal�
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v')
				{
					gecerkenAl = 0;
					*q = 0; 
					break;
				}
				// Ge�erken alma	
				else if(gecerkenAl == 1)
				{
					if(tahta[*y-1][*x-1+1] == 'p' && *x2-*x == 1 && tahta[*y2-1+1][*x2-1] == 'p')
						tahta[*y-1][*x-1+1] = '#';
					else if(tahta[*y-1][*x-1-1] == 'p' && *x2-*x == -1 && tahta[*y2-1+1][*x2-1] == 'p')
						tahta[*y-1][*x-1-1] = '#';
					else
					{
						*q = 1;
						break;
					}
					GecerkenAl = 0;
					*q = 0;
					break;
				}	
				// Aksi halde hatal� oynama yap�lm�� olur	
				else
				{
					*q = 1;
					break;
				}	 
			}
			// Piyonlar 1 birim ileri oynat�l�rsa 
			else
			{
				// Piyonun �n� bo�sa d�ng�den ��k�l�r oyun devam eder
				if(tahta[*y2-1][*x2-1] == '#')
				{
					gecerkenAl= 0; 
					*q = 0;
					break;
				}
				// Piyonun �n�nde herhangi bir ta� varsa hata al�n�r
				else
				{
					*q = 1;
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
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata(ta��n se�ildi�i konum)
		if((*x<1 || *x>8) || (*y<1 || *y>8))
		{
			*q = 1;
			break;
		}
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata(ta��n gidece�i konum)
		if((*x2<1 || *x2>8) || (*y2<1 || *y2>8))
		{
			*q = 1;
			break;
		}
		//Tahtadaki bo� bir karakteri se�ti�inde verilecek hata
		else if(tahta[*y-1][*x-1] == '#')
		{
			*q = 1;
			break;
		}		
		//Rakip tak�m�n ta�lar� se�ilirse verilecek hata		
		else if(tahta[*y-1][*x-1] == 'p' || tahta[*y-1][*x-1] == 'k' || tahta[*y-1][*x-1] == 'a' || tahta[*y-1][*x-1] == 'f' || tahta[*y-1][*x-1] == 'v' || tahta[*y-1][*x-1] == 's')
		{
			*q = 1;
			break;
		}
		// Kale ayn� s�tunda istenildi�i kadar ileri gidebilir
		if(*x2 == *x && *y2 != *y)
		{
			// Kale ileri oynarsa
			if(*y>*y2)
			{
				for(i=*y-1-1; i>*y2-1; i--)
				{	
					//  Kalenin �n�nde ta� versa *q = 1 atamas� yap�l�r (ana fonksiyonda q = 1 ise hata al�nacakt�r)
					if(tahta[i][*x-1] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while d�ng�s�nden ve dolay�s�yla 'K' fonksiyonundan ��k�l�r
				if(*q == 1)
					break;
				// Kalenin �n� bo�sa ve gitmek istedi�i yer bo� veya rakibin herhangi bir ta�� varsa  q = 0 (ana fonksiyonda hata al�nmayaca�� anlam�na gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin �n� bo�sa ve gitmek istedi�i konumda kendi ta�lar�ndan herhangi biri varsa hatal� se�im olacakt�r
				else
				{
					*q = 1;
					break;
				}
			}
			// Kale geri oynarsa
			else if(*y<*y2)
			{
				for(i=*y-1+1; i<*y2-1; i++)
				{
					//  Kalenin �n�nde ta� versa *q = 1 atamas� yap�l�r (ana fonksiyonda q = 1 ise hata al�nacakt�r)
					if(tahta[i][*x-1] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while d�ng�s�nden ve dolay�s�yla 'k' fonksiyonundan ��k�l�r
				if(*q == 1)
					break;
				// Kalenin �n� bo�sa ve gitmek istedi�i yer bo� veya rakibin herhangi bir ta�� varsa  q = 0 (ana fonksiyonda hata al�nmayaca�� anlam�na gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin �n� bo�sa ve gitmek istedi�i konumda kendi ta�lar�ndan herhangi biri varsa hatal� se�im olacakt�r
				else
				{
					*q = 1;
					break;
				}
			}				
		}
		else if(*y2 == *y && *x2 != *x)
		{	
			// Kale sa�a oynarsa
			if(*x2>*x)
			{	
				for(i=*x-1+1; i<*x2-1; i++)
				{	
					//  Kalenin �n�nde ta� versa *q = 1 atamas� yap�l�r (ana fonksiyonda q = 1 ise hata al�nacakt�r)
					if(tahta[*y-1][i] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while d�ng�s�nden ve dolay�s�yla 'k' fonksiyonundan ��k�l�r
				if(*q == 1)
					break;
				// Kalenin �n� bo�sa ve gitmek istedi�i yer bo� veya rakibin herhangi bir ta�� varsa  q = 0 (ana fonksiyonda hata al�nmayaca�� anlam�na gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin �n� bo�sa ve gitmek istedi�i konumda kendi ta�lar�ndan herhangi biri varsa hatal� se�im olacakt�r
				else
				{
					*q = 1;
					break;
				}
			}
			// Kale sola oynarsa
			else if(*x2<*x)
			{
				for(i=*x2-1-1; i>*x-1; i--)
				{
					//  Kalenin �n�nde ta� versa *q = 1 atamas� yap�l�r (ana fonksiyonda q = 1 ise hata al�nacakt�r)
					if(tahta[*y-1][i] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while d�ng�s�nden ve dolay�s�yla 'k' fonksiyonundan ��k�l�r
				if(*q == 1)
					break;
				// Kalenin �n� bo�sa ve gitmek istedi�i yer bo� veya rakibin herhangi bir ta�� varsa  q = 0 (ana fonksiyonda hata al�nmayaca�� anlam�na gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin �n� bo�sa ve gitmek istedi�i konumda kendi ta�lar�ndan herhangi biri varsa hatal� se�im olacakt�r
				else
				{
					*q = 1;
					break;
				}
			}				
		}
	}
}
int main()
{
	char tahta[8][8], gecici;
	int i, j, n=0, x, y, x2, y2;
	int q; // foksiyona gidildikten sonra hatali se�im yap�l�rsa q de�eri if ko�ulu olarak kullan�lacak 
	
	//Satranc tahtas�na ta�lar� yerle�tirme 
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
	//Oyun ba�l�yor
	while(1)
	{
		q = 0;
		//Satra� tahtas�n� yazd�rma
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
		scanf("%d%d", &x, &y); // x ve y oynat�lacak ta��n konumlar�n� tutuyor
		
		//Tahtadaki bo� bir karakteri se�ti�inde verilecek hata
		if(tahta[y-1][x-1] == '#')
		{
			system("cls");
			printf("Hatali secim! Tekrar sec\n\n");
			n--;
			continue;
		}
		//Tahtada bulunmayan bir konum se�ilirse veilecek hata
		if((x<1 || x>8) || (y<1 || y>8))
		{
			printf("Hatali secim\n");
			n--;
			continue;
		}
		//Rakip tak�m�n ta�lar� se�ilirse verilecek hata
		if(n == 1)
		{
			if(tahta[y-1][x-1] == 'P' || tahta[y-1][x-1] == 'K' || tahta[y-1][x-1] == 'A' || tahta[y-1][x-1] == 'F' || tahta[y-1][x-1] == 'V' || tahta[y-1][x-1] == 'S')
			{
				system("cls");
				printf("Hatali secim\n");
				n = 0;
				continue;
			}
		}
		else
		{
			if(tahta[y-1][x-1] == 'p' || tahta[y-1][x-1] == 'k' || tahta[y-1][x-1] == 'a' || tahta[y-1][x-1] == 'f' || tahta[y-1][x-1] == 'v' || tahta[y-1][x-1] == 's')
			{
				system("cls");
				printf("Hatali secim\n");
				n = 1;
				continue;
			}
		}		
		printf("Nereye oynayacaksin\n");
		scanf("%d%d", &x2, &y2); //  x2 ve y2 oynat�lacak yerin konumlar�n� tutuyor
		
		//S�ra 1.oyuncudayken sadece onun fonksiyonlar�n� kontrol eder
		if(n == 1)
		{
			if(tahta[y-1][x-1] == 'p')
			p(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'k')
			k(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'f')
			f(tahta, &x, &y, &x2, &y2, &q);
		}
		//S�ra 2.oyuncudayken sadece onun fonksiyonlar�n� kontrol eder
		else
		{
			if(tahta[y-1][x-1] == 'P')
			P(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'K')
			K(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'F')
			F(tahta, &x, &y, &x2, &y2, &q);
		}
	//	printf("%d\n", q);
		if(q == 1)
		{
			system("cls");
			printf("Hatali secim!\n");	
			n--;		
			continue;			
		}
		//Se�ilen ta� istenilen yere oynat�l�yor
		tahta[y2-1][x2-1] = tahta[y-1][x-1];
		tahta[y-1][x-1] = '#';
		
		system("cls");
			
		if(n == 2)
			n=0;
	}
	 
	return 0;
}
