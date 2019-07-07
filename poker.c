enum GRADE
{
     HIGHCARD,
     ONEPAIR,
     TWOPAIR,
     THREEOFAKIND,
     STRAIGHT,
     FLUSH,
     FULLHOUSE,
     FOUROFAKIND,
     STRAIGHTFLUSH
};

char* g_gradeName[9]={
     "HIGH CARD",
     "ONE PAIR",
     "TWO PAIR",
     "THREE OF A KIND",
     "STRAIGHT",
     "FLUSH",
     "FULL HOUSE",
     "FOUR OF A KIND",
     "STRAIGHT FLUSH"
};

int cmpfunc (const void * a, const void * b);
int checkStraightFlush(int card[]);
int checkFourOfAKind(int input[]);
int checkFullHouse(int input[]);
int checkFlush(int input[]);
int checkStraight(int input[]);
int checkThreeOfAKind(int input[]);
int checkTwoPair(int input[]);
int checkOnePair(int input[]);
int getGrade(int card[]);

int cmpfunc (const void * a, const void * b)
{
   if (*(int*) a > *(int*)b ) return 1;
   else if (*(int*)a == *(int*)b) return 0;
   return -1;
}

int checkStraightFlush(int card[])
{
    //assume cards is ascending
    int i = card[0];
    int j = card[1];
    int k = card[4];
    if (i == k - 4)
    {
        if((k < 14)||(i > 13 && k < 27)||(i > 26 && k < 40)||( i > 39 && k < 53))
            return 1;
    }
    // 10 J Q K A
    else if( i % 13 == 1 && j % 13 == 10 && (i-1) / 13 == (k-1) / 13)
        return 1;
    return 0;//8
}

int checkFourOfAKind(int input[])
{
    //assume cards is ascending
    int card[5];
    for(int i = 0; i < 5; i++)
        card[i] = input[i] % 13;
    qsort(card, 5, sizeof(int), cmpfunc);
    if( card[0] == card[3] || card[1] == card[4])
        return 1;
    return 0;//7
}

int checkFullHouse(int input[])
{
    int card[5];
    for(int i = 0; i < 5; i++)
        card[i] = input[i] % 13;
    qsort(card, 5, sizeof(int), cmpfunc);
    if(card[0] == card[1] && card[2] == card[4] || card[0] == card[2] && card[3] == card[4])
        return 1;
    return 0;//6
}

int checkFlush(int input[])
{
    int card[5];
    for(int i = 0; i < 5; i++)
        card[i] = (input[i]-1) / 13;
    qsort(card, 5, sizeof(int), cmpfunc);
    if(card[0] == card[4])
        return 1;
    return 0;//5
}

int checkStraight(int input[])
{
    int card[5];
    for(int i = 0; i < 5; i++)
        card[i] = input[i] % 13;
    qsort(card, 5, sizeof(int), cmpfunc);
    if(card[0] == card[4] - 4 && card[1] > card[0] && card[2] > card[1] && card[3] > card[2]  && card[4] > card[3])
        return 1;
    else if(card[0] == 0 && card[1] == 1 && card[2] == 10 && card[3] == 11 && card[4] == 12)
        return 1;
    return 0;//4
}

int checkThreeOfAKind(int input[])
{
    int card[5];
    for(int i = 0; i < 5; i++)
        card[i] = input[i] % 13;
    qsort(card, 5, sizeof(int), cmpfunc);
    if(card[0] == card[2] || card[1] == card[3] || card[2] == card[4])
        return 1;
    return 0;//3
}

int checkTwoPair(int input[])
{
    int card[5];
    for(int i = 0; i < 5; i++)
        card[i] = input[i] % 13;
    qsort(card, 5, sizeof(int), cmpfunc);
    if(card[0] == card[1] && card[2] == card[3]
            || card[0] == card[1] && card[2] == card[4]
            || card[0] == card[1] && card[3] == card[4]
            || card[0] == card[2] && card[3] == card[4]
            || card[1] == card[2] && card[3] == card[4])
        return 1;
    return 0;//2
}

int checkOnePair(int input[])
{   
    int card[5];
    for(int i = 0; i < 5; i++)
        card[i] = input[i] % 13;
    qsort(card, 5, sizeof(int), cmpfunc);
    if(card[0] == card[1] || card[1] == card[2]
            || card[2] == card[3] || card[3] == card[4])
        return 1;
    return 0;//1
}

int getGrade(int card[])
{
    enum GRADE res = HIGHCARD;
    //assume cards is ascending, and the size is 5
    if(checkStraightFlush(card))
        res =  STRAIGHTFLUSH;
    else if(checkFourOfAKind(card))
        res =  FOUROFAKIND;
    else if(checkFullHouse(card))
        res = FULLHOUSE;
    else if (checkFlush(card))
        res = FLUSH;
    else if (checkStraight(card))
        res = STRAIGHT;
    else if (checkThreeOfAKind(card))
        res = THREEOFAKIND;
    else if (checkTwoPair(card))
        res = TWOPAIR;
    else if (checkOnePair(card))
        res = ONEPAIR;
    return res;
}

int main(int argc,char *argv[])
{
    /*int a[5] = {0};
    a[0] = atoi(argv[1]);
    a[1] = atoi(argv[2]);
    a[2] = atoi(argv[3]);
    a[3] = atoi(argv[4]);
    a[4] = atoi(argv[5]);*/
    int long count = 0;
    int res[9] = {0};
    int card[5] = {0};
    for(int i = 1; i <= 52; i++)
    {
        card[0] = i;
        for(int j = i + 1; j <= 52; j++)
        {
            card[1] = j;
            for(int k = j + 1; k <= 52; k++)
            {
                card[2] = k;
                for(int l = k + 1; l <= 52; l++)
                {
                    card[3] = l;
                    for(int m = l + 1; m <= 52; m++)
                    {
                        card[4] = m;
                        enum GRADE gradOfCard = getGrade(card);
                        res[gradOfCard]++;
                        count++;
                    }
                }
            }
        }
    }
    printf("%10d | grade * | %15s | ratio %.8lf\n", count,"TOTAL",(double)(count/count));
    for(int i = 0; i < 9; i++)
    {
        printf("%10d | grade %i | %15s | ratio %.8lf\n", res[i], i,g_gradeName[i],(double)res[i]/(double)count);
    }
    return 0;
}
