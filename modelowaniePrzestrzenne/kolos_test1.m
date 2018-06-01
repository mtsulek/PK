%z=[-3:0.1:-1,1:0.1:3];
%fc=[0:pi/20:2*pi];
%[Z,FI]=meshgrid(z,fc);
%R=sqrt(Z.^2-1);
%X=R.*cos(FI);
%Y=R.*sin(FI);
%mesh(X,Y,Z);

%z=[-1:0.1:1];
%fi=[0:pi/20:2*pi]
%[Z,FI]=meshgrid(z,fi);
%R=sqrt(1-z.^2);
%X=R.*cos(FI);
%Y=R.*sin(FI);
%mesh(X,Y,Z);
%axis equal;

z=[-10:0.1:10];
fi=[0:pi/20:2*pi];
[Z,FI]=meshgrid(z,fi);
R=1;
X=R.*cos(FI);
Y=R.*sin(FI)*0.25;
mesh(X,Y,Z);
axis equal;