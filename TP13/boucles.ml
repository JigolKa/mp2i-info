let tri_selection (t: int array) : int array =
  let n = Array.length t in
  for i = 0 to (n-1) do
    let mini = ref t.(i) in
    let idx = ref i in
    for j = i + 1 to (n-1) do
      if !mini > t.(j) then 
        (idx := j; mini := t.(j))
    done;
    let tmp = t.(i) in
    t.(i) <- t.(!idx);
    t.(!idx) <- tmp
  done; t

(* t est trié *)
let dichotomie (t: 'a array) (x: 'a) : bool =
  let res = ref false in
  let low = ref 0 in 
  let high = ref (Array.length t - 1) in
  while (!high >= !low && not !res) do
    let mid = !low + (!high - !low)/2 in
    if x=t.(mid) then res := true
    else if x>t.(mid) then low := mid+1
    else high := mid-1
  done; !res
