### Q5. Il y a exactement n! arbres croissants

**Preuve par induction.** Soit T(n) le nombre d'arbres croissants sur {1,...,n}.

La racine doit être **1** (le minimum). On choisit k nœuds parmi {2,...,n} pour le sous-arbre gauche (0 ≤ k ≤ n-1) :

$$T(n) = \sum_{k=0}^{n-1} \binom{n-1}{k} T(k)\, T(n-1-k)$$

avec T(0) = 1. Par hypothèse d'induction T(k) = k! :

$$T(n) = \sum_{k=0}^{n-1} \binom{n-1}{k} k!\,(n-1-k)! = \sum_{k=0}^{n-1} (n-1)! = n \cdot (n-1)! = n! \quad \square$$
