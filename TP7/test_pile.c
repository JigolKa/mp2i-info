#include "archive_TP7/pile.h"
#include <assert.h>
int main()
{
    pile_t* P = pile_vide();
    empiler(P, 5);
    empiler(P,45);
    assert(depiler(P)==45);
    assert(depiler(P)==5);
}