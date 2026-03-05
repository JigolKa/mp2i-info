type pre_tree = Node of (bool * (char * pre_tree) list)

let string_of_list l = String.of_seq (List.to_seq l)


let rec taille (Node(b,l): pre_tree) : int =
  let neighbors = List.map (fun (x: char*pre_tree) -> snd x) l in
  let sum = List.fold_left (+) 0 (List.map taille neighbors) in
  if b = true then 1+sum else sum

let plus_long (Node(b,l):pre_tree) : int =
  let rec plus_long_subtree (Node(b,l):pre_tree) ((cur_depth, maxi): int*int) : int =
    match (b,l) with
    | (true, []) -> max cur_depth maxi
    | (false, []) -> maxi
    | _ -> 
      (* on prend que les pre_tree des descendants et non le charactère *)
      let neighbors = List.map (fun x -> snd x) l in

      (* on initialise une liste d'arguments pour utiliser avec le map2 *)
      let dummy_list = List.init (List.length l) (fun _ -> (cur_depth+1,if b then cur_depth else maxi)) in

      (* map2 applique la fonction récursivement avec la dummy_list *)
      List.fold_left max 0 (List.map2 plus_long_subtree neighbors dummy_list)
      
    in plus_long_subtree (Node(b,l)) (0,0)


(* Renvoie le noeud qui a pour charactère c, None si il n'existe pas *)
let rec find_node (l: (char*pre_tree) list) (c: char) : pre_tree option =
  match l with
  | [] -> None
  | x::q -> if fst x = c then Some (snd x) else (find_node q c)

(* enlève le 1er charactère *)
let cut_first_char s = assert(s!=""); (String.sub s 1 (String.length s -1))

let rec rechercher (s: string) (Node(b,l): pre_tree) : bool =
  match s with
  | "" -> b
  | s -> let node = find_node l s.[0] in
    if node = None then false else rechercher (cut_first_char s) (Option.get node)


let rec ajouter (s: string) (Node(b,l):pre_tree) : pre_tree =
  assert (s!="");
  match s with
  | s when String.length s = 0 -> Node(true, [])
  | _ -> let next_node = find_node l s.[0] in
    let others_node = List.filter (fun x -> fst x != s.[0]) l in
    (* On modifie seulement l'enfant contenant le caractère suivant, on laisse les autres *)
    if next_node != None then Node(b, [(s.[0], (ajouter (cut_first_char s) (Option.get next_node)))] @ others_node )
      (* On créé directement le nouvel enfant *)
    else Node(b, [(s.[0], ajouter (cut_first_char s) (Node(false, [])))] @ others_node)
  
let enumerer (a: pre_tree) : string list =
  let rec dfs (Node(b, l): pre_tree) (cur_word: string) (words_found: string list): string list =
    match List.length l with 
    | 0 -> if b then cur_word::words_found else words_found
    | len ->
      let i_th_neighbor (i:int) =
        let char_in_string = String.init 1 (fun _ -> fst (List.nth l i)) in
        let next_word = cur_word^char_in_string in
        if b then dfs (snd (List.nth l i)) next_word (cur_word::words_found)
        else dfs (snd (List.nth l i)) next_word words_found
      in List.fold_left (@) [] (List.map i_th_neighbor (List.init len (fun x -> x)))
    in List.sort compare (dfs a "" [])

let enumerer_prefixe (pre: string) (ab: pre_tree) : string list =
  List.filter (fun s -> String.starts_with pre s) (enumerer ab)

let construire (a: pre_tree) : pre_tree =
  List.fold_right ajouter (String.split_on_char ' ' (read_line ())) a

let fusion (a: pre_tree) (b: pre_tree) : pre_tree =
  List.fold_right ajouter (enumerer b) a

let t =
 Node(false, [
  ('t', Node(true, [
    ('r', Node(false, [
      ('o', Node(true, []))
    ]))
  ]));
  ('f', Node(false, [
    ('o', Node(true, []))
  ]))
 ])

 let c=Node(false, [])
 let c=ajouter "hello" c 