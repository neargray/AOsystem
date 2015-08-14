% 用于显示冲击响应函数的波前
% 需要首先运行PreCalc4AOSys_v10.m文件，获得其中的pupil_DM

filepath='D:\externLib\AOS\Output\PreCalc\in\';

% 读入直接积分法重建的Impulse波前
ImpulseWavefrontDirect=cell(144,1);  % 保存全部冲击响应的波前
for index=0:143
   load([filepath 'ImpulseWavefrontDirect_' num2str(index) '.txt']);
   ImpulseWavefrontDirect{index+1}=eval(strcat('ImpulseWavefrontDirect_',num2str(index)));
end


% 给数据加光瞳，光瞳来自PreCalc4AOSys_v10.m文件的pupil_DM
% 加光瞳的同时，显示波前图像
ImpulseWavefrontDirect_Pupil=cell(144,1); 
for index=1:144
    ImpulseWavefrontDirect_Pupil{index}=ImpulseWavefrontDirect{index}.*pupil_DM;
end
    
% 通过figure保存各帧信息
figure(1),set(gcf,'Name','Impulse动态过程','NumberTitle','off');
surf(ImpulseWavefrontDirect_Pupil{1});
axis([0 29 0 29 -2 1])
ax=gca;
ax.NextPlot = 'replaceChildren';

loops=144;
DirectWavefront(loops)=struct('cdata',[],'colormap',[]);
for index=1:loops
    surf(ImpulseWavefrontDirect_Pupil{index});
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

ImpulseWavefrontZernike_Pupil=cell(144,1);  % 添加光瞳
for index=1:144
    ImpulseWavefrontZernike_Pupil{index}=ImpulseWavefrontZernike{index}.*pupil_DM;
end

% 通过figure保存各帧信息
figure(1),set(gcf,'Name','Impulse动态过程','NumberTitle','off');
surf(ImpulseWavefrontZernike_Pupil{1});
axis([0 29 0 29 -2 1])
ax=gca;
ax.NextPlot = 'replaceChildren';

loops=144;
ZernikeWavefront(loops)=struct('cdata',[],'colormap',[]);
for index=1:loops
    surf(ImpulseWavefrontZernike_Pupil{index});
    drawnow;
    ZernikeWavefront(index)=getframe;
end
 movie(ZernikeWavefront,1,8); % 将上面存储的各帧，按照设定帧率播放

%%



