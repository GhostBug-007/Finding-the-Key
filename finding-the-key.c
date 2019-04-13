#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_TREE_HT 100 

struct node {
	int data ;
	struct node *next ;
	char cArray[25] ;
}*root1 = NULL,*root2= NULL, *end1=NULL , *end2 = NULL ;

struct freqNode{
	char alphabet;
	int frequency ;
};
/*struct max{
	int data ;
	char cArr[25] ;
};*/
int p,q,m,n,c[20][20];
// char aa[3][20],bb[3][20]
char bAb[20][20];
char final[3][20] ;
int g= 0;


int createList(char word[], int i)
{
	struct node *temp = (struct node *)malloc(sizeof(struct node)) ;
	temp->data = 1 ;
	temp->next = NULL ;

	int x =0; 
	// int n = sizeof(word)/sizeof(char) ;
	while(word[x])
	{
		temp->cArray[x] = word[x] ;
		x++ ;
	}
	printf("%s ",temp->cArray) ;

	if (i == 2)	
		goto list2 ;

	if (root1 == NULL)
		root1 = temp ;
	else
		end1->next = temp ;
	end1 = temp ;

	return 0 ;

	list2:

	if (root2 == NULL)
		root2 = temp ;
	else
		end2->next = temp ;
	end2 = temp ;

	return 0 ;
}

int print()
{
	struct node *ptr1 = root1 ;
	while(ptr1)
	{
		printf("%s * %d\n",ptr1->cArray, ptr1->data);
		ptr1 = ptr1->next ;
	}
	printf("\n\n") ;

	struct node *ptr2 = root2 ;
	while(ptr2)
	{
		printf("%s * %d\n",ptr2->cArray, ptr2->data);
		ptr2 = ptr2->next ;
	}
	return 0 ;
}

struct node *deleteNode(struct node *parent)
{
	struct node *ptr = parent->next ;
	parent->next = ptr->next ;
	ptr->next = NULL ;
	free(ptr) ; 
	return parent ;
}

int duplicateCheck(int fileNo) 
{
	struct node *i, *j, *parent ;

	if (fileNo == 1)
		goto label1 ;
	else
		goto label2 ;

	label1 :
	// struct node *i = root1 , *j, *parent ;
	i = root1 ;
	goto label ;

	label2 :
		// struct node *i = root2 , *j, *parent ;
	i = root2 ;

	label :
	while(i->next)
	{
		j = i->next ;
		parent = i ;
		while(j)
		{
			if(strcmp(i->cArray, j->cArray) == 0)
			{
				i->data++ ;
				j = deleteNode(parent) ;
				j = j->next ;
				continue ;
			}
			parent = parent->next ;
			j = parent->next ;
		}
		i = i->next ;
	}
	return 0 ;
}

int min(int a ,int b)
{
	return (a < b)? a : b ;
}


int compareForMax()
{
	struct node *ptr1 = root1, *ptr2 = root2 ;
	int count ;
	while(ptr1)
	{
		count = 0 ;
		while(ptr2)
		{
			if(strcmp(ptr1->cArray,ptr2->cArray)== 0)
			{
				ptr1->data = min(ptr1->data,ptr2->data) ;
				count = 1;
				break ;
			}	
			ptr2 = ptr2->next ;
		}
		if (count == 0)
			ptr1->data = 0 ;
		ptr1 = ptr1->next ;
		ptr2 = root2 ;
	}
	return 0;
}

char *getMax()
{
	int max = 0 ;
	struct node *ptr = root1, *ptrMax ;
	while(ptr)
	{
		if(ptr->data > max)
		{
			max = ptr->data ;
			ptrMax = ptr ; 
		}
		ptr = ptr->next ;
	}
	// printf("%d ",ptrMax->data) ;
	ptrMax->data = 0 - max ;
	return (char *)ptrMax->cArray ;
}

void printSub(int i,int j, char *string1,int z)
{
    if(i==0 || j==0)
        return;
    if(bAb[i][j]=='c')
    {
        printSub(i-1,j-1,string1,z);
        final[z][g] = string1[i-1] ;
        g++ ;
                    // printf("%c",string1[i-1]);
    }
    else if(bAb[i][j]=='u')
        printSub(i-1,j,string1,z);
    else
        printSub(i,j-1,string1,z);
}
 
void lcs(char *string1, char *string2)
{
    m=strlen(string1);
    n=strlen(string2);
    for(p=0;p<=m;p++)
        c[p][0]=0;
    for(p=0;p<=n;p++)
        c[0][p]=0;
                    
   
    for( p = 1 ; p <= m ; p++)
        for( q = 1; q <= n; q++)
        {
	        if(string1[p-1]==string2[q-1])
	        {
                c[p][q] = c[p-1][q-1] + 1;
                bAb[p][q]='c';
	        }
	        else if(c[p-1][q] >= c[p][q-1])
	        {
                c[p][q] = c[p-1][q];
                bAb[p][q]='u';
	        }
	        else
	        {
                c[p][q] = c[p][q-1];
                bAb[p][q] = 'l';
	        }
        }
}

int findLongest()
{
	if(strlen(final[0]) > strlen(final[1]))
		if(strlen(final[0]) > strlen(final[2]))
			return 0 ;
		else
			return 2 ; 
	else
		if(strlen(final[1]) > strlen(final[2]))
			return 1 ;
		else
			return 2 ;
}

struct MinHeapNode { 

	char data; 

	unsigned freq; 

	struct MinHeapNode *left, *right; 
}; 

struct MinHeap { 

	unsigned size; 

	unsigned capacity; 

	struct MinHeapNode** array; 
}; 

struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
	struct MinHeapNode* temp 
		= (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode)); 

	temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 

	return temp; 
} 

struct MinHeap* createMinHeap(unsigned capacity) 

{ 

	struct MinHeap* minHeap 
		= (struct MinHeap*)malloc(sizeof(struct MinHeap)); 

	minHeap->size = 0; 

	minHeap->capacity = capacity; 

	minHeap->array 
		= (struct MinHeapNode**)malloc(minHeap-> 
capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

void swapMinHeapNode(struct MinHeapNode** a, 
					struct MinHeapNode** b) 

{ 

	struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

void minHeapify(struct MinHeap* minHeap, int idx) 

{ 

	int smallest = idx; 
	int left = 2 * idx + 1; 
	int right = 2 * idx + 2; 

	if (left < minHeap->size && minHeap->array[left]-> 
freq < minHeap->array[smallest]->freq) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]-> 
freq < minHeap->array[smallest]->freq) 
		smallest = right; 

	if (smallest != idx) { 
		swapMinHeapNode(&minHeap->array[smallest], 
						&minHeap->array[idx]); 
		minHeapify(minHeap, smallest); 
	} 
} 

int isSizeOne(struct MinHeap* minHeap) 
{ 

	return (minHeap->size == 1); 
} 

struct MinHeapNode* extractMin(struct MinHeap* minHeap) 

{ 

	struct MinHeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] 
		= minHeap->array[minHeap->size - 1]; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return temp; 
} 

void insertMinHeap(struct MinHeap* minHeap, 
				struct MinHeapNode* minHeapNode) 

{ 

	++minHeap->size; 
	int i = minHeap->size - 1; 

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 

		minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = minHeapNode; 
} 

void buildMinHeap(struct MinHeap* minHeap) 

{ 

	int n = minHeap->size - 1; 
	int i; 

	for (i = (n - 1) / 2; i >= 0; --i) 
		minHeapify(minHeap, i); 
} 

void printArr(int arr[], int n) 
{ 
	int i; 
	for (i = 0; i < n; ++i) 
		printf("%d", arr[i]); 

	printf("\n"); 
} 

int isLeaf(struct MinHeapNode* root) 

{ 

	return !(root->left) && !(root->right); 
} 

struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) 

{ 

	struct MinHeap* minHeap = createMinHeap(size); 

	for (int i = 0; i < size; ++i) 
		minHeap->array[i] = newNode(data[i], freq[i]); 

	minHeap->size = size; 
	buildMinHeap(minHeap); 

	return minHeap; 
} 

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) 

{ 
	struct MinHeapNode *left, *right, *top; 

	struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size); 

	while (!isSizeOne(minHeap)) { 

		left = extractMin(minHeap); 
		right = extractMin(minHeap); 

		top = newNode('$', left->freq + right->freq); 

		top->left = left; 
		top->right = right; 

		insertMinHeap(minHeap, top); 
	} 

	return extractMin(minHeap); 
} 

void printCodes(struct MinHeapNode* root, int arr[], int top) 

{ 

	if (root->left) { 

		arr[top] = 0; 
		printCodes(root->left, arr, top + 1); 
	} 

	if (root->right) { 

		arr[top] = 1; 
		printCodes(root->right, arr, top + 1); 
	} 

	if (isLeaf(root)) { 

		printf("%c: ", root->data); 
		printArr(arr, top); 
	} 
} 

void HuffmanCodes(char data[], int freq[], int size) 

{ 
	struct MinHeapNode* root 
		= buildHuffmanTree(data, freq, size); 

	int arr[MAX_TREE_HT], top = 0; 

	printCodes(root, arr, top); 
} 

struct freqNode freqArr[26] ;

int frequencyFinder(char substring[]) 
{
	int len = strlen(substring) ; 
	int frequencyArr[26] = {0} ;

	for(int i=0; i<len; i++)
    {
        /* If the current character is lowercase alphabet */
        if(substring[i]>='a' && substring[i]<='z')
        {
            frequencyArr[substring[i] - 97]++;
        }
        else if(substring[i]>='A' && substring[i]<='Z')
        {
            frequencyArr[substring[i] - 65]++;
        }
    }
    
    int count = 0 ;
    for(int i=0 ; i < 26 ; i++)
    {
    	if(frequencyArr[i] != 0)
    	{
    		freqArr[count].alphabet = i+97 ;
    		freqArr[count].frequency = frequencyArr[i] ;
    		count++ ;
    	}
    }
    return 0;
}



int main()
{
	FILE *file1 ;
	file1 = fopen("daaTestFile1.txt","r") ;
	if (file1 == NULL)
	{
		printf("Unable to open file 1\n");
		return 1 ;
	}	
	char fileWord[50] ;
	// int i1 =0 ;
	while(fscanf(file1,"%s",fileWord) != EOF)
	{
		createList(fileWord,1) ;
		// i1++ ;
	}
	// fclose(file) ;
	printf("\n\nFile2 Opening now....\n\n") ;
	
	FILE *file2 ;
	file2 = fopen("daaTestFile2.txt","r") ;
	if (file2 == NULL)
	{
		printf("Unable to open file 2\n");
		return 1 ;
	}

	// int i2 =0 ;
	printf("file opened\n\n") ;
	while(fscanf(file2,"%s",fileWord) != EOF)
	{
		createList(fileWord,2) ;
		// i2++ ;
	}
	printf("\n") ;

	duplicateCheck(1) ;
	duplicateCheck(2) ;
	print() ;
	printf("\n*********\n") ;
	compareForMax() ;
	printf("\n*********\n") ;
	print() ;
	printf("\n") ;


	char *maxArray[3];
	
	maxArray[0] = getMax() ;
	maxArray[1] = getMax() ;
	maxArray[2] = getMax() ;
	for(int i=0; i<3; i++)
		printf("\n%s ",*(maxArray+i)) ;

	lcs(maxArray[0],maxArray[1]);
    printSub(m,n,maxArray[0],0);
    g = 0;
    printf("\n\n");
    lcs(maxArray[1],maxArray[2]);
    printSub(m,n,maxArray[1],1);
    g= 0; 
    printf("\n\n");
    lcs(maxArray[0],maxArray[2]);
    printSub(m,n,maxArray[0],2);

    printf("\n******\n") ;
    printf("%s\n",final[0]);
    printf("%s\n",final[1]);
    printf("%s\n",final[2]);

    int longest = findLongest() ;
    printf("Longest Common subsequence is : %s\n",final[longest]) ;


    frequencyFinder(final[longest]) ;

    int countSize = 0;
    while(freqArr[countSize].frequency)
    {
    	printf("%d \n", freqArr[countSize].frequency) ;
    	countSize++ ;
    }
    int freqArrFrequency[countSize] ;
    for(int i=0 ; i < countSize; i++)
    	freqArrFrequency[i] = freqArr[i].frequency ;

    char freqArrAlphabet[countSize+1] ;
	for(int i=0 ; i < countSize; i++)
		freqArrAlphabet[i] = freqArr[i].alphabet ;
	printf("\n\nThe Key is\n") ; 

    HuffmanCodes(freqArrAlphabet,freqArrFrequency,countSize) ;
	/*subsequence(maxArray, (maxArray+1)) ;
	subsequence(maxArray, (maxArray+2)) ;
	subsequence((maxArray+1), (maxArray+2)) ;*/

	return 0;
}	