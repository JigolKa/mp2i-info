type 'a ab =
| V (* Vide *)
| N of 'a * 'a ab * 'a ab (* Noeud: elem, gauche, droite *)

let t = N(3,
  N(5,
    V,
    N(8, V, V)
  ),
  N(7, V, V)
)

let rec hauteur (arb: 'a ab) : int =
  match arb with
  | V -> -1
  | N(x,g,d) -> let a = hauteur g in
                let b = hauteur d in
                1 + (if a>b then a else b)

let rec est_feuille (arb: 'a ab) : bool =
  match arb with
  | N(e,V,V) -> true
  | _ -> false

let rec etiquette (arb: 'a ab) (chemin: bool list) : 'a = 
  match (chemin,arb) with
  | _, V -> failwith "nul"
  | false::q, N(e,V,d) -> failwith "nul"
  | true::q, N(e,g,V) -> failwith "nul"
  | [], N(e,g,d) -> e
  | true::q, N(e,g,d) -> etiquette d q
  | false::q, N(e,g,d) -> etiquette g q

(* let rec etiquette_opt (arb: 'a ab) (chemin: bool list) : 'a =
  match chemin with
  | [] -> 
    begin match arb with
    | V -> None
    | N(e,g,d)->e
  end
  | x::q ->
    match (x,arb) with
    | _,V -> failwith "n"
    | true,N(e,g,V)-> failwith "n"
    | false, N(e,V,d) -> failwith "n"
    | true, N(e,g,d) -> etiquette_opt d q
    | false, N(e,g,d) -> etiquette_opt g q *)

let rec print_prefixe (a: int ab) : unit = 
  match a with
  | V -> ()
  | N(e,g,d) -> print_int e ; print_string " " ; print_prefixe g ; print_prefixe d 

let rec print_infixe (a: int ab) : unit = 
  match a with
  | V -> ()
  | N(e,g,d) ->  print_infixe g ; print_int e ; print_string " " ; print_infixe d 

let rec print_postfixe (a: int ab) : unit = 
  match a with
  | V -> ()
  | N(e,g,d) ->  print_postfixe g ; print_postfixe d ; print_int e ; print_string " " 

let liste_postfixe (a: 'a ab) : 'a list =
  let rec postfixe_concat (a: 'a ab) (l: 'a list) : 'a list =
    match a with
    | V -> l
    | N(e,g,d) -> postfixe_concat g (postfixe_concat d (x::l))
  in postfixe_concat a []

(* 
let liste_postfixe2 (a: 'a ab) : 'a list =
  let rec postfixe_concat (a: 'a ab) (l: 'a list) : 'a list =
    match a with
    | V -> l
    | N(e,g,d) -> let nd = postfixe_concat d l in
      let ng = postfixe_concat g nd
    in List.rev (e::ng)

  in postfixe_concat a [] *)

let rec tree_map (f: 'a -> 'b)  (a: 'a ab) : 'b ab =
  match a with
  | V -> V
  | N(e,g,d) -> N(f e, tree_map f g, tree_map f d)

let rec tree_sum (a: int ab) : int =
  match a with
  | V -> 0
  | N(e,g,d) -> e+ tree_sum g + tree_sum d

let rec appartient (x: 'a) (a: 'a ab) : bool =
  match a with
  | V -> false
  | N(e,g,d) -> e=x || appartient x g || appartient x d

let rec tree_fold (f: 'a -> 'acc -> 'b) (acc: 'acc) (a: 'a ab) : 'acc =
  match a with
  | V -> acc
  | N(e,g,d) -> f e (f (tree_fold f acc g) (tree_fold f acc d))


type ('k, 'v) dico = ('k * 'v) ab

let (|?) a b =
  match a with
  | Some _ -> a 
  | None -> b

let rec assoc_opt (x: 'k) (d: ('k, 'v) dico) : 'v option =
  match d with
  | V -> None
  | N(e,g,d) -> if fst e = x then Some (snd e) else (assoc_opt x g |? assoc_opt x d)

let rec assoc_all (x: 'k) (d: ('k, 'v) dico) : 'v list =
  match d with
  | V -> []
  | N(e,g,d) -> if fst e = x then 
    let tmp =  (assoc_all x g) @ (assoc_all x d) in
    snd e :: tmp
  else ((assoc_all x g) @ (assoc_all x d))