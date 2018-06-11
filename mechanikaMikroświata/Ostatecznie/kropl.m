

% wywolanie ODE45 i uzyskanie wyniku obliczeń numerycznych
% ic - warunki poczatkowe, t - zakres całkowania numerycznego w zmiennej niezaleznej
% vopcje - parametry dla ODE45 (opcjonalne)

r = [0.0 0.0];
t  = [0 3.0];
vopcje   = odeset ('RelTol', 1e-4, 'AbsTol', 1e-4, 'InitialStep', 0.01, 'MaxStep', 0.1);
[tt, xx] = ode45(@ode_1, t, r, vopcje);

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

title(['Kropla Wody'])
xlabel('t [s]')
ylabel('r(t)')

%axis ([0 9 -0.4 0.4]);

% koniec skryptu
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%