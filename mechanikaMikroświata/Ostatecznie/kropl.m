
pkg load odepkg;
% ODE45 USE
r = [0.001 0.0];
t = [0 5.0];
vopcje   = odeset ('RelTol', 1e-6, 'AbsTol', 1e-6, 'InitialStep', 0.01, 'MaxStep', 1.0);
[tt, xx] = ode45(@odekropli, t, r, vopcje);

% ODE45 - 2
r1 = [0.001 0.0];
t1 = [1.5 5.0];
vopcje2 = odeset('RelTol', 1e-6, 'AbsTol', 1e-6, 'InitialStep', 0.01, 'MaxStep', 1.0);
[t2, x2] = ode45(@odekropli, t1, r1, vopcje2);


% GRAPH OPTIONS
ode = plot(tt, xx(:,2), ["ro"]);
hold on
ode2 = plot(tt, xx(:,2), [ "b--"]);
g7 = plot(x2+1, 9.8/7*x2+4.4, [ "g-"]);
g = plot(x2, 9.8*x2,[ "b-"]); 
hold off

font = gca;
set(font,'FontSize',15.0);
set(ode,'MarkerSize',5.0);
set(g7,'MarkerSize',15.0);
set(g7,'LineWidth',2.5);
set(ode2,'LineWidth',2.0);
set(ode,'LineWidth',4.0);
set(ode,'LineWidth',4.0);

hl = legend ({'ode45', 'ode45', 'gt/7'});

title(['Kropla Wody'])
xlabel('t [s]')
ylabel('v(t) [m/s]')
axis ([0 3 0 10]);
% koniec skryptu
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
