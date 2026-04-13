type 'a matrix = 'a array array

let make_matrix (n: int) (m: int) (x: 'a) : 'a matrix =
  let rows = Array.make n [||] in
  for i=0 to n-1 do
    let cols = Array.make m x in
    rows.(i)<-cols
  done; rows

let sommes (src: int matrix) : int matrix =
  let n = Array.length src in
  let m = Array.length src.(0) in
  let res = make_matrix n m (-1) in
  let rec calc (i: int) (j: int) =    
    if i = 0 
      then 
        if j = 0 then res.(i).(j) <- src.(i).(j) else res.(i).(j)<-src.(i).(j)+res.(i).(j-1)
  else begin
    if j = 0 then (assert(i>0); res.(i).(j)<-src.(i).(j)+res.(i-1).(j))
    else
      (assert(i>0&&j>0);
      res.(i).(j)<-res.(i-1).(j)+res.(i).(j-1)-res.(i-1).(j-1)+src.(i).(j))
    end in
  for i = 0 to n-1 do
    for j = 0 to m-1 do
      calc i j
    done
  done; res


let m = [|
  [|2;3;5|];
  [|9;4;1|];
  [|8;6;3|]
|]