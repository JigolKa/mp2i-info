let rec taille (l: int list) : int = 
	match l with 
	| [] -> 0
	| x :: q -> 1 + taille q 

let rec recherche (a: 'a) (l: 'a list) : bool =
	match l with 
	| [] -> true
	| x :: q -> if x = a then true else recherche x q

let rec somme (l: int list) : int = 
	match l with 
	| [] -> 0
	| x :: q -> x + somme q 

let rec multi_concat (ll: 'a list list) : 'a list =
 	match ll with 
 	| [] -> []
 	| l :: qq -> List.append l (multi_concat qq) (* List.append fait une concaténation *)

let rec string_cat (l: string list) : string = 
	match l with 
	| [] -> ""
	| x :: q -> x ^ string_cat q 

let rec fold (f: 'a -> 'b -> 'b) (l: 'a list) (a: 'b) =
	match l with 
	| [] -> a
	| x :: q -> f x (fold f q a)


(* nouvelles définitions de taille, somme, 
   recherche, multi_concat et string_cat 
   en utilisant fold.
   On remarque que systématiquement, 
   le cas | [] -> se retrouve dans le dernier argument
   et le cas | x :: q -> se retrouve dans le premier argument *)

let taille2 l = 
	(* si on a une liste de la forme x :: q et qu'on
	   a déjà calculé la taille de q, que l'on note r,
	   alors la taille de l est 1 + r *)
	fold (fun x r -> 1 + r) l 0

let somme2 l = 
	(* si on a une liste de la forme x :: q et qu'on
	   a déjà calculé la somme de q, que l'on note r,
	   alors la somme de l est x + r *)
	fold (fun x r -> x + r) l 0 (*ou bien fold (+) l 0 *)

let recherche2 a l = 
	(* si on a une liste de la forme x :: q et qu'on
	   a déjà cherché a dans q, en notant r le résultat booléen,
	   alors a est dans l si x = a ou bien si a est dans
	   q, i.e. si x = a ou si r est vrai *)
	fold (fun x r -> x = a || r) l false

let multi_concat2 ll =
	(* même raisonnement (List.append est une fonction qui concatène deux listes) *)
	fold List.append ll []

let string_cat2 l =
	fold (fun x r -> x^r) l "" (* ou bien fold (^) l "" *)

(* liste des éléments de l qui vérifient prop *)
let rec filter1 (prop: 'a -> bool) (l: 'a list) : 'a list =
	match l with
	| [] -> []
	| x :: q -> if prop x then x :: filter1 prop q 
	            else             filter1 prop q 

let filter prop l =
	fold (fun x r -> if prop x then x::r else r) l []

let map f l =
	fold (fun x r -> f x :: r) l []

(* range_concat n = [0; ...; n-1] concaténé avec l *)
let rec range_concat (n: int) (l: int list) : int list =
	if n = 0 then l
	else range_concat (n-1) ((n-1)::l)

(* range n = [0; ...; n-1] *)
let range (n: int) : int list = range_concat n []


let sum_div (n: int) : int =
	(* liste des entiers de 1 à n *)
	let l = map ((+) 1) (range n) in 
	(* liste des diviseurs de n *)
	let divs = filter (fun i -> n mod i = 0) l in
	(* liste des carrés des diviseurs de n *)
	let carres = map (fun d -> d*d) divs in
	(* calcul de la somme *)
	fold (+) carres 0

(** BONUS: l'opérateur |> **)
(* L'opérateur |> : 'a -> ('a -> 'b) -> 'b
   vérifie:
   x |> f = f x
   On peut l'enchaîner:
   x |> f |> g = g (f x)

	Autrement dit, cet opérateur permet de
	partir d'un élément x, et de lui faire
	subir une suite d'opérations f1, f2 ... fk
	en faisant
	x |> f1 |> ... |> fk
	ce qui se lit beaucoup plus naturellement
	qu'en écrivant fk (... (f2 (f1 x))...)
	car on peut suivre les opérations que subit x
	dans le sens naturel de lecture (en français et en anglais).
	
	Par exemple, voici une manière alternative de
	coder la fonction précédente:
*)

let sum_div2 n =
	let div_carres = 
		n 
	   |> range 
	   |> map ((+) 1)
	   |> filter (fun i -> n mod i = 0)
	   |> map (fun d -> d*d)
	  (* la suite d'opérations précédente se lit:
	    - je pars de n
	    - j'applique range, j'obtiens donc  [0; ...; n-1]
	    - j'applique map ((+) 1), j'obtiens [1; ...; n]
	    - je ne garde que les diviseurs de n
	    - je mets les éléments restants au carré
	   donc, div_carres est la liste des carrés des diviseurs de n *)
	in
	fold (+) div_carres 0 

