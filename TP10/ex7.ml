type expr = 
  | Const of float
  | Add of expr * expr
  | Mul of expr*expr
  | Val of string
  | IFTE of boolexpr * expr * expr
and boolexpr = 
  | BConst of bool (* constantes true et false *)
  | Or of boolexpr * boolexpr (* OU booléen *)
  | And of boolexpr * boolexpr (* ET booléen *)
  | Not of boolexpr (* NON booléen *)
  | Eq of expr * expr (* égalité *)
  | Leq of expr * expr (* inférieur ou égal *)

type context = (string*float) list

let rec get_var (s:string) (c:context) : float = 
  match c with
  | [] -> failwith "not in context"
  | a::q -> if fst a <> s then get_var s q else snd a

let rec eval (e: expr) (c:context) : float =
  match e with
  | Const(a) -> a
  | Val(s) -> get_var s c
  | Add(x,y) -> eval x +. eval y
  | Mul(x,y) -> eval x *. eval y
  | IFTE(b,e1,e2) -> if eval_bool b then eval e1 else eval e2

and eval_bool (b:boolexpr) : bool =
  match b with
  | Bconst(x) -> x
  | Or(x,y) -> eval_bool x || eval_bool y
  | And(x,y) -> eval_bool x && eval_bool y
  | Not(x) -> not eval_bool x
  | Eq(x,y) -> eval x  = eval y
  | Leq(x,y) -> eval a <= eval b

