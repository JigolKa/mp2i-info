type formule =
	| Var of string
	| Top
	| Bot
	| And of formule * formule
	| Or of formule * formule
	| Not of formule

type valuation = (string*bool) list

type sat_result = valuation option

let implique (f1, f2) = Or(Not f1, f2)
let equivalence (f1, f2) = And(implique (f1, f2), implique (f2, f1))

(*** PARSER ***)

exception Erreur_syntaxe
exception Fichier_invalide

(* Symboles:
	'T' -> true
	'F' -> false
	'&' -> And
	'|' -> Or
	'~' -> Not
	'>' -> implication
	'=' -> equivalence
 *)

(* Détermine si c correspond à un opérateur binaire logique *)
let is_binop (c: char) : bool = match c with 
	| '&' |  '|' |  '>' |  '='  -> true
	| _ -> false 

(* Priorité de l'opérateur c. Permet de déterminer
	comment interpréter une formule sans parenthèses.
	Par exemple, "x&y|z" sera interprété comme "(x&y)|z"
	car & est plus prioritaire que | *)
let priority (c: char) : int = match c with
	| '&' -> 4
	| '|' -> 3
	| '=' -> 2
	| '>' -> 1
	| _ -> raise Erreur_syntaxe (* c n'est pas un opérateur *)

(* indice de l'opérateur le moins prioritaire parmis ceux
   qui ne sont pas entre parenthèses entre s.[i] et s.[j] 
   inclus *)
let find_op_surface (s: string) (i: int) (j: int) : int =
 	(* 
 	   Renvoie l'indice de l'opérateur le moins prioritaire entre
 	   i et j, sachant que res est l'indice du meilleur opérateur
 	   entre i et k-1.
 	   paren_lvl: niveau d'imbrication actuel des parenthèses *)
 	let rec find_op_paren (k:int) (res:int) (paren_lvl: int) : int  =
 		if k=j+1 then res else
 		if s.[k] = '(' then find_op_paren (k+1) res (paren_lvl+1)
 		else if s.[k] = ')' then find_op_paren (k+1) res (paren_lvl-1) 

 		(* Le caractère lu est pris si l'on est hors des parenthèses,
 		   que le caractère est bien un opérateur, et qu'il est moins
 		   prioritaire que le meilleur résultat jusqu'ici *)
 		else if paren_lvl = 0 
 			 && is_binop s.[k] 
 			 && (res = -1 || priority s.[k] < priority s.[res]) 
 			 then find_op_paren (k+1) k (paren_lvl)
 		else find_op_paren (k+1) res (paren_lvl)
 	in find_op_paren i (-1) 0;;

(* Renvoie une formule construite à partir de la chaîne s.
   Lève une exception Erreur_syntaxe si la chaîne ne représente pas une formule valide. *)
let parse (s: string) : formule =
	let n = String.length s in
	(* construit une formule à partir de s[i..j] *)
	let rec parse_aux (i: int) (j:int) =
		if not (0 <= i && i < n && 0 <= j && j < n && i <= j ) then raise Erreur_syntaxe else
		if s.[i] = ' ' then parse_aux (i+1) j
		else if s.[j] = ' ' then parse_aux i (j-1)
		else let k = find_op_surface s i j in 
		if k = -1 then
			if s.[i] = '~' then 
				Not (parse_aux (i+1) j)
			else if s.[i] = '(' then
				begin 
					if (s.[j] != ')') then (print_int j; failwith "mauvais parenthésage") else
					parse_aux (i+1) (j-1)
				end
			else if (i = j && s.[i] = 'T') then Top
			else if (i = j && s.[i] = 'F') then Bot
			else let nom_variable = String.sub s i (j-i+1) in 
			if String.contains nom_variable ' ' then raise Erreur_syntaxe else Var nom_variable

		else match s.[k] with
			| '&' -> And(parse_aux i (k-1), parse_aux (k+1) j)
			| '|' -> Or(parse_aux i (k-1), parse_aux (k+1) j)
			| '=' -> equivalence(parse_aux i (k-1), parse_aux (k+1) j)
			| '>' -> implique(parse_aux i (k-1), parse_aux (k+1) j)
			| _ -> raise Erreur_syntaxe
	in parse_aux 0 (String.length s -1)

(* Renvoie une formule construire à partir du contenu du fichier fn.
   Lève une exception Erreur_syntaxe si le contenu du fichier n'est pas une formule valide.
   Lève une exception Sys_error(message_erreur) si le nom du fichier n'est pas valide. *)
let from_file (filename: string) : formule = 
	(* concatène toutes les lignes de f en une seule chaîne *)
	let rec read_lines f = 
		try 
			let next_line = input_line f in
			let s = read_lines f in
			next_line ^ s
		with 
			| End_of_file -> ""
	in
	let f = open_in filename in 
	let s = read_lines f in
	parse s

let test_parse () =
	assert (parse "a | (b & ~c)" = Or(Var "a", And(Var "b", Not (Var "c"))));
  assert (parse "a | b" = Or(Var "a", Var "b"))

let test_from_file () =
  assert (from_file "./tests/a" = Or(Var "a", And(Var "b", Not(Var "c"))));
  assert (from_file "./tests/b" = Or(Var "a", Not(And(Var "b", Var "c"))))



let read_file (fn:string) : string = 
  let ic = open_in fn in
  let res = input_line ic in 
  close_in ic; res

let rec compte_ops (f: formule) : int =
  match f with
  | Var(_) | Top | Bot -> 0
  | Not(s) -> 1 + compte_ops s
  | And(a,b) | Or(a,b) -> 1 + compte_ops a + compte_ops b

let test_compte_ops () = 
  assert (compte_ops (parse "x|(y&~z)")=3);
  assert(compte_ops(parse "~(x|(x&~z)|y)")=5)


let rec sorted_list (l: 'a list) : bool = 
  match l with
  | [] | [_] -> true
  | a::b::q -> a < b && sorted_list (b::q)

let  union (a: 'a list) (b: 'a list) : 'a list =
  let rec union_concat (a: 'a list) (b: 'a list) (acc: 'a list) : 'a list =
    match a,b with 
    | [], [] -> List.rev acc
    | [], x::q -> union_concat a q (x::acc)
    | x::q, [] -> union_concat q b (x::acc)
    | x::q, y::q' -> if x<y then union_concat q b (x::acc)
    else union_concat a q' (y::acc)
  in union_concat a b []

let rec liste_var (f: formule) : string list =
  match f with
  | Top | Bot -> []
  | Var(s) -> [s]
  | Not(a) -> liste_var a
  | And(a,b) | Or(a,b) -> (liste_var a) @ (liste_var b)


let rec evaluate (s: valuation) (f: formule) : bool =
  match f with
  | Top -> true
  | Bot -> false
  | Var(m) -> List.assoc m s
  | Not(a) -> not (evaluate s a)
  | And(a,b) -> (evaluate s a) && (evaluate s b)
  | Or(a,b) -> (evaluate s a) || (evaluate s b)

let rec add_one (l: bool list) : bool list = 
  match l with
  | [] -> [true]
  | false::q -> [true]@q
  | true::q -> [false] @ (add_one q)

let valuation_next (v: valuation) : valuation option = 
  if List.for_all (fun x -> snd x = true) v then None
  else
    let order = List.map snd v in
    let variables = List.map fst v in
    let next_order = add_one order in
    Some (List.combine variables next_order)

let valuation_init (l: string list) : valuation = 
  let len = List.length l in
  let values = List.init len (fun _ -> false) in
  List.combine l values

let satsolver_naif (f:formule) : sat_result = 
  let rec eval (f: formule) (s: valuation) : sat_result =
    match evaluate s f with
    | true -> Some s
    | false -> 
      begin 
        match valuation_next s with
        | None -> None
        | Some s' -> eval f s'
      end
  in eval f (valuation_init (liste_var f))

(*
[("x",false);("y",true);("z",true)]
*)

let test () = 
  test_parse (); test_from_file ();
  assert (sorted_list [1;2;4;6]);
  assert (not (sorted_list [1;2;4;4]));
  assert (union [1;2;4] [3;5;6;7] = [1; 2; 3; 4; 5; 6; 7]);
  assert (liste_var (parse "x|(y&~z)") = ["x"; "y"; "z"]);
  assert (evaluate [("x",true);("y",false)] (Or(Var "x",Var"y")) = true);
  assert (add_one [false; true] = [true;true]);
  assert (add_one [true;true;false]=[false;false;true]);
  assert (add_one [true;true]=[false;false;true]);
  assert (valuation_next [("x",true);("y",true);("z",true)] = None);
  assert (valuation_next [("x",true);("y",false);("z",true)] = Some ([("x",false);("y",true);("z",true)]));
  assert (valuation_init ["x";"y"] = [("x",false);("y",false)]);
  assert (satsolver_naif (And(Var "x", Var"y")) = Some [("x", true); ("y", true)]);
  assert (satsolver_naif (And(Var "x", Not(Var "x"))) = None);
  print_string "Tests OK\n"

let main () =
  test();
  match Array.length Sys.argv with
  | 1 -> failwith "Pas d'arguments"
  | _ -> print_string (read_file (Sys.argv.(1)))

let _ = main()
