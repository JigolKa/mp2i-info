type graphe = float array array

let inf = Float.infinity

let distances (g: graphe) : float array array =
  let n = Array.length g in
  let t1 =  (Array.make_matrix n n inf) in
  for i=0 to n-1 do
    for j=0 to n-1 do
      t1.(i).(j)<-g.(i).(j)
    done
  done;
  for i=0 to n-1 do
    t1.(i).(i)<-0.
  done;
  for k=0 to n-1 do
    for i=0 to n-1 do
      for j=0 to n-1 do
        t1.(i).(j) <- min t1.(i).(j) (t1.(i).(k) +. t1.(k).(j))
      done
    done
  done; t1

let graphe = [|
  [|0.;1.;inf;inf;inf|];
  [|1.;0.;1.;inf;3.|];
  [|inf;1.;0.;5.;1.|];
  [|inf;inf;5.;0.;6.|];
  [|inf;3.;1.;6.;0.|]
|]