#include<stdio.h> 
#include<math.h>


int main(){
    int uType;
    int uPartSize;
    printf("---------------------------------------------------------------------------\n\n");
    printf("\t|||Welcome to parityEncryption Software||| Developed By: Apurv Patel \n");
    printf("---------------------------------------------------------------------------\n");
    printf("\nPlease Enter Your Type: 1 -> Sender 2 -> Receiver\n");
    scanf("%d",&uType);
    
    if(uType != 1 && uType != 2){
        printf("\nPlease Enter Proper Type!!!!\n");
        return 0;
    }
    if(uType == 1){
        printf("\nThat's Grate! You are sender...\n\n");
        // printf("---------------------------------------------------------------------------\n");
        int totalDigits,k=0;
        printf("\nEnter How Many Digits You Have:\n");
        scanf("%d",&totalDigits);
        int uMessage[totalDigits];
        printf("\nEnter partition size:\n");
        scanf("%d",&uPartSize);
        printf("\nPlease enter your message in binary form:\n");
        for(int i = 0; i < totalDigits;i++){
            scanf("%d",&uMessage[i]);
        }

        float size = sizeof(uMessage) / sizeof(uMessage[0]);
        int row = ceil(size / uPartSize);
        int u2DMessage[row][uPartSize];
        // printf("Size: %f\n",size);
        // printf("Row: %d\n",row);


        int count = 0;
        for(int i = 0;i < row; i++){
            for (int j = 0; j < uPartSize; j++ ){
                count++;
                if(size < count){
                    u2DMessage[i][j] = 0;
                }
                else{
                    u2DMessage[i][j] = uMessage[k];
                    k++;
                }
            }
        }
        // printf("2D Array:\n");
        // for(int i = 0;i < row; i++){
        //     for (int j = 0; j < uPartSize; j++ ){
        //         printf("%d",u2DMessage[i][j]);
        //     }
        //     printf("\n");
        // }

		// Note: This Is Row Array: 
        int columnArray[row];
        int columnSum = 0;
        for(int i = 0;i < row; i++){
            for (int j = 0; j < uPartSize; j++ ){
                columnSum = columnSum + u2DMessage[i][j];
                if(columnSum % 2 == 0){
                    columnArray[i] = 0;
                }
                else{
                    columnArray[i] = 1;
                }
            }
            columnSum = 0;
        }
		
		// This Is Column Array:
        int rowSum = 0;
        int rowArray[uPartSize];
        for(int i = 0;i < uPartSize; i++){
            for (int j = 0; j < row; j++ ){
                rowSum = rowSum + u2DMessage[j][i];
                if(rowSum % 2 == 0){
                    rowArray[i] = 0;
                }
                else{
                    rowArray[i] = 1;
                }
            }
            rowSum = 0;
        }
        // printf("Row Array is:\n");
        // for(int i =0 ; i < uPartSize;i++){
        //     printf("%d",rowArray[i]);
        // }
        // printf("\n");
        // printf("Completed....\n");

        int parityStramSum = 0;
        int parityStreamSize = uPartSize + 1;
        int parityStreamRowSize = uPartSize;
        int parityStream[parityStreamSize];
        for(int i = 0; i < parityStreamRowSize ;i++){
            parityStramSum = parityStramSum + rowArray[i];
            parityStream[i] = rowArray[i];
        }
        //int par = parityStreamSize - 1;
        if(parityStramSum % 2 == 0 ){
            parityStream[parityStreamRowSize] = 0;
        }
        else{
            parityStream[parityStreamRowSize] = 1;
        }

        // for(int i = 0; i < parityStreamSize ;i++){
        //     printf("%d",parityStream[i]);
        // }
        // printf("\n");
        
        int receiverStramSize  = totalDigits + parityStreamSize;
        int receiverStream[receiverStramSize];
        for(int i = 0; i < totalDigits; i++ ){
            receiverStream[i] = uMessage[i];
        }
        for(int j = totalDigits,i = 0 ; j < receiverStramSize && i < parityStreamSize; j++,i++){
            receiverStream[j] = parityStream[i];
        }
        printf("---------------------------------------------------------------------------\n");
        printf("\nNote: The Parity Stream Was Considered As Row And Its Even Parity\n \n");
        // printf("***************************************************************************\n");
        printf("\nYour Original Message Was:");
        for(int i = 0; i < totalDigits;i++){
            printf(" %d",uMessage[i]);
        }
        printf("\n \n");
        // printf("***************************************************************************\n");
        printf("\nCodeWord Is:");
        for(int i = 0; i < receiverStramSize;i++){
            printf(" %d",receiverStream[i]);
        }
        printf("\n \n");
    }
    else{
        printf("\nThat's Greate! You are receiver...\n");
        int totalCodeWordBits,totalParirtyBits;
        printf("\nHow Many Bits In Your CodeWord:\n");
        scanf("%d",&totalCodeWordBits);
        int codeWord[totalCodeWordBits];
        printf("\nEnter Your CodeWord: \n");
        for(int i = 0; i < totalCodeWordBits;i++){
            scanf("%d",&codeWord[i]);
        }
		int rPartitionSize;
        printf("\nEnter Partision Size:\n");
        scanf("%d",&rPartitionSize);
		totalParirtyBits = rPartitionSize;
		totalParirtyBits++;
		
        int receiverParityBit[totalParirtyBits];
        int totalRemainingBits = totalCodeWordBits - totalParirtyBits;
        int receivedStream[totalRemainingBits];
        for(int i = 0,j = 0; i < totalCodeWordBits;i++){
            if(i < totalRemainingBits){
                receivedStream[i] = codeWord[i];
            }
            else{
                receiverParityBit[j] = codeWord[i];
                j++;
            }
        }

        // printf("Receivered Stream:\n");
        // for(int i = 0; i < totalRemainingBits; i++){
        //     printf("%d",receivedStream[i]);
        // }
        // printf("Parity Bits:\n");
        // for(int i = 0; i < totalParirtyBits; i++){
        //     printf("%d",receiverParityBit[i]);
        // }
        int receiverPartSize = totalParirtyBits - 1;
        // printf("Enter partition size:\n");
        // scanf("%d",&receiverPartSize);

        float codeSize = sizeof(receivedStream) / sizeof(receivedStream[0]);
        int codeRow = ceil(codeSize / receiverPartSize);
        int u2DCode[codeRow][receiverPartSize];
        // printf("Size: %f\n",codeSize);
        // printf("Row: %d\n",codeRow);

        int rCount = 0,m = 0;
        for(int i = 0;i < codeRow; i++){
            for (int j = 0; j < receiverPartSize; j++ ){
                rCount++;
                if(codeSize < rCount){
                    u2DCode[i][j] = 0;
                }
                else{
                    u2DCode[i][j] = receivedStream[m];
                    m++;
                }
            }
        }

        // Column Array:
        int rRowSum = 0;
        int rRowArray[receiverPartSize];
        for(int i = 0;i < receiverPartSize; i++){
            for (int j = 0; j < codeRow; j++ ){
                rRowSum = rRowSum + u2DCode[j][i];
                if(rRowSum % 2 == 0){
                    rRowArray[i] = 0;
                }
                else{
                    rRowArray[i] = 1;
                }
            }
            rRowSum = 0;
        }

        int rParityStramSum = 0;
        int rParityStreamSize = receiverPartSize + 1;
        int rParityStreamRowSize = receiverPartSize;
        int rParityStream[rParityStreamSize];
        for(int i = 0; i < rParityStreamRowSize ;i++){
            rParityStramSum = rParityStramSum + rRowArray[i];
            rParityStream[i] = rRowArray[i];
        }
        if(rParityStramSum % 2 == 0 ){
            rParityStream[rParityStreamRowSize] = 0;
        }
        else{
            rParityStream[rParityStreamRowSize] = 1;
        }
        printf("---------------------------------------------------------------------------\n");
        int statusCount = 0;
        for(int i = 0; i < rParityStreamSize ; i++){
            if(rParityStream[i] != receiverParityBit[i]){
                statusCount = 1;
                printf("\nStatus: Your Message Was Received With Error!!!!\n");
                break;
            }
        }
        if(statusCount == 0){
            printf("\nStatus: Your Message Was Successfully Received....\n");
        }
        printf("\n");
    }
    printf("---------------------------------------------------------------------------");
    return 0;
}
