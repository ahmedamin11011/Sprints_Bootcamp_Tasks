#include"Payment_Sys.h"

ST_transaction Transaction;

 u8_t Max_amount=0;
 u8_t Account_check=0;
 u8_t Terminal_check=0;
 u8_t Expiration=0;
 u8_t Refrence_Number = 0;
 u8_t transactions = 0;

int main(void)
{
   u8_t User_choice=0;
	do
	{
		fillCardData(&Transaction);
		fillTerminalData(&Transaction);
		saveTransactionIntoServer(&Transaction);
		printf("Do you want to continue (y/n)?:\n");
		scanf(" %c",&User_choice);
	} while (User_choice == 'y');
return 0;
}
