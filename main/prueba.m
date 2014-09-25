zn = 0.1;
zf = 20;
mt = 64;
x = [zn:0.1:zf];
a = (-2*zf*zn)/(zf - zn)
b = (zf + zn)/(zf - zn)
y1 = b + a./x;

y2 = (y1.+1)/2;
y3 = (1.-y2)*mt;

%plot (x,y1);
%plot (x,y2);
plot (x,y3);
pause;
