%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% (RG) 5/4/2018
% rgebarowski@pk.edu.pl
%
%  
% Fizyka techniczna, modelowanie komputerowe
%
% Przyklad numerycznego calkowania ukladu rownan rozniczkowych zwyczajnych pierwszego rzedu
% Octave/MATLAB
% oscylator tlumiony (1DIM), 
% numeryczne rozwiazanie ukladu 2 rownan z wykorzystaniem  ODE45(...)
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
% parametry fizyczne modelu, wspolczynniki z odpowiednimi jednostkami fizycznymi...
%

m = 2.0;
k = 10.0;
b = 1.0;

%
% definicja ukladu rownan rozniczkowych (ODE);  t -> czas; z(1) -> x(t); z(2) -> vx(t)
%
%   dz(1)/dt = z(2);  dz(2)/dt = - k z(1)/m - b z(2)/m
%
%  (w przypadku zlozonego ODE, warto je zdefiniowac jako funkcje w odrebnym skrypcie *.m)
%

% wywolanie ODE45 i uzyskanie wyniku obliczeń numerycznych
% ic - warunki poczatkowe, t - zakres całkowania numerycznego w zmiennej niezaleznej
% vopcje - parametry dla ODE45 (opcjonalne)

ic = [0.0 1.0];
t  = [0.0 10.0];

[tt, xx] = ode45(@ode_1, t, ic);

% ilustracja/wykres (postprodukacja)

h1 = plot(tt, xx(:,1), "--");
hold on
h2 = plot(tt, xx(:,1), "ro");
hold off

id = gca;
set(id,'FontSize',24.0);

set(h2,'MarkerSize',12.0);
set(h1,'LineWidth',4.0);
set(h2,'LineWidth',4.0);
set(h2,'LineWidth',4.0);

title(['oscylator tlumiony, b = ', num2str(b), ' Ns/m '])
xlabel('t')
ylabel('x(t)')

axis ([0 9 -0.4 0.4]);

% koniec skryptu
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%