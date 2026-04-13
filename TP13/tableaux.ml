type 'a arbre =  
  | V
  | N of 'a * 'a arbre * 'a arbre
  
let max a b = if a > b then a else b

let maxi (t: int array) : int =
  let n = Array.length t in
  let rec maxi_from (i: int) : int =
    if i >= n then Stdlib.min_int
    else max t.(i) (maxi_from (i+1))
  in maxi_from 0


let range (n: int) : int array =
  let a = Array.make n 0 in 
  let rec modify (i: int) : unit =
    if i >= n then ()
    else (a.(i) <- i; modify (i+1))
  in modify 0; a

(* let copy_array (src: 'a array) (dst_length: int) (start_idx: int) : 'a array =
  let dst = Array.make dst_length 0 in
  let rec modify (i: int) =
    if i>=dst_length then ()
    else (dst.(i)<-src.(i+start_idx); modify(i+1))
  in modify 0; dst *)

let construire (t: int array) : int arbre =
  let n = Array.length t in
  let rec construire_range (a: int) (b: int) : int arbre =
    let n = b-a+1 in
    if n = 0 then V 
    else 
    let m =(a+b) /2 in
    let g = construire_range a (m-1) in
    let d = construire_range (m+1) b in
    N(t.(m), g, d) 
  in construire_range 0 (n-1)