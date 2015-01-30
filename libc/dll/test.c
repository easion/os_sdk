
#if 0
int printUPPERCASE ( inLine ) 
char inLine[]; 
{ 
char UPstring[256]; 
char *inptr, *outptr; 

inptr = inLine; 
outptr = UPstring; 
while ( *inptr != '\0' ) 
*outptr++ = toupper(*inptr++); 
*outptr++ = '\0'; 
printf(UPstring); 
return(1); 
} 
#endif

void test_2()
{
	printf("hello\n");
}

