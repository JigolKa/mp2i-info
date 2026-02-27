(*
NOTE: dans un match-with, on peut combiner les cas 
de la manière suivante:

match x with
| M1 
| M2 -> e1
| M3
| M4 -> e2

signifie que les motifs M1 et M2 mènent à l'expression e1,
et M3 et M4 mènent à l'expression e2.
*)

(* booléen indiquant si l est triée *)
let rec est_triee (l: 'a list) : bool = 
	match l with 
	| [] | [_] -> true
	| x :: y :: q -> x <= y && est_triee (y :: q)


(** TRI RAPIDE **)

(* partition de l en deux listes (li, ls), avec li contenant
   les éléments de l inférieurs ou égaux à p, et ls les autres. *)
let rec partition (p: 'a) (l: 'a list) : ('a list * 'a list) =
	match l with 
	| [] -> [], []
	| x :: q -> 
		let li, ls = partition p q in 
		if x <= p then 
			(x :: li, ls)
		else 
			(li, x :: ls)


(* copie triée de l *)
let rec tri_rapide (l: 'a list) : 'a list =
	match l with 
	| [] | [_] -> l
	| x :: q -> let li, ls = partition x q in 
		List.append (tri_rapide li)  (x :: tri_rapide ls) 

(** TRI FUSION **)

(* liste triée contenant les éléments de l1 et l2
    Précondition: l1 et l2 sont triées *)
let rec fusion (l1: 'a list) (l2: 'a list) : 'a list =
	match (l1, l2) with 
	| [], l | l, [] -> l 
	| x1 :: q1, x2 :: q2 -> 
		if x1 < x2 then 
			x1 :: fusion q1 l2
		else 
			x2 :: fusion l1 q2

(* couple (l1, l2) contenant les éléments de l, avec |taille(l1) - taille(l2)| < 2 *)
let rec separer l = 
	match l with 
	| [] | [_] -> (l, [])
	| x::y::q -> let l1, l2 = separer q in x :: l1, y :: l2


(* copie triée de l *)
let rec tri_fusion (l: 'a list) : 'a list =
	match l with 
	| [] | [_] -> l
	| _ -> let l1, l2 = separer l in
		   fusion (tri_fusion l1) (tri_fusion l2)

