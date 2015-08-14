clear all;close all;clc;

% 用于显示冲击响应函数的波前
% 因为没有光瞳，所以不需要预先运行PreCalc4AOSys_v10.m，只要保证相关目录有数据即可
filepath='D:\externLib\AOS\Output\PreCalc\in\';

% 读入直接积分法重建的Impulse波前
ImpulseWavefrontDirect=cell(144,1);  % 保存全部冲击响应的波前
for index=0:143
   load([filepath 'ImpulseWavefrontDirect_' num2str(index) '.txt']);
   ImpulseWavefrontDirect{index+1}=eval(strcat('ImpulseWavefrontDirect_',num2str(index)));
end
    
% 通过figure保存各帧信息
figure(1),set(gcf,'Name','Impulse动态过程','NumberTitle','off');
surf(ImpulseWavefrontDirect{1});
view([-90 0]);
axis([0 29 0 29 -5 5])
ax=gca;
ax.NextPlot = 'replaceChildren';

loops=144;
DirectWavefront(loops)=struct('cdata',[],'colormap',[]);
for index=1:loops
    surf(ImpulseWavefrontDirect{index});
    view([-90 0]);
    drawnow;
    DirectWavefront(index)=getframe;
end
 movie(DirectWavefront,1,8); % 将上面存储的各帧，按照设定帧率播放


%%

filepath='D:\externLib\AOS\Output\PreCalc\in\';
% 读入zernike拟合重建的Impulse波前
ImpulseWavefrontZernike=cell(144,1);  % 保存全部冲击响应的波前
for index=0:143
   load([filepath 'ImpulseWavefrontZernike_' num2str(index) '.txt']);
   ImpulseWavefrontZernike{index+1}=eval(strcat('ImpulseWavefrontZernike_',num2str(index)));
end

% 通过figure保存各帧信息
figure(1),set(gcf,'Name','Impulse动态过程','NumberTitle','off');
surf(ImpulseWavefrontZernike{1});
view([-90 0]);
axis([0 29 0 29 -5 5])
ax=gca;
ax.NextPlot = 'replaceChildren';

loops=144;
ZernikeWavefront(loops)=struct('cdata',[],'colormap',[]);
for index=1:loops
    surf(ImpulseWavefrontZernike{index});
    view([-90 0]);
    drawnow;
    ZernikeWavefront(index)=getframe;
end
 movie(ZernikeWavefront,1,8); % 将上面存储的各帧，按照设定帧率播放

%%



