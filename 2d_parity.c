#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>

int numOfBits;
int numOfLines;
int senderRowParity = 0, senderColumnParity, recieverRowParity, recieverColumnParity;
bool senderParityAssigned = false, recieverParityAssigned = false;

void generateRowParity(int arr[numOfLines][numOfBits], char identifier)
{
    int rowParity[numOfLines];
    int counter = 0;
    int n = numOfLines - 1;

    for (int a = 0; a < numOfLines; a++)
    {
        for (int b = 0; b < numOfBits; b++)
        {
            if (arr[a][b] == 1)
            {
                counter++;
            }
        }

        if (counter % 2 != 0)
        {
            rowParity[a] = 1;
        }
        else
        {
            rowParity[a] = 0;
        }
        counter = 0;
        if (identifier == 's')
        {
            senderRowParity = ((rowParity[a]) * ((int)pow(10, n))) + senderRowParity;
            senderParityAssigned = true;
        }
        else
        {
            recieverRowParity = ((rowParity[a]) * ((int)pow(10, n))) + recieverRowParity;
            recieverParityAssigned = true;
        }
        n--;
    }
}

void generateColumnParity(int arr[numOfLines][numOfBits], char identifier)
{
    int columnParity[numOfBits];
    int counter_1 = 0;
    int n = numOfBits - 1;

    for (int c = 0; c < numOfBits; c++)
    {
        for (int d = 0; d < numOfLines; d++)
        {
            if (arr[d][c] == 1)
            {
                counter_1++;
            }
        }

        if (counter_1 % 2 != 0)
        {
            columnParity[c] = 1;
        }
        else
        {
            columnParity[c] = 0;
        }
        counter_1 = 0;

        if (identifier == 's')
        {
            senderColumnParity = ((columnParity[c]) * ((int)pow(10, n))) + senderColumnParity;
        }
        else
        {
            recieverColumnParity = ((columnParity[c]) * ((int)pow(10, n))) + recieverColumnParity;
        }
        n--;
    }
}

void intializer(char state)
{
    if (senderParityAssigned == true && recieverParityAssigned == true)
    {
        senderParityAssigned = false;
        recieverParityAssigned = false;
        senderRowParity = 0;
        senderColumnParity = 0;
        recieverColumnParity = 0;
        recieverRowParity = 0;
    }

    if (senderParityAssigned == false && state == 'r')
    {
        printf("!!Please send data first!!\n");
    }
    else if (senderParityAssigned == true && state == 's')
    {
        printf("!!Already sent data please recieve it!!\n");
    }
    else
    {
        int temp;

        if (state == 's')
        {
            printf("Enter number of Bits :");
            scanf("%d", &numOfBits);

            printf("Enter number of data lines in the Data set :");
            scanf("%d", &numOfLines);
            printf("\n");
        }

        //Declaring a 2D array to store Data Set.
        int array[numOfLines][numOfBits];
        //Getting DataSet and storing into the array from the User
        for (int i = 0; i < numOfLines; i++)
        {
            printf("Enter data line :");
            scanf("%d", &temp);
            for (int j = numOfBits - 1; j >= 0; j--)
            {
                array[i][j] = temp % 10;
                temp = temp / 10;
            }
        }

        if (state == 's')
        {
            generateRowParity(array, 's');
            generateColumnParity(array, 's');
            printf("\nMessage sent and parity for your data is generated successfully\n\n");
        }
        if (state == 'r')
        {
            generateRowParity(array, 'r');
            generateColumnParity(array, 'r');
            printf("\nMessage recieved and parity for your data is checked successfully\n");
            printf("Results:\n");

            if (senderRowParity == recieverRowParity && senderColumnParity == recieverColumnParity)
            {
                printf("\n ---------Data at the reciever's end is perfectly fine with no flaws-------- \n");
            }
            else
            {
                printf("\n!!!!!!!!!!!!Data at the reciever's end is corrupted or tampered!!!!!!!!!!!!\n");
            }
        }
    }
}

void main()
{
    int choice;

    while (1)
    {
        printf("\n1. Sender or 2. Reciever and 3. Exit :");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            intializer('s');
            break;

        case 2:
            intializer('r');
            break;

        case 3:
            exit(0);
            break;

        default:
            printf("Invalid input!!");
            break;
        }
    }
}
