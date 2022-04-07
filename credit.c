#include <cs50.h>
#include <stdio.h>

//CN means Card Number (13 0r 15 or 16 digits)
//digits mean number of digits on the card number
//check_sum is Luhn's Algorithm to validate a card

int main(void)
{
    //Prompt user for Card Number
    long CN;
    int digits = 0;
    do
    {
        CN = get_long("Card Number: ");
    }
    while (CN < 0);
    long check = CN;

    //declaring every second number starting from the second to the last which is digit-15 when digits are 16
    int digit15, digit13, digit11, digit9, digit7, digit5, digit3, digit1;

    //identifying the actual number of each digit and multiplying each by 2
    digit15 = ((CN % 100) / 10) * 2;
    digit13 = ((CN % 10000) / 1000) * 2;
    digit11 = ((CN % 1000000) / 100000) * 2;
    digit9  = ((CN % 100000000) / 10000000) * 2;
    digit7  = ((CN % 10000000000) / 1000000000) * 2;
    digit5  = ((CN % 1000000000000) / 100000000000) * 2;
    digit3  = ((CN % 100000000000000) / 10000000000000) * 2;
    digit1  = ((CN % 10000000000000000) / 1000000000000000) * 2;

    /*incase multiplying each digit by 2 gives any two figures(digits), we need to identify each digit of
    the two figures too and add the two figures together */
    digit15 = ((digit15 % 100) / 10) + (digit15 % 10);
    digit13 = ((digit13 % 100) / 10) + (digit13 % 10);
    digit11 = ((digit11 % 100) / 10) + (digit11 % 10);
    digit9  = ((digit9  % 100) / 10) + (digit9  % 10);
    digit7  = ((digit7  % 100) / 10) + (digit7  % 10);
    digit5  = ((digit5  % 100) / 10) + (digit5  % 10);
    digit3  = ((digit3  % 100) / 10) + (digit3  % 10);
    digit1  = ((digit1  % 100) / 10) + (digit1  % 10);

    //declaring each remaining digits of the card number
    int digit16, digit14, digit12, digit10, digit8, digit6, digit4, digit2;

    //identifying the actual number of each remaining digit
    digit2  = (CN % 1000000000000000) / 100000000000000;
    digit4  = (CN % 10000000000000) / 1000000000000;
    digit6  = (CN % 100000000000) / 10000000000;
    digit8  = (CN % 1000000000) / 100000000;
    digit10 = (CN % 10000000) / 1000000;
    digit12 = (CN % 100000) / 10000;
    digit14 = (CN % 1000) / 100;
    digit16 =  CN % 10;

    //adding all the digits together
    int check_sum = digit1 + digit2 + digit3 + digit4 + digit5 + digit6 + digit7 + digit8 + digit9 + digit10 + digit11 + digit12 +
                    digit13 + digit14 + digit15 + digit16;

    //checking if the total modulo 10 is congruent to 0 (last digit of the sum of the digits is 0)
    if (check_sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }

    //counting the number of digits to determine if its 13, 15 0r 16
    //we divide the card number by 10 while digits++ counts till card number reaches 0. in which case now less than 0
    while (check > 0)
    {
        check = check / 10;
        digits++;
    }

    //validating the number of digits
    if (digits != 13 && digits != 15 && digits != 16)
    {
        printf("INVALID\n");
        return 0;
    }


    long AMEX = CN / 10000000000000; //identifying the first two digits for American-Express card
    long MC = CN / 100000000000000; //identifying the first two digits fof a Mastercard card
    long VISA = CN / 1000000000000000; //identifying the first digit for a Visa card

    //identifying an American-Express card
    if (digits == 15)
    {
        if (AMEX == 34 || AMEX == 37)
        {
            printf("AMEX\n");
            return 0;
        }
        else
        {
            printf("INVALID\n");
            return 0;
        }
    }

    //identifying a Mastercard and a Visa card
    if (digits == 16)
    {
        if (MC == 51 || MC == 52 || MC == 53 || MC == 54 || MC == 55)
        {
            printf("MASTERCARD\n");
            return 0;
        }
        else if (VISA == 4)
        {
            printf("VISA\n");
            return 0;
        }
        else if (MC != 51 && MC != 52 && MC != 53 && MC != 54 && MC != 55 && VISA == 4)
        {
            printf("INVALID\n");
            return 0;
        }
    }

    //since Visa cards can also have just 13 digits, another identifier for Visa card
    if (digits == 13 && VISA == 4)
    {
        printf("VISA\n");
        return 0;
    }
    else if (digits != 13 && VISA != 4)
    {
        printf("INVALID\n");
        return 0;
    }
}