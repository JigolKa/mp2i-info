let parent (i: int) =
  assert(i!=0); (i-1)/2

let gauche (i: int) = 2*i+1
let droite (i: int) = 2*i+2

let rec est_tas (t: 'a array) (i: int) : bool=
  let n = Array.length t in
  (if gauche i < n then t.(gauche i) <= t.(i) && est_tas t (gauche i) else true)
  && (if droite i < n then t.(droite i) <= t.(i) && est_tas t (droite i) else true)

let est_tas (t: 'a array) (i: int) : bool =
  let res = ref true in
  for j=1 to i-1 do
    let p = parent i in
    if t.(p) >  t.(j) then res := false
    done; !res


let echanger (t:'a array) (i:int)(j:int):unit=
  let tmp = t.(i) in 
  t.(i)<-t.(j);
  t.(j)<-tmp

let inserer (t: 'a array) (i: int) (x: 'a) : unit =
  t.(i)<-x;
  let cur = ref i in
  while !cur!=0 && t.(parent (!cur)) >= t.(!cur) do
    echanger t (parent (!cur)) !cur;
    cur := parent (!cur)
  done

(* type 'a tas = 'a array * int *)

let tasifier (t: 'a array) : unit =
  let n = Array.length t in
  for i =0 to (n-1) do
    (inserer t i (t.(i)))
  done

let est_bien_place (t: 'a array) (i: int) (j: int) =
  (if gauche j <= i then t.(gauche j) >= t.(j) else true)
  && (if droite j <= i then t.(droite j) >= t.(j) else true)

let bon_enfant (t: 'a array) (i: int) (j: int) : int =
  match (gauche j, droite j) with
  | (a,b) when a<=i && b<=i  -> if t.(a) < t.(b) then a else b
  | (a,b) when a<=i && b>i -> a
  | (a,b) when a>i && b<=i -> b
  | _ -> failwith "0 enfant"

let tas_extraire (t: 'a array) (i: int) : 'a =
  let r = ref 0 in
  let e = t.(!r) in
  let f = i in
  echanger t !r f;
  while not (est_bien_place t (i-1) !r) do
    let n = (bon_enfant t (i-1) !r) in
    echanger t !r n;
    r:=n
  done; e

let tri_tas (t: 'a array) : 'a array =
  tasifier t;
  let n = Array.length t in
  let res = Array.make n 0 in 
  for i = 0 to (n-1) do
    res.(i) <- tas_extraire t (n-1-i)
  done; res
