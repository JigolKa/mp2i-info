let test () = 
  assert false 

let valider (f: unit->unit) : bool =
  let t () = (f () ; true) in
  try t () with
  | Assert_failure(_) -> false
