#include<stdio.h>

typedef struct account{
    int accnum;
    char nm[25];
    float balance;
    int state;
}acc;

acc ac;
FILE *fa;

void input(int no)
{
    ac.accnum=no;
    printf("\nName: ");
    scanf("%s",ac.nm);
    do{
        printf("\nBalance: ");
        scanf("%f",&ac.balance);
    }while(ac.balance<0.0);
 
    ac.state=1;
}


int search(int no)
{
    int pos=0;
    rewind(fa);
    while(1)
    {
        fread(&ac,sizeof(ac),1,fa);
        if(feof(fa))
        {
            pos=-1;
            break;

        }
        if(ac.accnum==no)
            break;
        pos=ftell(fa);    
    }

    return pos;
}


void createAccount(){
    int no;
    printf("\nEnter Account No: ");
    scanf("%d",&no);
    if(search(no)>=0){
            printf("\nAccount Already Exists!");
            return;
    } 
    input(no);
    fseek(fa,0,SEEK_END);
    fwrite(&ac,sizeof(ac),1,fa);
    printf("\nAccount Created Successfully!\n\n");
    return;
}

void deposit()
{
    int no,pos;
    float amt;
    printf("\nEnter Account No: ");
    scanf("%d",&no);
    pos=search(no);
    if(pos>=0){
        printf("\nAmount to Deposit: ");
        scanf("%f",&amt);
        ac.balance+=amt;
        fseek(fa,pos,SEEK_SET);
        fwrite(&ac,sizeof(ac),1,fa);
    }
    printf("\nName: %s\n",ac.nm);
    printf("\nNew Balance: %6.2f\n\n",ac.balance);
    return;


}

void withdraw()
{
    int no,pos;
    float amt;
    printf("\nEnter Account No: ");
    scanf("%d",&no);
    pos=search(no);
    fseek(fa,pos,SEEK_SET);
    fread(&ac,sizeof(ac),1,fa);
    if(pos>=0){
        printf("\nAmount to Withdraw: ");
        scanf("%f",&amt);
        if(amt>ac.balance)
            printf("\nInsufficient Balance");
        else{
            ac.balance-=amt;
            fseek(fa,pos,SEEK_SET);
            fwrite(&ac,sizeof(ac),1,fa);
            printf("\nName: %s",ac.nm);
            printf("\nAmount Withdrawn: %6.2f\n",amt);
            printf("\nNew Balance: %6.2f\n\n",ac.balance);
    }
    return;
}
}

void balanceenquiry()
{
    int no,pos;
    printf("\nEnter Account No: ");
    scanf("%d",&no);
    pos=search(no);
    if(pos>=0)
    {
        fseek(fa,pos,SEEK_SET);
        fread(&ac,sizeof(ac),1,fa);
        printf("\nName: %s\n",ac.nm);
        printf("\nBalance: %6.2f\n\n",ac.balance);
    }
    return;
}


void main()
{
    int opt;
    fa=fopen("account.dat","r+b");
    if(fa==NULL)
    {
        fa=fopen("account.dat","w+b");
        fclose(fa);
        fa=fopen("account.dat","r+b");
    }

    while(1)
    {
        printf("\nWELCOME TO BANKING SYSTEM");
        printf("\n1.Create Account\n2.Deposit\n3.Withdraw\n4.Balance Enquiry\n5.Exit\n\nSelect Option: ");
        scanf("%d",&opt);
        if(opt>=5)
            break;
        switch(opt)
        {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                balanceenquiry();
                break;
        }
    }
    fclose(fa);
    return;
    

}