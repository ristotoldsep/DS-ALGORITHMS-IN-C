#include "stdio.h"
#include "DateTime.h"
#include "Objects.h"
#include "Headers.h"
#include "Structs.h"
#include "string.h"
#include "stdlib.h"
#include "time.h"
#include "ctype.h"

#pragma warning ( disable : 4996 ) //to avoid errors

//======================================================
//PROTOTÜÜBID
//======================================================
HeaderD* GetStruct7(int ObjectType, int nObjects);

void PrintObjects(HeaderD* pStruct7); //Objektide kuvamine

int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode); //Uue objekti sisestamine

int vordlus(char, char); //Kahe stringi võrdlemine

Object2* RemoveExistingObject(HeaderD** pStruct7, char* pExistingID); //Olemasoleva objekti eemaldamine

//=======================================================
//MAIN FUNKTSIOON
//=======================================================
int main()
{
	//	VIIDAD
	HeaderD* pStruct7 = GetStruct7(2, 30);

	HeaderD** ppStruct7;

	ppStruct7 = &pStruct7;

	Object2* removedObj;

	//char buf[100];

	//char* ID = (char*)malloc(strlen(buf) + 1);

	char* ID = (char*)malloc(100);

	char* removedID = (char*)malloc(100);
	//char* removedID = new char;

	int valik, kontroll;

	//int kood;

	//MENÜÜ
	while (1)
	{
		printf("\n");
		printf("1. Kuva objektid\n");
		printf("2. Lisa objekt\n");
		printf("3. Eemalda objekt\n");
		printf("7. Peata programm\n\n");

		printf("Sisesta valik: ");
		scanf("%d", &valik);

		if (valik == 7)
			break;

		switch (valik)
		{
		case 1:
			PrintObjects(pStruct7);
			break;
		case 2:
			printf("\nSisestage uue objekti ID: ");
			scanf("%s", ID);

			//strcpy(ID, buf);

			/*printf("Sisesta uue objekti kood: ");
			scanf("%d", &kood);*/

			kontroll = InsertNewObject(ppStruct7, ID, 1234567);
			if (kontroll == 1) //Kui funktsioon tagastab ühe, siis lisame uue objekti loendisse!
			{
				printf("\nUus objekt on struktuuri lisatud!\n");
			}
			else {
				printf("\nEi saanud objekti struktuuri lisada!\n");
			}
			break;
		case 3:
			printf("\nSisestage objekti ID, mida soovite eemaldada: ");
			scanf("%s", removedID);
			removedObj = RemoveExistingObject(ppStruct7, removedID);
			if (removedObj) {
				printf("\nEemaldatud objekt: %s\n", removedObj->pID);
			}
			break;
		case 7:
			printf("\nPeatasid programmi!");
			break;
		default:
			printf("\nSellist valikut ei ole!\n");
		}
	}
	free(ID);
	free(removedID);

	return 0;
}

/*typedef struct headd
{
	void *pObject;  // Pointer to the linked list of objects.
					// Objects may be of types Object1, ....Object10.
					// Declarations of objects are in file Objects.h
	char cBegin;    // The linked list contains objects in which
					// the first letter of object ID is cBegin.
	struct headd *pNext;
	struct headd *pPrior;
} HeaderD;*/

/*typedef struct ob2
{  // formatting string for printf is "%d) %s %lu %02d:%02d:%02d\n", the result is for example "1) Abcde 100 15:52:07"
   // or "10) Abcde Fghij 100 15:52:07"
	char *pID;
	unsigned long int Code;
	Time1 *pTime1; // Declaration of Time1 is in file DateTime.h
	struct ob2 *pNext;
} Object2;
 */

 /*typedef struct
 {
	 int Hour;
	 int Minute;
	 int Second;
 } Time1;*/

 //=======================================================
 //OBJEKTIDE VÄLJASTAMISE FUNKTSIOON
 //=======================================================
void PrintObjects(HeaderD* pStruct7)
{
	Object2* ob2 = (Object2*)pStruct7->pObject; //Objekt2 tüüpi viit ob2

	Time1* time1 = ob2->pTime1; //Time1 tüüpi viit time1

	HeaderD* pHeader; //HeaderD tüüpi viit, saab sisendsee iks pStruct7

	//KONTROLL, ega pStruct7 ehk sisend poleks tühi
	if (pStruct7 == NULL)
	{
		printf("Objektid puuduvad!\n");
		return;
	}

	int i = 1;

	printf("\nObjektid:\n");

	//Kammib lõpuni läbi pStructi Headerid
	for (pHeader = pStruct7; pHeader != NULL; pHeader = pHeader->pNext) {
		//Kammib läbi kõik struktuuris olevad objektide loendid
		for (ob2 = (Object2*)pHeader->pObject; ob2 != NULL; ob2 = ob2->pNext, i++) {
			printf("%d) %s %lu %02d:%02d:%02d\n", i, ob2->pID, ob2->Code, time1->Hour, time1->Minute, time1->Second);
		}
	}

	printf("\n");
}

//=======================================================
//OBJEKTIDE LISAMISE FUNKTSIOON
//=======================================================
int InsertNewObject(HeaderD** pStruct7, char* pNewID, int NewCode) ////Sisendiks HeaderD tüüpi viidaviit pStruct7-le, Uus ID ja selle kood
{
	//Kontrollin, et sisend poleks tühi
	if (pStruct7 == NULL || pNewID == NULL || NewCode < 0)
		return 0;

	//KONTROLLIN, KAS ID VASTAB FORMAADILE
	if ((int)pNewID[0] < 65 || (int)pNewID[0] > 90) //Kui sisestatud ID esimene täht ei ole A-Z
	{
		printf("\nVale ID algus (Peab algama suure t2hega!)\n");
		return 0;
	}

	for (int i = 1; i < (int)strlen(pNewID); i++) //Kammin läbi sisestatud ID stringi alates teisest tähest
	{
		int sobivus = (int)pNewID[i];
		if (sobivus < 97 || sobivus > 122) //Kui sisestatud ID sisaldab muid märke peale a-z
		{
			printf("\nID sisaldab valesid m2rke!\n");
			return 0;
		}
	}
	//OTSIN STRUKTUURIS POSITSIOONI
	HeaderD** ppHeader = pStruct7; //Headerpointer Header pointerile
	HeaderD* pHeader; //Headeri pointer
	pHeader = *ppHeader;
	HeaderD* pHtemp = pHeader; //Uue Headeri pointer = olemasoleva Headeri pointer
	Object2* ob2 = (Object2*)pHeader->pObject; //pointer ob2-le

	//KONTROLLIN, KAS SAMA ID ON JUBA OLEMAS
	for (; pHeader != NULL; pHeader = pHeader->pNext)
	{
		for (ob2 = (Object2*)pHeader->pObject; ob2 != NULL; ob2 = ob2->pNext)
		{
			if (strcmp(pNewID, ob2->pID) == 0) //Kui võrdsed, väljastab strcmp nulli!
			{
				printf("\nSellise ID-ga objekt on juba olemas!\n");
				return 0; //Väljastab nulli
			}
		}
	}

	//KONTROLLIN, KAS ID PUUDUB & KUI PUUDUB, LISAN OBJEKTI LOENDISSE
	pHeader = *ppHeader;
	Object2* ob2New = (Object2*)malloc(sizeof(Object2)); //Eraldan mallociga uuele objektile mälu
	//Object2* ob2New = new Object2;

	int stop = 0;
	for (int i = 0; stop != 1; pHtemp = pHeader, pHeader = pHeader->pNext, i++)
	{
		//KUI SISESTATUD ID on HEADERITE LOENDIS TÄHE POOLEST VIIMANE / Mingi HEADER PUUDUB
		if (pHeader == NULL)
		{
			HeaderD* pHnew = (HeaderD*)malloc(sizeof(HeaderD)); //uus headerD tüüpi viit
	
			pHnew->cBegin = pNewID[0]; //Uue Headeri esimene täht
			pHnew->pNext = NULL;
			pHnew->pPrior = NULL;
			pHnew->pObject = ob2New;
			ob2New->pNext = NULL;
			pHtemp->pNext = pHnew;
			stop = 1;
			break;
		}

		int kontroll = vordlus(pHeader->cBegin, pNewID[0]); //Võrdlen Headerite ID ja uue ID esimest tähte

		if (kontroll == 0) //Kui ID esitähed on võrdsed, lisada olemasoleva Headeri alla uus objekt (sorteeritult)
		{
			ob2 = (Object2*)pHeader->pObject;
			Object2* temp = ob2;
			int o = 0;
			int kont = 0;
			int n = 0;
			do {
				kont = 0;
				for (n = 0; kont == 0; n++) 
				{
					kont = vordlus(ob2->pID[n + 1], pNewID[n + 1]); //Alates teisest tähest
				}
				if (kont > 0) //Kui uus objekt peaks tulema esimeseks
				{
					if (o == 0)
					{
						ob2New->pNext = ob2;
						pHeader->pObject = ob2New;
						stop = 1;
						break;
					}
					if (o != 0)
					{
						temp->pNext = ob2New;
						ob2New->pNext = ob2;
						stop = 1;
						break;
					}
				}
				else { //Kui on väiksem kui 0
					o++;
					temp = ob2;
					ob2 = ob2->pNext;
					if (ob2 == NULL)
					{
						temp->pNext = ob2New;
						ob2New->pNext = NULL;
						stop = 1;
						break;
					}
				}
			} while (stop == 0);
		}
		if (kontroll > 0 && i == 0) //Kui uus objekt tuleb kõige esimesele kohale lisada
		{
			HeaderD* pHnew = (HeaderD*)malloc(sizeof(HeaderD));
			//HeaderD* pHnew = new HeaderD;
			pHnew->pNext = pHtemp;
			pHnew->cBegin = pNewID[0];
			pHnew->pObject = ob2New;
			ob2New->pNext = NULL;
			*pStruct7 = pHnew;

			stop = 1;
		}
		if (kontroll > 0 && i != 0) //
		{
			HeaderD* pHnew = (HeaderD*)malloc(sizeof(HeaderD));
			//HeaderD* pHnew = new HeaderD;
			pHtemp->pNext = pHnew;
			pHnew->pNext = pHeader;
			pHnew->cBegin = pNewID[0];
			pHnew->pObject = ob2New;
			ob2New->pNext = NULL;

			stop = 1;
		}
	}

	ob2New->pID = pNewID; //Uue objekti ID = uus ID
	ob2New->Code = NewCode; //Uue objekti kood = uus kood

	time_t RawTime;
	time(&RawTime);

	Time1* t = (Time1*)malloc(sizeof(Time1));

	int err = GetTime1(RawTime, t);
	if (err != 1) //GetTime1 peab väljastama 1
	{
		//error
		return NULL;
	}
	ob2New->pTime1 = t;

	/*Time1* time1 = ob2New->pTime1;

	time(&RawTime);
	GetTime1(RawTime, time1);*/

	return 1; //Kui uus objekt lisatud, väljastab funktsioon väärtuse 1
}

//=======================================================
//KAHE STRINGI VÕRDLEMISE FUNKTSIOON
//=======================================================
int vordlus(char esimene, char teine) {

	int tulemus = (int)esimene - (int)teine;

	return tulemus;
}

//=======================================================
//OBJEKTIDE EEMALDAMISE FUNKTSIOON
//=======================================================
Object2* RemoveExistingObject(HeaderD** pStruct7, char* pExistingID) {

	Object2* removedObj = NULL; //Eemaldatud objekti kustutada ei tohi. Väljundsuuruseks on viit eemaldatud objektile.

	//Kontrollin, et sisend poleks tühi
	if (pStruct7 == NULL || pExistingID == NULL)
		return removedObj;

	//Deklareerin viidad
	HeaderD** ppHeader = pStruct7;
	HeaderD* pHeader = *ppHeader;
	HeaderD* pHtemp = pHeader;
	Object2* pObj2;

	int o = 0, stop = 0, h = 0;

	for (;; pHeader = pHeader->pNext, o = 0, h++)
	{
		if (pHeader == NULL)
		{
			printf("\nSellise ID-ga objekti ei eksisteeri!\n");
			return 0;
		}
		pObj2 = (Object2*)pHeader->pObject;
		Object2* temp = pObj2;
		int kontroll;
		for (; pObj2 != NULL; pObj2 = pObj2->pNext, o++)
		{
			kontroll = strcmp(pExistingID, pObj2->pID);
			if (kontroll == 0)
			{
				break;
			}
			temp = pObj2;
		}
		if (kontroll == 0)
		{
			if (o != 0 && pObj2->pNext == NULL)
			{
				temp->pNext = NULL;
				removedObj = pObj2;
				return removedObj;
			}
			if (o != 0 && pObj2->pNext)
			{
				temp->pNext = pObj2->pNext;
				pObj2->pNext = NULL;
				removedObj = pObj2;
				return removedObj;
			}
			if (o == 0 && pObj2->pNext == NULL && pHeader->pNext == NULL) 
			{
				pHtemp->pNext = NULL;
				removedObj = pObj2;
				pHeader->pObject = NULL;
				free(pHeader);
				return removedObj;
			}
			if (o == 0 && pObj2->pNext)
			{
				pHeader->pObject = pObj2->pNext;
				pObj2->pNext = removedObj = pObj2;
				return removedObj;
			}
			if (o == 0 && pObj2->pNext == NULL && h == 0)
			{
				*pStruct7 = pHeader->pNext;
				removedObj = pObj2;
				pHeader->pObject = NULL;
				pHeader->pNext = NULL;
				free(pHeader);
				return removedObj;
			}
			if (o == 0 && pObj2->pNext == NULL && h != 0)
			{
				pHtemp->pNext = pHeader->pNext;
				pHeader->pObject = NULL;
				pHeader->pNext = NULL;
				free(pHeader);
				removedObj = pObj2;
				return removedObj;
			}
		}
		pHtemp = pHeader;
	}
}
