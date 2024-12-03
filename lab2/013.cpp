#include<cstdio>
#include<cstring>
#include<cstdlib>
#include<iostream>
int pyear[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
int ryear[12] = {31,29,31,30,31,30,31,31,30,31,30,31};
char d[7][10] = { "Friday" , "Saturday" , "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday" };
bool run(int n)
{
   return((n%4==0&&n%100!=0)||(n%400==0));
}
int main()
{
    int t;
    while(~scanf("%d", &t) && t != -1)
    {
        t++;
        int day = t%7;
        int c = 2000;
        int cnt = 0;
        while(t>366)
        {
            if(run(c))
            {
                t-=366;
                c++;
                cnt++;
            }
            else
            {
                t-=365;
                c++;
                cnt++;
            }
        }
        if(run(c))
        {
            int i;
            for(i = 0; t > ryear[i]; i++)
                t-=ryear[i];

            printf("%d-%02d-%02d %s\n", 2000+cnt, i+1, t, d[day]);
        }
        else
        {
            if(t>365)
            {
                t-=365;
                cnt++;
            }
            int i;
            for(i = 0; t > pyear[i]; i++)
                t-=pyear[i];

            printf("%d-%02d-%02d %s\n", 2000+cnt, i+1, t, d[day]);
        }
 
    }
 
 
    return 0;
}
