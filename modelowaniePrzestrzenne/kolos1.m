% WEKTORY
%  %x = 4:7;
%  %y = 10:12;

% SIATKA PUNKTOW ZROBIONA Z PKT x i y;
%  %[X, Y] = meshgrid(x, y);
%  %mesh(X, Y, Z);


% SFERA
%  z = [-1:0.01:1];
%  fi = 0:pi/20:2*pi;
%  [Z, FI] = meshgrid(z, fi);
%
%  R = sqrt(1-z.^2)
%  X = R.*cos(FI)
%  Y = R.*sin(FI)
%
%  mesh(X, Y, Z)

% FIGURA2
z = [-1:0.01:1];
fi = 0:pi/20:2*pi;
[Z, FI] = meshgrid(z, fi);

R = sqrt(1/ ((cos(FI)*cos(FI)) + ((sin(FI)*sin(FI)) * 0.25)))
X = R.*cos(FI)
Y = R.*sin(FI)

mesh(X, Y, Z)