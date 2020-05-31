#ifndef PAYMENT_SYS_H
#define PAYMENT_SYS_H


/*- INCLUDES -----------------------------------------------*/
#include <stdio.h>
#include <string.h>

/*- New Types -----------------------------------------------*/
typedef unsigned char u8_t;


/*- ENUMS --------------------------------------------------*/
/*Enum that represents the status of the transaction (APPROVED, or DECLINED)*/
typedef enum EN_transStat
{
	DECLINED,APPROVED
}EN_transStat;



/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct ST_cardData
{
	unsigned char cardHolderName[25];
	unsigned char primaryAccountNumber[19];
	unsigned char cardExpirationDate[6];
}ST_cardData;

typedef struct ST_serverData
{
	EN_transStat transactionStatus;
	unsigned int receiptReferenceNumber;
}ST_serverData;

typedef struct ST_terminalData
{
	unsigned char transAmount[8];
	unsigned char maxTransAmount[8];
	unsigned char transactionDate[11];
}ST_terminalData;

typedef struct ST_transaction
{
	ST_cardData cardHolderData;
	ST_terminalData transData;
	ST_serverData transResponse;
}ST_transaction;

typedef struct ST_accountBalance
{
	unsigned char primaryAccountNumber[19];
	unsigned char balance[8];
}ST_accountBalance;



/*- FUNCTION DECLARATIONS ----------------------------------*/
void fillCardData(ST_transaction *transaction);
void checkAmount(ST_transaction *transaction);
void fillTerminalData(ST_transaction *transaction);
void checkExpiryDate(ST_transaction *transaction);
void saveTransactionIntoServer(ST_transaction *transaction);
void checkBalance(ST_transaction *transaction);


#endif
