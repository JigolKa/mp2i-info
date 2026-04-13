type 'a arbre =
  | V
  | N of 'a arbre * 'a * 'a arbre 

let rec recherche (x: 'a) (a: 'a arbre) : bool = 
  match a with
  | V -> false
  | N(g,x',d) -> if x < x' then recherche x g
  else if x > x' then recherche x d
  else true

let rec ajoute (x: 'a) (a: 'a arbre) : 'a arbre =
  match a with
  | V -> N(V,x,V)
  | N(g,x',d) -> if x>x' then N(g,x',ajoute x d)
  else if x<x' then N(ajoute x g, x', d)
  else N(g,x',d)

let rec extraire_max (a: 'a arbre) : 'a*'a arbre =
  assert(a!=V);
  match a with
  | N(g,x,V) -> (x,g)
  | N(g,x,d) -> let (x', res) = extraire_max d in
    (x', N(g,x,res))

(* let rec supprimer (x: 'a) (N(g,x',d): 'a arbre) : 'a arbre =
  assert(recherche x a);
  match x' with
  | a when a>x -> N(supprimer x g, x', d)
  | a when a<x -> N(g,x', supprimer x d)
  | a when a=x -> snd (extraire_max ) *)

let time_a (n: int) : float =
  let start = Sys.time () in
  List.fold_right ajoute (List.init n (fun x -> n - x)) V ;
  Sys.time() -. start