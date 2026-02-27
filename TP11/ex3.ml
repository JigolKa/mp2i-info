type 'a tree =
  N of 'a * (('a tree) list) 

let rec hauteur (N(_,l): 'a tree) : int = 
  1 + hauteur_liste l

and hauteur_liste (l: 'a tree list) : int =
  match l with
  | [] -> 0
  | d::q -> max (hauteur d) (hauteur_liste q)

let t = N(3, [N(2, []); N(1,[N(5,[]);N(4,[])]); N(3, []); N(5,[N(1,[])])])
let t' = N(2, [N(1, []); N(3, [])])

(* let rec etiquette (a: 'a tree) (a:) *)



(* let rec liste_prefixe (N(x,l): 'a tree) : 'a list =
  match l with
  | [] -> [x]
  | d::q -> x :: aux q
and aux (q: 'a tree list) : 'a list =
  match q with 
  | [] -> []
  | d::q -> liste_prefixe d @ aux q *)

  

let rec print_prefixe (N(x,l): 'a tree) : unit =
  print_int x ; print_string " " ; List.iter print_prefixe l


let rec print_postfixe (N(x,l): 'a tree) : unit =
  List.iter print_postfixe l  ; print_int x ; print_string " " 

type 'a file = 'a list * 'a list (* (tete, queue) *)

let file_vide () = ([], [])
let est_vide ((t,q): 'a file) = (t=[]) && (q=[])

let enfiler ((t,q): 'a file) (x: 'a) : 'a file =
  (t,x::q)

let rec defiler ((t,q):'a file) : ('a * 'a file) =
  assert (t!=[] || q != []) ;
  match t with
  | [] -> defiler (List.rev q, [])
  | d::t' -> (d,(t',q))
  
let liste_largeur (a: 'a tree) =
  let rec liste_largeur_file (f: 'a tree file) : 'a list =
    
  in 
  let file_depart = enfiler (file_vide) a in
  liste_largeur_file file_depart