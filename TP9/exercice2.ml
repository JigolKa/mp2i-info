let delta (a, b, c) = b*b - 4*a*c

let n_roots (a,b,c) = 
  if delta (a,b,c) > 0 then 2 else
    if delta(a,b,c) = 0 then 1 else 
      0

let nom_chiffre d = match d with
      | 2 -> "deux"
      | 3 -> "trois"
      | 4 -> "quatre"
      | 5 -> "cinq"
      | _ -> ""

let f x y = match (x-1, y) with
      | (0,0) -> 0
      | (0,_) -> y+1
      | (z,0)->z+100
      | _ -> x*y

let g x y = match (x-y, x+y) with
      | 0, _ 
      | _,0 -> 0
      | 1, _ 
      | -1, _ -> (x+y)*(x+y) + 1
      | _, 1 
      | _,-1 ->(x-y)*(x-y) - 1
      | _ -> x*y

let h n = if n mod 3 = 0 then "ga" else
  if n mod 5 = 0 then "bu" else
    string_of_int n