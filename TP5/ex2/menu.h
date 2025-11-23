// élément de menu
struct menu_elem
{
    char nom[50];
    double prix_unite;
    bool vegan;
};
typedef struct menu_elem menu_elem_t;

#define MAX_ELEMS 128

struct menu
{
    menu_elem_t elements[MAX_ELEMS];
    int nb_elems;
};
typedef struct menu menu_t;