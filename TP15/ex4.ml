type graphe = int list array


let dfs_iter (g: graphe) (s: int) : int array =
  let n = Array.length g in
  let st = Stack.create () in
  Stack.push s st;
  let pr = Array.make n (-1) in
  pr.(s)<-s;

  while not (Stack.is_empty st) do
    let cur = Stack.top st in
    Stack.pop st;
    List.iter (fun v ->
      if pr.(v) = -1 then
        begin
        Stack.push v st;
        pr.(v)<-cur
        end
    ) (List.rev g.(cur))
  done; pr

let dfs_rec (g: graphe) (s: int) : int array =
  let n = Array.length g in
  let pr = Array.make n (-1) in
  pr.(s)<-s;
  let rec dfs (cur: int) =
    List.iter (fun v -> if pr.(v) = -1 then 
        begin
          pr.(v)<-cur;
          dfs v
        end
      ) g.(cur)
  in dfs s; pr


let g = [|
  [4;1];
  [0;3;2];
  [3;1];
  [2;1];
  [0]
|]

let g2 = [|
  [1;2];
  [0;2];
  [0;1]
|]