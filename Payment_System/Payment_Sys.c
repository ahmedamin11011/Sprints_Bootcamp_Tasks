/*- INCLUDES -----------------------------------------------*/
#include "Payment_Sys.h"

/*Global Flags*/
extern u8_t Max_amount;
extern u8_t Account_check;
extern u8_t Terminal_check;
extern u8_t Expiration;
extern u8_t Refrence_Number;
extern u8_t transactions;


/* Global Arrays --------> Transactions array------and ------array of structures for [primary account number , balance] */
ST_transaction Total_Transactions[255] = {0};

/* Number of accounts : [Primary_Account_Number , Balance]*/
ST_accountBalance Accounts[10] = {{"123456789","0100.00"},
								  {"234567891","6000.00"},
								  {"567891234","3250.25"},
								  {"456789123","1500.12"},
								  {"258649173","0500.00"},
								  {"654823719","2100.00"},
								  {"971362485","0000.00"},
								  {"793148625","0001.00"},
								  {"123123456","0010.12"},
								  {"456789321","0000.55"}};






/*****************************************************************************************************/
/******Function Name: fillCardData
*******Function parameter: pointer to structure
*******Function Description: /*It fills the card data structure into the ST_transaction structure.*/
void fillCardData(ST_transaction *transaction)
{
    printf("Please Enter Card Data:\n");
    printf("Please Enter the Card Holder Name:\n");
    scanf("%s",transaction -> cardHolderData.cardHolderName);
    printf("Please Enter the Primary Account Number:\n");
    scanf("%s",transaction -> cardHolderData.primaryAccountNumber);
    printf("Please card Expiry Date:\n");
    scanf("%s",transaction -> cardHolderData.cardExpirationDate);
    Refrence_Number++;
}




/******************************************************************************************************************/
/******Function Name: checkAmount
*******Function parameter: pointer to structure
*******Function Description: It reads the amount.
It checks if the amount > maximum transaction Amount (5000.00)
Then it saves the response as DECLINED and prints ”The transaction is DECLINED”
Else do nothing.*/
void checkAmount(ST_transaction *transaction)
{
    strcpy(transaction -> transData.maxTransAmount , "5000.00");

    for(u8_t i = 0 ; i < 10 ; i++)
    {
        if( (transaction -> transData.transAmount[i] - '0') < (transaction -> transData.maxTransAmount[i] - '0') )
        {
            break;
        }
        else if ((transaction -> transData.transAmount[i] - '0') > (transaction -> transData.maxTransAmount[i] - '0') )
        {
            Max_amount = 1;
            transaction ->transResponse.transactionStatus = DECLINED;
            transaction ->transResponse.receiptReferenceNumber = Refrence_Number;
            printf("Transaction is DECLINED!\n");
            return ;
        }

    }
     Max_amount = 0;

}



/******************************************************************************************************************/
/******Function Name: fillTerminalData
*******Function parameter: pointer to structure
*******Function Description: It fills the transaction amount, maximum transaction amount
and expiry date in the ST_transaction structure.
*/
void fillTerminalData(ST_transaction *transaction)
{
    printf("Please Enter Terminal Data:\n");
    printf("Please Enter the transaction Amount:\n");
    scanf("%s",transaction -> transData.transAmount);

    checkAmount(transaction);

    if(Max_amount)
    {
        Terminal_check = 1;
        return;
    }
    else
    {
        printf("Please Enter Transaction Date:\n");
        scanf("%s",transaction -> transData.transactionDate);
    }
    Terminal_check = 0;
}



/******************************************************************************************************************/
/******Function Name: checkExpiryDate
*******Function parameter: pointer to structure
*******Function Description: Reads the expiry and transaction dates from the transaction structure.
It checks if the expiry date > than transaction date
Then saves the response as DECLINED and prints ”The transaction is DECLINED”
Else do nothing.
*/
void checkExpiryDate(ST_transaction *transaction)
{
    /*Transaction date  : DD/MM/YYYY*/
   u8_t Month_transaction_date = (transaction -> transData.transactionDate[3] - '0') * 10 + ((transaction -> transData).transactionDate[4] - '0');
    u8_t Year_transaction_date  = (transaction -> transData.transactionDate[8] - '0') * 10 + ((transaction -> transData).transactionDate[9] - '0');

    /*Expiration date  : MM/YY*/
   u8_t Month_expiration_date = (transaction -> cardHolderData.cardExpirationDate[0] - '0') * 10 + ((transaction -> cardHolderData).cardExpirationDate[1] - '0');
    u8_t Year_expiration_date  = (transaction -> cardHolderData.cardExpirationDate[3] - '0') * 10 + ((transaction -> cardHolderData).cardExpirationDate[4] - '0');

    if(Year_transaction_date > Year_expiration_date)
    {
        Expiration = 1;
        transaction ->transResponse.transactionStatus = DECLINED;
        printf("Transaction is DECLINED!\n");

        return;
    }
    else if(Month_transaction_date > Month_expiration_date)
    {
         Expiration = 1;
        transaction ->transResponse.transactionStatus = DECLINED;
        printf("Transaction is DECLINED!\n");

       return;
    }
    else
    {
        Expiration = 0;
    }

}



/******************************************************************************************************************/
/******Function Name: saveTransactionIntoServer
*******Function parameter: pointer to structure
*******Function Description: It checks for the expiry date.It checks for balance.
Saves the transaction data into the server array.
*/

void saveTransactionIntoServer(ST_transaction *transaction)
{
    if(Terminal_check)
    {
        Total_Transactions[transactions++] = *transaction;
        return;
    }

    checkExpiryDate(transaction);

    if(Expiration)
    {
         Total_Transactions[transactions++] = *transaction;
         return;
    }
    else
    {
        checkBalance(transaction);

        if(Account_check)
        {
           Total_Transactions[transactions++] = *transaction;
           return;
        }

    }
    Total_Transactions[transactions++] = *transaction;
}



/******************************************************************************************************************/
/******Function Name: checkBalance
*******Function parameter: pointer to structure
*******Function Description: It reads the primary account number from the transaction structure.
It searches for the primary account number into the account/balance array.
Then saves the response as DECLINED  Else it checks if the transaction amount > account balance
Then saves the response as DECLINED and print Else saves the response as APPROVED and print ”The transaction is APPROVED”
*/
void checkBalance(ST_transaction *transaction)
{
    for(u8_t i = 0 ; i < 10 ; i++)
    {
        if(strcmp(transaction -> cardHolderData.primaryAccountNumber , Accounts[i].primaryAccountNumber) == 0)
        {
            for(u8_t i = 0 ; i < 8 ; i++)
            {
                if( ((transaction ->transData).transAmount[i] - '0') < (Accounts[i].balance[i] - '0') )
                {
                    break;
                }
                else if ( (transaction ->transData.transAmount[i] - '0') > (Accounts[i].balance[i] - '0') )
                {
                     Account_check= 1;
                    (transaction ->transResponse).transactionStatus = DECLINED;
                    printf("The transaction is DECLINED\n");
                    return;
                }


            }
             Account_check = 0;
            transaction ->transResponse.transactionStatus = APPROVED;
            printf("The transaction is APPROVED\n");
            return;

        }

    }
    Account_check = 1;
    transaction ->transResponse.transactionStatus = DECLINED;
    printf("The transaction is DECLINED\n");


}
