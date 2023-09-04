#include <stdio.h>
#include <string.h>

struct Atk
{
    int physical;
    int magic;
    int fire;
    int lightning;
    int bonus;
};
struct Def
{
    int physical;
    int magic;
    int fire;
    int lightning;
    int stab;
};
struct Effects
{
    int poison;
    int bleed;
    int divine;
    int occult;
};
struct Req
{
    int strength;
    int dexterity;
    int intelligence;
    int faith;
};
struct Scale
{
    int strength;
    int dexterity;
    int intelligence;
    int faith;
};

struct Item
{
    char name[200];
    int durability;
    char attackTypes[2][200];
    char obtained[2][200];
    bool aotaOnly;
    Atk akt;
    Def def;
    Effects effects;
    Req req;
    Scale scale;
};

void CleanCurrentCharArray(char *currentColumnChar)
{
    // renar datan
    for (int i = 0; i < 200; i++)
    {
        currentColumnChar[i] = 0;
    }
}

int main()
{
    FILE *fptr = fopen("advanced.json", "r");

    if (fptr == NULL)
    {
        printf("%s", "fungera inte");
        return -1;
    }

    /*
    fseek(fptr, 0, SEEK_END);
    int end = ftell(fptr);
    printf("%i \n", end);
    */

    // printar och sparar hur många rader fillen har -1 för 0

    int numberOfColumns = 1;

    int countingNumberItem = 0;
    int numberOfItems = 0;

    // Extract characters from file and store in character c
    for (int i = getc(fptr); i != EOF; i = getc(fptr))
    {
        // Increment count if this character is newline
        if (i == '\n')
        {
            numberOfColumns++;
        }
        if (i == '{')
        {
            countingNumberItem++;
        }
        if (i == '}')
        {
            countingNumberItem--;

            if (countingNumberItem == 0)
            {
                numberOfItems++;
            }
        }
    }

    printf("END LINES %i \n", numberOfColumns);
    printf("END ITEMS %i \n", numberOfItems);

    // läser datan

    Item itemList[numberOfItems];

    fseek(fptr, 0, SEEK_SET);
    char currentChar;
    char currentColumnChar[200];

    CleanCurrentCharArray(currentColumnChar);

    // runtime

    // håller koll på saker
    int countCurlyBrackets = 0;

    int startReadingString = 0;
    int countCharArraySlot = 0;

    // räknar vilket item vi är på
    int itemCurrentIndex = 0;

    // debug
    int countName = 0;

    while (feof(fptr) != true)
    {
        currentChar = getc(fptr);
        // printf("%c\n", currentChar);

        if (currentChar == ' ')
        {
            continue;
        }

        // if (currentChar == '�')
        // {
        //     break;
        // }

        // kollar måsvingar

        if (currentChar == '{')
        {
            countCurlyBrackets++;
        }
        if (currentChar == '}')
        {
            countCurlyBrackets--;
            if (countCurlyBrackets == 0)
            {
                itemCurrentIndex++;
            }
        }

        // Kollar om string ska läsas
        if (currentChar == '"')
        {
            if (startReadingString == 0)
            {
                startReadingString = 1;
            }
            else
            {
                startReadingString = 0;
                countCharArraySlot = 0;

                // printf("%s \n", currentColumnChar);
            }
            continue;
        }

        if (startReadingString == 1)
        {
            currentColumnChar[countCharArraySlot] = currentChar;
            // printf("Count %i char %c \n", countCharArraySlot, currentChar);
            countCharArraySlot++;

            continue;
        }

        if (currentChar == ',')
        {
            CleanCurrentCharArray(currentColumnChar);
        }

        if (currentChar == ':')
        {
            if (countCurlyBrackets == 2)
            {
                // kolla efter saker under top nivån
            }

            if (countCurlyBrackets == 1)
            {
                // int durability;
                // char attackTypes[2][50];
                // char obtained[2][50];
                // bool aotaOnly;
                // Atk akt;
                // Def def;ß
                // Effects effects;
                // Req req;
                // Scale scale;

                if (strcmp(currentColumnChar, "name") == 0)
                {
                    printf("hitta name %i \n ", countName);
                    countName++;
                }

                CleanCurrentCharArray(currentColumnChar);
            }
        }
    }

    // avslutar
    // fclose(fptr);
    return 0;
}