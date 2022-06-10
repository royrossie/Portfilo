clear all;close all;

sizeA = [2 Inf];


%formatSpec = "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d";
formatSpec = "%d %d ";
file = fopen ("result_2.dat", "r");

A = fscanf (file, formatSpec, sizeA);
A = A';

%yi = interp1(A (:,1),A(:,2),A(:,2),'spline','extrap')

%for i = 2:101;
  plot (A (:,1), A(:,2), 'Linewidth', 4);
  hold on;
   title ('final result');
   grid minor;
  xlabel ('QBER');
ylabel ('Quantity of same messages');
set(gca,'xtick',0:10:250);
set(gca,'ytick',0:5:50, 'FontSize',26);
  %p = polyfit(A(:,1), A(:,2),1); 
  
%f = polyval (p, A(:,2));
 %   plot (A (:,1), f);
 % plot (yi);
%endfor

