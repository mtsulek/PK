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

function dr = oscylator_ode45(t,r)
  dr = zeros(2,1);
  g = 9.8;
  lambda = 1;
  rho = 1000;

  dr(1) = (lambda*r(2))/(4*rho);
  dr(2) = g - (3*lambda*(r(2)^2))/(4*rho*r(1));
end
%
% definicja ukladu rownan rozniczkowych (ODE);  t -> czas; z(1) -> x(t); z(2) -> vx(t)
%
%   dz(1)/dt = z(2);  dz(2)/dt = - k z(1)/m - b z(2)/m
%
%  (w przypadku zlozonego ODE, warto je zdefiniowac jako funkcje w odrebnym skrypcie *.m)
%

kropla = @(t,r) [ r(2); (lambda * r * g /4 *q) - (3 * (r(1) * r(1)))];

% wywolanie ODE45 i uzyskanie wyniku obliczeń numerycznych
% ic - warunki poczatkowe, t - zakres całkowania numerycznego w zmiennej niezaleznej
% vopcje - parametry dla ODE45 (opcjonalne)

ic = [0.0 1.0];
t  = [0.0 10.0];

vopcje   = odeset ('RelTol', 1e-4, 'AbsTol', 1e-4, 'InitialStep', 0.01, 'MaxStep', 0.1);
[tt, rr] = ode45(kropla, t, ic, vopcje);

% ilustracja/wykres (postprodukacja)

h1 = plot(tt, rr(:,1), "--");
hold on
h2 = plot(tt, rr(:,1), "ro");
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