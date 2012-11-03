/**
	Lab1.c
	
	1) suliejimo metodas
	2) piramides metodas
	3) bucket sort metodas
	
	source kodas 1-am labaratoriiam darbui.
	merge-sortas
	heap-sortas
	bucket-sortas
**/

#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sys/time.h>

//*******************

#define	LIST	0	// 0 - no list(array); 1 - yes;
#define	MODE	1
/* mode tipai
	1 merge		|
	2 heap		|	Sorting
	3 bucket	|
	default generate&print
*/
#if (MODE == 1)
	#define GO "merge"
#elif (MODE == 2)
	#define GO "heap"
#elif (MODE == 3)
	#define GO "bucket"
#else
	#define GO "generate&print"
#endif

//*******************

			/* generuojamu skaiciu kiekis */
const int	n = 50,
				//100, 
				//200, 
				//400, 
				//800, 
				//1600, 
				//3200, 
				//6400, 
				//12800,
				//25600,
				//51200,
				//102400,
				//204800,
				//409600,
				//819200,
				//ir nereikia
				
			/* galutinis rezis */
			z = 1000000;
			
	/* veiksmai */	
int operations = 0;

//*******************

/* Laiko skaiciavimui */
long currentTick() {
    struct timeval tv;
    gettimeofday( &tv, NULL );
    return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/**
 *	Funkciju prototipai
 **/
void write_to_file (int number, int *W, char *fname);
//===================================================

/**
 *	Funkcijos
 **/

/**
 *	Generuoja skaicius
 *	number 	- skaiciu kiekis
 *	upto 	- galutinis rezis (n-1)
 *	*A 		- rodykle i masyva
 *	*fname	- failo pavadinimas
 **/
void generate (int number, int upto, int *A, char *fname)
{
	int v;
	srand(time(NULL));
	for (int i = 0; i < number; i++) {
		A[i] = v = rand() % upto;
	//A[i] = v;// - upto * (v / upto);
	//printf ("Random number: %d\n", v);
	
	//srand(time(NULL));
	//printf ("This compiler can generate random numbers from 0 to %d\n", RAND_MAX);
	}
	write_to_file (number, A, fname);
}

/**
 *	Sukuria faila / raso duomenis i faila
 *	number 	- skaiciu kiekis
 *	*W 		- rodykle i masyva rasymui
 *	*fname 	- failo pavadinimas
 **/
void write_to_file (int number, int *W, char *fname)
{
	FILE *fw = fopen(fname, "wb");
	for (int i = 0; i < number; i++) {
		fwrite(&W[i],sizeof(int),1,fw);
	} 
	fclose(fw);
}

void write_to_file2 (char *fname, char *name, int n, long t, int o)
{
	
	FILE *fw = fopen(fname, "a+");
	//for (int i = 0; i < number; i++) {
		//fwrite(&W[i],sizeof(int),1,fw);
		fprintf(fw, "%s\t%d\t\t%ld\t%d\n", name, n, t, o);
	//} 
	fclose(fw);
}

/**
 *	Nuskaito faila
 *	*R - rodykle i masyva nuskaitymui
 *	*file - failo pavadinimas
 *	number - elementu skaicius
 **/
void read_file_binary (int *R, char *file, int number)
{

	int input,
		i = 0;
	FILE *fr;
	//fr = fopen ( file, "r" );//( "data.txt","r" );
	//for binary files
	fr = fopen ( file, "rb" );
	if( fr == NULL ) printf("NO FILE!!!\n");
	//paieksoti geriau
	else for (i; i < n; i++){//while ( !feof(fr) ) {
			//fscanf(fr, "%d", &(R[i]));
			fread(&(R[i]),sizeof(int),1,fr);
				//if ( R[i] == EOF ) break ;
			printf("%d)\t%d\n",i+1,R[i]);
			//i++;
		}
	//printf("Nuskaityta: %d kartus(-u)\n",i);
	fclose(fr);

}

/**
 *	Nuskaito faila
 *	*file - failo pavadinimas
 *	number - elementu skaicius
 **/
void read_print_binary_file (char *file, int number)
{

	int input;
	//int *R;
	FILE *fr = fopen ( file, "rb" );
	if ( fr == NULL ) { printf("NO FILE!!!\n"); exit(1); }
	else for (int i = 0; i < n; i++){
			fread(&input, sizeof(int), 1, fr);
			printf("%d)\t %d\n", i+1 , input);
		}
	//printf("Nuskaityta: %d kartus(-u)\n",i);
	fclose(fr);

}

/**
 *	Surikiuoja ir sulieja du masyvus i viena
 *	*A - rodykle i (rikiuojama) masyva
 *	a  - masyvo lementu kiekis
 *	*B - rodykle i (rikiuojama) masyva
 *	b  - masyvo lementu kiekis
 *	*C - rodykle i (rezultatu) masyva
 **/
int merge_sort (int *A, int a, int *B, int b, int *C) 
{
	int i = 0,
		j = 0,
		k = 0,
		r = 0;  /* number of inversions */
	
	while (i < a && j < b) {
		if (A[i] <= B[j]) {
			/* copy A[i] to C[k] and move the pointer i and k forward */
			C[k] = A[i];
			i++;
			k++;
		} else {
			/* copy B[j] to C[k] and move the pointer j and k forward */
			C[k] = B[j];

			/* the number of inversions for B[j] is (a-i) */
			r = r + (a - i);  

			j++;
			k++;
		}
	}
	/* move the remaining elements in A into C */
	while (i < a) {
		C[k]= A[i];
		i++;
		k++;
	}
	/* move the remaining elements in B into C */
	while (j < b)  {
		C[k]= B[j];
		j++;
		k++;
	}


	/*while (r < b - pr){
		//A[r] = W[r];
		printf("W [%d] = %d\n",r, W[r]);
		r++;
	}*/
	
	return 0;//r;
}

/**
 *	Skaidom turimus duomenis
 *	*A - rodykle i masyva
 *	n  - pabaigos indeksas
 **/
int divide(int *A, int n) 
{
	int *A1, *A2;
    int i,
		n1, /* Pabaigos */
		n2,
		r1 = 0, /* Veiksmu skaicius */
		r2 = 0,
		r  = 0;

	if (n < 2) return 0;   /* Masyvo rikiuot nereikia */

	/* Skaidymas i 2 masyvus */
	n1 = n / 2;   /* elementu kiekis A1 masyvui */
	n2 = n - n1;  /* elementu kiekis A2 masyvui */
	
	A1 = (int *)malloc(sizeof(int) * n1);
	A2 = (int *)malloc(sizeof(int) * n2);
	
	/* move the first n/2 elements to A1 */
	for (i = 0; i < n1; i++)
		A1[i] = A[i];
	/* move the rest to A2 */
	for (i = 0; i < n2; i++)
		A2[i] = A[i+n1];
	
	/* rekurentinis kvietimas */
	r1 = divide(A1, n1);
	r2 = divide(A2, n2);
	
	/* conquer */
	r = merge_sort(A1, n1, A2, n2, A);
	
	/* Atlaisvinama atmintis */
	free(A1);
	free(A2);
	
	return r1 + r2 + r;
}

/**
 *	Surikiuoja ir sulieja dvi dalis(isskaidymus) i viena
 *	pr	- pirmos dalies pradzios indeksas
 *	pb	- pirmos dalies pabaigos indeksas
 *	pr2	- antros dalies pradzios indeksas
 *	pb2	- antros dalies pabaigos indeksas
 *	*fr	-	rodykle i duomenu faila
 *	*frt-	rodykle i duomenu failo kopija
 **/
int file_merge_sort (int pr, int pb, int pr2, int pb2, FILE *fr, FILE *frt) 
{
	//printf("%d %d %d %d\n", pr, pb, pr2, pb2);
	int i = pr,
		j = pr2,
		k = pr,	/* Pagrindinis */
		r = 0,  /* number of inversions */
		var = 0, /* kintamieji */
		var2 = 0;							operations += 3;
		
#if LIST == 1
	int prev,
		curr = 0,
		next,
		z;
	if (curr != k)
		for (z=0; z<k; z++) {
			fseek(frt,sizeof(int)*z,SEEK_SET);
			fread(&var,sizeof(int),1,frt);
			curr = ftell(frt);
		}
	if (curr == 0) { prev = 0; next = curr+1; }
	else if (curr == n) { prev = curr-1; next = curr; }
	else { prev = curr-1; next = curr+1; }	operations += z*4+6;
#endif

	fseek(frt,sizeof(int)*k,SEEK_SET);		operations += 1;
	while (i < pb && j < pb2) {
	
		/* Nuskaitymas */
#if LIST == 1
	for (z=0; z<i; z++) {
		fseek(fr,sizeof(int)*z,SEEK_SET);
		fread(&var,sizeof(int),1,fr);
		}									operations += z*3+2;
#endif		
		/* 1-os dalies */
		fseek(fr,sizeof(int)*i,SEEK_SET);
        fread(&var,sizeof(int),1,fr);
		//printf("\nvar1 : %d\n", var);

#if LIST == 1
	//if ()
	for (z=0; z<j; z++) {
		fseek(fr,sizeof(int)*z,SEEK_SET);
		fread(&var2,sizeof(int),1,fr);
		}									operations += z*3+2;
#endif		
		/* 2-os dalies */
		fseek(fr,sizeof(int)*j,SEEK_SET);
        fread(&var2,sizeof(int),1,fr);
		//printf("var2 : %d\n\n", var2);
		
											operations += 4;
		//============
		/* Palyginimai ir rasymai */
		if (var <= var2)//if (A[i] <= A[j])
		{
			/* copy A[i] to C[k] and move the pointer i and k forward */
			//W[k] = A[i];			
			fwrite(&var,sizeof(int),1,frt);
			//printf("\nRasom : %d\n", var);
			
			
			/* Pasitikrinam */
			/*fseek(frt,sizeof(int)*k,SEEK_SET);
			int a;
			fread(&a,sizeof(int),1,frt);
			if (a == var)
				printf("Rasymas pavyko!\n\n");
			else { printf("Rasymas nepavyko!\n\n"); break;}*/
			
		
			//moving forward
			i++;							operations += 3;
		}
		else {
			/* copy B[j] to C[k] and move the pointer j and k forward */
			//W[k] = A[j];
			fwrite(&var2,sizeof(int),1,frt);
			//printf("Rasom : %d\n\n", var2);
			
			
			/* Pasitikrinam */
			/*fseek(frt,sizeof(int)*k,SEEK_SET);
			int a;
			fread(&a,sizeof(int),1,frt);
			if (a == var2)
				printf("Rasymas pavyko!\n\n");
			else { printf("Rasymas nepavyko!\n\n"); break;}*/
			
			
			//moving forward
			j++;							operations += 2;
		}
	}
	/* move the remaining elements in A into C */
	while (i < pb) {
		//W[k]= A[i];
#if LIST == 1
	for (z=0; z<i; z++) {
		fseek(fr,sizeof(int)*z,SEEK_SET);
		fread(&var,sizeof(int),1,fr);
		}									operations += z*3+2;
#endif
		fseek(fr,sizeof(int)*i,SEEK_SET);
		fread(&var,sizeof(int),1,fr);
		fwrite(&var,sizeof(int),1,frt);
		//("\nRasom : %d\n", var);
		
		
		/* Pasitikrinam */
		/*fseek(frt,sizeof(int)*k,SEEK_SET);
		int a;
		fread(&a,sizeof(int),1,frt);
		if (a == var)
			printf("Rasymas pavyko!\n\n");
		else { printf("Rasymas nepavyko!\n\n"); break;}*/
		
		//moving forward
		i++;								operations += 5;
	}
	/* move the remaining elements in B into C */
	while (j < pb2)  {
		//W[k]= A[j];
#if LIST == 1
	for (z=0; z<j; z++) {
		fseek(fr,sizeof(int)*z,SEEK_SET);
		fread(&var,sizeof(int),1,fr);
		}									operations += z*3+2;
#endif
		fseek(fr,sizeof(int)*j,SEEK_SET);
		fread(&var2,sizeof(int),1,fr);
		fwrite(&var2,sizeof(int),1,frt);
		//printf("\nRasom : %d\n", var2);
		
		
		/* Pasitikrinam */
		/*fseek(frt,sizeof(int)*k,SEEK_SET);
		int a;
		fread(&a,sizeof(int),1,frt);
		if (a == var2)
			printf("Rasymas pavyko!\n\n");
		else { printf("Rasymas nepavyko!\n\n"); break;}*/
		
		//moving forward
		j++;								operations += 5;
	}
	
	/* Nukopijuojam dalinai surikiuotus duomnis i originala */
	fseek(fr,sizeof(int)*pr,SEEK_SET);
	fseek(frt,sizeof(int)*pr,SEEK_SET);		operations += 2;
	for (int t, k = pr; k<pb2; ++k)
	{
		fread(&t,sizeof(int),1,frt);
		//printf("%d ", t);
		fwrite(&t,sizeof(int),1,fr);
	}										operations += pb2-pr+3;
	//puts("------------");
	return 0;
}

/**
 *	Skaidom turimus duomenis(faila)
 *	s	-	Padzios indeksas
 *	n	-	pabaigos indeksas
 *	*fr	-	rodykle i duomenu faila
 *	*frt-	rodykle i duomenu failo kopija
 **/
int divide_file(int s, int n, FILE *fr, FILE *frt) 
{
    int i = 0,
		st1 = s, /* Pradzios indeksai */
		st2,
		n1, /* Pabaigos indeksai */
		n2;									operations += 1;

	i = n - s;	//Galas - pradzia
	if (i < 2) { 
		return 0;   /* masyvo rikiuot nereikia */
	}										operations += 3;

	/* Skaidymas i 2 dalis */
	n1 = (n + s) / 2;   /*  */
	n2 = n - n1;  /*  */
	
	st2 = n1; /* 2-os dalies pradzios vieta */
	n2 = n;	/* 2-os dalies galas */
											operations += 7;
	/* rekurentinis kvietimas */
	divide_file(st1, n1, fr, frt);
	divide_file(st2, n2, fr, frt);
	
	//r = r + 6;
	/* conquer */
	file_merge_sort(st1, n1, st2, n2, fr, frt);

	return 0;
}


/**
 *	main programos funkcija
 *	kviecia funkcija generevimui,
 *	nuskaitymui, skaidymui(rikiavimui)
 **/
int main( int argc, char *argv[] )
{
/**
 *	kintamieji
 **/
 
	/* Atminties isskyrimas generavimui */
	int *A = (int *)malloc(sizeof(int) * n);
	
	/* Failu vardai */
	char 	org_file[]	= "data.txt",
			org_temp[]	= "data.temp",
			org_bak[]	= "data.bak";
	
	char pav[15];
	//int r = 0; /* Veiksmu skaicius */
/**
 *	Pradedam skaiciuot laika
 **/
	long startas = currentTick();
	
/**
 *	Veiksmai
 **/
 	

/**
 *	Merge_sort'ingas
 **/
	if (GO == "merge")
	{
		printf("\n\tMerge sort dalis\n\n");
		//pav = "Merge sort";
		
		generate (n, z, A, org_file);		//Susigeneruojam duomenis
		
		system("cp data.txt data.temp");		//Pardiniu duomenu kopija
		system("cp data.txt data.bak");			//Pardiniu duomenu kopija
		
		FILE *fr, *frt;
		fr = fopen ( org_file,"rb+" );
		if( fr == NULL ) {
			printf("NO FILE!!!\n");
			exit(1);
		}
		frt = fopen ( org_temp,"rb+" );
		if( frt == NULL ) {
			printf("NO FILE!!!\n");
			exit(1);
		}
		
		read_print_binary_file (org_file, n);
		
		divide_file(0, n, fr, frt);/* pradedamas rikiavimas */
		fclose(fr);
		
		
		printf("\n\tPo rikiavimo\n");
		read_print_binary_file (org_file, n);
		printf("\nVeiksmu skaicius: %d\n", operations);
	}
/**
 *	Heap_sort'ingas
 **/
	else if (GO == "heap")
	{	
		printf("\n\tHeap sort dalis\n\n");
		//pav = "Heap sort";
		
		generate (n, z, A, org_file);		//Susigeneruojam duomenis
			
		system("cp data.txt data.temp");		//Pardiniu duomenu kopija
		system("cp data.txt data.bak");			//Pardiniu duomenu kopija
		
		FILE *fr, *frt;
		fr = fopen ( org_file,"rb+" );
		if( fr == NULL ) {
			printf("NO FILE!!!\n");
			exit(1);
		}
		frt = fopen ( org_temp,"rb+" );
		if( frt == NULL ) {
			printf("NO FILE!!!\n");
			exit(1);
		}
		
		read_print_binary_file (org_file, n);
	
	//generate (n, z, A, "data.txt");
	//system("cp data.txt temp");
	/*FILE *fr, *frt;
	fr = fopen ( "data.txt","rb+" );
	if( fr == NULL ) {
		printf("NO FILE!!!\n");
		exit(1);
	}
	frt = fopen ( "temp","rb+" );
	if( frt == NULL ) {
		printf("NO FILE!!!\n");
		exit(1);
	}*/

	//read_file_binary (A, "data.txt", n);
	
	//r = divide2(r, n, fr, frt);/* pradedamas rusiavimas */
	//fclose(fr);
	
	
	//printf("\nPo\n");
	//read_file_binary (A, "data.txt", n);
	
	}
/**
 *	Bucket_sort'ingas
 **/
	else if (GO == "bucket")
	{
	
		printf("\n\tBucket sort dalis\n\n");
		
		generate (n, z, A, org_file);		//Susigeneruojam duomenis
			
		system("cp data.txt data.temp");		//Pardiniu duomenu kopija
		system("cp data.txt data.bak");			//Pardiniu duomenu kopija
		
		FILE *fr, *frt;
		fr = fopen ( org_file,"rb+" );
		if( fr == NULL ) {
			printf("NO FILE!!!\n");
			exit(1);
		}
		frt = fopen ( org_temp,"rb+" );
		if( frt == NULL ) {
			printf("NO FILE!!!\n");
			exit(1);
		}
		
		read_print_binary_file (org_file, n);
		
	}
	else if (GO == "generate&print")
	{
		printf("\n\tGenerate & print dalis\n\n");
		
		generate (n, z, A, org_file);		//Susigeneruojam duomenis
		printf("\nSugeneruoti duomenys faile %s\n", org_file);
		read_print_binary_file (org_file, n);
	}
/**
 *	Veiksmu pabaiga
 **/
	
	/* Sustabdom laika */
	long endas = currentTick();
/**
 *	Veikimo laikas	
 **/
	printf("\n\tTime: %ld msec\n", endas-startas);
	
	time_t mytime;
	mytime = time(NULL);
	write_to_file2 ("log.txt", "Merge", n, endas-startas, operations);
	//printf("%s\n", ctime(&mytime));

/**
 *	Atminties atlaisvinimas
 **/
	free(A);
	return 0;
}