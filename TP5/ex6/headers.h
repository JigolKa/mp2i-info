struct CHOIX
{
    char texte[700];
    int page_suivante;
};
struct PAGE
{
    char texte[700];
    int n_choix;
    struct CHOIX **choix; // tableau de pointeurs vers des choix
};
struct LIVRE
{
    int n_pages;
    struct PAGE **pages; // tableau de pointeurs vers des pages
};

typedef struct CHOIX choix_t;
typedef struct PAGE page_t;
typedef struct LIVRE livre_t;