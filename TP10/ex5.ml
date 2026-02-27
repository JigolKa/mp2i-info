type boisson =
  | Eau
  | Jus of string
  | Cola of bool
  | Cocktail of boisson * boisson * float

let rec prix (b: boisson) : float =
  match b with
  | Eau -> 0.
  | Jus(fruit) -> if fruit = "ramboutan" then 5.3 else 4.
  | Cola(_) -> 1.
  | Cocktail (x, y, p) -> p *. (prix x) +. (1.-.p) *. (prix y)

let rec shaker (l: boisson list) : boisson =
  assert(l!=[]) ;
  match l with 
  | [a] -> a 
  | a::q -> Cocktail (a, shaker q, 0.5)

let string_of_boisson (a: boisson) : string =
  match a with
  | Eau -> "eau"
  | Cola _ -> "cola"
  | Jus _ -> "jus"
  | _ -> ""

let ingredients (b:boisson) : (boisson*float) list =
  let rec ingredients_rec (b: boisson) (total: float) : (boisson*float) list =
    match b with
    | Cocktail(x,y,p) -> [(x, p *. total)] @ (ingredients_rec y ((1.-.p)*.total))
    | _ -> [(b, total)]
  in ingredients_rec b 1.

let rec agreg_sum (l: ('a * float)list) : ('a * float)list =
  match l with
  | a::b::q -> 
    if (fst a) <> (fst b) 
    then a :: (agreg_sum (b::q)) 
    else agreg_sum ((fst a, (snd a) +. (snd b))::q)
  | _ -> l

let recette (b:boisson) : unit = 
  let rec display (l: (boisson*float)list) : unit =
    match l with 
    | [] -> ()
    | a::q -> print_string (string_of_boisson b); display q
  in display (agreg_sum(ingredients b))
