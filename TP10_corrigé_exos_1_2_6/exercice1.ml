(* somme des éléments de l *)
let rec somme (l: int list) : int = 
	match l with 
	| [] -> 0
	| x :: q -> x + somme q 

let test_somme () =
	assert (somme [] = 0);
	assert (somme [2; 3; 4] = 9);
	assert (somme [1; 12; -4; 7] = 16)

(* true si x est dans l, false sinon *)
let rec recherche (x: 'a) (l: 'a list) : bool =
	match l with 
	| [] -> false
	(* On ne peut pas mettre x dans le motif
	   car un motif sert à décrire une forme
	   et pas une valeur *)
	| y :: q -> if x = y then true else recherche x q

let test_recherche () =
	assert (recherche 5 [1; 3; 5; 2; 0]);
	assert (not (recherche 5 []));
	assert (not (recherche 5 [1; 3; 7; 0; 4; 2; 4]))

(* [x1; .. xn; y1; ...; ym],
   où l1 = [x1; ...; xn] et l2 = [y1; ...; ym] *)
 let rec concatener (l1: 'a list) (l2: 'a list) : 'a list =
 	match l1 with 
 	| [] -> l2
 	| x :: q -> x :: concatener q l2

let test_concatener () =
	assert (concatener [1;2;3] [4;5;6] = [1;2;3;4;5;6]);
	assert (concatener [1;2;3] [] = [1;2;3]);
	assert (concatener [] [1;2;3] = [1;2;3])

(* concaténation de toutes les listes contenues dans l *)
 let rec multi_concat (ll: 'a list list) : 'a list =
 	match ll with 
 	| [] -> []
 	| l :: qq -> concatener l (multi_concat qq)

let test_multi_concat () =
	assert (multi_concat [[1;2]; [3;4;5;6]; []; [7;8]] = [1;2;3;4;5;6;7;8]);
	assert (multi_concat [] = []);
	assert (multi_concat [[]] = [])

 (* [f x1; f x2; ...; f xn],
    où l = [x1; x2; ...; xn] *)
let rec map (f: 'a -> 'b) (l: 'a list) : 'b list =
	match l with 
	| [] -> []
	| x :: q -> f x :: map f q

let test_map () =
	assert (map (fun x -> x + 5) [1;2;3;4] = [6;7;8;9]);
	assert (map ((=) 4) [1; 3; 4; 2; 4] = [false;false;true;false;true])


(* concaténation de (l1 renversée) et l2 *)
let rec rev_concat (l1: 'a list) (l2: 'a list) : 'a list =
	match l1 with 
	| [] -> l2
	| x :: q -> rev_concat q (x::l2)

(* l dans l'ordre inverse *)
let reverse (l: 'a list) : 'a list =
	rev_concat l []

let test_reverse () =
	assert (reverse [1;2;3;4;5] = [5;4;3;2;1])

(* range_concat n = [0; ...; n-1] concaténé avec l *)
let rec range_concat (n: int) (l: int list) : int list =
	if n = 0 then l
	else range_concat (n-1) ((n-1)::l)

(* [0; ...; n-1] *)
let range (n: int) : int list = range_concat n []

let test_range () =
	assert (range 7 = [0;1;2;3;4;5;6]);
	assert (range 0 = [])

let test () =
	test_somme ();
	test_recherche ();
	test_map ();
	test_concatener ();
	test_multi_concat ();
	test_reverse ();
	test_range ();
	print_string "Tests réussis !\n"
