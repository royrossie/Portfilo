clear all;close all;

sizeA = [101 Inf];
formatSpec = "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d";
file = fopen ("result.dat", "r");

A = fscanf (file, formatSpec, sizeA);
A = A';

for i = 2:101;
  plot (A (:,1), A(:,i));
  hold on;
endfor