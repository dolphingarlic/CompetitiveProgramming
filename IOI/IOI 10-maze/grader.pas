program grader;
uses fielddata;
const
  dir: array[1..4, 1..2] of longint = ((-1, 0), (1, 0), (0, -1), (0, 1));
  huge: longint = 60000;
var
  grid: array [1..300] of string;
  r, c: longint;
  sr, sc: longint;
  id, score: longint;

  Q: array [1..50000, 1..2] of longint;
  d: array [1..300, 1..300] of longint;
  tail: longint;

procedure checksubset;
var
  i, j: longint;
begin
  if (r <> mazes[id].r) or (c <> mazes[id].c) then
    exit;
  for i := 1 to r do
    for j := 1 to c do
      if(grid[i][j] = '.') then
        begin
          if(mazes[id].grid[i][j] <> '#') then exit;
        end
      else if(grid[i][j] <> mazes[id].grid[i][j]) then exit;
  writeln('OK ', id, ' ', score);
  halt;
end;

procedure findstart;
var
  i, j, count: longint;
begin
  count := 0;
  for i := 1 to r do
    for j := 1 to c do
      if ((i = 1) or (j = 1) or (i = r) or (j = c)) and (grid[i][j] = '.') then
        begin 
          inc(count);
          sr := i;
          sc := j;
        end;
  if count <> 1 then
    begin
      halt(91);
    end;
end;

procedure consider(r1, c1, d1:longint);
begin
  if (r1 >= 1) and (r1 <= r) and (c1 >= 1) and (c1 <= c) and
    (grid[r1][c1] = '.') and (d1 < d[r1][c1]) then
    begin
      if d1 > score then score := d1;
      d[r1][c1] := d1;
      inc(tail);
      q[tail][1] := r1;
      q[tail][2] := c1;
    end;
end;

procedure BFS;
var
  i, j, r1, c1: longint; 
begin 
  for i := 1 to r do
    for j := 1 to c do
      d[i][j] := huge;
  tail := 0;
  score := 0;
  consider(sr, sc, 1);
  i := 1;
  while i <= tail do
    begin
      for j := 1 to 4 do
        begin
          r1 := q[i][1] + dir[j][1];
          c1 := q[i][2] + dir[j][2];
          consider(r1, c1, d[q[i][1]][q[i][2]] + 1);
        end;
      inc(i);
    end;
end;

begin
  r := 0;
  while not eof do
    begin
       inc(r);
      readln(grid[r]);
    end;
  c := length(grid[1]);
  findstart;
  BFS;
  for id := 1 to 10 do
    checksubset;
  halt(91);
end.
