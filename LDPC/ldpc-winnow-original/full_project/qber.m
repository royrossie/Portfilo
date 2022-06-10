clear all;close all;

sizeA = [101 Inf];
formatSpec = "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d";
file = fopen ("qber.dat", "r");

A = fscanf (file, formatSpec, sizeA);
A = A';

for i = 2:101;
  plot (A (:,1), A(:,i));
  hold on;
   title ('final result');
  xlabel ('QBER');
ylabel ('Found errors');
set(gca,'xtick',0:10:250);
set(gca,'ytick',0:10:250, 'FontSize',26);
endfor
