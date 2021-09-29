#include<stdio.h> 
#include<math.h>
#include<stdlib.h>

// Harming Code:

void receiver(){
    // Receiver Code:
    int rCodewordSize;
    printf("Enter Codeword Size: ");
    scanf("%d",&rCodewordSize);
    printf("\n");
    int rArray[rCodewordSize];
    printf("Enter Codeword: ");
    for(int i = 1; i <= rCodewordSize ; i++ ){
        scanf("%d",&rArray[i]);
    }

    int rIntLCovt = 0;
    int rRedundantSize[10];
    int j = 0;
    for(float l = 0; l < rCodewordSize;l++){
        int powAns = pow(2.0,l);
        if (powAns <= rCodewordSize){
            rRedundantSize[j] = powAns;
            j++;
        }
        else{
            rIntLCovt = l;
            break;
        }
    }

    int h = 1;
    int rNewReverseArray[rCodewordSize];
    for(int i = rCodewordSize ; i >= 1 ; i-- ){
        rNewReverseArray[i] = rArray[h];
        h++;
    }

    // Find value of every bit:
    int sum = 0;
    int newBitOneArraySize = (rCodewordSize / 2) + 1;
    int newBitOneArray[rIntLCovt];
    int rNewArray[newBitOneArraySize];
    int p = 0;
    for(j=0; j < rIntLCovt; j++){
        int i,count = 0;
        i = rRedundantSize[j];
        int tempI = i;
    
        while(i <= rCodewordSize){
            for(int j = i; j <= rCodewordSize; j++){
               if(count==tempI){
                    count = 0;
                    j += (tempI);
                    i = j;
                    break;
                }
                else{    
    
                    sum = sum + rNewReverseArray[j];
                    count++;    
                    i++;
                }
            }
        }

        newBitOneArray[p] = sum;
        p++;
        sum = 0;
    }


    int binaryBits[rIntLCovt];
    for(int i = 0; i <=rIntLCovt; i++){
        if(newBitOneArray[i] % 2 == 0){
            binaryBits[i] = 0;
        }
        else{
            binaryBits[i] = 1;
        }
    }
    
    
    
    // Error Checking::
    int errorSum = 0;
    int decimalCount = 0;
    for(int i = 0; i < rIntLCovt;i++){
        errorSum += newBitOneArray[i];
    }
    if(errorSum % 2 == 0){
        printf("\nStatus: Successfully Received\n");
        return;
    }
    else{
        printf("\nStatus: Message Currupted\n");
        int i = 0;
        int powerI;
        while (i < 4){
            if(binaryBits[i] == 1){
                powerI = pow(2.0,i);
                int intPowerI = powerI;
                decimalCount += intPowerI;
            }
            i++;
        }
    }
    printf("\nError Bit Position: %d\n",decimalCount);

    int reachDecimalCountPosition = (rCodewordSize - decimalCount) + 1;
    for(int i = 1; i<=rCodewordSize;i++){
        if(i == reachDecimalCountPosition){
            if(rArray[i] == 0){
                rArray[i] = 1;
            }
            else{
                rArray[i] = 0;
            }
        }
    }
    printf("\nOriginal Codeword: ");
    for(int i = 1; i <= rCodewordSize ; i++ ){
        printf("%d",rArray[i]);
    }
    printf("\n");
}

void sender(){
    int graterPartAns;
    int powAns;
    int totalBits;
    printf("How Many Bits You Have: ");
    scanf("%d",&totalBits);
    printf("\n");

    int arrTB[totalBits];
    printf("Enter Bits You Have: ");
    for(int i = 0; i<totalBits;i++){
        scanf("%d",&arrTB[i]);
    }    
    printf("\n");

    int totalKeyWordsBits = 0;
    int intICovt = 0;
    int aS[10];
    int j = 0;
    for(float l = 0; l <= totalBits;l++){
        graterPartAns = totalBits + l + 1;
        powAns = pow(2.0,l);
        if (powAns >= graterPartAns){
            intICovt = l;
            totalKeyWordsBits = totalBits + intICovt;
            break;
        }
        else{
            aS[j] = powAns;
            j++;
        }
    }

    int countAnswerIs = 0;
    int h = 0;
    int newArray[totalKeyWordsBits];
    for(int i = totalKeyWordsBits ; i >= 1 ;i-- ){
        for(j=0;j<intICovt;j++){
            if(i==aS[j]){
                newArray[i] = 0;
                break;
            }
            else{
                countAnswerIs += 1;
            }
        }
        if(countAnswerIs == intICovt){
            newArray[i] = arrTB[h];
            h++;
        }
        countAnswerIs = 0;
    }

    int sum = 0;
    int newBitOneArraySize = (totalKeyWordsBits / 2) + 1;
    int newBitOneArray[intICovt];
    int p = 0;
    for(j=0;j<intICovt;j++){
        int i,count = 0;
        i = aS[j];
        int tempI = i;
        while(i <= totalKeyWordsBits){
            for(int j = i; j <= totalKeyWordsBits; j++){
               if(count==tempI){
                    count = 0;
                    j += (tempI);
                    i = j;
                    break;
                }
                else{    
                    sum = sum + newArray[j];
                    count++;    
                    i++;
                }
            }
        }
        newBitOneArray[p] = sum;
        p++;
        sum = 0;
    }

    int binaryAns[intICovt];

    int ans = 0; 
    for(int i = 0; i < intICovt;i++){
        if(newBitOneArray[i] % 2 == 0){
            binaryAns[i] = 0;
        }
        else{
            binaryAns[i] = 1;
        }
    }

    for(int i = 1,j = 0 ; i <= totalKeyWordsBits ;i++ ){
        if(i == aS[j]){
            newArray[i] = binaryAns[j];
            j++;
        }
    }


    int f = 1;
    int newReverseArray[totalKeyWordsBits];
    for(int i = totalKeyWordsBits ; i >= 1 ;i-- ){
        newReverseArray[i] = newArray[f];
        f++;
    }

    printf("Your CodeWord:\t");
    for(int i = 1 ; i <= totalKeyWordsBits ;i++ ){
        printf("%d",newReverseArray[i]);
    }
    printf("\n");
}

int main(){
    printf("\n");
    printf("\n********************************************************************************\n");
    printf("|| Welcome To Harming Code Generator || Developed By : Apurv Patel ||\n\n");
    int uSide;
    printf("Which side you want to go? 1 -> Sender side 2 -> Receiver Side :");
    scanf("%d",&uSide);
    printf("\n");
    if(uSide == 1){
        sender();
    }
    else if(uSide == 2){
        receiver();
    }
    else{
        printf("!!!!Please Enter Proper Value!!!!");
    }
    printf("\n|| Thanks For Choosing Us ||\n");
    printf("\n********************************************************************************\n");    
    return 0;
}