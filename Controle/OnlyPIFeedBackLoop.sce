clc;
delete(gcf());
clear;
xdel(winsid());

// ============================================================================

kilo = 1000;
mega = 1000*kilo;
giga = 1000*mega;
mili = 0.001;
micro = 0.001*mili;
nano = 0.001*micro;

// ============================================================================

step_simul = 1*micro;
t_simul = 1;
t = [0:step_simul:t_simul];
ref = ones(1,length(t));

fsp = 15;
Tsp = 1/fsp;
u1 = ones(1,round(t_simul/Tsp)); 
N1=0:length(u1)-1;

// ============================================================================

Kp = 1.15;
Taui = 50*mili;

// ============================================================================

s = poly(0,'s');
Gs = Kp+1/(Taui*s);
Gs = syslin('c',Gs);
Hs = Gs/(1+Gs);
Pf = (1+Kp*Taui*s*0.1)/(1+Kp*Taui*s)
Pf = syslin('c',Pf);
Ytc = csim('step',t,Pf*Hs);
hfig = figure();
hfig.background=-2;
plot2d(t',[ref' Ytc']);
xtitle("Continuo");

// ============================================================================

z = poly(0,'z');
s = (2/Tsp)*(z-1)/(z+1);
Gz = Kp+1/(Taui*s);
Gz = syslin('d',Gz);
Hz = Gz/(1+Gz)
Pf = (1+Kp*Taui*s*0.1)/(1+Kp*Taui*s)
Pf = syslin('d',Pf);
Ydb = dsimul(tf2ss(Pf*Hz),u1);
hfig = figure();
hfig.background=-2;
plot2d2(N1',[u1' Ydb']);
xtitle("Bilinear");

