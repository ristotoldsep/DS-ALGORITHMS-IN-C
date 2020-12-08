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

int vordlus(char, char); //Kahe stringi võrdlemine täht-haaval

Object2* RemoveExistingObject(HeaderD** pStruct7, char* pExistingID); //Olemasoleva objekti eemaldamine

//===================BINARY TREE FUNCTIONS===============
Node* CreateBinaryTree(HeaderD* pStruct7); //Mitterekursiivne funktsioon, mis loob kahendpuu

void TreeTraversal(Node* pTree);

Node* DeleteTreeNode(Node* pTree, unsigned long int Code);

Stack* push(Stack* pStack, void* pOb);

Stack* pop(Stack* pStack, void** pResult);

void printTree(Node* pTree, int space);


//typedef struct node
//{
//	void* pObject;		// Pointer to object belonging to this node
//						// Objects may be of types Object1, ....Object10.
//						// Declarations of objects are in file Objects.h
//	struct node* pLeft, // Pointer to the left child node
//		* pRight;		// Pointer to the right child node
//} Node;
//
//typedef struct stack
//{
//	void* pObject;
//	struct stack* pNext;
//} Stack;


//=======================================================
//MAIN FUNKTSIOON
//=======================================================
int main()
{
	//	VIIDAD
	HeaderD* pStruct7 = GetStruct7(2, 10);

	HeaderD** ppStruct7;

	ppStruct7 = &pStruct7;

	Object2* removedObj;

	Node* pTree = (Node*)malloc(sizeof(Node) * 10);

	char* ID = (char*)malloc(100);

	char* removedID = (char*)malloc(100);

	int valik, kontroll;

	unsigned long int removedCode;

	int test = 0;

	//MENÜÜ
	while (1)
	{
		printf("\n");
		printf("1. Kuva objektid\n");
		printf("2. Lisa objekt\n");
		printf("3. Eemalda objekt\n");
		printf("4. Loo kahendpuu\n");
		printf("5. K2i l2bi kahendpuu\n");
		printf("6. Kustuta objekt kahendpuust\n");
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
		case 4: 
			pTree = CreateBinaryTree(pStruct7);
			printf("\nKahendpuu loodud!\n");

			test = 1;
			break;
		case 5: 
			if (test != 1) {
				printf("\nLoo enne kahendpuu!\n");
			}
			else {
				printf("\nKahendpuu:\n");
				TreeTraversal(pTree);

				printTree(pTree, 0);

			}
			break;
		case 6: 
			if (test != 1) {
				printf("\nLoo enne kahendpuu!\n");
			}
			else {
				printf("\nSisesta objekti kood, mille soovid eemaldada: ");
				scanf("%lu", &removedCode);
				pTree = DeleteTreeNode(pTree, removedCode);
				if (pTree) {
					printf("\nEemaldatud objekt: %d\n", removedCode);
				}
			}
			break;
		case 7:
			printf("\nPeatasid programmi!\n");
			break;
		default:
			printf("\nSellist valikut ei ole!\n");
		}
	}
	free(ID);
	free(removedID);
	free(pTree);
	//free(newTree);

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
	HeaderD* pHtemp = pHeader; //Abipointer 
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
	for (int i = 0; stop != 1; pHtemp = pHeader, pHeader = pHeader->pNext, i++)  //tempi kaudu saab kätte eelmise objekti/headeri, i loeb läbitud headereid
	{
		int kasVordsed = vordlus(pHeader->cBegin, pNewID[0]); //Võrdlen Headerite ID ja uue ID esimest tähte

		 //Kui ID esitähed on võrdsed, on selle tähega header olemas, ehk vaja lisada sorteeritult objekt!
		if (kasVordsed == 0) //On võrdsed
		{
			ob2 = (Object2*)pHeader->pObject;
			Object2* temp = ob2;
			int objekt = 0;
			int comp = 0;
			int n = 0;
			do {
				comp = 0;
				for (n = 0; comp == 0; n++) //Võrdlemaks olemasoleva ja uue ID teisi tähti (alates teisest tähest)
				{
					comp = vordlus(ob2->pID[n + 1], pNewID[n + 1]); 
				}
				if (comp > 0) //Kui uus objekt peaks tulema esimeste hulka (nt b-a = 98-97 = 1)
				{
					if (objekt == 0) //Kui esimeseks objektiks
					{
						ob2New->pNext = ob2; //uue objekti viit = vana objekt
						pHeader->pObject = ob2New; //Pea header viitab uuele objektile
						stop = 1; //Loop peatub
						break;
					}
					if (objekt != 0) //Kui samade tähtedega objekte on veel
					{
						temp->pNext = ob2New; //Sisesta uus objekt tempiga viidatud kohale
						ob2New->pNext = ob2;
						stop = 1;
						break;
					}
				}
				else { //Kui uus objekt ei tule esimeseks (nt c-d = 98-99 = -1)
					objekt++;
					temp = ob2; //temp liigub kaasa objekti viidaga ning näitab, kuhu uus objekt sisestada tuleb
					ob2 = ob2->pNext; //liigutame objektiviita edasi
					if (ob2 == NULL) //kui objekt viitab nullile, lisame uue objekti lõppu!
					{
						temp->pNext = ob2New;
						ob2New->pNext = NULL;
						stop = 1;
						break;
					}
				}
			} while (stop == 0);
		}

		//Kui kontroll ei ole null, ei ole sellise tähega headerit ja see tuleb luua!
		if (kasVordsed > 0 && i == 0) //Kui uus header tuleb struktuuris kõige esimesele kohale lisada (nt B-A = 66-65 = 1 ja pHeader pole liikunud)
		{
			HeaderD* pHnew = (HeaderD*)malloc(sizeof(HeaderD)); //annan uuele headerile mälu
			//HeaderD* pHnew = new HeaderD;
			pHnew->pNext = pHtemp; //Uus header viitab ajutisele headerile
			pHnew->pPrior = NULL; //Uue headeri eelmine linkur = NULL (pStruct7)
			pHnew->cBegin = pNewID[0]; //Uue headeri esimene täht = Uue ID esimene täht
			pHnew->pObject = ob2New; //Uus header viitab uuele objektile
			ob2New->pNext = NULL; //Alguses järgmist objekti ei ole
			*pStruct7 = pHnew; //Muutub ka esimene siduja

			stop = 1;
		}
		if (kasVordsed > 0 && i != 0) //Kui uus header tuleb lisada struktuuri keskele
		{
			HeaderD* pHnew = (HeaderD*)malloc(sizeof(HeaderD)); //annan uuele headerile mälu
			//HeaderD* pHnew = new HeaderD;
			pHtemp->pNext = pHnew; //Eelmine header viitab uuele
			pHnew->pNext = pHeader; //Uus header viitab järgmisele
			pHnew->pPrior = pHtemp; //Uus header on lingitud eelmisega
			pHnew->cBegin = pNewID[0]; //Uue headeri esimene täht on sisestatud ID esimene täht
			pHnew->pObject = ob2New; //Uus header viitab 
			ob2New->pNext = NULL;

			stop = 1;
		}
		//KUI SISESTATUD ID-GA OBJEKT PUUDUB (viimaseks)
		if (pHeader == NULL)
		{
			HeaderD* pHnew = (HeaderD*)malloc(sizeof(HeaderD)); //uus headerD tüüpi viit

			pHnew->cBegin = pNewID[0]; //Uue Headeri esimene täht
			pHnew->pNext = NULL;
			pHnew->pPrior = pHtemp;
			pHnew->pObject = ob2New;
			ob2New->pNext = NULL;
			pHtemp->pNext = pHnew;
			stop = 1;
			break;
		}
	}

	ob2New->pID = pNewID; //Uue objekti ID = uus ID
	ob2New->Code = NewCode; //Uue objekti kood = uus kood

	//Aja funktsiooni teisendus
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
	Object2* ob2; //Abiviit objektidele

	int objekt = 0, stop = 0, header = 0, kasVordsed;

	for (;; pHeader = pHeader->pNext, objekt = 0, header++) //Kammin läbi headerid, loetlen läbitud headereid
	{
		if (pHeader == NULL) //Kontrollin, kas sellise ID-ga header on olemas
		{
			printf("\nSellise ID-ga objekti ei eksisteeri!\n");
			return 0;
		}
		ob2 = (Object2*)pHeader->pObject; //Omistan pObj2-le vastavad pHeaderi objekti viida
		Object2* temp = ob2; //Ajutine object 2 tyypi viit temp = pObj2

		for (; ob2 != NULL; ob2 = ob2->pNext, objekt++) //Kammin läbi objektid, loetlen läbitud objekte
		{
			kasVordsed = strcmp(pExistingID, ob2->pID); //Võrdlen sisestatud ja olemasolevaid ID-sid
			if (kasVordsed == 0) //strcmp väljastab võrdsete stringide korral nulli!
			{
				break;     //Kui sobiv leitud, peata loop
			}
			temp = ob2;  //Abiviit viitab objektile, kus loop peatus
		}
		if (kasVordsed == 0)
		{
			if (objekt != 0 && ob2->pNext == NULL) //Kui objekt on oma headeri loendis viimane
			{
				temp->pNext = NULL; 
				removedObj = ob2;
				return removedObj;
			}
			if (objekt != 0 && ob2->pNext) //Kui objekt ei ole esimene, aga järgmine on olemas
			{
				temp->pNext = ob2->pNext;
				ob2->pNext = NULL;
				removedObj = ob2;
				return removedObj;
			}
			if (objekt == 0 && ob2->pNext == NULL && pHeader->pNext == NULL) //Kui tegemist on viimase headeri ainukese objektiga
			{
				pHtemp->pNext = NULL;
				removedObj = ob2;
				pHeader->pObject = NULL;
				free(pHeader); //Vabastame ka vastava headeri siduja
				return removedObj;
			}
			if (objekt == 0 && ob2->pNext) //Kui objekt on esimene ja järgmine on olemas
			{
				pHeader->pObject = ob2->pNext; //Suunan headeri viida järgmisele objektile loendis
				ob2->pNext = removedObj = ob2;
				return removedObj;
			}
			if (objekt == 0 && ob2->pNext == NULL && header == 0) //Kui tegemist on esimese headeri ainukese objektiga
			{
				*pStruct7 = pHeader->pNext; //Muudan esimese siduja viida järgmisele
				removedObj = ob2;
				pHeader->pObject = NULL;
				pHeader->pNext = NULL;
				pHeader->pPrior = NULL;
				free(pHeader); //Vabastan vastava headeri siduja
				return removedObj;
			}
			if (objekt == 0 && ob2->pNext == NULL && header != 0) //Kui tegemist on ainukese objektiga headerite struktuuri keskel
			{
				pHtemp->pNext = pHeader->pNext;
				pHeader->pNext->pPrior = pHtemp;
				pHeader->pObject = NULL;
				pHeader->pNext = NULL;
				pHeader->pPrior = NULL;
				free(pHeader); //Vabastan vastava headeri siduja
				removedObj = ob2;
				return removedObj;
			}
		}
		pHtemp = pHeader; //tempi kaudu saab ligi eelmisele headerile
	}
}

//typedef struct node
//{
//	void* pObject;		// Pointer to object belonging to this node
//						// Objects may be of types Object1, ....Object10.
//						// Declarations of objects are in file Objects.h
//	struct node* pLeft, // Pointer to the left child node
//		* pRight;		// Pointer to the right child node
//} Node;
//
//typedef struct stack
//{
//	void* pObject;
//	struct stack* pNext;
//} Stack;

//Node* getnode(int *x)
//{
//	Node* p = (Node*)malloc(sizeof(Node));
//	p->pObject = x;
//	p->pLeft = NULL;
//	p->pRight = NULL;
//	return p;
//}

//=======================================================
//KAHENDOTSINGPUU LOOMISE FUNKTSIOON
//=======================================================
Node* CreateBinaryTree(HeaderD* pStruct7) {

	HeaderD* pHeader = pStruct7; //HeaderD tüüpi pointer esimesele sidujale
	Object2* pObj; //Objekt2 tüüpi pointer
	int stop, n = 0; //arvud loetlemiseks
	Object2* pNodeObj; //Objekt2 tüüpi pointer	
	Node* pNode; //Node tüüpi pointer
	Node* pRoot = (Node*)malloc(sizeof(Node)); //Eraldan puu tipule mälu
	pRoot->pObject = pHeader->pObject;
	pRoot->pLeft = 0;
	pRoot->pRight = 0;
	for (; pHeader != NULL; pHeader = pHeader->pNext) {
		if (n == 0) {
			pObj = (Object2*)pHeader->pObject;
			pObj = pObj->pNext;
			if (pObj == NULL) {
				pHeader = pHeader->pNext;
				pObj = (Object2*)pHeader->pObject;
			}
		}
		pObj = (Object2*)pHeader->pObject;
		for (; pObj != NULL; pObj = pObj->pNext) {
			stop = 0;
			pNode = pRoot;
			for (; stop != 1;) {
				pNodeObj = (Object2*)pNode->pObject;
				if (pNodeObj->Code > pObj->Code) {
					if (!pNode->pLeft) {
						pNode->pLeft = (Node*)malloc(sizeof(Node));
						pNode = pNode->pLeft;
						pNode->pLeft = 0;
						pNode->pRight = 0;
						pNode->pObject = pObj;
						stop = 1;
						n++;
					}
					else {
						pNode = pNode->pLeft;
					}
				}
				else {
					if (!pNode->pRight) {
						pNode->pRight = (Node*)malloc(sizeof(Node));
						pNode = pNode->pRight;
						pNode->pLeft = 0;
						pNode->pRight = 0;
						pNode->pObject = pObj;
						stop = 1;
						n++;
					}
					else {
						pNode = pNode->pRight;
					}
				}

			}
		}
	}
	return pRoot; //Väljastab pointeri puu tipule
}

Stack* push(Stack* pStack, void* pOb) {

	Stack* pNew = (Stack*)malloc(sizeof(Stack));
	pNew->pObject = pOb;
	pNew->pNext = pStack;
	return pNew;
}

Stack* pop(Stack* pStack, void** pResult) {

	Stack* p;
	*pResult = pStack->pObject;
	p = pStack->pNext;
	free(pStack);
	return p;
}

void TreeTraversal(Node* pTree) {
	Stack* pStack = 0;
	Node* p1 = pTree, * p2;
	Object2* pOb;
	int count = 0;
	pOb = (Object2*)p1->pObject;
	printf("\nPuu tipu kood: %lu\n", pOb->Code);
	printf("\n");
	printf("Objekti kood    Objekti ID\n");
	printf("===============================\n");
	do {
		while (p1)
		{
			pStack = push(pStack, p1);
			p1 = p1->pLeft;
			
		}
		pStack = pop(pStack, (void**)&p2);
		pOb = (Object2*)p2->pObject;
		count++;
		printf("%d) %lu        %s \n",count, pOb->Code, pOb->pID);
		p1 = p2->pRight;

	} while (!(!pStack && !p1));

}

void printTree(Node* pTree, int space) {
	if (pTree == NULL)
		return;
	space += 10;
	printTree(pTree->pRight, space);
	for (int i = 10; i < space; i++)
		printf("\t");
	printf("%d\n", (int)pTree);
	//cout << root->data << "\n";
	printTree(pTree->pLeft, space);
}

Node* DeleteTreeNode(Node* pTree, unsigned long int Code) {
	Node* pNewTree, * pNode, * NodeBuf = 0;
	Object2* pOb;
	pNode = pTree;
	int LastMoveRight;
	for (;;) {
		pOb = (Object2*)pNode->pObject;
		if (pOb->Code == Code)
		{
			if (NodeBuf == NULL)
			{
				NodeBuf = pNode;
				pNode = pNode->pRight;
				while (pNode->pLeft != 0)
				{
					pNode = pNode->pLeft;
				}
				pNode->pLeft = NodeBuf->pLeft;
				pNewTree = NodeBuf->pRight;
				return pNewTree;
			}
			if (pNode->pLeft != 0 && pNode->pRight != 0 && NodeBuf)
			{
				if (LastMoveRight == 1)
				{
					NodeBuf->pRight = pNode->pRight;
					NodeBuf = pNode;
					pNode = pNode->pRight;
					while (pNode->pLeft != 0)
					{
						pNode = pNode->pLeft;
					}
					pNode->pLeft = NodeBuf->pLeft;
					return pTree;
				}
				if (LastMoveRight == 0)
				{
					NodeBuf->pLeft = pNode->pRight;
					NodeBuf = pNode;
					pNode = pNode->pRight;
					while (pNode->pLeft != 0)
					{
						pNode = pNode->pLeft;
					}
					pNode->pLeft = NodeBuf->pLeft;
					return pTree;
				}
			}
			if (pNode->pLeft == 0 && pNode->pRight == 0 && LastMoveRight == 1)
			{
				NodeBuf->pRight = 0;
				return pTree;
			}
			if (pNode->pLeft == 0 && pNode->pRight == 0 && LastMoveRight == 0)
			{
				NodeBuf->pLeft = 0;
				return pTree;
			}
			if (pNode->pLeft == 0 && LastMoveRight == 0)
			{
				NodeBuf->pLeft = pNode->pRight;
				return pTree;
			}
			if (pNode->pLeft == 0 && LastMoveRight == 1)
			{
				NodeBuf->pRight = pNode->pRight;
				return pTree;
			}
			if (pNode->pRight == 0 && LastMoveRight == 1)
			{
				NodeBuf->pRight = pNode->pLeft;
				return pTree;
			}
			if (pNode->pRight == 0 && LastMoveRight == 0)
			{
				NodeBuf->pLeft = pNode->pLeft;
				return pTree;
			}

		}
		if (pNode->pLeft == NULL && pNode->pRight == NULL && pOb->Code != Code)
		{
			printf("Sellise koodiga tippu ei ole puus, eemaldamist ei toimunud\n");
			return 0;
		}
		if ((pNode->pLeft == NULL && pOb->Code > Code) || (pNode->pRight == NULL && pOb->Code < Code))
		{
			printf("Sellise koodiga tippu ei ole puus, eemaldamist ei toimunud\n");
			return 0;
		}
		if (pOb->Code > Code)
		{
			NodeBuf = pNode;
			pNode = pNode->pLeft;
			LastMoveRight = 0;
		}
		if (pOb->Code < Code)
		{
			NodeBuf = pNode;
			pNode = pNode->pRight;
			LastMoveRight = 1;
		}
	}

}


//Node* CreateBinaryTree(HeaderD* pStruct7){ //pStruct7 = root
//	
//	Object2* ob2 = (Object2*)pStruct7->pObject;
//
//	Node* pNew = (Node*)malloc(sizeof(Node)); //Uus tipp
//
//	pNew->pObject = ob2;
//	pNew->pLeft = NULL;
//	pNew->pRight = NULL;
//
//	if (!pStruct7)
//		return pNew;
//
//	Node* p = pStruct7;
//
//	HeaderD* pHeader; //HeaderD tüüpi viit, saab sisendsee iks pStruct7
//
//	Object2* ob2 = (Object2*)pStruct7->pObject; //Objekt2 tüüpi viit ob2
//
//	Time1* time1 = ob2->pTime1; //Time1 tüüpi viit time1
//
//	Node* temp, * par;
//	
//	Node* pNew = pStruct7;
//
//	p->pObject = ob2;
//	
//	p->pLeft = NULL;
//	p->pRight = NULL;
//
//	//p=root;
//	par = NULL;
//	
//
//	int i = 1;
//
//	//Kammib lõpuni läbi pStructi Headerid
//	for (pHeader = pStruct7; pHeader != NULL; pHeader = pHeader->pNext) {
//		//Kammib läbi kõik struktuuris olevad objektide loendid
//		for (ob2 = (Object2*)pHeader->pObject; ob2 != NULL; ob2 = ob2->pNext, i++) {
//			par = p;
//			if(ob2->Code < pHeader->pObject->Code)
//		}
//	}
//} // CreateBinaryTree lõpp
////
//void TreeTraversal(Node* pTree){
//	if (pTree == NULL)
//	{
//		return;
//	}
//}
//
//Node* DeleteTreeNode(Node* pTree, unsigned long int Code){}
