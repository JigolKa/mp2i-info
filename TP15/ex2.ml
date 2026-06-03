type graphe = int list array

let g= [|
  [1];
  [2;3];
  [0;3];
  []
|]

(* affiche les sommets de g accessibles depuis s,
dans l'ordre d'un parcours en profondeur. *)
let dfs (g: graphe) (s: int) : unit =
  let n = Array.length g in
  let vus = Array.make n false in
  let p = Stack.create () in
  vus.(s) <- true;
  Stack.push s p;

  while not (Stack.is_empty p) do
    let u = Stack.pop p in
    print_int u; print_newline ();

    let voisins = g.(u) in
    List.iter (fun v ->
      if not vus.(v) then begin
      vus.(v) <- true;
      Stack.push v p
    end)
    voisins
  done

let dfs_nombre_accessible (g: graphe) (s: int) : int =
  let n = Array.length g in
  let vus = Array.make n false in
  let p = Stack.create () in
  vus.(s) <- true;
  Stack.push s p;
  let ans = ref 0 in
  
  while not (Stack.is_empty p) do
    let u = Stack.pop p in
    ans := !ans + 1;
    
    List.iter (fun v ->
      if not vus.(v) then begin
      vus.(v) <- true;
      Stack.push v p
    end) g.(u)
  done; !ans

let dfs_liste_accessible (g: graphe) (s: int) : int list =
  let n = Array.length g in
  let vus = Array.make n false in
  let p = Stack.create () in
  vus.(s) <- true;
  Stack.push s p;
  let ans = ref [] in
  
  while not (Stack.is_empty p) do
    let u = Stack.pop p in
    ans := u::!ans;
    
    List.iter (fun v ->
      if not vus.(v) then begin
      vus.(v) <- true;
      Stack.push v p
    end) g.(u)
  done; !ans