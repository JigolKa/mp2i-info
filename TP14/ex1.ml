let rendu_glouton (x: int) (pieces: int array) : int array =
  assert (x>=0);
  let v = ref x in
  let len = Array.length pieces in
  let acc = Array.make len 0 in
  for i = len-1 downto 0 do
    if !v >=pieces.(i) then
      acc.(i)<- !v/pieces.(i);
      v:=!v mod pieces.(i)
  done; if !v != 0 then failwith "impossible" else acc
