let print_retour s = 
  print_string s ; print_newline () ;;

let print_pair d = 
  if d mod 3 = 0 then print_int d ;;

let print_pairs (a,b,c) = 
  print_pair a ; print_pair b ; print_pair c ;; 