type formule =
  | Var of string
  | Top
  | Bot
  | And of formule * formule
  | Or of formule * formule
  | Not of formule

let implique (f1, f2) = Or (Not f1, f2)
let equivalence (f1, f2) = And (implique (f1, f2), implique (f2, f1))

type valuation = (string * bool) list
type sat_result = valuation option

(* --------------------------------------------------------------  PARSER *)

exception Erreur_syntaxe
exception Fichier_invalide
exception Argument_failure
exception Liste_vide

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
let is_binop (c : char) : bool =
  match c with '&' | '|' | '>' | '=' -> true | _ -> false

(* Priorité de l'opérateur c. Permet de déterminer
	comment interpréter une formule sans parenthèses.
	Par exemple, "x&y|z" sera interprété comme "(x&y)|z"
	car & est plus prioritaire que | *)
let priority (c : char) : int =
  match c with
  | '&' -> 4
  | '|' -> 3
  | '=' -> 2
  | '>' -> 1
  | _ -> raise Erreur_syntaxe (* c n'est pas un opérateur *)

(* indice de l'opérateur le moins prioritaire parmis ceux
   qui ne sont pas entre parenthèses entre s.[i] et s.[j] 
   inclus *)
let find_op_surface (s : string) (i : int) (j : int) : int =
  (* 
 	   Renvoie l'indice de l'opérateur le moins prioritaire entre
 	   i et j, sachant que res est l'indice du meilleur opérateur
 	   entre i et k-1.
 	   paren_lvl: niveau d'imbrication actuel des parenthèses *)
  let rec find_op_paren (k : int) (res : int) (paren_lvl : int) : int =
    if k = j + 1 then res
    else if s.[k] = '(' then find_op_paren (k + 1) res (paren_lvl + 1)
    else if s.[k] = ')' then find_op_paren (k + 1) res (paren_lvl - 1)
      (* Le caractère lu est pris si l'on est hors des parenthèses,
 		   que le caractère est bien un opérateur, et qu'il est moins
 		   prioritaire que le meilleur résultat jusqu'ici *)
    else if
      paren_lvl = 0
      && is_binop s.[k]
      && (res = -1 || priority s.[k] < priority s.[res])
    then find_op_paren (k + 1) k paren_lvl
    else find_op_paren (k + 1) res paren_lvl
  in
  find_op_paren i (-1) 0

(* Renvoie une formule construite à partir de la chaîne s.
   Lève une exception Erreur_syntaxe si la chaîne ne représente pas une formule valide. *)
let parse (s : string) : formule =
  let n = String.length s in
  (* construit une formule à partir de s[i..j] *)
  let rec parse_aux (i : int) (j : int) =
    if not (0 <= i && i < n && 0 <= j && j < n && i <= j) then
      raise Erreur_syntaxe
    else if s.[i] = ' ' then parse_aux (i + 1) j
    else if s.[j] = ' ' then parse_aux i (j - 1)
    else
      let k = find_op_surface s i j in
      if k = -1 then
        if s.[i] = '~' then Not (parse_aux (i + 1) j)
        else if s.[i] = '(' then begin
          if s.[j] != ')' then (
            print_int j;
            failwith "mauvais parenthésage")
          else parse_aux (i + 1) (j - 1)
        end
        else if i = j && s.[i] = 'T' then Top
        else if i = j && s.[i] = 'F' then Bot
        else
          let nom_variable = String.sub s i (j - i + 1) in
          if String.contains nom_variable ' ' then raise Erreur_syntaxe
          else Var nom_variable
      else
        match s.[k] with
        | '&' -> And (parse_aux i (k - 1), parse_aux (k + 1) j)
        | '|' -> Or (parse_aux i (k - 1), parse_aux (k + 1) j)
        | '=' -> equivalence (parse_aux i (k - 1), parse_aux (k + 1) j)
        | '>' -> implique (parse_aux i (k - 1), parse_aux (k + 1) j)
        | _ -> raise Erreur_syntaxe
  in
  parse_aux 0 (String.length s - 1)

(* Renvoie une formule construire à partir du contenu du fichier fn.
   Lève une exception Erreur_syntaxe si le contenu du fichier n'est pas une formule valide.
   Lève une exception Sys_error(message_erreur) si le nom du fichier n'est pas valide. *)
let from_file (filename : string) : formule =
  (* concatène toutes les lignes de f en une seule chaîne *)
  let rec read_lines f =
    try
      let next_line = input_line f in
      let s = read_lines f in
      next_line ^ s
    with End_of_file -> ""
  in
  let f = open_in filename in
  let s = read_lines f in
  parse s

(* renvoie le contenu du fichier fn sous forme de string 
remarque : fn ne doit être qu'une seule ligne *)
let read_file (fn : string) : string =
  let ic = open_in fn in
  let res = input_line ic in
  close_in ic;
  res

(* renvoie le nombre d'opérateurs utilisés *)
let rec compte_ops (f : formule) : int =
  match f with
  | Var _ | Top | Bot -> 0
  | And (f1, f2) | Or (f1, f2) -> compte_ops f1 + compte_ops f2 + 1
  | Not f1 -> compte_ops f1 + 1

(* renvoie true si l est une liste triée sans doublons *)
let strict_croissante (l : 'a list) : bool =
  (* conserve également le dernier élément vu *)
  let rec strict_croissante_prev (ll : 'a list) (p : 'a) : bool =
    match ll with
    | [] -> true
    | x :: q -> if x <= p then false else strict_croissante_prev q x
  in
  match l with [] -> true | x :: q -> strict_croissante_prev q x

(* tri fusion ordre ddécroissant *)
let rec fusion_sort (l : 'a list) (f : 'a -> 'a -> bool) : 'a list =
  let rec split (l : 'a list) : 'a list * 'a list =
    match l with
    | [] | _ :: [] -> (l, [])
    | x1 :: x2 :: q ->
        let l1, l2 = split q in
        (x1 :: l1, x2 :: l2)
  in
  let rec fuse (l1 : 'a list) (l2 : 'a list) =
    match (l1, l2) with
    | [], l | l, [] -> l
    | x :: l1', y :: l2' -> if f x y then x :: fuse l1' l2 else y :: fuse l1 l2'
  in
  match l with
  | [] | _ :: [] -> l
  | _ ->
      let l1, l2 = split l in
      fuse (fusion_sort l1 f) (fusion_sort l2 f)

(* renvoie une liste contenant l1 et l2 triée sans doublons 
remarque : il faut que l1 et l2 soient triées sans doublons*)
let rec union (l1 : 'a list) (l2 : 'a list) : string list =
  match (l1, l2) with
  | [], l | l, [] -> l
  | x :: l1', y :: l2' ->
      if x < y then x :: union l1' l2
      else if x > y then y :: union l1 l2'
      else x :: union l1' l2'

(* renvoie la liste des variables dans f triée sans doublons*)
let rec variables (f : formule) : 'a list =
  match f with
  | Var v -> v :: []
  | Top | Bot -> []
  | And (f1, f2) | Or (f1, f2) -> union (variables f1) (variables f2)
  | Not f1 -> variables f1

(* --------------------------------------------------------------  SAT *)

(* renvoie f dans la valuation v 
remarques : il faut que toutes les variables de f soit dans v*)
let rec evaluate (f : formule) (v : valuation) : bool =
  match f with
  | Var x -> List.assoc x v
  | Top -> true
  | Bot -> false
  | And (f1, f2) -> evaluate f1 v && evaluate f2 v
  | Or (f1, f2) -> evaluate f1 v || evaluate f2 v
  | Not f1 -> not (evaluate f1 v)

(* ajoute 1 à une écriture binaire petit boutiste 
remarque : si l est une liste vide, renvoie true::[] *)
let rec add_one (l : bool list) : bool list =
  match l with
  | [] -> true :: []
  | true :: q -> false :: add_one q
  | false :: q -> true :: q

(* renvoie la prochaine valuation suivant l'ordre binaire*
remarque : si v est maximal, alors renvoie None *)
let valuation_next (v : valuation) : valuation option =
  let vars = List.map fst v in
  let v_next = add_one (List.map snd v) in
  (* si la liste est plus grande, alors forcément valuation v maximale *)
  if List.length v_next > List.length v then None
  else Some (List.combine vars v_next)

(* renvoie la valuation initiale associée à une liste de variables l correspondant à tout false *)
let rec valuation_init (l : string list) : valuation =
  match l with [] -> [] | x :: q -> (x, false) :: valuation_init q

(* implémentation naïve du SAT solver en itérant à travers toutes les valuations possibles selon l'ordre binaire *)
let satsolver_naif (f : formule) : sat_result =
  let v = ref (Some (valuation_init (variables f))) in
  while !v != None && evaluate f (Option.get !v) = false do
    v := valuation_next (Option.get !v)
  done;
  !v

(* --------------------------------------------------------------  QUINE *)

(* applique une étape de simplificition (dans l'ordre) avec un booléen indiqant si la simplificaiton est possiible *)
let rec simple_step (f : formule) : formule * bool =
  match f with
  | And (Top, f') -> (f', true)
  | And (f', Top) -> (f', true)
  | Or (Top, f') -> (Top, true)
  | Or (f', Top) -> (Top, true)
  | And (Bot, f') -> (Bot, true)
  | And (f', Bot) -> (Bot, true)
  | Or (Bot, f') -> (f', true)
  | Or (f', Bot) -> (f', true)
  | Not (Not f') -> (f', true)
  | Not Bot -> (Top, true)
  | Not Top -> (Bot, true)
  (* récursivité  : règle 8 : *)
  | And (f1, f2) ->
      ( And (fst (simple_step f1), fst (simple_step f2)),
        snd (simple_step f1) || snd (simple_step f2) )
  | Or (f1, f2) ->
      ( Or (fst (simple_step f1), fst (simple_step f2)),
        snd (simple_step f1) || snd (simple_step f2) )
  | Not f' -> (Not (fst (simple_step f')), snd (simple_step f'))
  | _ -> (f, false)

(* simplifie au maximum selon les règles précédentes f *)
let simple_full (f : formule) : formule =
  let f' = ref f in
  while snd (simple_step !f') = true do
    f' := fst (simple_step !f')
  done;
  !f'

(* remplace toute les instances de s dans f par f' *)
let rec subst (f : formule) (s : string) (f' : formule) : formule =
  match f with
  | Var x -> if x = s then f' else Var x
  | And (f1, f2) -> And (subst f1 s f', subst f2 s f')
  | Or (f1, f2) -> Or (subst f1 s f', subst f2 s f')
  | Not f1 -> Not (subst f1 s f')
  | _ -> f

(* renvoie le nombre d'occurences de chaque variable dans f *)
let rec occ_variables (f : formule) (vars : string list) : (string * int) list =
  (* renvoie le nombre d'occurence de var dans ff *)
  let rec occ_variable (ff : formule) (var : string) (r : int) : int =
    match ff with
    | Var v -> r + 1
    | And (f1, f2) | Or (f1, f2) ->
        let r' = occ_variable f1 var r in
        occ_variable f2 var r'
    | Not f1 -> occ_variable f1 var r
    | _ -> r
  in
  match vars with
  | [] -> []
  | var :: q -> (var, occ_variable f var 0) :: occ_variables f q

(* algorithme de quine *)
let quine (f : formule) : sat_result =
  let rec quine_vars (ff : formule) (occ_vars : (string * int) list) :
      sat_result =
    match simple_full ff with
    | Top -> Some []
    | Bot -> None
    | _ -> (
        match occ_vars with
        | [] -> raise Liste_vide
        | x :: q -> begin
            let var = fst x in
            let f_top = simple_full (subst ff var Top) in
            let res_top = quine_vars f_top q in
            match res_top with
            | Some assign -> Some ((var, true) :: assign)
            | None -> begin
                let f_bot = simple_full (subst ff var Bot) in
                let res_bot = quine_vars f_bot q in
                match res_bot with
                | Some assign -> Some ((var, false) :: assign)
                | None -> None
              end
          end)
  in
  let cmp (v1 : string * int) (v2 : string * int) : bool =
    if snd v1 >= snd v2 then true else false
  in
  quine_vars f (fusion_sort (occ_variables f (variables f)) cmp)

(* affiche l'ensemble des valeurs mises à vraies dans une valuation (une par ligne) *)
let rec print_true (v : valuation) : unit =
  match v with
  | [] -> ()
  | (var, b) :: q ->
      if b = true then print_string (var ^ "\n");
      print_true q

(* --------------------------------------------------------------  TESTS *)
let t_parse () =
  assert (parse "a | (b & ~c)" = Or (Var "a", And (Var "b", Not (Var "c"))));
  assert (
    parse "((a & ~b) & ~c) > (d | ~e)"
    = implique
        ( And (And (Var "a", Not (Var "b")), Not (Var "c")),
          Or (Var "d", Not (Var "e")) ))

let t_from_file () =
  assert (from_file "tests/test1" = Or (Var "a", And (Var "b", Not (Var "c"))));
  assert (
    from_file "tests/test2"
    = implique
        ( And (And (Var "a", Not (Var "b")), Not (Var "c")),
          Or (Var "d", Not (Var "e")) ))

let t_compte_ops () =
  assert (compte_ops (parse "a | (b & ~c)") = 3);
  assert (compte_ops (parse "((a & ~b) & ~c) > (d | ~e)") = 8)

let t_stric_croissante () =
  assert (strict_croissante [ "a"; "b"; "d"; "g" ] = true);
  assert (strict_croissante [ "a"; "a"; "c"; "h" ] = false);
  assert (strict_croissante [ "c"; "d"; "a"; "e" ] = false)

let t_union () =
  assert (
    union [ "a"; "b"; "d"; "g" ] [ "c"; "d"; "e" ]
    = [ "a"; "b"; "c"; "d"; "e"; "g" ]);
  assert (union [ "a" ] [ "a"; "b" ] = [ "a"; "b" ])

let t_variables () =
  assert (
    variables (Or (Var "a", And (Var "b", Not (Var "c")))) = [ "a"; "b"; "c" ]);
  assert (
    variables
      (implique
         ( And (And (Var "b", Not (Var "c")), Not (Var "e")),
           Or (Var "a", Not (Var "d")) ))
    = [ "a"; "b"; "c"; "d"; "e" ])

let t_evaluate () =
  assert (
    evaluate
      (Or (Var "a", And (Var "b", Not (Var "c"))))
      [ ("a", true); ("b", false); ("c", false) ]
    = true);
  assert (
    evaluate
      (implique
         ( And (And (Var "a", Not (Var "b")), Not (Var "c")),
           Or (Var "d", Not (Var "e")) ))
      [ ("a", true); ("b", false); ("c", false); ("d", false); ("e", true) ]
    = false)

let t_add_one () =
  assert (add_one [] = [ true ]);
  assert (add_one [ true ] = [ false; true ]);
  assert (add_one [ true; true; false; true ] = [ false; false; true; true ])

let t_valuation_next () =
  assert (
    valuation_next [ ("x", false); ("y", true); ("z", false) ]
    = Some [ ("x", true); ("y", true); ("z", false) ]);
  assert (valuation_next [ ("x", true); ("y", true); ("z", true) ] = None)

let t_valuation_init () =
  assert (
    valuation_init [ "x"; "y"; "z" ]
    = [ ("x", false); ("y", false); ("z", false) ])

let t_satsolver_naif () =
  assert (satsolver_naif (And (Var "a", Not (Var "a"))) = None);
  assert (
    satsolver_naif (Or (Var "a", And (Var "b", Not (Var "c"))))
    = Some [ ("a", true); ("b", false); ("c", false) ]);
  assert (
    satsolver_naif
      (implique
         ( And (And (Var "a", Not (Var "b")), Not (Var "c")),
           Or (Var "d", Not (Var "e")) ))
    = Some
        [ ("a", false); ("b", false); ("c", false); ("d", false); ("e", false) ])

let t_simple_full () =
  assert (
    simple_full
      (implique
         (And (And (Top, Not Bot), Not (Var "a")), Or (Var "b", Not Bot)))
    = Top);
  assert (
    simple_full (Or (Var "a", And (Var "b", Not (Var "c"))))
    = Or (Var "a", And (Var "b", Not (Var "c"))));
  assert (
    simple_full
      (implique
         (And (And (Var "a", Not Bot), Not (Var "b")), Or (Var "c", Not Top)))
    = implique (And (Var "a", Not (Var "b")), Var "c"))

let t_subst () =
  assert (
    subst (Or (Var "a", And (Var "b", Not (Var "c")))) "a" Top
    = Or (Top, And (Var "b", Not (Var "c"))));
  assert (
    subst
      (implique
         ( And (And (Var "a", Not (Var "b")), Not (Var "c")),
           Or (Var "b", Not (Var "e")) ))
      "b" (Not Bot)
    = implique
        ( And (And (Var "a", Not (Not Bot)), Not (Var "c")),
          Or (Not Bot, Not (Var "e")) ))

(* renvoie true si t réussi, false sinon. *)
let valider (t : unit -> unit) : bool =
  try
    let _ = t () in
    true
  with
  | Assert_failure _ -> false
  | Erreur_syntaxe -> false

let tests () =
  if valider t_parse = false then print_string "Erreur : t_parse \n";
  if valider t_from_file = false then print_string "Erreur : t_from_file \n";
  if valider t_compte_ops = false then print_string "Erreur : t_compte_ops \n";
  if valider t_stric_croissante = false then
    print_string "Erreur : t_stric_croissante \n";
  if valider t_union = false then print_string "Erreur : t_union \n";
  if valider t_variables = false then print_string "Erreur : t_variables \n";
  if valider t_evaluate = false then print_string "Erreur : t_evaluate \n";
  if valider t_add_one = false then print_string "Erreur : t_add_one \n";
  if valider t_valuation_next = false then
    print_string "Erreur : t_valuation_next \n";
  if valider t_valuation_init = false then
    print_string "Erreur : t_valuation_init \n";
  if valider t_satsolver_naif = false then
    print_string "Erreur : t_satsolver_naif \n";
  if valider t_simple_full = false then print_string "Erreur : t_simple_full \n";
  print_string "Tous les tests ont réussi ! \n\n"

(* --------------------------------------------------------------  MAIN *)

let main () =
  try
    if Array.length Sys.argv = 1 then raise Argument_failure;
    if Sys.argv.(1) = "test" then (
      print_string "Vérification des tests... \n";
      tests ())
    else
      let sat = quine (from_file Sys.argv.(1)) in
      if sat = None then print_string "IMPOSSIBLE \n\n"
      else (
        print_string
          "La formule est satisfiable en assignant 1 aux variables suivantes \
           et 0 aux autres : \n";
        print_true (Option.get sat);
        print_string "\n")
  with Argument_failure ->
    print_string "Argument Failure : not enough arguments \n\n"

let _ = main ()
