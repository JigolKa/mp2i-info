type 'a ab = V | N of 'a * 'a ab * 'a ab

let dfs (a: 'a ab) : 'a list =
  match a with
  | V -> []
  | N(v,g,d) -> 
    let p = ref [] in
    let res = ref [] in
    p := a::!p;
    (* print_int (List.hd !p); *)
    while !p <> [] do
      let u = List.hd !p in
      p:=List.tl !p; 
      match u with
      | V -> ()
      | N(a',g',d') -> 
        (res:=a'::!res;
        p:=g'::!p;
        p:=d'::!p; ())

    done; !res

type formule =
 | Top | Bot | Var of int
 | And of formule * formule
 | Or of formule * formule
 | Not of formule

let nombre_var (f: formule) (n: int) : int array =
  let res = Array.make n 0 in
  match f with
  | Top | Bot -> res
  | Var(x) -> res.(x)<-1;res
  | _ ->
    let pile = ref [] in
    pile:=f::!pile;
    while !pile<>[] do
      let u = List.hd !pile in
      pile := List.tl !pile;
      match u with 
      | Bot | Top -> ()
      | Var(x) -> res.(x)<-res.(x)+1
      | And(a,b) | Or(a,b) -> (pile:=a::!pile;pile:=b::!pile)
      | Not(a) -> pile:=a::!pile
    done; res