type ('a, 'b) abs =
  | F of 'a
  | N of 'b * ('a, 'b) abs * ('a, 'b) abs