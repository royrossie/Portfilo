clear all;close all;

sizeA = [2 Inf];


%formatSpec = "%d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d %d";
formatSpec = "%d %d ";
file = fopen ("qber_2.dat", "r");

A = fscanf (file, formatSpec, sizeA);
A = A';
idx = [50, 100]; 

%yi = interp1(A (:,1),A(:,2),A(:,2),'spline','extrap')

%for i = 2:101;
  plot (A (:,1), A(:,2), 'Linewidth', 4);
  hold on;
   title ('final result');
   grid minor;
  xlabel ('QBER');
ylabel ('found errors');
set(gca,'xtick',0:10:250);
set(gca,'ytick',0:10:250, 'FontSize',26);
hold on;
  %p = polyfit(A(:,1), A(:,2),1); 
  hold on;
  
%  temp_y = 0:250;
%  temp_x = ones(1,251);
%  temp_x = temp_x .* 70;
%  plot(temp_y,temp_x);
%f = polyval (p, A(:,2));
 %   plot (A (:,1), f);
 % plot (yi);
%endfor

