#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<assert.h>

FILE *in;
FILE *out;
FILE *sortie;
int e;
char c;
int i=0;
int d;


void normaliserFichier(FILE *in, FILE* out){
    e=fscanf(in,"%c",&c);     
    while(e!=EOF)
    {
        if(c>='a' && c<='z')
        	{

        		fprintf(out,"%c",c);
        		
        	}
        else if(c>='A' && c<='Z')
        {
           c = c + 'a' - 'A';
           fprintf(out,"%c",c);
        
        }
         
        e=fscanf(in,"%c",&c);
        
    }
    
}




char prochaineLettre(FILE* in)
{
	int c;
	char l;
	if(in!=NULL)
	{
		c=fscanf(in,"%c",&l);
	    	while(c!=EOF)
	    	{
			if((l>='a' && l<='z')||(l>='A' && l<='Z'))
			{
				return l;
			}
			c=fscanf(in,"%c",&l);
			
			}
	}
	else
	{
		 return EXIT_FAILURE;
	}
	return EOF;
}


char lettreLaPlusFrequente(FILE* in)
{
	int occ=0,i;
	int tab[26]={0};
	char l;

	do{
		l=prochaineLettre(in);
		if(l>='A' && l<='Z'){
			tab[l-'A']++;
		}
		if(l>='a' && l<='z'){
			tab[l-'a']++;
		}
		
	}while(l!=EOF);
	for(i=0;i<26;i++){
		if(tab[i]>tab[occ]){
			occ=i;
		}		
	}
	return 'a'+occ;
}

void decouperFichier(FILE *in, FILE *out, int longueur, int d){
    char c;
    int e;
    
    fseek(in,d,SEEK_SET);
    e=fscanf(in,"%c",&c);
         
    while(e!=EOF)
    { 
      fprintf(out,"%c",c);
      fseek(in,longueur-1,SEEK_CUR);
      e=fscanf(in,"%c",&c);
    }
    
}







char* recuperer_mdp(FILE *in,FILE *out,int l){
    char *mdp=malloc((l+1)*sizeof(char));
    char lf;
    FILE *k,*tmp;
    k=fopen("test.txt","w+");
    rewind(in);
    normaliserFichier(in,k);
    rewind(k);
    
    for(int i=0;i<l;i++)
    {   tmp=fopen("tmp.txt","w+");
 	    decouperFichier(k,tmp,l,i);
 	    rewind(k);
 	    rewind(tmp);
 	    lf=lettreLaPlusFrequente(tmp);
 	    fclose(tmp);
        mdp[i]=((lf-'e'+26)%26)+'a';
     }
        mdp[l]='\0';
        
        return mdp;
  }
        



double IndiceCoincidence(FILE *in){

	FILE *k;
	double s=0;
	double f;
	k=fopen("test.txt","w+");
	int t[26]={0};
	char l;
	double h;
	normaliserFichier(in,k);
	fseek(k,0,SEEK_SET);
	
	while(l!=EOF)
	{   l=prochaineLettre(k);
	
		if(l>='a' && l<='z')
		{
			t[l-'a']++;
			h++;
		}
	}
    
    
	for(int i=0;i<26;i++)
	{
		s=s+(t[i]*(t[i]-1));
	}
	
	f=s/(h*(h-1));
	fclose(k);
	return f;
}




int longueurMotPasseVigenere(FILE *in){
	int j=1;
	int compt=0;
	double m;
	FILE *g;
	g=fopen("montxt.txt","w+");
	normaliserFichier(in,g);
	do
	{  
		FILE *tmp;
	    	tmp=fopen("tst.txt","w+");
		decouperFichier(g,tmp,j,0);
		fclose(tmp);
		tmp=fopen("tst.txt","rb");
		m=IndiceCoincidence(tmp);
		printf("ic=%lf",m);
		j++;
		compt++;
		fclose(tmp);
	} while(m<0.07 ); 
	
		printf("la longuer du mot de passe est:%d",compt);
	return compt; 	
}


void decrypter(FILE *in, FILE *out,int var){
        char r;
        int j=0;
        char *mdp=recuperer_mdp(in,out,var);
        printf("%s",mdp);
        rewind(in);
		e=fscanf(in,"%c",&r);
		while(e!=EOF){
        
			if(r>='a'&& r<='z')
		{
			r=(r-'a'-mdp[j%var]+'a'+26)%26+'a';
			fputc(r,out);
			j++;
		}
	else if(r>='A'&& r<='Z')
		{
			r=(r-'A'-mdp[j%var]+'a'+26)%26+'Z';
			fputc(r,out);
			
		        j++;
		}
	
	else
	{
		fputc(r,out);
	}
	
	e=fscanf(in,"%c",&r);
			
	}
	
}



int main(int argc,char *argv[])
{
	in=fopen(argv[1],"r"); 
	out=fopen(argv[2],"w");
	if(in==NULL)
	{ 
	    printf("votre fichier n existe pas");
	    return EXIT_FAILURE;
	}
	int lgt=longueurMotPasseVigenere(in);
	decrypter(in,out,lgt);
	fclose(in);
	fclose(out);
	return 0;
}





