#include <stdio.h>
#include <string.h>
#include "splitting.h"


void split(char* str, char delim)
{
    int size = strlen(str);
    int delim_counter=0 ,i,j=0, last=0, _new;

    for (i = 0; i < size; i++)
    {
        if(str[i] == delim)
            delim_counter++;
    }

    int delim_index[delim_counter+1];
    char* res[delim_counter+1];
    for (i=0; i<= delim_counter; i++)
    {
        res[i]= "";
    }

    for (i = 0; i < size; i++)
    {
        if(str[i] == delim)
        {
            delim_index[j] = i;
            j++;
        }
    }
    delim_index[delim_counter] = size;

    for (i = 0; i <= delim_counter; i++)
    {
        _new = delim_index[i];

        for (j=last; j< _new; j++)
        {
            printf("%c", str[j]);
//            res[i] += *str;
//            str++;
        }
        printf("\n");
        last = _new+1;

    }

//    for (i = 0; i < 4; i++)
//    {
//          printf("%s\n", res[i]);
//    }


}
















































//{
//    int size = strlen(str);
//    int tmp;
//    char* res[size];
//    int i,k,j=0, counter= 0;
//    for (i=0; i< size; i++)
//    {
//        if (str[i] == delim)
//        {
//            tmp = i;
//            for (k = 0; k <i; k++)
//            {
//                res[counter] = str[k];

//            }

//            counter++;
////            res[j] = tmp;
////            tmp[0] = '\0';
//            j++;
//        }

////        else
////        {
//////            tmp[counter] = str[i];
////            counter++;
////        }
//    }
//    for (i = 0; i < 4; i++)
//    {
//        printf("%s\n", res[i]);
//    }

//}
