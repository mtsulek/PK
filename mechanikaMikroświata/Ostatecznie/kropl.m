

% ODE45 USE
r = [0.001 0.0];
t = [0 5.0];
vopcje   = odeset ('RelTol', 1e-6, 'AbsTol', 1e-6, 'InitialStep', 0.01, 'MaxStep', 1.0);
[tt, xx] = ode45(@ode_1, t, r, vopcje);

%
r1 = [0.001 0.0];
t1 = [1.5 5.0];
vopcje2 = odeset('RelTol', 1e-6, 'AbsTol', 1e-6, 'InitialStep', 0.01, 'MaxStep', 1.0);
[t2, x2] = ode45(@ode_1, t1, r1, vopcje2);


% GRAPH OPTIONS
% remember to make xx(:,2) cuz of larger matrix size of dr: dr(1), dr(2)
dashed = plot(tt, xx(:,2), "--"); 
hold on
dots = plot(tt, xx(:,2), "ro");
hold on
g7_line = plot(x2+1, 9.8/7*x2+4.4,"-"); %g/7+const
hold on
g_line = plot(x2, 9.8*x2,"--"); %g
hold off

font = gca;
set(font,'FontSize',20.0);
set(dots,'MarkerSize',5.0);
set(g7_line,'MarkerSize',15.0);
set(g7_line,'LineWidth',2.5);
set(dashed,'LineWidth',4.0);
set(dots,'LineWidth',4.0);
set(dots,'LineWidth',4.0);

title(['Kropla Wody'])
xlabel('t [s]')
ylabel('r(t) [m/s]')
axis ([0 3 0 10]);

% koniec skryptu
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
