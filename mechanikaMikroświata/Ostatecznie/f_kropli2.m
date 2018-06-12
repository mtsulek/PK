function dr = ode_1(t,r)

dr = zeros(2,1);
g = 9.8;
lambda = 1;
rho = 1000;

dr(1) = (lambda*r(2))/(4*rho);
dr(2) = g - (3*lambda*(r(2)^2))/(4*rho*r(1));

end
