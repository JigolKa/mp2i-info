let rec est_triee (l: 'a list) : bool =
  match l with
  | a::b::q -> if a>b then false else est_triee (b::q)
  | _ -> true

let partition (x: 'a) (l: 'a list) : ('a list) * ('a list) =
  (* l1 contient <= x, l2 > x *)
  let rec partition_aux (l: 'a list) (l1: 'a list) (l2: 'a list) : ('a list) * ('a list) =
    match l with
    | [] -> (l1, l2)
    | a::q -> if a > x then partition_aux q l1 (a::l2) else partition_aux q (a::l1) l2
  in partition_aux l [] [] 

let rec tri_rapide (l: 'a list) : 'a list =
  match l with 
  | a::b::q -> let (l1, l2) = partition a (b::q) in
    tri_rapide l1 @ [a] @ tri_rapide l2
  | _ -> l

let rec fusion (l1: 'a list) (l2: 'a list) : 'a list = 
  match (l1, l2) with
  | ([], _) -> l2
  | (_, []) -> l1
  | (a::q, a'::q') -> if a > a' then a'::(fusion l1 q') else a::(fusion q l2)

let rec separer (l: 'a list) : ('a list) * ('a list) = 
  match l with
  | [] | [_] -> (l,[])
  | a::b::q -> let l1, l2 = separer q in (a::l1, b::l2)

let rec tri_fusion (l: 'a list) : 'a list = 
  match l with
  | [] | [_] -> l
  | _ -> let l1, l2 = separer l in fusion (tri_fusion l1) (tri_fusion l2)