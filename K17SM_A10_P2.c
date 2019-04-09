#include<stdio.h>
#include<math.h>
#include<conio.h>
int main()
{
	double PFnotModified, PFModified, MAT, Modifiedper, EAT,PFR;
	char ch = 'y';
	while(ch =='y' || ch =='Y'){
	printf("Enter the time for Page Fault not modified in milliseconds: ");
	scanf("%lf",&PFnotModified);
	PFnotModified *=pow(10,-3);
	printf("Enter the time for Page Fault modified in milliseconds: ");
	scanf("%lf",&PFModified); 
	PFModified *=pow(10,-3);
	printf("Enter the time for Memory Access in nano seconds: ");
	scanf("%lf",&MAT);
	MAT *=pow(10,-9); 
	printf("Enter the modified percentage: ");
	scanf("%lf",&Modifiedper);
	Modifiedper = Modifiedper/100;
	printf("Enter the time for Efficiency Access in nano seconds: ");
	scanf("%lf",&EAT);
	EAT *=pow(10,-9); 
	printf("PAGE FAULT RATE: ");
	PFR = (EAT-MAT)/(Modifiedper*PFModified + (1-Modifiedper)*PFnotModified - MAT);
	printf("%lf",PFR);
	printf("\nplease enter Y/y to calculate again: " );
	scanf("%c",&ch);
	}
	getch();
}
