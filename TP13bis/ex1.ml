let map (f: 'a -> 'b) (a: 'a array) : 'b array =
  let n = Array.length a in
  for i = 0 to n-1 do
    a.(i) <- f a.(i)
  done; a

let for_all (f: 'a -> bool) (a: 'a array) : bool =
  let res = ref true in
  let n = Array.length a in
  for i =0 to n-1 do
    res := !res && (f a.(i))
  done; !res

let append (x: 'a) (a: 'a array) : 'a array =
  let n = Array.length a in
  let res = Array.make (n+1) 0 in
  for i=0 to n-1 do
    res.(i)<-a.(i)
  done;
  res.(n)<-x;
  res

let concat (a: 'a array) (b: 'a array) : 'a array =
  let res = ref a in
  let nb = Array.length b in
  for i =0 to nb-1 do
    res:=append b.(i) !res
  done; !res

let blit (src: 'a array) (src_pos: int) (dst: 'a array) (dst_pos: int) (len: int) : unit =
  let nsrc = Array.length src in
  let ndst = Array.length dst in
  assert (src_pos+len < nsrc && dst_pos+len<ndst);
  for i = src_pos to src_pos+len-1 do
    dst.(i) <- src.(i)
  done;