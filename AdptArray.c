#include <stdio.h>
#include "AdptArray.h"
#include <stdlib.h>
#include <string.h>
#include <math.h>

typedef struct AdptArray_
{
    int ArrSize;
    PElement* pElementArr;
    DEL_FUNC delFunc;
    COPY_FUNC copyFunc;
    PRINT_FUNC printFunc;
}AdptArray;

AdptArray* CreateAdptArray(COPY_FUNC copy, DEL_FUNC delete, PRINT_FUNC print)
{
    AdptArray* pArr = malloc(sizeof(*pArr));
    if (!pArr)
        return NULL;
    pArr->ArrSize = 0;
    pArr->pElementArr = malloc(sizeof(PElement));
    pArr->delFunc = delete;
    pArr->copyFunc = copy;
    pArr->printFunc = print;
    return pArr;
}

Result SetAdptArrayAt(AdptArray* pArr, int index, PElement pElem)
{
    if (pArr == NULL || pElem == NULL || index < 0) {
        return FAIL;
    }

    if (index >= pArr->ArrSize) {
        int newSize = index + 1;

        PElement* newElements = realloc(pArr->pElementArr, newSize * sizeof(PElement));
        if (newElements == NULL) {
            return FAIL;
        }

        memset(newElements + pArr->ArrSize, 0, (newSize - pArr->ArrSize) * sizeof(PElement));

        pArr->pElementArr = newElements;
        pArr->ArrSize = newSize;
    }

    if (pArr->pElementArr[index] != NULL) {
        pArr->delFunc(pArr->pElementArr[index]);
    }

    pArr->pElementArr[index] = pArr->copyFunc(pElem);

    return SUCCESS;
}



void DeleteAdptArray(AdptArray* pArr)
{
    if (pArr == NULL)
        return;

    for (int i = 0; i < pArr->ArrSize; ++i) {
        if (pArr->pElementArr[i]) {
            pArr->delFunc(pArr->pElementArr[i]);
        }
    }

    free(pArr->pElementArr);
    pArr->pElementArr = NULL;

    free(pArr);
    pArr = NULL;
}

PElement GetAdptArrayAt(AdptArray* pArr, int index) {

    if (!pArr || index < 0 || index >= pArr-> ArrSize || !pArr->pElementArr[index]) {
        return NULL;
    }

    PElement newpElem = pArr->copyFunc(pArr->pElementArr[index]);
    return newpElem;
}

int GetAdptArraySize(AdptArray* pArr) {
    return pArr ? pArr->ArrSize : -1;
}

void PrintDB(AdptArray* pArr) {
    if (!pArr) {
        return;
    }

    for (size_t i = 0; i < pArr->ArrSize; ++i) {
        if (pArr->pElementArr[i]) {
            pArr->printFunc(pArr->pElementArr[i]);
        }
    }
}
