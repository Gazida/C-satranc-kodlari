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
		//Tahtada bulunmayan bir konum seçilirse veilecek hata(taþýn seçildiði konum)
		if((*x<1 || *x>8) || (*y<1 || *y>8))
		{
			*q = 1;
			break;
		}
		//Tahtada bulunmayan bir konum seçilirse veilecek hata(taþýn gideceði konum)
		if((*x2<1 || *x2>8) || (*y2<1 || *y2>8))
		{
			*q = 1;
			break;
		}
		//Tahtadaki boþ bir karakteri seçtiðinde verilecek hata
		else if(tahta[*y-1][*x-1] == '#')
		{
			*q = 1;
			break;
		}		
		//Rakip takýmýn taþlarý seçilirse verilecek hata		
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
			// ilk defa oynanacak piyonun iki birim ileriye gidebilme þartlarý
			else
			{
				// Ayný sütunda iki birim ileri oynayabilir
				if(*x2-*x == 0)
				{
					// Piyonun önü boþsa döngüden çýkýlýr oyun devam eder
					if(tahta[*y2-1][*x2-1] == '#')
					{
						gecerkenAl = 1; // bu komut rakip takýmýn piyon sürüþünde kullanýlýcak  gecerkenAl ==1 olmasý piyonun 2 defa sürülmüþ olmasýný gösterir
						GecerkenAl = 0; // Her while dan çýkýþýmýzda rakibin GecerkenAl ý 0 olmalý
						*q = 0;
						break; 
					}
					// Piyonun önünde herhangi bir taþ varsa hata alýnýr
					else
					{
						*q = 1;
						break;
					}
				}
				// Ýki birim oynanan piyon hiçbir zaman baþka sütuna geçemz
				else
				{
					*q = 1;
					break;
				}
			}
		}				
		//Piyonlar geriye oynayamaz ve ayný satýrda hareket edemez
		else if(*y2-*y <= 0)
		{		
			*q = 1;
			break;
		}				
		//2 birimden fazla ilerlenildiðinde verilecek hata
		else if(*y2-*y > 2)
		{
			*q = 1;
			break;
		}		
		//Piyonlar genellikle 1 birim ileri oynatýlabilir(Önünde herhangi bir taþ olmadýðý sürece) dolayýsýyla artýk döngüden çýkabiliriz
		else if(*y2-*y == 1)
		{			
			// Piyonlar 1 birim çapraz hareket ettrilirse
			if(*x2-*x == 1 || *x2-*x == -1)
			{
				// Piyonlarýn çapraz hareket edebilmesi için gideceði karede rakip takýmýn taþlarý bulunmalý
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V')
				{
					GecerkenAl = 0;
					*q = 0;
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
						*q = 1;
						break;
					}
					GecerkenAl = 0;
					*q = 0;
					break;
				}
				// Aksi halde hatalý oynama yapýlmýþ olur	
				else
				{
					*q = 1;
					break;
				}	 
			}
			// Piyonlar 1 birim ileri oynatýlýrsa 
			else
			{				
				// Piyonun önü boþsa döngüden çýkýlýr oyun devam eder
				if(tahta[*y2-1][*x2-1] == '#')
				{
					GecerkenAl = 0;
					*q = 0;
					break;
				}
				// Piyonun önünde herhangi bir taþ varsa hata alýnýr
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
		//Tahtada bulunmayan bir konum seçilirse veilecek hata(taþýn seçildiði konum)
		if((*x<1 || *x>8) || (*y<1 || *y>8))
		{
			*q = 1;
			break;
		}
		//Tahtada bulunmayan bir konum seçilirse veilecek hata(taþýn gideceði konum)
		if((*x2<1 || *x2>8) || (*y2<1 || *y2>8))
		{
			*q = 1;
			break;
		}
		//Tahtadaki boþ bir karakteri seçtiðinde verilecek hata
		else if(tahta[*y-1][*x-1] == '#')
		{
			*q = 1;
			break;
		}		
		//Rakip takýmýn taþlarý seçilirse verilecek hata		
		else if(tahta[*y-1][*x-1] == 'P' || tahta[*y-1][*x-1] == 'K' || tahta[*y-1][*x-1] == 'A' || tahta[*y-1][*x-1] == 'F' || tahta[*y-1][*x-1] == 'V' || tahta[*y-1][*x-1] == 'S')
		{
			*q = 1;
			break;
		}
		// Kale ayný sütunda istenildiði kadar ileri gidebilir
		if(*x2 == *x && *y2 != *y)
		{	
			// Kale ileri oynarsa
			if(*y2>*y)
			{	
				for(i=*y-1+1; i<*y2-1; i++)
				{	
					//  Kalenin önünde taþ versa *q = 1 atamasý yapýlýr (ana fonksiyonda q = 1 ise hata alýnacaktýr)
					if(tahta[i][*x-1] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while döngüsünden ve dolayýsýyla 'k' fonksiyonundan çýkýlýr
				if(*q == 1)
					break;
				// Kalenin önü boþsa ve gitmek istediði yer boþ veya rakibin herhangi bir taþý varsa  q = 0 (ana fonksiyonda hata alýnmayacaðý anlamýna gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin önü boþsa ve gitmek istediði konumda kendi taþlarýndan herhangi biri varsa hatalý seçim olacaktýr
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
					//  Kalenin önünde taþ versa *q = 1 atamasý yapýlýr (ana fonksiyonda q = 1 ise hata alýnacaktýr)
					if(tahta[i][*x-1] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while döngüsünden ve dolayýsýyla 'k' fonksiyonundan çýkýlýr
				if(*q == 1)
					break;
				// Kalenin önü boþsa ve gitmek istediði yer boþ veya rakibin herhangi bir taþý varsa  q = 0 (ana fonksiyonda hata alýnmayacaðý anlamýna gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin önü boþsa ve gitmek istediði konumda kendi taþlarýndan herhangi biri varsa hatalý seçim olacaktýr
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
					//  Kalenin önünde taþ versa *q = 1 atamasý yapýlýr (ana fonksiyonda q = 1 ise hata alýnacaktýr)
					if(tahta[*y-1][i] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while döngüsünden ve dolayýsýyla 'k' fonksiyonundan çýkýlýr
				if(*q == 1)
					break;
				// Kalenin önü boþsa ve gitmek istediði yer boþ veya rakibin herhangi bir taþý varsa  q = 0 (ana fonksiyonda hata alýnmayacaðý anlamýna gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin önü boþsa ve gitmek istediði konumda kendi taþlarýndan herhangi biri varsa hatalý seçim olacaktýr
				else
				{
					*q = 1;
					break;
				}
			}
			// Kale saða oynarsa
			else if(*x2<*x)
			{
				for(i=*x2-1-1; i>*x-1; i--)
				{
					//  Kalenin önünde taþ versa *q = 1 atamasý yapýlýr (ana fonksiyonda q = 1 ise hata alýnacaktýr)
					if(tahta[*y-1][i] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while döngüsünden ve dolayýsýyla 'k' fonksiyonundan çýkýlýr
				if(*q == 1)
					break;
				// Kalenin önü boþsa ve gitmek istediði yer boþ veya rakibin herhangi bir taþý varsa  q = 0 (ana fonksiyonda hata alýnmayacaðý anlamýna gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'P' || tahta[*y2-1][*x2-1] == 'K' || tahta[*y2-1][*x2-1] == 'A' || tahta[*y2-1][*x2-1] == 'F' || tahta[*y2-1][*x2-1] == 'V' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin önü boþsa ve gitmek istediði konumda kendi taþlarýndan herhangi biri varsa hatalý seçim olacaktýr
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
		//Tahtada bulunmayan bir konum seçilirse veilecek hata(taþýn seçildiði konum)
		if((*x<1 || *x>8) || (*y<1 || *y>8))
		{
			*q = 1;
			break;
		}
		//Tahtada bulunmayan bir konum seçilirse veilecek hata(taþýn gideceði konum)
		if((*x2<1 || *x2>8) || (*y2<1 || *y2>8))
		{
			*q = 1;
			break;
		}
		//Tahtadaki boþ bir karakteri seçtiðinde verilecek hata
		if(tahta[*y-1][*x-1] == '#')
		{
			*q = 1;
			break;
		}
		//Rakip takýmýn taþlarý seçilirse verilecek hata
		else if(tahta[*y-1][*x-1] == 'p' || tahta[*y-1][*x-1] == 'k' || tahta[*y-1][*x-1] == 'a' || tahta[*y-1][*x-1] == 'f' || tahta[*y-1][*x-1] == 'v' || tahta[*y-1][*x-1] == 's')
		{
			*q = 1;
			break;
		}
		// Piyonlar 2 birim ileri oynatýlýrsa
		if(*y-*y2 == 2)
		{
			//ilk defa oynanmayan piyon 1 birimden fazla oynanamaz
			if(*y != 7)
			{
				*q = 1;
				break;
			}	
			// ilk defa oynanacak piyonun iki birim ileriye gidebilme þartlarý
			else
			{
				// Ayný sütunda iki birim ileri oynayabilir
				if(*x-*x2 == 0)
				{
					// Piyonun önü boþsa döngüden çýkýlýr oyun devam eder
					if(tahta[*y2-1][*x2-1] == '#')
					{
						GecerkenAl = 1; // bu komut rakip takýmýn piyon sürüþünde kullanýlýcak. GecerkenAl ==1 olmasý piyonun 2 defa sürülmüþ olmasýný gösterir
						gecerkenAl = 0; // Her while dan çýkýþýmýzda rakibin gecerkenAl ý 0 olmalý
						*q = 0;
						break; 
					}
					// Piyonun önünde herhangi bir taþ varsa hata alýnýr
					else
					{
						*q = 1;
						break;
					}
				}
				// Ýki birim oynanan piyon hiçbir zaman baþka sütuna geçemz
				else
				{
					*q = 1;
					break;
				}
			}
		}		
		//Piyonlar geriye oynayamaz ve ayný satýrda hareket edemez
		else if(*y-*y2 <= 0)
		{		
			*q = 1;
			break;
		}				
		//2 birimden fazla ilerlenildiðinde verilecek hata
		else if(*y-*y2 > 2)
		{
			*q = 1;
			break;
		}			
		//Piyonlar genellikle 1 birim ileri oynatýlabilir(Önünde herhangi bir taþ olmadýðý sürece) dolayýsýyla artýk döngüden çýkabiliriz
		else if(*y-*y2 == 1)
		{			
			// Piyonlar 1 birim çapraz hareket ettrilirse
			if(*x-*x2 == 1 || *x-*x2 == -1)
			{
				// Piyonlarýn çapraz hareket edebilmesi için gideceði karede rakip takýmýn taþlarý bulunmalý
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v')
				{
					gecerkenAl = 0;
					*q = 0; 
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
						*q = 1;
						break;
					}
					GecerkenAl = 0;
					*q = 0;
					break;
				}	
				// Aksi halde hatalý oynama yapýlmýþ olur	
				else
				{
					*q = 1;
					break;
				}	 
			}
			// Piyonlar 1 birim ileri oynatýlýrsa 
			else
			{
				// Piyonun önü boþsa döngüden çýkýlýr oyun devam eder
				if(tahta[*y2-1][*x2-1] == '#')
				{
					gecerkenAl= 0; 
					*q = 0;
					break;
				}
				// Piyonun önünde herhangi bir taþ varsa hata alýnýr
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
		//Tahtada bulunmayan bir konum seçilirse veilecek hata(taþýn seçildiði konum)
		if((*x<1 || *x>8) || (*y<1 || *y>8))
		{
			*q = 1;
			break;
		}
		//Tahtada bulunmayan bir konum seçilirse veilecek hata(taþýn gideceði konum)
		if((*x2<1 || *x2>8) || (*y2<1 || *y2>8))
		{
			*q = 1;
			break;
		}
		//Tahtadaki boþ bir karakteri seçtiðinde verilecek hata
		else if(tahta[*y-1][*x-1] == '#')
		{
			*q = 1;
			break;
		}		
		//Rakip takýmýn taþlarý seçilirse verilecek hata		
		else if(tahta[*y-1][*x-1] == 'p' || tahta[*y-1][*x-1] == 'k' || tahta[*y-1][*x-1] == 'a' || tahta[*y-1][*x-1] == 'f' || tahta[*y-1][*x-1] == 'v' || tahta[*y-1][*x-1] == 's')
		{
			*q = 1;
			break;
		}
		// Kale ayný sütunda istenildiði kadar ileri gidebilir
		if(*x2 == *x && *y2 != *y)
		{
			// Kale ileri oynarsa
			if(*y>*y2)
			{
				for(i=*y-1-1; i>*y2-1; i--)
				{	
					//  Kalenin önünde taþ versa *q = 1 atamasý yapýlýr (ana fonksiyonda q = 1 ise hata alýnacaktýr)
					if(tahta[i][*x-1] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while döngüsünden ve dolayýsýyla 'K' fonksiyonundan çýkýlýr
				if(*q == 1)
					break;
				// Kalenin önü boþsa ve gitmek istediði yer boþ veya rakibin herhangi bir taþý varsa  q = 0 (ana fonksiyonda hata alýnmayacaðý anlamýna gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin önü boþsa ve gitmek istediði konumda kendi taþlarýndan herhangi biri varsa hatalý seçim olacaktýr
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
					//  Kalenin önünde taþ versa *q = 1 atamasý yapýlýr (ana fonksiyonda q = 1 ise hata alýnacaktýr)
					if(tahta[i][*x-1] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while döngüsünden ve dolayýsýyla 'k' fonksiyonundan çýkýlýr
				if(*q == 1)
					break;
				// Kalenin önü boþsa ve gitmek istediði yer boþ veya rakibin herhangi bir taþý varsa  q = 0 (ana fonksiyonda hata alýnmayacaðý anlamýna gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin önü boþsa ve gitmek istediði konumda kendi taþlarýndan herhangi biri varsa hatalý seçim olacaktýr
				else
				{
					*q = 1;
					break;
				}
			}				
		}
		else if(*y2 == *y && *x2 != *x)
		{	
			// Kale saða oynarsa
			if(*x2>*x)
			{	
				for(i=*x-1+1; i<*x2-1; i++)
				{	
					//  Kalenin önünde taþ versa *q = 1 atamasý yapýlýr (ana fonksiyonda q = 1 ise hata alýnacaktýr)
					if(tahta[*y-1][i] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while döngüsünden ve dolayýsýyla 'k' fonksiyonundan çýkýlýr
				if(*q == 1)
					break;
				// Kalenin önü boþsa ve gitmek istediði yer boþ veya rakibin herhangi bir taþý varsa  q = 0 (ana fonksiyonda hata alýnmayacaðý anlamýna gelecek) kale oraya gidebilir
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin önü boþsa ve gitmek istediði konumda kendi taþlarýndan herhangi biri varsa hatalý seçim olacaktýr
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
					//  Kalenin önünde taþ versa *q = 1 atamasý yapýlýr (ana fonksiyonda q = 1 ise hata alýnacaktýr)
					if(tahta[*y-1][i] != '#')
					{
						*q = 1;
						break;
					}
				}
				// *q = 1 ise while döngüsünden ve dolayýsýyla 'k' fonksiyonundan çýkýlýr
				if(*q == 1)
					break;
				// Kalenin önü boþsa ve gitmek istediði yer boþ veya rakibin herhangi bir taþý varsa  q = 0 (ana fonksiyonda hata alýnmayacaðý anlamýna gelecek) kale oraya gidebilir	
				if(tahta[*y2-1][*x2-1] == 'p' || tahta[*y2-1][*x2-1] == 'k' || tahta[*y2-1][*x2-1] == 'a' || tahta[*y2-1][*x2-1] == 'f' || tahta[*y2-1][*x2-1] == 'v' || tahta[*y2-1][*x2-1] == '#')
				{
					*q = 0;
					break;
				}
				// Kalenin önü boþsa ve gitmek istediði konumda kendi taþlarýndan herhangi biri varsa hatalý seçim olacaktýr
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
	int q; // foksiyona gidildikten sonra hatali seçim yapýlýrsa q deðeri if koþulu olarak kullanýlacak 
	
	//Satranc tahtasýna taþlarý yerleþtirme 
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
	//Oyun baþlýyor
	while(1)
	{
		q = 0;
		//Satraç tahtasýný yazdýrma
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
		scanf("%d%d", &x, &y); // x ve y oynatýlacak taþýn konumlarýný tutuyor
		
		//Tahtadaki boþ bir karakteri seçtiðinde verilecek hata
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
			printf("Hatali secim\n");
			n--;
			continue;
		}
		//Rakip takýmýn taþlarý seçilirse verilecek hata
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
		scanf("%d%d", &x2, &y2); //  x2 ve y2 oynatýlacak yerin konumlarýný tutuyor
		
		//Sýra 1.oyuncudayken sadece onun fonksiyonlarýný kontrol eder
		if(n == 1)
		{
			if(tahta[y-1][x-1] == 'p')
			p(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'k')
			k(tahta, &x, &y, &x2, &y2, &q);
			if(tahta[y-1][x-1] == 'f')
			f(tahta, &x, &y, &x2, &y2, &q);
		}
		//Sýra 2.oyuncudayken sadece onun fonksiyonlarýný kontrol eder
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
		//Seçilen taþ istenilen yere oynatýlýyor
		tahta[y2-1][x2-1] = tahta[y-1][x-1];
		tahta[y-1][x-1] = '#';
		
		system("cls");
			
		if(n == 2)
			n=0;
	}
	 
	return 0;
}
