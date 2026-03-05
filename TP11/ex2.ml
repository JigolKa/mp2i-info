type ('a, 'b) abs =
  | F of 'a
  | N of 'b * ('a, 'b) abs * ('a, 'b) abs

type ('a, 'b) union = A of 'a | B of 'b

(*
'a est le type des feuilles
'b est le type des noeuds internes

même principe que pour un mot bien parenthésé, avec une "pile"
*)
let construire_post (l: ('a, 'b) union list) : ('a, 'b) abs =
  let rec construire_post_rev (l: ('a, 'b) union list) (stack: ('a, 'b) abs list) : ('a, 'b) abs =
    match l with
    | [] -> begin match stack with
      | x when List.length x = 1 -> List.hd stack
      | _ -> failwith "error"
    end
    | A(a')::l' -> construire_post_rev l' (F(a')::stack) (*([F(a')] @ stack) *)
    | B(b')::l' -> 
      begin match stack with
      | a::b::q -> construire_post_rev l' (N(b', b, a)::q)
      | _ -> failwith "error"
      end
  in construire_post_rev l []
    
let l = [A 5; A 3; B "toto"; A 4; B "ici"]