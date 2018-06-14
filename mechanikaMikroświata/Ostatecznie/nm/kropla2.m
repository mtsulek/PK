%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%krople ocatve
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%
%  Uklad N-rownan (N=2 u Pana?)  postaci
%  dz/dt = F(t,z)
%

% czyli np dla 2 zmiennych z_1, z_2
%  dz_1/dt = F_1 (t, z_1, z_2)
%  dz_2/dt = F_2 (t, z_1, z_2)
% po prawej stronie nie moze byc zalez<nosc od pochodnych - tak trzeba przedefiniowac oryginalne rownania
%
% przedzial czasu dla calkowania
%
tzakres  = [0.0 3.0];
tzakres2  = [0.9 3.0];
%
% warunki poczatkowe dla zmiennych: zm(1), zm(2) ... Tzn ich wartosci dla poczatkowego czasu z tzakres
% elementow tyle ile rownan (tyle ile zmiennych) - trzeba porownac i uzgodnic z funkcja opisujaca rownania ODE!
% MUSI BYC CONSYSTENTNE

warpocz = [0.001 0.0];

%
%  ponizej definicje opcji dla integratora ode45(...) 
%

mojeopcje   = odeset ('RelTol', 1e-6, 'AbsTol', 1e-6, 'InitialStep', 0.01, 'MaxStep', 1.0);

% wywolanie procedury calkowania numerycznego Runge-Kutta
%
%   f_kropli2 - funkcja wywowlywana wewnetrznie przez ode45(..) - okresla uklad rownan rozniczkowych
%             z rownan wynika jaki sens maja poszczegolne zmienne (tzn ktora jest promieniem, predkoscią masą , pedem zaleznym od czasu, itp)
%

[tt, zz] = ode45(@f_kropli2, tzakres, warpocz, mojeopcje); %nazwa pliku: ode_1; zalezne od (wartosc t, wartosc r)
[ww, aa] = ode45(@f_kropli2, tzakres2, warpocz, mojeopcje);

%[tt,zz] = ode45(9.8*0.14+5, tzakres, warpocz, mojeopcje);
%
%
%  tt - kolumna zawiera chwile czasu dla ktorych ode45 policzyl wartosci zmiennych z(1) itp
%  zz - macierz, ktorej poszczegolne kolumny odpowiadaja poszczegolnym zmiennym
%
%  t0  z_1(0)  z_2(0)
%  t1  z_1(1)  z_2(1)
%  t2  z_1(2)  z_2(2)
%    .............
%
% ilustracja/wykres (postprodukacja)
% 
%   ponizej na dwa sposoby rysujemy zaleznosc 2-szej zmiennej od czasu
%
%  niebieska (b-lue) linia przerywana
%
h1 = plot(tt, zz(:,2), "b--");
%
% nalozona z 
% 
hold on
%
% czerownymi (r-ed) kropkami: choci o to aby zobaczyc jak gesto sa faktycznie wyliczone punkty przez ODE45
% warto zauwazyc, ze wielkosc kroku czasowego dobiera sobie ODE45(...) na podstawie m.in zadeklarowanych opcji...
%
h3 = plot(ww, 9.8/7*ww+3,"go");%g/7+const
hold on

h2 = plot(tt, zz(:,2),"ro");
hold off

id = gca;%? to sluzy do zmiany wlasciwosci grafiki - przykladowo, wielkosc czcionki:
set(id,'FontSize',24.0);


%
% cechy wykresow, do ktorych wczesniej zdefiniowalismy "uchwyty" h1, h2...
% grubosc kresek, wielkosc punktow itp
%
set(h2,'MarkerSize',10.0);
set(h1,'LineWidth',4.0);
set(h2,'LineWidth',4.0);
set(h3,'LineWidth',4.0);
legend('ODE45',"g/7+3",'ODE45',1)
title(['model spadku kropli w chmurze'])
xlabel('t[s]')
ylabel('v(t)[m/s]')

axis ([0 3 0 11]);

% koniec skryptu
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%