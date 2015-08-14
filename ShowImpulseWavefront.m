% ������ʾ�����Ӧ�����Ĳ�ǰ
% ��Ҫ��������PreCalc4AOSys_v10.m�ļ���������е�pupil_DM

filepath='D:\externLib\AOS\Output\PreCalc\in\';

% ����ֱ�ӻ��ַ��ؽ���Impulse��ǰ
ImpulseWavefrontDirect=cell(144,1);  % ����ȫ�������Ӧ�Ĳ�ǰ
for index=0:143
   load([filepath 'ImpulseWavefrontDirect_' num2str(index) '.txt']);
   ImpulseWavefrontDirect{index+1}=eval(strcat('ImpulseWavefrontDirect_',num2str(index)));
end


% �����ݼӹ�ͫ����ͫ����PreCalc4AOSys_v10.m�ļ���pupil_DM
% �ӹ�ͫ��ͬʱ����ʾ��ǰͼ��
ImpulseWavefrontDirect_Pupil=cell(144,1); 
for index=1:144
    ImpulseWavefrontDirect_Pupil{index}=ImpulseWavefrontDirect{index}.*pupil_DM;
end
    
% ͨ��figure�����֡��Ϣ
figure(1),set(gcf,'Name','Impulse��̬����','NumberTitle','off');
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
 movie(DirectWavefront,1,8); % ������洢�ĸ�֡�������趨֡�ʲ���


%%

filepath='D:\externLib\AOS\Output\PreCalc\in\';
% ����zernike����ؽ���Impulse��ǰ
ImpulseWavefrontZernike=cell(144,1);  % ����ȫ�������Ӧ�Ĳ�ǰ
for index=0:143
   load([filepath 'ImpulseWavefrontZernike_' num2str(index) '.txt']);
   ImpulseWavefrontZernike{index+1}=eval(strcat('ImpulseWavefrontZernike_',num2str(index)));
end

ImpulseWavefrontZernike_Pupil=cell(144,1);  % ��ӹ�ͫ
for index=1:144
    ImpulseWavefrontZernike_Pupil{index}=ImpulseWavefrontZernike{index}.*pupil_DM;
end

% ͨ��figure�����֡��Ϣ
figure(1),set(gcf,'Name','Impulse��̬����','NumberTitle','off');
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
 movie(ZernikeWavefront,1,8); % ������洢�ĸ�֡�������趨֡�ʲ���

%%



