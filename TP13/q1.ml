type 'a arbre =  
  | V
  | N of 'a * 'a arbre * 'a arbre

let lister (a: 'a arbre) : 'a list =
  let r = ref [] in
  let rec ajouter (a: 'a arbre) =
    match a with
    | V ->  []
    | N(x,g,d) -> ajouter g; ajouter d; !r@[x]
  in ajouter a; !r

let a = N(3, N(2,V,V),N(5,N(4,V,V),V))