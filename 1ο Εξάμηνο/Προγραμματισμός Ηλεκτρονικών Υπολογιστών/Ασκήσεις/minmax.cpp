#include <pzhelp>
PROGRAM {
  int N, M;
    N=READ_INT();  M=READ_INT();  SKIP_LINE();

      //general board
  int i, j, a[N][M];
for(i=0; i<N; i++)
  for(j=0; j<M; j++)
    a[i][j] = READ_INT();


      //board of columns-the max of each column
  int col[M], c;
col[0] = a[0][0]; c=0;
  FOR(j, 0 TO M-1){
    FOR(i, 1 TO N-1){
      if(a[i][j] > col[c]) col[c] = a[i][j];}
       c = c+1; col[c] = a[0][j+1];}

      //finding the least
  int l=col[0];
for(c=1; c<M; c++)
  if(col[c] < l) l=col[c];
    WRITELN(l);


     //board of rows-the least of each row
  int row[N], r;
row[0] = a[0][0]; r=0;
  FOR(i, 0 TO N-1){
    FOR(j, 1 TO M-1){
      if(a[i][j] < row[r])row[r] = a[i][j];}
      r = r+1; row[r]=a[i+1][0];}


     //finding the max
  int m=row[0];
for(r=1; r<N; r++)
  if(row[r] > m) m = row[r];
    WRITELN(m);
}