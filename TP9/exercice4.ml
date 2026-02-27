let rec puiss (x, n)=
  if n<0 then failwith "jkdhzakhd"
  else if n = 0 then 1
  else x*puiss (x,n-1)

let rec puiss2 x n=
  if n<0 then failwith "jkdhzakhd"
  else if n = 0 then 1
  else x*puiss2 x (n-1)

  (* b%a *)
let rec reste a b =
  if (0<=b && b<a) then b
  else reste a (b-a)

let rec pgcd a b =
  if b = 0 then a
  else pgcd b (reste b a)

let square x = x*x

let rec fast_exp x n = 
  if n = 0 then 1
  else if n mod 2 = 0 then square (fast_exp x (n/2))
  else x* square (fast_exp x ((n-1)/2))

  (* a=qb+r *)
let rec div_eucl a b = 
  if a>=b then 
    let res = div_eucl (a-b) b in 
    (1+fst res,snd res)
  else (0,a) (* a<b *)


let rec decomp b x =
  let (q,r) = div_eucl x b in
  if q<0 then failwith "kdhagjd"
  else print_int r ; print_newline () ; decomp b ((x-r)/b) ;; 