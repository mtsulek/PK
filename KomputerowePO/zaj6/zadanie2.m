L=imread('portret.jpg');
figure;
imshow(L);
[w,k]=size(L);
for i=1:w
    for j=1:k
        if L(i,j)>150
            L(i,j)= L(i,j)+35;
        elseif L(i,j)<120
            L(i,j)= L(i,j)-25;
        elseif L(i,j)==130
            L(i,j)=L(i,j)+125;
        end
    end
end
px=L(120,130)
figure
imshow(L);