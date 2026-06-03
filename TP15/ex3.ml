type graphe = int list array

let g= [|
  [1];
  [2;3];
  [0;3];
  []
|]

let arborescence_dfs (g: graphe) (s: int) : int array =
  let n = Array.length g in
  let vus = Array.make n false in
  let pr = Array.make n (-1) in
  pr.(s)<-s;
  let st = Stack.create () in
  vus.(s) <- true;
  Stack.push s st;

  while not (Stack.is_empty st) do
    let u = Stack.pop st in
    List.iter (fun v -> 
      if not vus.(v) then begin
        vus.(v)<-true; pr.(v)<-u;Stack.push v st
    end) g.(u)
  done; pr

let rec reconstruction (pr: int array) (u: int) : int list =
  match pr.(u) with
  | -1 -> []
  | k when k=u -> [k]
  | _ -> reconstruction pr (pr.(u)) @ [u]