#include <pzhelp>
PROGRAM{
  int N, M;
  N=READ_INT();  M=READ_INT();  SKIP_LINE();

   //general board
  int i, j;  REAL a[N][M];
for(i=0; i<N; i++)
  for(j=0; j<M; j++)
    a[i][j]=READ_REAL();


   //board of rows - the sum of each row
  int r=0; REAL sumrow[N];  sumrow[0]=a[0][0];
 for(i=0; i<N; i++){
   for(j=1; j<M; j++){ sumrow[r]= sumrow[r]+a[i][j]; }
  r=r+1; sumrow[r]=a[i+1][0];}

   //average of each row
  int v=0, z;  REAL avr[N];  r=0;
 for(z=0; z<N; z++){ avr[v]= sumrow[r]/M; v=v+1; r=r+1; }

   //average of the averages of each row (oof)
  REAL sumavr=0.0, avrf;
 for(v=0; v<N; v++) sumavr = sumavr + avr[v];
 avrf = (sumavr/N);
 WRITELN(FORM(avrf, 0, 3));


   //board of columns - the sum of each column
  int c=0;  REAL sumcol[M];  sumcol[0]=a[0][0];
 for(j=0; j<M; j++){
   for(i=1; i<N; i++){ sumcol[c] = sumcol[c]+a[i][j]; }
  c=c+1; sumcol[c]=a[0][j+1];}

   //average of each column
  int g=0, w;  REAL avc[M]; c=0;
 for(w=0; w<M; w++){ avc[g]= sumcol[c]/N; g=g+1; c=c+1; }

   //average of the averages of each column (big oof)
  REAL avcf, sumavc=0.0;
 for(g=0; g<M; g++) sumavc = sumavc + avc[g];
 avcf = (sumavc/M);
 WRITELN(FORM(avcf, 0, 3));
}