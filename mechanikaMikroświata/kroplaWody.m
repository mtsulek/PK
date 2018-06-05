% pkg load symbolic;
% pkg install -forge symbolic;
% pkg install -forge symbolic
% PARAMETRY
% g - stała grawitacyjna; gk - gęstość kropli; gch - gęstosć chmury
g = 9.81;
gk = 1;
gch = 0.1;

% zmienne symboliczne
%syms a x v M t g gk gch g r;
%syms a x
%f = sin(a*x);
%rozniczka = diff(f, a)
%rozniczka2 = diff(f, a, 2)



syms v M t g gk gch g r;
drdt = diff(r, t);

funkcja = 12 * drdt + 4;

 %syms x
 %f = x * cos (x)
 %df = diff (f)
 
 
  %syms y(x) 
 %sqrt2=sym(1.41421);
 %de =diff(y, 3 ) +sqrt2*diff(y,2) + diff(y) == 0;
 %f = dsolve(de, y(0) == 0, diff(y,1)(0) == 0 , diff(y,2)(0) == 1)f
% wynik = dsolve('(12 * Dr) + 4* D2r = r*g*gch/gk', 'r(0) = 0', 'Dr(0) = 1');
% pretty(wynik);

%syms x y;       % definicja zmiennych symbolicznych ‘x’ 
%y = dsolve('D2x + 3*Dx + 2*x=0' , 'x(0)=0' , 'Dx(0)=2');