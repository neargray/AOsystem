clear all;close all;clc;

% ������ʾ�����Ӧ�����Ĳ�ǰ
% ��Ϊû�й�ͫ�����Բ���ҪԤ������PreCalc4AOSys_v10.m��ֻҪ��֤���Ŀ¼�����ݼ���
filepath='D:\externLib\AOS\Output\PreCalc\in\';

% ����ֱ�ӻ��ַ��ؽ���Impulse��ǰ
ImpulseWavefrontDirect=cell(144,1);  % ����ȫ�������Ӧ�Ĳ�ǰ
for index=0:143
   load([filepath 'ImpulseWavefrontDirect_' num2str(index) '.txt']);
   ImpulseWavefrontDirect{index+1}=eval(strcat('ImpulseWavefrontDirect_',num2str(index)));
end
    
% ͨ��figure�����֡��Ϣ
figure(1),set(gcf,'Name','Impulse��̬����','NumberTitle','off');
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
 movie(DirectWavefront,1,8); % ������洢�ĸ�֡�������趨֡�ʲ���


%%

filepath='D:\externLib\AOS\Output\PreCalc\in\';
% ����zernike����ؽ���Impulse��ǰ
ImpulseWavefrontZernike=cell(144,1);  % ����ȫ�������Ӧ�Ĳ�ǰ
for index=0:143
   load([filepath 'ImpulseWavefrontZernike_' num2str(index) '.txt']);
   ImpulseWavefrontZernike{index+1}=eval(strcat('ImpulseWavefrontZernike_',num2str(index)));
end

% ͨ��figure�����֡��Ϣ
figure(1),set(gcf,'Name','Impulse��̬����','NumberTitle','off');
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
 movie(ZernikeWavefront,1,8); % ������洢�ĸ�֡�������趨֡�ʲ���

%%



