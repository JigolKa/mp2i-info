type couleur = Rouge | Noir

type 'a noeud_arn = 
  | Feuille of 'a 
  | Noeud of couleur * 'a * 'a noeud_arn * 'a noeud_arn

type 'a arn ='a noeud_arn option

let get_couleur (a: 'a noeud_arn) : couleur option =
  match a with
  | Feuille(_) -> None
  | Noeud(b,_,_,_) -> Some b

let rec detection_2_noeuds (a: 'a noeud_arn) : bool =
  match a with
  | Feuille(_) -> false
  | Noeud(b,x,g,d) -> 
    (begin match get_couleur g with
    | None -> false
    | Some b' -> b=b'
  end) || (begin match get_couleur d with
    | None -> false
    | Some b' -> b=b'
  end) || (detection_2_noeuds g) || (detection_2_noeuds d)

let a = Noeud(Noir, 3, Noeud(Rouge, 2,Feuille(1), Feuille(3)),  Noeud(Noir, 5, Feuille(6), Feuille(7)))

exception Erreur_hauteur_noire

let rec hauteur (a: 'a noeud_arn) : int =
  match a with
  | Feuille(_) -> 0
  | Noeud(_,x,g,d) -> 1 + max (hauteur g) (hauteur d)

let rec hauteur_noires (a: 'a noeud_arn) : int list = 
  match a with 
  | Feuille(_) -> []
  | Noeud(b, x,g,d) -> if b = Noir then [hauteur (Noeud(b,x,g,d))] @ hauteur_noires g @ hauteur_noires d
  else hauteur_noires g @ hauteur_noires d

let hauteur_noire (a: 'a noeud_arn) : int =
  let h = hauteur a in
  let l = hauteur_noires a in
  match List.for_all (fun x -> x= (List.hd l)) l with
  | true -> h
  | false -> raise Erreur_hauteur_noire

let arn_valide (a: 'a noeud_arn) : bool =
  try hauteur_noire a ; detection_2_noeuds a ; true with
  | Erreur_hauteur_noire -> false

let rec mirror (a: 'a noeud_arn) : 'a noeud_arn = 
  match a with 
  | Feuille(_) -> a
  | Noeud(b,x,g,d) -> Noeud(b, x, mirror d, mirror g)

let correctionARN (a :'a noeud_arn) : 'a noeud_arn =
  match a with
  | Noeud(Noir, z, Noeud(Rouge, y, Noeud(Rouge, x, a, b), c),d)
  | Noeud(Noir, z, Noeud(Rouge, x, a, Noeud(Rouge, y, b,c)), d)
  | Noeud(Noir, x, a, Noeud(Rouge, z, Noeud(Rouge, y,b,c), d))
  | Noeud(Noir, x, a, Noeud(Rouge, y, Noeud(Rouge, z, b,c), d))
  -> Noeud(Noir, y, Noeud(Rouge, x,a,b),Noeud(Rouge,z,c,d))
  | _ -> a

let rec insertionARNrelax (x: 'a) (a: 'a noeud_arn) : 'a noeud_arn =
  match a with
  | Feuille(x') -> Noeud(Rouge, x', Feuille(min x x'), Feuille(max x' x))
  | Noeud(b,x',g,d) -> if x>x' then Noeud(b,x',g,correctionARN(insertionARNrelax x d))
  else if x<x' then Noeud(b,x', correctionARN(insertionARNrelax x g), d)
  else Noeud(b,x',g,d)

let rec insertionARN (x: 'a) (a: 'a noeud_arn) : 'a noeud_arn =
  correctionARN (insertionARNrelax x a)

(* let construire (n: int) : 'a noeud_arn =
  List.fold_right insertionARN (List.init (n-1) (fun x -> n - x)) Feuille(1) ; *)
