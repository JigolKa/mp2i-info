type graphe = int list array

let g0 = [|
  [1];
  [2;3];
  [0;3];
  []
|]

let degre_moyen (g: graphe) : float =
  let n = Array.length g in
  let sum = ref 0. in 
  for i=0 to n-1 do
    sum:=!sum +. float_of_int (List.length (g.(i)))
  done;!sum/. (float_of_int n)

let est_arc (g: graphe) (u: int) (v: int) : bool =
  List.exists (fun j -> j=v) g.(u)

let ajouter_arc (g:graphe) (u: int) (v:int) : unit =
  g.(u) <- [v] @ g.(u)

let renverser (g:graphe) : graphe =
  let n = Array.length g in
  let ans = Array.make n [] in
  for u=0 to n-1 do
    List.iter (fun v ->  ajouter_arc ans v u) g.(u)
  done; ans