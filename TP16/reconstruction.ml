type graphe = float array array
let inf = Float.infinity

let distances (g: graphe) : int array array =
  let n = Array.length g in
  let t1 =  (Array.make_matrix n n inf) in
  let prev = (Array.make_matrix n n (-1)) in
  for i=0 to n-1 do
    for j=0 to n-1 do
      t1.(i).(j)<-g.(i).(j);
      if g.(i).(j) < inf then 
      prev.(i).(j)<-i else prev.(i).(j)<- -1;
    done
  done;
  for i=0 to n-1 do
    t1.(i).(i)<-0.;
    prev.(i).(i)<-i
  done;
  
  for k=0 to n-1 do
    for i=0 to n-1 do
      for j=0 to n-1 do
        if t1.(i).(k) +. t1.(k).(j) < t1.(i).(j) then
          begin
          t1.(i).(j) <- t1.(i).(k) +. t1.(k).(j);
          prev.(i).(j)<-prev.(k).(j)
          end
      done
    done
  done; prev


(* let plus_court_chemin (prev: int array array) (i: int) (j: int) : int list = *)


let graphe = [|
  [|0.;inf;inf;inf;inf|];
  [|inf;0.;1.;inf;3.|];
  [|inf;1.;0.;5.;1.|];
  [|inf;inf;5.;0.;6.|];
  [|inf;3.;1.;6.;0.|]
|]