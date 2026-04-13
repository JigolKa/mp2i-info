type intervalle = int*int

let e = [|(1,2);(2,3);(1,3);(1,1);(2,2);(1,5);(1,4)|]

let compare_intervalle ((d1,f1): intervalle) ((d2,f2): intervalle) : int =
  if f1=f2 then 
    if d1<d2 then -1 else 1
  else if f1<f2 then -1 else 1

let glouton_evenements (l: intervalle array) : bool array =
  Array.sort compare_intervalle l;
  let len = Array.length l in
  let res = Array.make len false in
  let cend = ref 0 in (*end of last event*)

  for i = 0 to len-1 do
    (* print_int !cend ; print_string " ";
    print_int (fst l.(i)) ; print_string " ";
    print_int (snd l.(i)) ; print_string "\n"; *)
    if ((!cend = 0) || (fst l.(i) >= !cend)) then
      begin res.(i) <- true;
      cend := snd l.(i) end
  done; res
